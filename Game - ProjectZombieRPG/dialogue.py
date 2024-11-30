from json import load
from os.path import join as path_join

import pygame
import pygame.font
from pygame.surface import Surface

from reference import SECTOR_RECT, site_types

MAX_LINE_COUNT = 4


class Dialogue:
    def __init__(self, site: site_types, dialogue_tag: str) -> None:
        self.image = Surface((SECTOR_RECT.width, SECTOR_RECT.height * (1 / 3)))
        self.image.fill((0, 0, 0))  # Black
        self.image.set_alpha(127)
        self.rect = self.image.get_rect(
            topleft=(SECTOR_RECT.x, SECTOR_RECT.height * (2 / 3))
        )

        self.font = pygame.font.SysFont(
            "Calibri", int(self.rect.height / MAX_LINE_COUNT)
        )
        self.text_color = pygame.Color(255, 255, 255)  # White

        with open(
            path_join("assets", "localization", "en" + "_dialogue.json"), "r"
        ) as out_file:
            dialogue_data: dict[str, dict[str, str]] = load(out_file)
        self.dialogue_data = dialogue_data[site.name][dialogue_tag]
        self.rendered_text, self.rendered_text_rect = self.get_rendered_text()

    def wrap_text(self):
        text_lines = [self.dialogue_data]
        for i, line in enumerate(text_lines):
            next_line = ""
            while self.font.size(line)[0] > self.rect.width:
                next_line = " " + line.split(" ")[-1] + next_line
                line = " ".join(line.split(" ")[:-1])

            if next_line != "":
                text_lines.append(next_line.strip())
            text_lines[i] = line.strip()
        return text_lines

    def get_rendered_text(self) -> tuple[list[pygame.Surface], list[pygame.Rect]]:
        rendered_text = []
        rendered_text_rect = []
        for i, line in enumerate(self.wrap_text()):
            rendered_line = self.font.render(line, True, self.text_color)
            rendered_line_rect = rendered_line.get_rect(
                centerx=self.rect.centerx,
                y=self.rect.y + i * (self.rect.height / MAX_LINE_COUNT),
            )
            rendered_text.append(rendered_line)
            rendered_text_rect.append(rendered_line_rect)
        return rendered_text, rendered_text_rect

    def draw(self, screen: pygame.Surface):
        screen.blit(self.image, self.rect)
        screen.blits(zip(self.rendered_text, self.rendered_text_rect))
