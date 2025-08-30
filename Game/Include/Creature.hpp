#pragma once

#include "defGameEngine.hpp"
#include "AssetsManager.hpp"

#include "../Extensions/DGE_AffineTransforms.hpp"

class Creature
{
public:
    Creature(const def::Vector2f& pos, const def::Vector2f& vel, bool isStatic = true);
    virtual ~Creature() = default;

    virtual void Update(def::GameEngine*) = 0;
    virtual void Draw(def::TileAffineTransforms&) = 0;

public:
    def::Vector2f pos;
    def::Vector2f vel;

    bool IsStatic;

};

class Creature_Player : public Creature
{
public:
    Creature_Player(const def::Vector2f& pos, const def::Vector2f& vel);

    void Update(def::GameEngine*) override;
    void Draw(def::TileAffineTransforms&) override;

private:
    enum Direction
    {
        DIR_DOWN,
        DIR_LEFT,
        DIR_UP,
        DIR_RIGHT
    } m_Direction = DIR_DOWN;

    float m_Timer = 0.0f;
    int m_Frame = 0;

    constexpr static float c_Speed = 5.0f;
    constexpr static int c_FramesCount = 2;
    constexpr static float c_FrameTime = 0.2f;

};
