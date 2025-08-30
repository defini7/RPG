#define DGE_CAMERA2D
#define DGE_AFFINE_TRANSFORMS
#include "../Include/Game.hpp"

Game::Game()
{
    UseOnlyTextures(true);
    GetWindow()->SetTitle("Role-Playing-Game");
}

Game::~Game()
{
    for (auto& c : m_Creatures)
        delete c;
}

#include <filesystem>

bool Game::OnUserCreate()
{
    for (const auto& s : std::filesystem::directory_iterator(std::filesystem::current_path()))
        std::cout << s << std::endl;

    // Load player assets
    AssetsManager::Get().LoadSprite("player", "Game/Assets/player.png");

    // Load a map
    AssetsManager::Get().LoadMap("village", "Game/Assets/village.lvl", "Game/Assets/village.png");

    // Create the player
    m_Creatures.push_back(new Creature_Player({ 5.0f, 5.0f }, {}));
    m_Player = m_Creatures.front();

    // Initialise the map
    m_CurrentMap = AssetsManager::Get().GetMap("village");

    m_Transformed.SetPixelScale(c_TileSize);
    m_Transformed.SetViewArea(GetWindow()->GetScreenSize());
    m_Camera.Initialise(m_Player->pos, GetWindow()->GetScreenSize() / c_TileSize, def::Camera2D::Mode::LazyLock);

    return true;
}

bool Game::OnUserUpdate(float deltaTime)
{
    if (GetInput()->GetKeyState(def::Key::Z).pressed)
        m_Script.AddCommand(new Command_ShowDialog({ "Hello", "my name is Bob!" }));

    UpdateCreatures(deltaTime);
    m_Transformed.SetOffset(m_Camera.Update(m_Player->pos, deltaTime * 5.0f));

    m_Script.ProcessCommands(this);
    m_Player->IsStatic = m_Script.HaltUserControl;

    ClearTexture(def::DARK_GREEN);

    SetPixelMode(def::Pixel::Mode::MASK);

    m_CurrentMap->Draw(m_Transformed);

    for (const auto& creature : m_Creatures)
        creature->Draw(m_Transformed);

    if (m_ShowDialog)
        DrawDialog({ 10, 10 });

    SetPixelMode(def::Pixel::Mode::DEFAULT);

    return true;
}

void Game::UpdateCreatures(float deltaTime)
{
    static constexpr float EPSILON = 0.1f;

    auto UpdateCreature = [&](Creature* creature)
        {
            creature->Update(this);

            if (!creature->IsStatic)
            {
                def::Vector2f newPos = creature->pos + creature->vel * deltaTime;

                if (creature->vel.x <= 0.0f)
                {
                    if (m_CurrentMap->GetSolid(newPos.x, creature->pos.y) || m_CurrentMap->GetSolid(newPos.x, creature->pos.y + 1.0f - EPSILON))
                        newPos.x = (int)newPos.x + 1;
                }
                else
                {
                    if (m_CurrentMap->GetSolid(newPos.x + 1.0f, creature->pos.y) || m_CurrentMap->GetSolid(newPos.x + 1.0f, creature->pos.y + 1.0f - EPSILON))
                        newPos.x = (int)newPos.x;
                }

                if (creature->vel.y <= 0.0f)
                {
                    if (m_CurrentMap->GetSolid(newPos.x, newPos.y) || m_CurrentMap->GetSolid(newPos.x + 1.0f - EPSILON, newPos.y))
                        newPos.y = (int)newPos.y + 1;
                }
                else
                {
                    if (m_CurrentMap->GetSolid(newPos.x, newPos.y + 1.0f) || m_CurrentMap->GetSolid(newPos.x + 1.0f - EPSILON, newPos.y + 1.0f))
                        newPos.y = (int)newPos.y;
                }

                creature->pos = newPos;
            }
        };

    UpdateCreature(m_Player);

    for (auto it = std::next(m_Creatures.begin()); it != m_Creatures.end(); it++)
        UpdateCreature(*it);
}

void Game::ShowDialog(const std::list<std::string>& lines)
{
    m_ShowDialog = true;
    m_Dialog = lines;
}

void Game::HideDialog()
{
    m_ShowDialog = false;
    m_Dialog.clear();
}

void Game::DrawDialog(const def::Vector2i& pos)
{
    int maxTextLength = 0;
    
    for (const auto& s : m_Dialog)
    {
        if (maxTextLength < s.length())
            maxTextLength = (int)s.length();
    }

    def::Vector2i size(maxTextLength * 8 + 2, m_Dialog.size() * 9 + 2);

    FillTextureRectangle(pos, size, def::BLUE);
    DrawTextureRectangle(pos, size, def::RED);

    int i = 0;
    for (const auto& s : m_Dialog)
        DrawTextureString({ pos.x + 2, pos.y + 2 + 9 * i++ }, s, def::WHITE);
}
