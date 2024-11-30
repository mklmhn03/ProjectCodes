from enum import Enum, auto
from os.path import join as pathjoin

from pygame import USEREVENT, Rect

# https://stackoverflow.com/questions/13034496/using-global-variables-between-files
APPLICATION_NAME = "Project Zombie RPG"
APPLICATION_ICON_PATH = pathjoin("assets", "icon32x32.png")
FPS = 60
SCREEN_WIDTH = 1366
SCREEN_HEIGHT = 768
SECTOR_IMAGE_SIZE = (436, 333)
screen_rect = Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
SECTOR_RECT = Rect((0, 0), SECTOR_IMAGE_SIZE).fit(screen_rect)
SECTOR_RECT.center = screen_rect.center
del screen_rect

# Scene Playable
DIALOGUE_EVENT = USEREVENT + 1
PLAYER_HARMED_EVENT = USEREVENT + 2


class return_codes(Enum):
    QUIT = auto()
    TITLE = auto()
    PLAYABLE = auto()


class entity_direction(Enum):  # Counter Clockwise
    TOP = 0
    LEFT = 1
    BOTTOM = 2
    RIGHT = 3
    # TOP = 0
    # TOP_LEFT = 1
    # LEFT = 2
    # BOTTOM_LEFT = 3
    # BOTTOM = 4
    # BOTTOM_RIGHT = 5
    # RIGHT = 6
    # TOP_RIGHT = 7


class site_types(Enum):
    TOWN_ORIGIN = auto()


class character_types(Enum):
    BERSERKER = auto()
    ASSASSIN = auto()
    BATMASTER = auto()
    BOWMASTER = auto()
