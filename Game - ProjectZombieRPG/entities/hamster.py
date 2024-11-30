import pygame
import pygame.image
from reference import *

from . import player
from .entity import Entity


class Hamster(Entity):
    def __init__(self, stats: dict[str, int], coordinates: tuple[int, int]) -> None:
        image = pygame.Surface((32, 24))
        image.fill((218, 158, 56))
        # image = pygame.image.load("assets/hamster.png").convert()
        super().__init__(stats, coordinates, image)

    def update(self, player: player.Player, collidable_entities: tuple[Entity]) -> None:
        if self.dead:  # TODO: Make it same as elif
            pixel_speed = self.get_pixel_speed()
            # If player is above
            if player.rect.bottom - self.rect.bottom < 0:
                self.rect.move_ip(0, -pixel_speed)
            # If player is below
            if player.rect.top - self.rect.top > 0:
                self.rect.move_ip(0, pixel_speed)
            # If player is to the left
            if player.rect.right - self.rect.left < 0:
                self.rect.move_ip(-pixel_speed, 0)
            # If player is to the right
            if player.rect.left - self.rect.right > 0:
                self.rect.move_ip(pixel_speed, 0)

        # elif zombie is nearby, then attack zombie

        # TODO:
        # Use 2D Vector distance_to for elif.
        # Move using Ball update in https://stackoverflow.com/a/60214064 for smoother movement.

        elif self.pos.distance_to(player.pos) > 100:
            dir = pygame.Vector2(player.pos.x - self.pos.x, player.pos.y - self.pos.y)
            dir.scale_to_length(self.get_pixel_speed())
            self.update_pos(self.pos + dir)

        if self.current_grit <= 0:
            # hide self
            self.death()

    def get_data(self):
        return {
            "stats": {
                "grit": {"current_grit": self.current_grit, "max_grit": self.max_grit},
                "strength": 1,
                "speed": 4,
                "agility": 1,
            },
            "coordinates": self.pos[:],
        }
