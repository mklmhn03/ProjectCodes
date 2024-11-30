from enum import Enum, auto

import pygame
import pygame.image
from pygame.sprite import GroupSingle
from pygame.surface import Surface

from entities.npc import NPC

from .entity import Entity
from .player import Player


class Turbodoc(Entity):
    def __init__(self) -> None:
        # image = pygame.image.load("character.png")
        image = pygame.Surface((32, 64))
        image.fill((255, 0, 0))  # Red
        stats = {
            "grit": {"current_grit": 1, "max_grit": 1},
            "strength": 100,
            "speed": 10,
            "agility": 10,
        }
        super().__init__(stats, (0, 0), image)
        self.base_image = self.image
        self.image.set_alpha(0)
        self.taken_entity = GroupSingle()
        self.phase = self.splash_phases.IDLE

    class splash_phases(Enum):
        IDLE = auto()
        FLYING_TO = auto()
        KILLING = auto()
        FLYING_AWAY = auto()
        FLYING_BACK = auto()
        LEAVE = auto()

    def attacked(self, hurt):
        self.grit += hurt

    def draw(self, screen: pygame.Surface):
        screen.blit(
            self.image,
            self.rect.topleft,
        )

    def update(self, player: Player, npcs: list[NPC], sector_loc: tuple[int, int]):
        pixel_speed = self.get_pixel_speed()
        if bool(self.taken_entity):
            if isinstance(self.taken_entity.sprite, Player):
                pass  # Kill Zombies and take player
            else:
                taken_entity: Entity = self.taken_entity.sprite
                if self.phase == self.splash_phases.IDLE:
                    self.update_pos((taken_entity.pos.x, 0))
                    self.update_rect(bottom=0)
                    self.image.set_alpha(255)
                    self.phase = self.splash_phases.FLYING_TO
                elif self.phase == self.splash_phases.FLYING_TO:
                    self.update_pos((self.pos.x, self.pos.y + pixel_speed))
                    if self.hitbox.colliderect(taken_entity.hitbox):
                        self.update_hitbox(bottom=taken_entity.hitbox.top)
                        image = Surface(
                            (
                                self.rect.width,
                                self.image.get_height() + taken_entity.hitbox.height,
                            )
                        )
                        image.blit(self.image, (0, 0))
                        image.blit(
                            self.taken_entity.sprite.image,
                            (
                                0,
                                taken_entity.hitbox.height,
                            ),
                        )
                        self.image = image
                        self.taken_entity.sprite.image.set_alpha(0)
                        # If NPC ran away
                        self.taken_entity.sprite.update_pos(
                            tuple(
                                [
                                    (
                                        self.taken_entity.sprite.home_location[
                                            "sector"
                                        ][i]
                                        - sector_loc[i]
                                        + 1
                                    )
                                    * self.taken_entity.sprite.home_location[
                                        "coordinates"
                                    ][i]
                                    for i in range(2)
                                ]
                            )
                        )
                        self.phase = self.splash_phases.FLYING_AWAY
                elif self.phase == self.splash_phases.FLYING_AWAY:
                    self.update_pos((self.pos.x, self.pos.y - pixel_speed))
                    if self.image.get_rect(topleft=self.rect.topleft).bottom < 0:
                        self.image.set_alpha(0)
                        self.update_pos((taken_entity.pos.x, self.pos.y))
                        self.image.set_alpha(255)
                        self.phase = self.splash_phases.FLYING_BACK
                elif self.phase == self.splash_phases.FLYING_BACK:
                    self.update_pos((self.pos.x, self.pos.y + pixel_speed))
                    if self.hitbox.colliderect(taken_entity.hitbox):
                        self.update_hitbox(bottom=taken_entity.hitbox.top)
                        self.image = self.base_image
                        self.taken_entity.sprite.dead = False
                        self.taken_entity.sprite.image.set_alpha(255)
                        self.taken_entity.empty()
                        self.phase = self.splash_phases.LEAVE
        if self.phase == self.splash_phases.LEAVE:
            self.update_pos((self.pos.x, self.pos.y - pixel_speed))
            if self.rect.bottom < 0:
                self.image.set_alpha(0)
                self.phase = self.splash_phases.IDLE
        else:
            if player.dead:
                self.taken_entity.add(player)
                return
            for npc in npcs:
                if npc.dead:
                    self.taken_entity.add(npc)
                    return
