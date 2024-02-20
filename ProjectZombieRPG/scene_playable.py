from random import randrange
from typing import Union

import pygame
import pygame.display
import pygame.event
import pygame.image
import pygame.time
import pygame.transform
from pygame.locals import MOUSEBUTTONUP, QUIT
from pygame.sprite import Group, spritecollideany

from dialogue import Dialogue
from entities.entity import Entity
from entities.hamster import Hamster
from entities.npc import NPC
from entities.player import Player
from entities.turbodoc import Turbodoc
from entities.zombie import Zombie
from game_save import retrieve_save_data
from reference import (
    DIALOGUE_EVENT,
    FPS,
    PLAYER_HARMED_EVENT,
    SECTOR_IMAGE_SIZE,
    SECTOR_RECT,
    character_types,
    return_codes,
    site_types,
)
from sites_static_info import get_site_data


class Scene_Playable:
    def __init__(self, screen: pygame.Surface, save_name: str) -> None:
        self.save_name = save_name
        self.screen = screen
        self.clock = pygame.time.Clock()

        data = retrieve_save_data(save_name)

        self.player = Player(
            character_types[data["player"]["character"]],
            data["player"]["stats"],
            data["player"]["inventory"],
            data["player"]["money"],
            data["player"]["exp"],
            tuple(data["player"]["coordinates"]),
        )
        self.hamster = Hamster(
            data["hamster"]["stats"], tuple(data["hamster"]["coordinates"])
        )
        self.turbo_doc = Turbodoc()
        self.all_npc = Group()
        self.all_zombies = Group()
        self.existing_sprites = Group(self.player, self.hamster, self.turbo_doc)
        self.dialogue: Union[Dialogue, None] = None

        self.site: site_types = None
        self.bg_color: pygame.Color = None
        self.sectors_rects: list[pygame.Rect] = None
        self.sectors_images: dict[tuple[int, int], pygame.Surface] = None
        self.sectors_loaded = None
        self.sector_loc: tuple[int, int] = None  # left -> right, top -> bottom
        self.set_site(
            site_types[data["world"]["location"]["site"]],
            tuple(data["world"]["location"]["sector"]),
        )

    def get_data(self):
        data = retrieve_save_data(self.save_name)
        data["player"] = self.player.get_data()
        data["hamster"] = self.hamster.get_data()
        data["world"]["location"] = {
            "site": self.site.name,
            "sector": self.sector_loc,
        }
        return data

    def load_sector(self, new_sector: tuple[int, int]):
        """
        Set `self.sector_loc`, `self.sectors_loaded`, and `self.sector_image`.

        Load `self.sector_image` and create zombies for `self.all_zombies`
        """

        self.sector_loc = new_sector

        if new_sector not in self.sectors_loaded:
            self.sectors_loaded.append(new_sector)
            sector_data = get_site_data(self.site)["sectors"][new_sector]
            for npc_data in sector_data["npcs"]:
                npc = NPC(
                    npc_data["name"],
                    npc_data["type"],
                    npc_data["image"],
                    npc_data["dialogue_tag"],
                    self.sector_loc,
                    npc_data["coordinates"],
                )
                self.all_npc.add(npc)
            for _ in range(sector_data["zombie_num"]):
                zombie = Zombie("runner", (0, 0))  # TODO: Zombie type
                while True:
                    zombie.update_pos(
                        (
                            randrange(
                                SECTOR_RECT.left,
                                SECTOR_RECT.right - zombie.rect.width,
                            ),
                            randrange(
                                SECTOR_RECT.top,
                                SECTOR_RECT.bottom - zombie.rect.height,
                            ),
                        )
                    )
                    if spritecollideany(zombie, self.existing_sprites) is None:
                        break
                self.all_zombies.add(zombie)
            self.existing_sprites.add(
                self.all_npc.sprites(), self.all_zombies.sprites()
            )

    def set_site(self, site: site_types, new_sector: tuple[int, int]):
        """Set `self.site`, `self.site_image`, and `self.bg_color`"""

        site_data = get_site_data(site)
        self.site = site
        site_image = pygame.image.load(site_data["image_path"]).convert()
        self.sectors_rects: list[pygame.Rect] = []
        self.sectors_images: dict[tuple[int, int], pygame.Surface] = {}
        self.sectors_loaded = []
        for sector_loc in site_data["sectors"].keys():
            sector_image = site_image.subsurface(
                [sector_loc[i] * SECTOR_IMAGE_SIZE[i] for i in range(2)],
                SECTOR_IMAGE_SIZE,
            )
            self.sectors_rects.append(
                pygame.Rect(
                    [
                        (sector_loc[i] - new_sector[i]) * SECTOR_RECT.size[i]
                        + SECTOR_RECT.topleft[i]
                        for i in range(2)
                    ],
                    SECTOR_RECT.size,
                )
            )
            sector_image = pygame.transform.scale(sector_image, SECTOR_RECT.size)
            self.sectors_images[sector_loc] = sector_image
        # TODO: Figure it how to determine what color to set `self.bg_color` to...
        self.bg_color = pygame.Color(0, 100, 0)  # Dark Green
        self.screen.fill(self.bg_color)
        self.load_sector(new_sector)

    def is_changing_sectors(self):
        """TO BE CHANGED: Look at github project
        If touching sector edge and next sector exists, change sectors
        """
        if self.player.dead:
            return None

        all_sectors = get_site_data(self.site)["sectors"].keys()

        if (
            self.player.rect.centery < SECTOR_RECT.top
            and (self.sector_loc[0], self.sector_loc[1] - 1) in all_sectors
        ):
            return "top"
        elif (
            self.player.rect.centerx < SECTOR_RECT.left
            and (self.sector_loc[0] - 1, self.sector_loc[1]) in all_sectors
        ):
            return "left"
        elif (
            self.player.rect.centery > SECTOR_RECT.bottom
            and (self.sector_loc[0], self.sector_loc[1] + 1) in all_sectors
        ):
            return "bottom"
        elif (
            self.player.rect.centerx > SECTOR_RECT.right
            and (self.sector_loc[0] + 1, self.sector_loc[1]) in all_sectors
        ):
            return "right"
        else:
            return None

    def change_sector(self, moving_to: str):
        # TODO: Move `self.change_sector` into here
        moving_to_dict: dict[str, tuple[int, int]] = {
            "top": (0, -1),
            "left": (-1, 0),
            "bottom": (0, 1),
            "right": (1, 0),
        }
        n = moving_to_dict[moving_to]

        entity: Entity
        for rect in self.sectors_rects:
            rect.topleft = [
                rect.topleft[i] - n[i] * SECTOR_RECT.size[i] for i in range(2)
            ]
        for entity in self.existing_sprites.sprites():
            entity.update_pos(
                tuple([entity.pos[i] - n[i] * SECTOR_RECT.size[i] for i in range(2)])
            )
        self.load_sector(tuple([self.sector_loc[i] + n[i] for i in range(2)]))

    def get_collidable_entities(self, self_entity: Entity) -> tuple[Entity]:
        """Get all entities that `self_entity` can collide with."""
        entity_list: list[Entity] = self.existing_sprites.sprites()
        entity_list.remove(self_entity)
        entity_list.remove(self.turbo_doc)
        for entity in entity_list:
            if entity.dead:
                entity_list.remove(entity)
        return entity_list

    def draw(self):
        """Draw all images onto the screen"""
        self.screen.blit(self.sectors_images[self.sector_loc], SECTOR_RECT)
        for sprite in sorted(
            self.existing_sprites.sprites(), key=lambda sprite: sprite.rect.bottom
        ):
            sprite.draw(self.screen)

        if self.dialogue is not None:
            self.dialogue.draw(self.screen)

    def run(self) -> str:
        pygame.display.update()

        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    return return_codes.QUIT
                if event.type == DIALOGUE_EVENT:
                    self.dialogue = Dialogue(self.site, event.tag)
                if event.type == MOUSEBUTTONUP:
                    if self.dialogue is not None:
                        self.dialogue = None

                # TODO: Change to ENTITY_HARMED_EVENT
                if event.type == PLAYER_HARMED_EVENT:
                    # TODO: create `@property` in `Entity` for `current_grit` that will be the equivilate of `Entity.attacked()`
                    self.player.current_grit -= event.damage

            # Updates
            if self.dialogue is None:
                self.player.update(
                    self.sectors_rects,
                    self.get_collidable_entities(self.player),
                )
            self.hamster.update(self.player, self.get_collidable_entities(self.hamster))
            for zombie in self.all_zombies:
                self.all_zombies.update(
                    self.player, self.get_collidable_entities(zombie)
                )
            self.all_npc.update(self.player.pos)
            self.turbo_doc.update(
                self.player,
                self.all_npc.sprites(),
                self.sector_loc,
            )

            sector_change = self.is_changing_sectors()
            if sector_change is not None:
                self.change_sector(sector_change)

            self.draw()
            pygame.display.update(SECTOR_RECT)

            self.clock.tick(FPS)
