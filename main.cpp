#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <set>
#include "platform.h"

class Player
{
public:
    float x_cord;
    float y_cord;

    float velocity_y;

    bool on_platform;
    bool is_jumping;

    sf::Sprite tested;
    std::vector<sf::Texture> tested_sprites;

    size_t frame_counter;
    sf::Clock clock;

    Player(const float x, const float y)
    {
        x_cord = x;
        y_cord = y;

        velocity_y = 0.0f;

        frame_counter = 0;

        on_platform = false;
        is_jumping = false;
    }

    void load()
    {
        for(int i = 1; i <= 4; i++)
        {
            sf::Texture texture;
            texture.loadFromFile("runr" + std::to_string(i) + ".png");
            tested_sprites.push_back(texture);
        }
        tested.setTexture(tested_sprites[0]);
        tested.setPosition(x_cord, y_cord);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(tested);
    }

    void move(const float dx, const float dy)
    {
        x_cord = x_cord + dx;
        y_cord = y_cord + dy;

        tested.setPosition(x_cord, y_cord);
    }

    void jump(const float jump_force)
    {
        if (!is_jumping && on_platform)
        {
            is_jumping = true;
            velocity_y = -jump_force;
        }
    }

    void jump1(const float jump_force)
    {
        if(!is_jumping && on_platform)
        {
            is_jumping = true;
            velocity_y = -jump_force;
        }
    }

    void apply_gravity(const float gravity, const float delta_time)
    {
        if (!on_platform || is_jumping)
        {
            velocity_y = velocity_y + gravity * delta_time;

            y_cord = y_cord + velocity_y * delta_time;

            tested.setPosition(x_cord, y_cord);
        }
        if (on_platform)
        {
            is_jumping = false;
            velocity_y = 0.0f;
        }
    }

    void set_position(const float x, const float y)
    {
        x_cord = x;
        y_cord = y;
        tested.setPosition(x_cord, y_cord);
    }

    sf::Vector2f get_position() const
    {
        return tested.getPosition();
    }

    sf::Vector2f get_size() const
    {
        return {tested.getGlobalBounds().getSize().x,
            tested.getGlobalBounds().getSize().y};
    }

    void update()
    {
        if(clock.getElapsedTime().asMilliseconds() > 100)
        {
            frame_counter = (frame_counter + 1) % tested_sprites.size();
            tested.setTexture(tested_sprites[frame_counter]);
            clock.restart();
        }
    }
};

enum class GameState
{
    Start,
    Play,
    Lose
};

void start_screen(sf::RenderWindow &window, const sf::Font &font, const sf::Sprite &startBackground_sprite)
{
    sf::Text introText;
    introText.setFont(font);

    introText.setString("Welcome to the Game");
    introText.setCharacterSize(50);
    introText.setFillColor(sf::Color::White);
    introText.setPosition(550, 100);

    sf::Text daunText;
    daunText.setFont(font);

    daunText.setString("G to start game\n\nSpace to jump");
    daunText.setCharacterSize(50);
    daunText.setFillColor(sf::Color::White);
    daunText.setPosition(600, 200);

    sf::Text left;
    left.setFont(font);

    left.setString("A to walk left\n\nD to walk right");
    left.setCharacterSize(30);
    left.setFillColor(sf::Color::White);
    left.setPosition(200, 400);

    sf::Text right;
    right.setFont(font);

    right.setString("I to up gravity\n\nK to low gravity");
    right.setCharacterSize(30);
    right.setFillColor(sf::Color::White);
    right.setPosition(1200, 400);

    window.clear();

    window.draw(startBackground_sprite);

    window.draw(introText);
    window.draw(daunText);
    window.draw(right);
    window.draw(left);

    window.display();
}

void lose_screen(sf::RenderWindow &window, const sf::Font &font, const sf::Sprite &loseBackground_sprite)
{
    sf::Text lose;
    lose.setFont(font);

    lose.setString("Game over loser");
    lose.setCharacterSize(50);
    lose.setFillColor(sf::Color::White);
    lose.setPosition(610, 200);

    sf::Text some_shit;
    some_shit.setFont(font);

    some_shit.setString("To try again press R");
    some_shit.setCharacterSize(50);
    some_shit.setFillColor(sf::Color::White);
    some_shit.setPosition(560, 300);

    window.clear();

    window.draw(loseBackground_sprite);

    window.draw(lose);
    window.draw(some_shit);

    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Valik");

    sf::Texture plat_text;
    plat_text.loadFromFile("plat.png");

    sf::Texture background;
    background.loadFromFile("back.png");
    background.setRepeated(true);
    sf::Sprite background_sprite;
    background_sprite.setTexture(background);
    background_sprite.setTextureRect(sf::IntRect(0, 0, 1600, 800));

    sf::Clock clock;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(400, 700);

    std::vector<Platform> platforms;
    for (int i = 0; i < 10; i++)
    {
        platforms.emplace_back(static_cast<float>(i) * 150.0f, dist(gen), plat_text);
    }

    sf::Texture test;
    test.loadFromFile("runr1.png");

    Player player(45, platforms[0].y_cord - 150.0f);
    player.load();

    float scroll_speed = -100.0f;

    sf::Font text;
    text.loadFromFile("letters.ttf");

    sf::Text coordinates;
    sf::Text level;
    sf::Text grav;

    coordinates.setFont(text);
    coordinates.setString("");
    coordinates.setCharacterSize(40);
    coordinates.setFillColor(sf::Color::White);

    level.setFont(text);
    level.setString("");
    level.setCharacterSize(40);
    level.setFillColor(sf::Color::White);

    grav.setFont(text);
    grav.setString("");
    grav.setCharacterSize(40);
    grav.setFillColor(sf::Color::White);

    sf::Texture easy_texture;
    easy_texture.loadFromFile("easy.png");
    sf::Sprite easy_sprite;
    easy_sprite.setTexture(easy_texture);
    easy_sprite.setScale(0.05f, 0.05f);
    easy_sprite.setPosition(1530, 10);

    sf::Texture medium_texture;
    medium_texture.loadFromFile("medium.png");
    sf::Sprite medium_sprite;
    medium_sprite.setTexture(medium_texture);
    medium_sprite.setScale(0.05f, 0.05f);
    medium_sprite.setPosition(1530, 10);

    sf::Texture hard_texture;
    hard_texture.loadFromFile("hard.png");
    sf::Sprite hard_sprite;
    hard_sprite.setTexture(hard_texture);
    hard_sprite.setScale(0.05f, 0.05f);
    hard_sprite.setPosition(1530, 10);

    sf::Texture start_texture;
    start_texture.loadFromFile("start.png");
    start_texture.setRepeated(true);
    sf::Sprite start_sprite;
    start_sprite.setTexture(start_texture);
    start_sprite.setTextureRect(sf::IntRect(0, 0, 1600, 800));

    sf::Texture lose_texture;
    lose_texture.loadFromFile("lose.png");
    lose_texture.setRepeated(true);
    sf::Sprite lose_sprite;
    lose_sprite.setTexture(lose_texture);
    lose_sprite.setTextureRect(sf::IntRect(0, 0, 1600, 800));

    int for_sprites = 0;

    int counter = 0;
    std::set<std::pair<float, float>> unique_platforms;

    auto what_type = GameState::Start;

    float gravity = 800.0f;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                window.close();
            }

            if (what_type == GameState::Start && sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                what_type = GameState::Play;
            }

            if (what_type == GameState::Lose && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
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
            }
        }

        float delta_time = clock.restart().asSeconds();

        if (what_type == GameState::Start)
        {
            static float offset_start = 0.0f;
            offset_start = offset_start + -scroll_speed * delta_time;
            if (offset_start >= static_cast<float>(start_texture.getSize().x))
            {
                offset_start = offset_start - static_cast<float>(start_texture.getSize().x);
            }

            start_sprite.setTextureRect(sf::IntRect(static_cast<int>(offset_start), 0, 1600, 800));

            start_screen(window, text, start_sprite);
        }
        else if (what_type == GameState::Play)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.move(-400.0f * delta_time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.move(400.0f * delta_time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                player.jump(700.0f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                player.jump1(350.0f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                gravity = gravity + 1.0f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                gravity = gravity - 1.0f;
            }

            player.on_platform = false;
            for (auto &platform : platforms)
            {
                if (platform.is_player_on_platform(player.get_position(), player.get_size()))
                {
                    player.on_platform = true;

                    if (!unique_platforms.contains({platform.x_cord, platform.y_cord}))
                    {
                        unique_platforms.insert({platform.x_cord, platform.y_cord});
                        counter++;
                    }

                    float platform_movement_x = scroll_speed * delta_time;
                    player.y_cord = platform.y_cord - player.get_size().y;
                    player.x_cord = player.x_cord + platform_movement_x;
                    player.set_position(player.x_cord, player.y_cord);

                    break;
                }
            }

            player.apply_gravity(gravity, delta_time);

            player.update();

            coordinates.setString("Your score is " + std::to_string(counter));
            grav.setString("Gravity is " + std::to_string(static_cast<int>(gravity / 10)));

            if (counter < 5000)
            {
                level.setString("Level " + std::to_string(1));
            }
            else if (counter < 10000)
            {
                level.setString("Level " + std::to_string(2));
                for_sprites = 1;
                scroll_speed = -200;
            }
            else
            {
                level.setString("Level " + std::to_string(3));
                for_sprites = 2;
                scroll_speed = -300;
            }

            if (player.get_position().x <= 0 || player.get_position().y + player.get_size().y >= 800)
            {
                what_type = GameState::Lose;
            }

            for (auto &platform : platforms)
            {
                platform.move(scroll_speed * delta_time);
            }

            std::erase_if(platforms, [](const Platform &p)
            {
                return p.is_off_screen();
            });

            if (platforms.back().x_cord < 1500)
            {
                platforms.emplace_back(platforms.back().x_cord + 150.0f, dist(gen), plat_text);
            }

            static float offset = 0.0f;
            offset = offset + -scroll_speed * delta_time;
            if (offset >= static_cast<float>(background.getSize().x))
            {
                offset = offset - static_cast<float>(background.getSize().x);
            }

            background_sprite.setTextureRect(sf::IntRect(static_cast<int>(offset), 0, 1600, 800));

            window.clear(sf::Color::White);
            window.draw(background_sprite);

            for (const auto &platform : platforms)
            {
                platform.draw(window);
            }

            player.draw(window);

            if (for_sprites == 0)
            {
                window.draw(easy_sprite);
            }
            if (for_sprites == 1)
            {
                window.draw(medium_sprite);
            }
            if (for_sprites == 2)
            {
                window.draw(hard_sprite);
            }

            coordinates.setPosition(10, 10);
            window.draw(coordinates);

            level.setPosition(1380, 10);
            window.draw(level);

            grav.setPosition(675, 10);
            window.draw(grav);

            window.display();
        }
        else
        {
            static float offset_lose = 0.0f;
            offset_lose = offset_lose + -scroll_speed * delta_time;
            if (offset_lose >= static_cast<float>(lose_texture.getSize().x))
            {
                offset_lose = offset_lose - static_cast<float>(lose_texture.getSize().x);
            }

            lose_sprite.setTextureRect(sf::IntRect(static_cast<int>(offset_lose), 0, 1600, 800));

            lose_screen(window, text, lose_sprite);
        }
    }

    return 0;
}
