#include "../Include/ScriptManager.hpp"

ScriptManager::~ScriptManager()
{
    for (auto& c : m_AsyncCommands)
        delete c;

    for (auto& c : m_SyncCommands)
        delete c;
}

void ScriptManager::AddCommand(Command* command, bool sync)
{
    if (!command)
        return;

    if (sync)
        m_SyncCommands.push_back(command);
    else
        m_AsyncCommands.push_back(command);
}

void ScriptManager::ProcessCommands(Game* game)
{
    auto ProcessCommand = [&](Command* command)
        {
            if (command->IsStarted)
            {
                if (!command->IsFinished)
                    command->Update(game);

                HaltUserControl = !command->IsFinished;
            }
            else
            {
                command->Create(game);
                command->IsStarted = true;
            }
        };

    // Handle async commands
    
    for (auto& command : m_AsyncCommands)
    {
        ProcessCommand(command);

        if (command->IsFinished)
            delete command;
    }

    m_AsyncCommands.remove_if([](Command* c) { return c->IsFinished; });

    // Handle sync commands

    if (!m_SyncCommands.empty())
    {
        Command* command = m_SyncCommands.front();

        ProcessCommand(command);

        if (command->IsFinished)
        {
            delete command;
            m_SyncCommands.pop_front();
        }
    }
}
