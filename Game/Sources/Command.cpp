#include "../Include/Command.hpp"
#include "../Include/Game.hpp"

Command_MoveTo::Command_MoveTo(Creature* creature, const def::Vector2f& pos, float duration)
    : Command(), m_Creature(creature), m_Target(pos), m_Duration(duration) {}

void Command_MoveTo::Create(Game*)
{
    m_Start = m_Creature->pos;
    m_Dir = m_Target - m_Start;
}

void Command_MoveTo::Update(Game* game)
{
    m_Creature->pos = m_Start + m_Dir * m_Timer / m_Duration;
    m_Creature->vel = m_Dir;

    m_Timer += game->GetDeltaTime();

    if (m_Timer >= m_Duration || (m_Creature->pos - m_Target).Abs() < def::Vector2f(0.01f, 0.01f))
    {
        m_Creature->pos = m_Target;
        IsFinished = true;
    }
}

Command_ShowDialog::Command_ShowDialog(const std::list<std::string>& lines) : m_Lines(lines)
{
}

void Command_ShowDialog::Create(Game* game)
{
    game->ShowDialog(m_Lines);
}

void Command_ShowDialog::Update(Game* game)
{
    if (game->GetInput()->GetKeyState(def::Key::SPACE).pressed)
    {
        game->HideDialog();
        IsFinished = true;
    }
}
