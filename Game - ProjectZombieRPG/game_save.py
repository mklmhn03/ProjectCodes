from json import dump, load
from os.path import isfile as pathisfile
from os.path import join as pathjoin

from reference import character_types, site_types


def create_save_file(save_name: str, character: character_types):
    if character == character_types.BERSERKER:
        stats = {"grit": 10, "strength": 10, "speed": 4, "agility": 10}
    elif character == character_types.ASSASSIN:
        stats = {"grit": 20, "strength": 10, "speed": 4, "agility": 5}
    elif character == character_types.BATMASTER:
        stats = {"grit": 1, "strength": 1, "speed": 4, "agility": 1}
    else:  # `character_types.BOWMASTER`
        stats = {"grit": 2, "strength": 4, "speed": 4, "agility": 30}
    stats["grit"] = {"current_grit": stats["grit"], "max_grit": stats["grit"]}

    data = {
        "player": {
            "character": character.name,
            "stats": stats,
            "inventory": {"weapon": None, "armor": [None] * 4, "items": [None] * 20},
            "money": 0,
            "exp": 0,
            "coordinates": (1024, 512),
        },
        "hamster": {
            "stats": {
                "grit": {"current_grit": 1, "max_grit": 1},
                "strength": 2,
                "speed": 4,
                "agility": 5,
            },
            "coordinates": (1024, 600),
        },
        "world": {
            "quest_data": {
                "origin_town": {
                    "cut_wood": False,
                    "check_house": False,
                    "check_survivors": False,
                    "escort_survivor": False,
                },
                "second_town": {"interact_mayor": False},
            },
            "shop_data": {
                "origin_town": [{"item": "iron_axe_rusted", "stock": 1}],
                "second_town": [
                    {"item": "sharp_sword", "stock": 1},
                    {"item": "grenade", "stock": 5},
                ],
            },
            "location": {
                "site": site_types.TOWN_ORIGIN.name,
                "sector": (1, 0),
            },
        },
    }
    store_save_data(save_name, data)


def get_save_path(save_name: str):
    return pathjoin("saves", save_name + ".json")


def store_save_data(save_name: str, data: dict):
    file_path = get_save_path(save_name)
    with open(file_path, "w", encoding="utf-8") as in_file:
        dump(data, in_file, ensure_ascii=False, indent=4)


def retrieve_save_data(save_name: str):
    file_path = get_save_path(save_name)
    data = dict
    with open(file_path, "r") as out_file:
        data = load(out_file)
    return data


def verify_save_data():
    """Check if data is corrupt before retrieving or saving"""
    # TODO: Create html instuctions on what to do if file is corrupt.
    pass


# Used to test data saves.
if __name__ == "__main__":
    # Template for save files.
    # Notes:
    # `inventory` array should as long as its size and filled with `None` for blank spots.
    # Need convention for naming quests.

    save_name = "Temp Save"
    if not pathisfile(get_save_path(save_name)):
        create_save_file(save_name, character_types.BATMASTER)
    data = retrieve_save_data(save_name)
    data["player"]["stats"]["agility"] = 5
    data["player"]["inventory"][
        data["player"]["inventory"].index(None)
    ] = "iron_axe_rusted"
    data["player"]["inventory"][data["player"]["inventory"].index(None)] = "auto_rifle"
    data["player"]["money"] += 1024
    data["world"]["quest_data"]["origin_town"]["cut_wood"] = True
    data["world"]["shop_data"]["origin_town"][0]["stock"] = 0

    store_save_data(save_name, data)
    save_data = retrieve_save_data(save_name)

    from json import dumps

    print(dumps(save_data, ensure_ascii=False, indent=2))
