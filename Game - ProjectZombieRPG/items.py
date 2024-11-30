from os.path import join as path_join
from typing import Union

import pygame
import pygame.image
from pygame import Rect, Surface
from pygame.sprite import Group, Sprite
from pygame.transform import scale

from entities.entity import Entity
from reference import entity_direction


class Item(Sprite):
    def __init__(self, name: str, image: Surface) -> None:
        super().__init__()
        # Else: 0 = some integer greater than 0 | TODO: Define what 'Else' is.
        self.name = name
        self.base_image = image
        self.image = image


class Weapon(Item):
    def __init__(
        self,
        name: str,
        image: Surface,
        durability: int,
        strength: int,
        speed: int,
        agility: int,
    ) -> None:
        super().__init__(name, image)
        self.name = name
        self.image = image
        self.durability = durability
        self.strength = strength
        self.speed = speed
        self.agility = agility
        self.hit_entities = Group()

    def get_hitting_entities(
        self, item_rect: pygame.Rect, entities: list[Entity]
    ) -> list[Entity]:
        hit_entites = []
        for entity in entities:
            if item_rect.colliderect(entity.rect) and not self.hit_entities.has(entity):
                hit_entites.append(entity)
                self.hit_entities.add(entity)
        return hit_entites

    def get_weapon_rect(self, player_direction: entity_direction, player_rect: Rect):
        weapon_rect = self.image.get_rect()
        weapon_rect.center = player_rect.center
        if player_direction == entity_direction.TOP:
            weapon_rect.bottom = player_rect.top
        elif player_direction == entity_direction.LEFT:
            weapon_rect.right = player_rect.left
        elif player_direction == entity_direction.BOTTOM:
            weapon_rect.top = player_rect.bottom
        elif player_direction == entity_direction.RIGHT:
            weapon_rect.left = player_rect.right
        return weapon_rect


class Armor(Item):
    def __init__(self, name: str, image: Surface, durability: int, grit: int) -> None:
        super().__init__(name, image)
        self.name = name
        self.durability = durability
        self.grit = grit


class Heal(Item):
    def __init__(
        self, name: str, image: Surface, healpts: int, count: int
    ) -> None:
        super().__init__(name, image)
        self.healpts = healpts
        self.count = count


class Hamster_Buff(Item):
    def __init__(
        self, name: str, image: Surface, durability: int, grit: int, count: int
    ) -> None:
        super().__init__(name, image)
        self.name = name
        self.durability = durability
        self.grit = grit
        self.count = count


def get_item(item_name: Union[str, None]) -> Union[Weapon, Armor, Heal, Hamster_Buff]:
    if item_name == "bat":
        image = pygame.image.load(
            path_join("assets", "items", item_name + ".png")
        ).convert_alpha()
        image = scale(image, (8, 32))
        return Weapon(item_name, image, 150, 1, 2, 2)
    elif item_name is None:
        return None
    else:
        raise ValueError(item_name + " is not an item")
