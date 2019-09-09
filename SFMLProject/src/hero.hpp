#ifndef HERO_H
#define HERO_H

#include "pch.hpp"
#include "base_sprite.hpp"

class Hero: public BaseSprite
{
private:
    int jumpCount = 0;
    float m_mass;
    float m_velocity;
    const float m_gravity = 9.80f;
    bool m_grounded;
    int m_frameCount;
    float m_animDuration;
    float m_elapsedTime;
    sf::Vector2i m_spriteSize;
public:
    Hero(/* args */);
    ~Hero();

    void init(std::string textureName, int frameCount, float animDuration, sf::Vector2f position, float mass);
    void update(float dt) override;
    void jump(float velocity);
};
#endif