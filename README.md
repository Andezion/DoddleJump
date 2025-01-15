# DoddleJump
A small single-player game written in C++ using SFML 

## Table of contents
* [General info](#general-info)
* [Gameplay](#gameplay)
* [Technologies](#technologies)
* [Features](#features)
* [Inspiration](#inspiration)
* [Setup](#setup)
---

## General info
I decided to write a small game with moving platforms, animated background and character. For implementation I naturally chose C++ and SFML. A couple of simple correlation functions, a couple of simple move functions, and some generation.
---
## Gameplay
This is start screen:

https://github.com/user-attachments/assets/1f55e511-e4d7-45c4-99c3-f193e261bcc5

This is play process:

https://github.com/user-attachments/assets/647d02a1-2067-4cb5-bd94-c429f73088b5

This is lose screen:

https://github.com/user-attachments/assets/6939ca94-703b-4a27-8d37-871d19cc530d

---
## Technologies
Project created with:
* SFML
* C++
* LibreSprite
* Paper and pen 
---
## Features
For easier use, I decided to put Player and Platform into separate classes. 
The first class, Player, has several methods, moving, jumping of two kinds, rendering, texture loading, main sprite updates and gravity application!
In the Platform class we have the same orisovka and movement. There are also two crossing functions, one checks if the platform has gone beyond the screen, the second checks if the platform and the player have crossed:
```
bool is_player_on_platform(const sf::Vector2f &player_position, const sf::Vector2f &player_size) const
{
        return player_position.x + player_size.x > x_cord &&
               player_position.x < x_cord + platform.getGlobalBounds().width &&
               player_position.y + player_size.y >= y_cord &&
               player_position.y + player_size.y <= y_cord + platform.getGlobalBounds().height;
}
```
For ease of switching windows, I decided to divide the game into 3 stages and put them in enum. 
Next we have a function describing the loading screen and a function describing the losing screen. Also in main() we declare texts, load photos and fonts.
An important point is the generation of platform heights, which is implemented through: 
```
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(400, 700);
```
And the value of dist we're using here: 
```
std::vector<Platform> platforms;
for (int i = 0; i < 10; i++)
{
        platforms.emplace_back(static_cast<float>(i) * 150.0f, dist(gen), plat_text);
}
```
The location of the player we have also depends on the location of the first platform generation.
Then moving into the main game loop, switching between modes is done by pressing the keys, or the death of the player :)))) 
Also if we want to start the game again - all our data is cleared, as well as platforms are generated anew:
```
counter = 0;
platforms.clear();

scroll_speed = -100;
for_sprites = 0;
gravity = 800.0f;
                
for (int i = 0; i < 10; i++)
{
        platforms.emplace_back(static_cast<float>(i) * 150.0f, dist(gen), plat_text);
}

player.x_cord = 35;
player.y_cord = platforms[0].y_cord - 150.0f;
player.move(35, 10);

what_type = GameState::Start;
```
Next, we handle the background animation, parodying the infinite screen effect:
```
static float offset_start = 0.0f;
offset_start = offset_start + -scroll_speed * delta_time;
if (offset_start >= static_cast<float>(start_texture.getSize().x))
{
        offset_start = offset_start - static_cast<float>(start_texture.getSize().x);
}

start_sprite.setTextureRect(sf::IntRect(static_cast<int>(offset_start), 0, 1600, 800));
```
If we have a Play loop, we just process events from keystrokes. Check the intersections of the Player with the Platform, apply gravity and update the Player's animation. Then there is a mechanism of level switching depending on the number of points gained. Depending on this, the inscription and smiley face changes, which can be seen in GamePlay. Then we check the Player's location, move all platforms, remove those that have gone off the screen and add new ones. 
At the end we display the background, the platforms, the texts, and the player.

---
## Inspiration
- God Bless FTiMS
- Doddle Jump
- Flappy Bird
- My hatred for Python
--
## Setup
Just install the latest release, if there is no release you can try to compile this yourself
