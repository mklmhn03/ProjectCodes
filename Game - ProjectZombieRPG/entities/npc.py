import pygame
import pygame.image
from items import Item
from items import Weapon
from items import Armor
from items import Heal
from items import Hamster_Buff

from .entity import Entity


class NPC(Entity):
    def __init__(
        self,
        name: str,
        type: str,
        image_name: str,
        dialogue_tag: str,
        sector: tuple,
        coordinates: tuple,
    ) -> None:
        self.run = False
        self.name = name
        self.type = type  # "Shop", "Quest", or "Crowd" (everyone else)
        # image = pygame.image.load("assets/" + image_name + ".png")
        image = pygame.Surface((32, 64))
        image.fill((148, 0, 211))
        stats = {
            "grit": 2,
            "strength": 0,
            "speed": 3,
            "agility": 0,
        }
        stats["grit"] = {"current_grit": stats["grit"], "max_grit": stats["grit"]}
        super().__init__(stats, coordinates, image)
        self.home_location = {"sector": sector, "coordinates": coordinates}
        self.dialogue_tag = dialogue_tag

        if self.type == "shop":  # Each item slot replenishes after 2-3 days
            self.shop = [Item] * 5
            self.shop[0] = Heal("Super Glue", pygame.Surface((32, 24)), 7, 5)
            #self.shop[1] = Hamster_Buff("Hamster Steroid", pygame.Surface((32, 24)), [2])

        elif self.type == "quest":
            pass
        else:
            pass

    def interact(self):
        if self.type == "shop":
            pass
        elif self.type == "quest":
            pass
        else:
            pass

    def death(self):
        super().death()
        self.run = False

    def update(self, player_pos: pygame.Vector2) -> None:
        # TODO: Move using Ball update in https://stackoverflow.com/a/60214064 for smoother movement.
        if not self.dead and self.run:
            dir = pygame.Vector2(self.pos.x - player_pos.x, self.pos.y - player_pos.y)
            dir.scale_to_length(self.get_pixel_speed())
            self.update_pos(self.pos + dir)

        if self.current_grit <= 0:
            # self.image = pygame.image.load("assets/dead.png").convert()
            self.death()
        elif self.current_grit < self.max_grit:
            self.run = True
