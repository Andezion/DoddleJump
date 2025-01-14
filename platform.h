#ifndef PLATFORM_H
#define PLATFORM_H

class Platform
{
public:
    float x_cord;
    float y_cord;

    sf::Sprite platform;

    Platform(const float x, const float y, const sf::Texture &texture)
    {
        x_cord = x;
        y_cord = y;
        platform.setTexture(texture);
        platform.setScale(sf::Vector2f(0.25, 0.25));
        platform.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(platform);
    }

    void move(const float dx)
    {
        x_cord = x_cord + dx;
        platform.setPosition(x_cord, y_cord);
    }

    bool is_off_screen() const
    {
        return x_cord + platform.getGlobalBounds().width < 0;
    }

    bool is_player_on_platform(const sf::Vector2f &player_position, const sf::Vector2f &player_size) const
    {
        return player_position.x + player_size.x > x_cord &&
               player_position.x < x_cord + platform.getGlobalBounds().width &&
               player_position.y + player_size.y >= y_cord &&
               player_position.y + player_size.y <= y_cord + platform.getGlobalBounds().height;
    }
};

#endif //PLATFORM_H
