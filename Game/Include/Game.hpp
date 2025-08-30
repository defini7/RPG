#pragma once

#include "defGameEngine.hpp"

#include "Creature.hpp"
#include "ScriptManager.hpp"

#include "../Extensions/DGE_Camera2D.hpp"

class Game : public def::GameEngine
{
public:
    Game();
    ~Game();

private:
    std::list<Creature*> m_Creatures;
    Creature* m_Player = nullptr;

    Map* m_CurrentMap = nullptr;

    ScriptManager m_Script;

    std::list<std::string> m_Dialog;
    bool m_ShowDialog = false;

    def::Camera2D m_Camera;
    def::TileAffineTransforms m_Transformed;

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float deltaTime) override;

    void UpdateCreatures(float deltaTime);
    void ShowDialog(const std::list<std::string>& lines);
    void HideDialog();

    void DrawDialog(const def::Vector2i& pos);

};
