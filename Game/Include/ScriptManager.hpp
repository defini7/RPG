#pragma once

#include "Command.hpp"

class ScriptManager
{
public:
    ScriptManager() = default;
    ~ScriptManager();

    void AddCommand(Command* command, bool sync = true);
    void ProcessCommands(Game*);

public:
    bool HaltUserControl = false;

private:
    // The difference between sync and async commands is that
    // every sync command won't be executed until a previous one wasn't finished
    // async commands are executed on every frame in an order that you pushed them in

    std::list<Command*> m_SyncCommands;
    std::list<Command*> m_AsyncCommands;

};
