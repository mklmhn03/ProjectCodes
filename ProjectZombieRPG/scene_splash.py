from enum import Enum, auto

import pygame
import pygame.display
import pygame.event
import pygame.font
import pygame.image
import pygame.key
import pygame.sprite
import pygame.time
import pygame.transform
from pygame.locals import MOUSEBUTTONUP, QUIT

from reference import FPS, SCREEN_HEIGHT, SCREEN_WIDTH, return_codes


class Scene_Splash:
    def __init__(self, screen: pygame.Surface):
        self.clock = pygame.time.Clock()
        self.screen = screen
        self.scene = 0
        self.scene_phase = self.splash_phases.FADE_IN

        self.bg_color = pygame.Color(0, 0, 0)  # Black
        self.speed_fade_in = round(255 / (FPS * 4.25))
        self.speed_fade_out = round(255 / (FPS * 1))
        self.pause_timer_length = self.pause_timer = FPS * 1

        font_color = pygame.Color(255, 255, 255)  # White
        font_format = pygame.font.SysFont("Calibri", 100)

        self.splash_arts = (
            font_format.render("ME Productions", True, font_color),
            pygame.image.load("assets/pygame_logo.gif").convert_alpha(),
        )
        for art in self.splash_arts:
            art.set_alpha(0)

    class splash_phases(Enum):
        FADE_IN = auto()
        PAUSE = auto()
        FADE_OUT = auto()
        END = auto()

    def draw(self, splash_art: pygame.Surface, splash_art_rect: pygame.Rect) -> None:
        self.screen.fill(self.bg_color)
        self.screen.blit(splash_art, splash_art_rect)
        pygame.display.update(splash_art_rect)

    def sub_scene_splash(self) -> None:
        splash_art = self.splash_arts[self.scene]
        splash_art_rect = splash_art.get_rect(
            center=(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
        )
        if self.scene_phase == self.splash_phases.FADE_IN:
            splash_art.set_alpha(splash_art.get_alpha() + self.speed_fade_in)
            self.draw(splash_art, splash_art_rect)
            if splash_art.get_alpha() >= 255:
                self.scene_phase = self.splash_phases.PAUSE
        elif self.scene_phase == self.splash_phases.PAUSE:
            self.pause_timer -= 1
            if self.pause_timer <= 0:
                self.pause_timer = self.pause_timer_length
                self.scene_phase = self.splash_phases.FADE_OUT
        elif self.scene_phase == self.splash_phases.FADE_OUT:
            splash_art.set_alpha(splash_art.get_alpha() - self.speed_fade_out)
            self.draw(splash_art, splash_art_rect)
            if splash_art.get_alpha() <= 0:
                self.scene_phase = self.splash_phases.END

    def run(self) -> return_codes:
        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    return return_codes.QUIT
                elif event.type == MOUSEBUTTONUP:
                    return return_codes.TITLE

            self.sub_scene_splash()
            if self.scene_phase == self.splash_phases.END and self.scene != len(
                self.splash_arts
            ):
                if self.scene != len(self.splash_arts) - 1:
                    self.scene += 1
                    self.scene_phase = self.splash_phases.FADE_IN
                else:
                    return return_codes.TITLE
            self.clock.tick(FPS)
