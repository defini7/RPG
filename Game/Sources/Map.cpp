#include "../Include/Map.hpp"

Map::Map(std::string_view mapPath, std::string_view sprPath)
{
    Load(mapPath, sprPath);
}

Map::~Map()
{
    if (m_Indices)
        delete[] m_Indices;

    if (m_Solids)
        delete[] m_Solids;
}

bool Map::Load(std::string_view mapPath, std::string_view tilesheetPath)
{
    std::ifstream ifs(mapPath.data(), std::ios::binary);
    
    if (!ifs.is_open())
        return false;

    ifs >> m_Size.x >> m_Size.y;

    int size = m_Size.x * m_Size.y;

    m_Indices = new int[size];
    m_Solids = new bool[size];

    for (int i = 0; i < size; i++)
    {
        ifs >> m_Indices[i];
        ifs >> m_Solids[i];
    }

    m_Tiles = std::make_shared<def::Graphic>(tilesheetPath);

    m_TilesInWidth = m_Tiles->sprite->size.x / c_TileSize.x;

    return true;
}

int Map::GetIndex(const def::Vector2i& pos) const
{
    return GetIndex(pos.x, pos.y);
}

bool Map::GetSolid(const def::Vector2i& pos) const
{
    return GetSolid(pos.x, pos.y);
}

int Map::GetIndex(int x, int y) const
{
    return m_Indices[y * m_Size.x + x];
}

bool Map::GetSolid(int x, int y) const
{
    return m_Solids[y * m_Size.x + x];
}

std::shared_ptr<def::Graphic> Map::GetTilesheet()
{
    return m_Tiles;
}

void Map::Draw(def::TileAffineTransforms& at)
{
    def::Vector2i tl = at.GetTileOrigin().Max({ 0, 0 });
    def::Vector2i br = at.GetTileEnd().Min(m_Size);

    def::Vector2i pos;

    for (pos.y = tl.y; pos.y < br.y; pos.y++)
        for (pos.x = tl.x; pos.x < br.x; pos.x++)
        {
            int index = GetIndex(pos);
            def::Vector2i filePos(index % m_TilesInWidth, index / m_TilesInWidth);

            at.DrawPartialTexture(pos, m_Tiles->texture, filePos * c_TileSize, c_TileSize);
        }
}

int Map::GetWidth() const
{
    return m_Size.x;
}

int Map::GetHeight() const
{
    return m_Size.y;
}

def::Vector2i Map::GetSize() const
{
    return m_Size;
}
