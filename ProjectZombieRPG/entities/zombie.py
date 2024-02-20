import pygame
import pygame.event
import pygame.image
import pygame.sprite
from reference import FPS, PLAYER_HARMED_EVENT

import entities.player

from .entity import Entity


class Zombie(Entity):
    def __init__(self, type: str, coordinates: tuple[int, int]) -> None:
        stats = ()  # grit, strength, speed, agility
        image = pygame.Surface
        if type == "boss":
            stats = {"grit": 300, "strength": 34, "speed": 5, "agility": 10}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        elif type == "semi-boss":
            stats = {"grit": 150, "strength": 17, "speed": 5, "agility": 5}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        elif type == "hefty":
            stats = {"grit": 70, "strength": 12, "speed": 3, "agility": 3}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        elif type == "runner":
            stats = {"grit": 30, "strength": 8, "speed": 5, "agility": 6}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        elif type == "ranger":
            stats = {"grit": 40, "strength": 8, "speed": 5, "agility": 6}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        elif type == "surprise":
            stats = {"grit": 2, "strength": 10, "speed": 0, "agility": 5}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        else:  # "savage baby"
            stats = {"grit": 35, "strength": 10, "speed": 3, "agility": 3}
            # image = pygame.image.load("zombie.png")
            image = pygame.Surface((32, 64))
        stats["grit"] = {"current_grit": stats["grit"], "max_grit": stats["grit"]}
        image.fill((105, 131, 98))  # Green
        super().__init__(stats, coordinates, image)
        self.type = type
        self.attack_timer = 0

    def attacked(self, hurt):
        if self.type != "surprise":
            pass
        else:
            super().attacked(hurt)
            if self.type == "savage baby":  # Gets more savage when attacked
                self.agility += 1
                self.speed += 1

    def update(
        self,
        player: entities.player.Player,
        collidable_entities: list[Entity],
    ) -> None:
        # TODO: Move using Ball update in https://stackoverflow.com/a/60214064 for smoother movement.
        # TODO: Change rect to update_rect

        if self.attack_timer != 0:
            self.attack_timer -= 1
            if self.attack_timer == 0:
                pygame.event.post(
                    pygame.event.Event(PLAYER_HARMED_EVENT, {"damage": 1})
                )
        elif player in collidable_entities:
            dir = pygame.Vector2(player.pos.x - self.pos.x, player.pos.y - self.pos.y)
            dir.scale_to_length(self.get_pixel_speed())
            self.update_pos(self.pos + dir)
            is_collision = self.collide_any(collidable_entities)
            if is_collision is not None:
                if is_collision is player and self.attack_timer == 0:
                    # Change to `self.strength`
                    self.attack_timer = 0.5 * FPS
                # if sprite.spritecollisionall isinstance player
                self.update_pos(self.pos - dir)

        if self.current_grit <= 0:
            # self.image = pygame.image.load("assets/dead.png").convert()
            self.death()
