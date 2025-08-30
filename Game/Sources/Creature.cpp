#include "../Include/Creature.hpp"

Creature::Creature(const def::Vector2f& pos, const def::Vector2f& vel, bool isStatic)
    : pos(pos), vel(vel), IsStatic(isStatic)
{
}

Creature_Player::Creature_Player(const def::Vector2f& pos, const def::Vector2f& vel)
    : Creature(pos, vel, false)
{
}

void Creature_Player::Update(def::GameEngine* engine)
{
    vel.x = vel.y = 0;

    bool stand = true;

    if (!IsStatic)
    {
        if (engine->GetInput()->GetKeyState(def::Key::LEFT).held)
        {
            vel.x = -c_Speed;
            m_Direction = DIR_LEFT;
            stand = false;
        }

        if (engine->GetInput()->GetKeyState(def::Key::RIGHT).held)
        {
            vel.x = c_Speed;
            m_Direction = DIR_RIGHT;
            stand = false;
        }

        if (engine->GetInput()->GetKeyState(def::Key::UP).held)
        {
            vel.y = -c_Speed;
            m_Direction = DIR_UP;
            stand = false;
        }

        if (engine->GetInput()->GetKeyState(def::Key::DOWN).held)
        {
            vel.y = c_Speed;
            m_Direction = DIR_DOWN;
            stand = false;
        }
    }

    if (stand)
        m_Timer = 0.0f;

    if (m_Timer <= c_FrameTime)
        m_Timer += engine->GetDeltaTime();
    else
    {
        ++m_Frame %= c_FramesCount;
        m_Timer = 0.0f;
    }
}

void Creature_Player::Draw(def::TileAffineTransforms& renderer)
{
    def::Vector2f fileOffset(m_Direction, m_Frame);
    renderer.DrawPartialTexture(pos, AssetsManager::Get().GetSprite("player")->texture, fileOffset * c_TileSize, c_TileSize);
}
