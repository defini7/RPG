#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "defGameEngine.hpp"

#include "Map.hpp"

class AssetsManager
{
public:
    static AssetsManager& Get();
    ~AssetsManager();

    void LoadSprite(std::string_view name, std::string_view path);
    def::Graphic* GetSprite(std::string_view name);

    void LoadMap(std::string_view name, std::string_view mapPath, std::string_view tilesheetPath);
    Map* GetMap(std::string_view name);

    AssetsManager(AssetsManager&&) = delete;
    AssetsManager(const AssetsManager&) = delete;

    void operator=(AssetsManager&&) = delete;
    void operator=(const AssetsManager&) = delete;

private:
    AssetsManager() = default;

private:
    std::unordered_map<std::string, def::Graphic*> m_Sprites;
    std::unordered_map<std::string, Map*> m_Maps;

};
