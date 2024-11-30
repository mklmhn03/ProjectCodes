from enum import Enum, auto
from os import mkdir
from os.path import isdir
from os.path import join as path_join
from os.path import split as path_split
from tkinter import PhotoImage, Tk
from tkinter.filedialog import askopenfilename, asksaveasfilename

import pygame
import pygame.display
import pygame.event
import pygame.font
import pygame.image
import pygame.key
import pygame.sprite
import pygame.time
import pygame.transform
from pygame.locals import MOUSEBUTTONDOWN, MOUSEBUTTONUP, QUIT
from pygame.mouse import get_pos as mouse_get_pos

from game_save import create_save_file
from reference import (
    APPLICATION_ICON_PATH,
    APPLICATION_NAME,
    FPS,
    SCREEN_HEIGHT,
    SCREEN_WIDTH,
    character_types,
    return_codes,
)


class Button:
    def __init__(
        self,
        surface: pygame.Surface,
        rect: pygame.Rect,
        text: tuple[str, pygame.Color] = None,
    ) -> None:
        self.image = surface
        self.rect = rect
        self.text = None

        if text is not None:
            font = pygame.font.SysFont("Calibri", self.rect.height)
            i = 0
            while font.size(text[0])[0] > self.rect.width:
                i += 1
                font = pygame.font.SysFont("Calibri", self.rect.height - i)
            self.text = font.render(text[0], True, text[1])
        self.image.fill((0, 0, 139))

    def draw(self, screen: pygame.Surface):
        screen.blit(self.image, self.rect)
        if self.text is not None:
            text_rect = self.text.get_rect(center=self.rect.center)
            screen.blit(self.text, text_rect)


class Scene_Title:
    def __init__(self, screen: pygame.Surface) -> None:
        self.clock = pygame.time.Clock()
        self.screen = screen

        # "Menu" Buttons
        menu_goto_saves = pygame.Surface((SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8))
        menu_goto_saves = Button(
            menu_goto_saves,
            menu_goto_saves.get_rect(center=(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)),
            text=("Play", (255, 255, 255)),
        )
        self.menu_buttons = {"goto_saves": menu_goto_saves}

        # "Save" Buttons
        saves_goto_menu = pygame.Surface((SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16))
        saves_goto_menu = Button(
            saves_goto_menu,
            saves_goto_menu.get_rect(topleft=(10, 10)),
            text=("Back", (255, 255, 255)),
        )
        saves_open_save = pygame.Surface((SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8))
        saves_open_save = Button(
            saves_open_save,
            saves_open_save.get_rect(
                bottom=SCREEN_HEIGHT / 2 - 5, centerx=SCREEN_WIDTH / 2
            ),
            text=("Open", (255, 255, 255)),
        )
        saves_create_save = pygame.Surface((SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8))
        saves_create_save = Button(
            saves_create_save,
            saves_create_save.get_rect(
                top=SCREEN_HEIGHT / 2 + 5, centerx=SCREEN_WIDTH / 2
            ),
            text=("Create", (255, 255, 255)),
        )
        self.saves_buttons = {
            "goto_menu": saves_goto_menu,
            "open_save": saves_open_save,
            "create_save": saves_create_save,
        }

        self.bgcolor = pygame.Color(175, 238, 238)
        self.mouse_click_pos = []
        self.buttons = self.menu_buttons
        self.sub_scene = self.sub_scenes.MENU

    class sub_scenes(Enum):
        MENU = auto()
        SAVES = auto()
        CREATE_SAVE = auto()

    def draw(self):
        self.screen.fill(self.bgcolor)
        for button in self.buttons.values():
            button.draw(self.screen)

    def is_button_clicked(self, button_name: str):
        if all(
            [
                self.buttons[button_name].rect.contains(
                    (*self.mouse_click_pos[i], 1, 1)
                )
                for i in range(2)
            ]
        ):
            return True
        else:
            return False

    def change_sub_scenes(self, sub_scene: sub_scenes):
        self.sub_scene = sub_scene
        # dirty_rects = [button.rect for button in self.buttons.values()]
        if self.sub_scene == self.sub_scenes.MENU:
            self.buttons = self.menu_buttons
        elif self.sub_scene == self.sub_scenes.SAVES:
            self.buttons = self.saves_buttons
        self.draw()
        pygame.display.update()

    def run(self):
        self.screen.fill(self.bgcolor)
        self.draw()
        pygame.display.update()

        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    return return_codes.QUIT, None
                elif event.type == MOUSEBUTTONDOWN:
                    self.mouse_click_pos = [mouse_get_pos(), None]
                elif event.type == MOUSEBUTTONUP:
                    self.mouse_click_pos[1] = mouse_get_pos()
                    if self.sub_scene == self.sub_scenes.MENU:
                        if self.is_button_clicked("goto_saves"):
                            self.change_sub_scenes(self.sub_scenes.SAVES)
                    elif self.sub_scene == self.sub_scenes.SAVES:
                        if not isdir("saves"):
                            mkdir("saves")

                        if self.is_button_clicked("goto_menu"):
                            self.change_sub_scenes(self.sub_scenes.MENU)
                        elif self.is_button_clicked("open_save"):
                            tk = Tk()
                            tk.withdraw()
                            tk.iconphoto(False, PhotoImage(file=APPLICATION_ICON_PATH))
                            while True:
                                save_name = askopenfilename(
                                    defaultextension=".json",
                                    filetypes=[("JSON", "*.json")],
                                    initialdir="saves",
                                    title=APPLICATION_NAME + " - Open Save File",
                                )
                                if save_name != "":
                                    save_name = path_split(save_name)[-1].split(".")[0]
                                    return return_codes.PLAYABLE, save_name
                                else:
                                    break
                            tk.destroy()
                        elif self.is_button_clicked("create_save"):
                            tk = Tk()
                            tk.withdraw()
                            tk.iconphoto(False, PhotoImage(file=APPLICATION_ICON_PATH))
                            while True:
                                save_name = asksaveasfilename(
                                    defaultextension=".json",
                                    filetypes=[("JSON", "*.json")],
                                    initialdir="saves",
                                    title=APPLICATION_NAME + " - Create Save File",
                                )
                                if save_name != "":
                                    save_name = path_split(save_name)[-1].split(".")[0]
                                    # Change so player can choose character
                                    create_save_file(
                                        save_name, character_types.BATMASTER
                                    )
                                    return return_codes.PLAYABLE, save_name
                                else:
                                    break
                            tk.destroy()
                    self.mouse_click_pos = []

            self.clock.tick(FPS)
