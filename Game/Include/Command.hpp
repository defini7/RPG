#pragma once

#include "Creature.hpp"

class Game;

struct Command
{
    Command() = default;
    virtual ~Command() = default;

    virtual void Create(Game*) = 0;
    virtual void Update(Game*) = 0;

    bool IsFinished = false;
    bool IsStarted = false;
};

struct Command_MoveTo : Command
{
    Command_MoveTo(Creature* creature, const def::Vector2f& target, float duration);

    void Create(Game*) override;
    void Update(Game*) override;

private:
    def::Vector2f m_Target;
    def::Vector2f m_Start;
    def::Vector2f m_Dir;

    float m_Duration;
    float m_Timer = 0.0f;
    
    Creature* m_Creature;

};

struct Command_ShowDialog : Command
{
    Command_ShowDialog(const std::list<std::string>& lines);

    void Create(Game*) override;
    void Update(Game*) override;

private:
    std::list<std::string> m_Lines;

};
