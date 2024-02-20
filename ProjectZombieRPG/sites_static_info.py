from os.path import join as pathjoin
from typing import Union

from pygame.rect import Rect

from reference import SCREEN_HEIGHT, SCREEN_WIDTH, site_types


def get_site_data(
    site: site_types,
) -> dict[str, Union[str, dict[tuple[int, int], dict]]]:
    if site == site_types.TOWN_ORIGIN:
        return _data_origin_town()


def _data_origin_town():
    # objects use pixels from background image.
    data = {
        "image_path": pathjoin("assets", "backgrounds", "town_origin.png"),
        "sectors": {
            (0, 0): {
                "static_objects": [
                    Rect(35, 62, 96, 57),  # topleft_house
                    Rect(307, 62, 96, 57),  # topright_house
                    Rect(35, 62, 96, 57),  # bottomleft_house
                    Rect(0, 310, 207, 23),  # bottomleft_river
                    Rect(241, 310, 195, 23),  # bottomright_river
                ],
                "npcs": [
                    {
                        "name": "karen",
                        "type": "crowd",
                        "image": "npc1",
                        "coordinates": (SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
                        "dialogue_tag": "karen_default",
                    }
                ],
                "zombie_num": 0,
            },
            (0, 1): {
                "static_objects": [
                    Rect(0, 334, 207, 23),  # topleft_river
                    Rect(241, 334, 195, 23),  # topright_river
                    Rect(35, 374, 57, 96),  # shop
                    Rect(35, 554, 96, 58),  # greenhouse
                    Rect(326, 515, 58, 97),  # rightbottom
                ],
                "npcs": [],
                "zombie_num": 1,
            },
            (1, 0): {
                "static_objects": [Rect(744, 62, 108, 71)],  # Our_house
                "npcs": [],
                "zombie_num": 0,
            },
        },
    }
    return data
