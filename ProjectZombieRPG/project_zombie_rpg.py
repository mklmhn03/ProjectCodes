import pygame
import pygame.display
import pygame.event
import pygame.font
import pygame.image
import pygame.key
import pygame.locals
import pygame.sprite
import pygame.time
import pygame.transform

from game_save import store_save_data
from reference import (
    APPLICATION_ICON_PATH,
    APPLICATION_NAME,
    SCREEN_HEIGHT,
    SCREEN_WIDTH,
    return_codes,
)
from scene_playable import Scene_Playable
from scene_splash import Scene_Splash
from scene_title import Scene_Title

# Outdated reference
"""
def scene_temp(screen: pygame.Surface) -> str:
    clock = pygame.time.Clock()

    player = Player(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4)
    zombie = Zombie(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)

    color_grass = pygame.Color(50, 205, 50)
    screen.fill(color_grass)
    pygame.display.update()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.locals.QUIT:
                return "QUIT"
        clock.tick(FPS)

        old_sprites_rect = [player.rect.copy(), zombie.rect.copy()]

        # Updates
        player.update()

        if pygame.sprite.spritecollideany(player, [zombie]):
            pass

        # Drawing
        screen.fill(color_grass)
        zombie.draw(screen)
        player.draw(screen)

        pygame.display.update(old_sprites_rect + [player.rect, zombie.rect])
"""


def main() -> None:
    pygame.init()

    pygame.display.set_icon(pygame.image.load(APPLICATION_ICON_PATH))
    pygame.display.set_caption(APPLICATION_NAME)
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

    return_code = Scene_Splash(screen).run()
    save_name = str

    while return_code != return_codes.QUIT:
        if return_code == return_codes.TITLE:
            return_code, save_name = Scene_Title(screen).run()
        elif return_code == return_codes.PLAYABLE:
            scene_playable = Scene_Playable(screen, save_name)
            return_code = scene_playable.run()
            store_save_data(save_name, scene_playable.get_data())


if __name__ == "__main__":
    main()
