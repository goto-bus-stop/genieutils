/*
    genie/dat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
    Copyright (C) 2011 - 2017  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/dat/Terrain.h"

namespace genie {

unsigned short Terrain::terrain_count_ = 0;

void Terrain::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);

    Borders.resize(getTerrainCount(gv), 0);
}

//------------------------------------------------------------------------------
void Terrain::setTerrainCount(unsigned short cnt)
{
    terrain_count_ = cnt;
}

//------------------------------------------------------------------------------
unsigned short Terrain::getTerrainCount(GameVersion gv)
{
    if (terrain_count_) {
        return terrain_count_;
    }

    if (gv >= GV_SWGB) {
        return 55;
    }

    if (gv >= GV_T2 && gv <= GV_LatestTap) {
        return 96;
    }

    if (gv == GV_Cysion) {
        return 100;
    }

    if (gv == GV_TC) {
        return 42;
    }

    return 32;
}

//------------------------------------------------------------------------------
size_t Terrain::getNameSize()
{
    if (getGameVersion() >= GV_SWGB) {
        return 17;
    } else {
        return 13;
    }
}

//------------------------------------------------------------------------------
void Terrain::serializeObject(void)
{
    GameVersion gv = getGameVersion();

    serialize<int8_t>(Enabled);
    serialize<int8_t>(Random);

    if (gv > GV_LatestTap || gv < GV_Tapsa) {
        serialize(Name, getNameSize());
        serialize(Name2, getNameSize());
    } else {
        if (gv >= GV_T2) {
            serialize<int8_t>(IsWater);
            serialize<int8_t>(HideInEditor);
            serialize<int32_t>(StringID);

            int16_t blend = BlendPriority;
            serialize<int16_t>(blend);
            BlendPriority = blend;

            blend = BlendType;
            serialize<int16_t>(blend);
            BlendType = blend;
        }

        serializeDebugString(Name);
        serializeDebugString(Name2);
    }

    if (gv >= GV_AoEB) {
        serialize<int32_t>(SLP);
    }

    serialize<int32_t>(ShapePtr);
    serialize<int32_t>(SoundID);

    if (gv >= GV_AoKB) {
        serialize<int32_t>(BlendPriority);
        serialize<int32_t>(BlendType);
    }

    serialize(Colors);
    serializePair<uint8_t>(CliffColors);
    serialize<int8_t>(PassableTerrain);
    serialize<int8_t>(ImpassableTerrain);

    serialize<int8_t>(IsAnimated);
    serialize<int16_t>(AnimationFrames);
    serialize<int16_t>(PauseFames);
    serialize<float>(Interval);
    serialize<float>(PauseBetweenLoops);
    serialize<int16_t>(Frame);
    serialize<int16_t>(DrawFrame);
    serialize<float>(AnimateLast);
    serialize<int8_t>(FrameChanged);
    serialize<int8_t>(Drawn);

    serialize(ElevationGraphics);
    serialize<int16_t>(TerrainToDraw);
    serializePair<int16_t>(TerrainDimensions);

    if (isOperation(OP_READ)) {
        serialize<int16_t>(Borders, getTerrainCount(gv));
    } else {
        serialize<int16_t>(Borders, Borders.size());
    }

    serialize(TerrainUnitID);
    serialize(TerrainUnitDensity);
    serialize(TerrainUnitCentering);
    serialize<int16_t>(NumberOfTerrainUnitsUsed);

    if (gv < GV_SWGB) {
        serialize<int16_t>(Phantom);
    }
}
} // namespace genie
