#ifndef BASE_SPRITE_H
#define BASE_SPRITE_H

#include "pch.hpp"

class BaseSprite
{
private:
    sf::Texture m_texture;

public:
    sf::Vector2f m_position;
    sf::Sprite m_sprite;
public:
    BaseSprite(/* args */);
    ~BaseSprite();

    virtual void init(std::string textureName, sf::Vector2f position);
    virtual void update(float dt) = 0;
    virtual inline sf::Sprite getSprite() { return m_sprite; }
};
#endif