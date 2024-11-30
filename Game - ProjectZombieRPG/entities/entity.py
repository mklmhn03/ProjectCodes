from __future__ import annotations

from typing import Union

import pygame
import pygame.key
import pygame.mouse
from pygame.sprite import Sprite
from reference import FPS, entity_direction


class Entity(Sprite):
    def __init__(self, stats: dict, coordinates: tuple, image: pygame.Surface) -> None:
        super().__init__()
        self.dead = False
        self.image = image

        self.pos = pygame.Vector2(coordinates)
        self.rect = self.image.get_rect(center=self.pos)
        self.hitbox = self.rect.inflate(0, -self.image.get_height() * (2 / 3))
        self.hitbox.bottomleft = self.rect.bottomleft
        self.direction = entity_direction.BOTTOM

        self.max_grit = stats["grit"]["max_grit"]
        self.current_grit = stats["grit"]["current_grit"]
        self.strength = stats["strength"]
        self.speed = stats["speed"]
        self.agility = stats["agility"]

    def update_pos(
        self,
        vector: Union[pygame.Vector2, tuple[float, float], list[float]],
    ):
        """Update sprite's pos"""
        self.pos.update(vector)
        self.rect.center = [round(c) for c in vector]
        self.hitbox.bottomleft = self.rect.bottomleft

    def update_rect(self, **kwargs):
        """Update sprite's rect"""
        new_rect = self.rect.copy()
        for key, value in kwargs.items():
            setattr(new_rect, key, value)
        pos = self.pos
        if self.rect.y - new_rect.y != 0:
            pos.y = new_rect.centery
        if self.rect.x - new_rect.x != 0:
            pos.x = new_rect.centerx
        self.update_pos(pos)

    def update_hitbox(self, **kwargs):
        """Update sprite's hitbox"""
        new_hitbox = self.hitbox.copy()
        for key, value in kwargs.items():
            setattr(new_hitbox, key, value)
        self.update_rect(bottomleft=new_hitbox.bottomleft)

    def collide_any(self, entities: list[Entity]) -> Union[Entity, None]:
        """If colliding return the collided rect else returns None."""
        for entity in entities:
            if self.hitbox.colliderect(entity.hitbox):
                return entity
        return None

    def draw(self, screen: pygame.Surface):
        screen.blit(self.image, self.rect)

    def lvl_up(self):
        self.max_grit *= 1.05
        self.current_grit = self.max_grit
        self.strength *= 1.05
        self.speed *= 1.05
        self.agility *= 1.05

    def attack(self):
        if pygame.key.get_pressed()[pygame.K_SPACE] or pygame.mouse.get_pressed()[0]:
            pass

    def get_pixel_speed(self):
        return self.speed * 30 / FPS

    def death(self):
        self.dead = True
