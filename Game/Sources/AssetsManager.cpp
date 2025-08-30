#include "../Include/AssetsManager.hpp"

AssetsManager& AssetsManager::Get()
{
    static AssetsManager me;
    return me;
}

AssetsManager::~AssetsManager()
{
    for (const auto& [_, sprite] : m_Sprites)
        delete sprite;

    for (const auto& [_, map] : m_Maps)
        delete map;
}

void AssetsManager::LoadSprite(std::string_view name, std::string_view path)
{
    m_Sprites[name.data()] = new def::Graphic(path);
}

def::Graphic* AssetsManager::GetSprite(std::string_view name)
{
    std::string key(name);

    if (m_Sprites.count(key) > 0)
        return m_Sprites[key];

    return nullptr;
}

void AssetsManager::LoadMap(std::string_view name, std::string_view mapPath, std::string_view tilesheetPath)
{
    m_Maps[name.data()] = new Map(mapPath, tilesheetPath);
}

Map* AssetsManager::GetMap(std::string_view name)
{
    std::string key(name);

    if (m_Maps.count(key) > 0)
        return m_Maps[key];

    return nullptr;
}
