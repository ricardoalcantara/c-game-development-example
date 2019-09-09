#include "base_sprite.hpp"

BaseSprite::BaseSprite()
{
}

BaseSprite::~BaseSprite()
{
}

void BaseSprite::init(std::string textureName, sf::Vector2f position)
{
    m_position = position;
    // Load a Texture
    m_texture.loadFromFile(textureName.c_str());
    // Create Sprite and Attach a Texture
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

    LOG_DEBUG("{} Initialized", textureName);
}