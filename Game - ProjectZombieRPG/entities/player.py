from typing import Union

import pygame
import pygame.event
import pygame.image
import pygame.key
import pygame.mouse
import pygame.transform
from items import Armor, Hamster_Buff, Heal, Weapon, get_item
from reference import DIALOGUE_EVENT, FPS, character_types, entity_direction

from . import hamster
from .entity import Entity
from .npc import NPC


class Player(Entity):
    def __init__(
        self,
        character: character_types,
        stats: dict,
        inventory: dict[str, Union[str, None, list[Union[str, None]]]],
        money: int,
        exp: int,
        coordinates: tuple[int, int],
    ) -> None:
        if character == character_types.BERSERKER:
            image = pygame.image.load("assets/character.png").convert_alpha()
        elif character == character_types.ASSASSIN:
            image = pygame.image.load("assets/character.png").convert_alpha()
        elif character == character_types.BATMASTER:
            image = pygame.image.load("assets/character.png").convert_alpha()
        else:
            image = pygame.image.load("assets/character.png").convert_alpha()
        self.image_direction = dict(
            zip(
                [entity_direction(i) for i in range(4)],
                [
                    pygame.transform.scale(
                        image.subsurface((i * 18, 0, 16, 32)), (32, 64)
                    )
                    for i in range(4)
                ],
            )
        )
        image = self.image_direction[entity_direction.BOTTOM]
        super().__init__(stats, coordinates, image)

        self.character = character
        # TODO: Make it so item stats (like durability and count) can be saved and loaded
        self.inventory: dict[
            str, Union[Weapon, None, list[Union[Armor, Heal, Hamster_Buff, None]]]
        ] = {}
        self.inventory["weapon"] = get_item(inventory["weapon"])
        for key in ("armor", "items"):
            self.inventory[key] = [get_item(i) for i in inventory[key]]
        # ocassionally dropped by zombie and reward for quests and side quests
        self.money = money
        # automatically awarded after zombie killed; 50% if hamster kills
        self.exp = exp
        self.attack_cooldown = 0

    def move_item(self, slot_one, slot_two):
        # TODO: Move equip and unequip here
        pass

    def equip_item(self, item: Union[Weapon, Armor]):
        if isinstance(item, Weapon):
            self.strength += item.strength
            self.speed += item.speed  # Slows down player
            self.agility += item.agility  # Weapon cooldown
        elif isinstance(item, Armor):
            self.maxgrit += item.grit
            self.current_grit += item.grit

    def upequip_item(self, item: Union[Weapon, Armor]):
        if isinstance(item, Weapon):
            self.strength -= item.strength
            self.speed -= item.speed
            self.agility -= item.agility
        elif isinstance(item, Armor):
            self.maxgrit -= item.grit

    def use_item(self, item: Union[Heal, Hamster_Buff]):
        if isinstance(item, Heal):
            item.count -= 1
            self.current_grit += item.healing_amount
            if self.current_grit > self.max_grit:
                self.current_grit = self.max_grit
        elif isinstance(item, Hamster_Buff):
            item.count -= 1
            # Buff hamster

    def change_direction(self, direction):
        if direction != self.direction:
            self.direction = direction
            self.image = self.image_direction[self.direction]

    def in_site_rects(self, site_rects: list[pygame.Rect]):
        for corner in (self.rect.topleft, self.rect.bottomright):
            in_rect = False
            for rect in site_rects:
                if rect.collidepoint(corner):
                    in_rect = True
                    break
            if not in_rect:
                return False
        return True

    def update(
        self,
        sectors_rects: list[pygame.Rect],
        collidable_entities: tuple[Entity],
    ):
        if not self.dead:
            pressed_keys = pygame.key.get_pressed()
            pressed_mouse = pygame.mouse.get_pressed()

            dir = pygame.Vector2()
            if pressed_keys[pygame.K_w] or pressed_keys[pygame.K_UP]:
                dir.y -= 1

                if self.attack_cooldown == 0:
                    self.change_direction(entity_direction.TOP)

            if pressed_keys[pygame.K_s] or pressed_keys[pygame.K_DOWN]:
                dir.y += 1

                if self.attack_cooldown == 0:
                    self.change_direction(entity_direction.BOTTOM)

            if pressed_keys[pygame.K_a] or pressed_keys[pygame.K_LEFT]:
                dir.x -= 1

                if self.attack_cooldown == 0:
                    self.change_direction(entity_direction.LEFT)

            if pressed_keys[pygame.K_d] or pressed_keys[pygame.K_RIGHT]:
                dir.x += 1

                if self.attack_cooldown == 0:
                    self.change_direction(entity_direction.RIGHT)

            if dir != (0, 0):
                dir.scale_to_length(self.get_pixel_speed())
                self.update_pos(self.pos + dir)
                is_collision = self.collide_any(
                    tuple([entity.hitbox for entity in collidable_entities])
                )
                if not self.in_site_rects(sectors_rects):
                    self.update_pos(self.pos - (0, dir.y))
                    if not self.in_site_rects(sectors_rects):
                        self.update_pos(self.pos + (0, dir.y))
                        self.update_pos(self.pos - (dir.x, 0))
                        if not self.in_site_rects(sectors_rects):
                            self.update_pos(self.pos - (0, dir.y))

                elif is_collision is not None:
                    sides_dist = tuple(
                        [
                            abs(self.hitbox.top - is_collision.bottom),
                            abs(self.hitbox.bottom - is_collision.top),
                            abs(self.hitbox.left - is_collision.right),
                            abs(self.hitbox.right - is_collision.left),
                        ]
                    )
                    index = sides_dist.index(min(sides_dist))
                    if index == 0:
                        self.update_hitbox(top=is_collision.bottom)
                    elif index == 1:
                        self.update_hitbox(bottom=is_collision.top)
                    elif index == 2:
                        self.update_hitbox(left=is_collision.right)
                    else:
                        self.update_hitbox(right=is_collision.left)

            if pressed_mouse[0]:
                if self.inventory["weapon"] is not None and self.attack_cooldown == 0:
                    # TODO: Use agility instead.
                    self.attack_cooldown = int(0.5 * FPS)
                    rotated_item = lambda degree: pygame.transform.rotate(
                        self.inventory["weapon"].image, degree
                    )
                    if self.direction == entity_direction.TOP:
                        self.inventory["weapon"].image = rotated_item(0)
                    elif self.direction == entity_direction.LEFT:
                        self.inventory["weapon"].image = rotated_item(90)
                    elif self.direction == entity_direction.BOTTOM:
                        self.inventory["weapon"].image = rotated_item(180)
                    elif self.direction == entity_direction.RIGHT:
                        self.inventory["weapon"].image = rotated_item(270)

            if self.attack_cooldown != 0:
                item_rect = self.inventory["weapon"].get_weapon_rect(
                    self.direction, self.rect
                )
                for entity in self.inventory["weapon"].get_hitting_entities(
                    item_rect, collidable_entities
                ):
                    if not isinstance(entity, hamster.Hamster):
                        entity.current_grit -= self.strength

                self.attack_cooldown -= 1
                if self.attack_cooldown == 0:
                    self.inventory["weapon"].image = self.inventory["weapon"].base_image
                    self.inventory["weapon"].hit_entities.empty()

            if pressed_keys[pygame.K_f]:
                """Interact with world objects and entities"""
                player_pos = pygame.Vector2(self.rect.center)
                near_npcs = [
                    entity for entity in collidable_entities if isinstance(entity, NPC)
                ]
                if near_npcs:
                    closest_npc = min(
                        near_npcs,
                        key=lambda npc: player_pos.distance_to(npc.rect.center),
                    )
                    if player_pos.distance_to(closest_npc.rect.center) <= 50:
                        pygame.event.post(
                            pygame.event.Event(
                                DIALOGUE_EVENT, tag=closest_npc.dialogue_tag
                            )
                        )

            if pressed_keys[pygame.K_e]:  # activate special skill
                if self.character == 1:
                    pass
                elif self.character == 2:
                    pass
                elif self.character == 3:
                    pass
                else:
                    pass

        if self.current_grit <= 0:
            # TODO: Get rid of `self.dead` and maybe `self.death()`
            # self.image = pygame.image.load("assets/dead.png").convert()
            self.death()

    def draw(self, screen: pygame.Surface):
        super().draw(screen)
        # TODO: Change to look more accurate.
        if self.attack_cooldown != 0:
            weapon_rect = self.inventory["weapon"].get_weapon_rect(
                self.direction, self.rect
            )
            screen.blit(self.inventory["weapon"].image, weapon_rect)

    def get_data(self):
        inventory: dict[str, Union[str, None, list[Union[str, None]]]] = {}
        inventory["weapon"] = self.inventory["weapon"].name
        for key in ("armor", "items"):
            inventory[key] = [
                item.name if item is not None else None for item in self.inventory[key]
            ]
        return {
            "character": self.character.name,
            "stats": {
                "grit": {"current_grit": self.current_grit, "max_grit": self.max_grit},
                "strength": 1,
                "speed": 4,
                "agility": 1,
            },
            "inventory": inventory,
            "money": self.money,
            "exp": self.exp,
            "coordinates": self.pos[:],
        }
