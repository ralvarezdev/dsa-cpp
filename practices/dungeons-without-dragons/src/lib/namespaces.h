#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace setup
{
  // Debug Mode
  const bool debugMode = true;
}

namespace dungeons
{
  // Dungeon Rooms per Level
  const int level1Rooms = 5;
  const int level2Rooms = 8;
  const int level3Rooms = 15;

  // Dungeon First Node ID
  const int firstNodeId = 0;

  // Dungeon Room Edges
  const int minRoomEdge = 1;
  const int maxRoomEdge = 3;

  // Dungeon Level Special Rooms Indexes
  const int keyIndex = 0;
  const int entranceIndex = 1;
  const int exitIndex = 2;

  // Undirected Graph Edge Weight
  const int edgeWeight = 1;
}

#endif