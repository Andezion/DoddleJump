#include <SFML/Graphics.hpp>
#include <vector>

constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 800;
float BACKGROUND_SPEEDS[] = {50.0f, 100.0f, 150.0f};
constexpr float GRAVITY = 700.0f;
constexpr float JUMP_FORCE = -600.0f;
constexpr float GROUND_HEIGHT = 750.0f;

int is_intersects(const sf::Sprite &sprite, const sf::Sprite &player)
{
    const sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    const sf::FloatRect playerr = player.getGlobalBounds();

    if (spriteBounds.intersects(playerr))
    {
        return 1;
    }
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Parallax");

    std::vector<sf::Texture> backgroundTextures(3);
    backgroundTextures[0].loadFromFile("background_layer_1.png");
    backgroundTextures[1].loadFromFile("background_layer_2.png");
    backgroundTextures[2].loadFromFile("background_layer_3.png");

    for (auto &texture : backgroundTextures)
    {
        texture.setRepeated(true);
    }

    std::vector<sf::Sprite> backgroundSprites(3);
    for (int i = 0; i < 3; ++i)
    {
        backgroundSprites[i].setTexture(backgroundTextures[i]);
        backgroundSprites[i].setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
        backgroundSprites[i].setScale(4.45, 4.45);
    }

    std::vector<float> backgroundOffsets(3, 0.0f);

    sf::Texture player1;
    player1.loadFromFile("popa.png");
    sf::Sprite player_sprite(player1);
    player_sprite.setScale(3.0f, 3.0f);
    player_sprite.setPosition(0, GROUND_HEIGHT - 95);

    sf::Texture ground;
    ground.loadFromFile("ground.png");
    sf::Sprite groundSprite(ground);
    groundSprite.setScale(3.0f, 1.0f);
    groundSprite.setPosition(0, GROUND_HEIGHT);

    sf::Texture lampTexture;
    lampTexture.loadFromFile("lamp.png");

    sf::Texture signTexture;
    signTexture.loadFromFile("sign.png");

    sf::Sprite lampSprite(lampTexture);
    lampSprite.setScale(4.0f, 4.0f);
    lampSprite.setPosition(500, 500);

    sf::Sprite signSprite(signTexture);
    signSprite.setScale(7.0f, 7.0f);
    signSprite.setPosition(1200, 550);

    sf::Texture rock1;
    rock1.loadFromFile("rock_1.png");

    sf::Texture rock2;
    rock2.loadFromFile("rock_2.png");

    sf::Texture rock3;
    rock3.loadFromFile("rock_3.png");

    sf::Sprite rock1_sprite(rock1);
    sf::Sprite rock2_sprite(rock2);
    sf::Sprite rock3_sprite(rock3);

    rock1_sprite.setScale(4.0f, 4.0f);
    rock2_sprite.setScale(4.0f, 4.0f);
    rock3_sprite.setScale(4.0f, 4.0f);

    rock1_sprite.setPosition(400, 710);
    rock2_sprite.setPosition(900, 710);
    rock3_sprite.setPosition(1400, 710);

    //sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
    //player.setFillColor(sf::Color::Black);
    //player.setPosition(100.0f, GROUND_HEIGHT - player.getSize().y);

    float playerVelocityY = 0.0f;
    bool isJumping = false;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isJumping)
            {
                playerVelocityY = JUMP_FORCE;
                isJumping = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player_sprite.move(5.0f, 0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                BACKGROUND_SPEEDS[0] = BACKGROUND_SPEEDS[0] + 10.0f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            {
                BACKGROUND_SPEEDS[1] = BACKGROUND_SPEEDS[1] + 10.0f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            {
                BACKGROUND_SPEEDS[2] = BACKGROUND_SPEEDS[2] + 10.0f;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                BACKGROUND_SPEEDS[0] = BACKGROUND_SPEEDS[0] - 10.0f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                BACKGROUND_SPEEDS[1] = BACKGROUND_SPEEDS[1] - 10.0f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            {
                BACKGROUND_SPEEDS[2] = BACKGROUND_SPEEDS[2] - 10.0f;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        for (int i = 0; i < 3; ++i)
        {
            backgroundOffsets[i] += -BACKGROUND_SPEEDS[i] * deltaTime;

            if (backgroundOffsets[i] <= -static_cast<float>(backgroundTextures[i].getSize().x))
            {
                backgroundOffsets[i] += static_cast<float>(backgroundTextures[i].getSize().x);
            }

            backgroundSprites[i].setTextureRect(
                    sf::IntRect(static_cast<int>(backgroundOffsets[i]), 0, WINDOW_WIDTH, WINDOW_HEIGHT));
        }

        lampSprite.move(-BACKGROUND_SPEEDS[1] * deltaTime, 0);
        if (lampSprite.getPosition().x + lampSprite.getGlobalBounds().width < 0)
        {
            lampSprite.setPosition(WINDOW_WIDTH, lampSprite.getPosition().y);
        }

        signSprite.move(-BACKGROUND_SPEEDS[1] * deltaTime, 0);
        if (signSprite.getPosition().x + signSprite.getGlobalBounds().width < 0)
        {
            signSprite.setPosition(WINDOW_WIDTH, signSprite.getPosition().y);
        }

        rock1_sprite.move(-BACKGROUND_SPEEDS[2] * deltaTime, 0);
        if (rock1_sprite.getPosition().x + rock1_sprite.getGlobalBounds().width < 0)
        {
            rock1_sprite.setPosition(WINDOW_WIDTH, rock1_sprite.getPosition().y);
        }

        rock2_sprite.move(-BACKGROUND_SPEEDS[2] * deltaTime, 0);
        if (rock2_sprite.getPosition().x + rock2_sprite.getGlobalBounds().width < 0)
        {
            rock2_sprite.setPosition(WINDOW_WIDTH, rock2_sprite.getPosition().y);
        }

        rock3_sprite.move(-BACKGROUND_SPEEDS[2] * deltaTime, 0);
        if (rock3_sprite.getPosition().x + rock3_sprite.getGlobalBounds().width < 0)
        {
            rock3_sprite.setPosition(WINDOW_WIDTH, rock3_sprite.getPosition().y);
        }

        playerVelocityY += GRAVITY * deltaTime;
        player_sprite.move(0, playerVelocityY * deltaTime);

        if (player_sprite.getPosition().y + player_sprite.getScale().y >= GROUND_HEIGHT - 95)
        {
            player_sprite.setPosition(player_sprite.getPosition().x, GROUND_HEIGHT - player_sprite.getScale().y - 95);
            playerVelocityY = 0;
            isJumping = false;
        }

        window.clear();

        for (int i = 0; i < 3; ++i)
        {
            window.draw(backgroundSprites[i]);

            if (i == 2)
            {
                window.draw(rock1_sprite);
                window.draw(rock2_sprite);
                window.draw(rock3_sprite);

                if(is_intersects(rock1_sprite, player_sprite) ||
                   is_intersects(rock2_sprite, player_sprite) ||
                   is_intersects(rock3_sprite, player_sprite))
                {
                    window.close();
                }
            }

            if (i == 1)
            {
                window.draw(lampSprite);
                window.draw(signSprite);
            }
        }

        window.draw(groundSprite);
        window.draw(player_sprite);

        window.display();
    }

    return 0;
}
