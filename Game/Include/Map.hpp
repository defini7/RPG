#pragma once

#include <string>
#include <fstream>

#include "../Extensions/DGE_AffineTransforms.hpp"

const def::Vector2i c_TileSize(16, 16);

class Map
{
public:
    Map() = default;
    explicit Map(std::string_view mapPath, std::string_view sprPath);
    
    ~Map();

public:
    bool Load(std::string_view mapPath, std::string_view tilesheetPath);

    int GetIndex(const def::Vector2i& pos) const;
    bool GetSolid(const def::Vector2i& pos) const;

    int GetIndex(int x, int y) const;
    bool GetSolid(int x, int y) const;

    std::shared_ptr<def::Graphic> GetTilesheet();

    void Draw(def::TileAffineTransforms&);

    int GetWidth() const;
    int GetHeight() const;

    def::Vector2i GetSize() const;

private:
    bool* m_Solids = nullptr;
    int* m_Indices = nullptr;

    def::Vector2i m_Size;

    std::shared_ptr<def::Graphic> m_Tiles = nullptr;

    int m_TilesInWidth = 0;

};
