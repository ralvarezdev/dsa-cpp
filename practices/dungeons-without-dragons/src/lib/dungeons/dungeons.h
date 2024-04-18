#include <algorithm>
#include <sstream>
#include <random>
#include <iostream>

#include "../../../../../data-structures/undirected-graphs/base.h"
#include "../../../../../data-structures/single-linked-lists/number.h"
#include "../namespaces.h"

using std::cout;
using std::fill;
using std::ostringstream;
using std::random_device;
using std::uniform_int_distribution;

#ifndef DUNGEONS
#define DUNGEONS

// Initialize Seed
random_device rd;

// DUNGEON ROOM CLASS

class DungeonRoom
{
private:
  bool hasKey;
  bool isEntrance;
  bool isExit;

public:
  // Constructors
  DungeonRoom(bool, bool, bool);

  // Public Methods
  bool getHasKey() { return hasKey; };
  bool getIsEntrance() { return isEntrance; };
  bool getIsExit() { return isExit; };
};

// DungeonRoomPtr Definition
using DungeonRoomPtr = DungeonRoom *;

// DUNGEONS GRAPH CLASS

class DungeonsGraph : public UndirGraph<DungeonRoomPtr>
{
public:
  // Inherit Constructors
  using UndirGraph<DungeonRoomPtr>::UndirGraph;

  // Destructor
  virtual ~DungeonsGraph()
  {
    UndirNodePtr<DungeonRoomPtr> node;
    DungeonRoomPtr t;

    // Get First Node
    while (!this->nodes->isEmpty())
    {
      node = this->nodes->remove();
      t = node->data;
      node->data = NULL;

      // Deallocate Node's Data
      delete t, node;
    }
  }
};

// DungeonsGraphPtr Definition
using DungeonsGraphPtr = DungeonsGraph *;

// DUNGEONS CLASS

class Dungeons
{
private:
  DungeonsGraphPtr level1 = new DungeonsGraph(dungeons::firstNodeId);
  DungeonsGraphPtr level2 = new DungeonsGraph(dungeons::firstNodeId);
  DungeonsGraphPtr level3 = new DungeonsGraph(dungeons::firstNodeId);

  // Private Methods
  int *getSpecialRooms(int);
  QueueLinkedList<int> *getDungeonRoomsId(int);
  QueueLinkedList<DungeonRoomPtr> *getDungeonRooms(QueueLinkedList<int> *, int *);
  QueueLinkedList<WeightedNodeEdgesPtr> *getDungeonRoomsConns(SingleLinkedList<int> *, int *, int);

public:
  // Constructors
  Dungeons();

  // Destructor
  virtual ~Dungeons()
  {
    delete level1, level2, level3;
  }
};

// Dungeon Room Class Constructors
DungeonRoom::DungeonRoom(bool hasKey, bool isEntrance, bool isExit)
{
  this->hasKey = hasKey;
  this->isEntrance = isEntrance;
  this->isExit = isExit;
}

// Dungeon Class Constructors
Dungeons::Dungeons()
{
  UndirGraphPtr<DungeonRoomPtr> dungeonLevels[3] = {this->level1, this->level2, this->level3};
  QueueLinkedList<int> *dungeonsRoomsId[3];
  QueueLinkedList<DungeonRoomPtr> *dungeonsRooms[3];
  QueueLinkedList<WeightedNodeEdgesPtr> *dungeonsRoomsConns[3];
  SingleLinkedList<int> *dungeonsNodesIds[3];
  int *t, **distsResults;
  int numberRooms[3] = {dungeons::level1Rooms, dungeons::level2Rooms, dungeons::level3Rooms};
  ostringstream msg;

  distsResults = new int *[3];

  // Create Dungeon Levels
  for (int i = 0; i < 3; i++)
  {
    // Get Key, Entrance and Exit Room ID
    distsResults[i] = this->getSpecialRooms(numberRooms[i]);

    // Get Random Dungeon Rooms ID
    dungeonsRoomsId[i] = this->getDungeonRoomsId(numberRooms[i]);
    dungeonsRooms[i] = this->getDungeonRooms(dungeonsRoomsId[i], distsResults[i]);
  }

  // Print Dungeons Levels
  if (setup::debugMode)
  {
    int key, entrance, exit, nRooms;

    for (int j = 0; j < 3; j++)
    {
      // Get Dungeon Data
      key = distsResults[j][dungeons::keyIndex];
      entrance = distsResults[j][dungeons::entranceIndex];
      exit = distsResults[j][dungeons::exitIndex];
      nRooms = dungeonsRooms[j]->getLength();

      msg << "Level [" << j + 1 << "]\n"
          << "Key Room: " << key << '\n'
          << "Entrance Room: " << entrance << '\n'
          << "Exit Room: " << exit << '\n'
          << "Total Rooms: " << nRooms << '\n'
          << "Non-special Rooms: " << nRooms - 3
          << "\n\n";
    }
    cout << msg.str();
  }

  for (int i = 0; i < 3; i++)
  {
    // Add Dungeon Rooms to its Given Graph
    dungeonsNodesIds[i] = dungeonLevels[i]->addNodes(dungeonsRooms[i]);

    // Get Random Dungeon Rooms Connections
    dungeonsRoomsConns[i] = this->getDungeonRoomsConns(dungeonsNodesIds[i], distsResults[i], numberRooms[i]);

    // Add Dungeon Rooms Connections to its Given Graph
    dungeonLevels[i]->addEdges(dungeonsRoomsConns[i]);
  }

  // Deallocate Memory
  for (int i = 0; i < 3; i++)
  {
    t = distsResults[i];
    distsResults[i] = NULL;
    delete t;
  }
  delete distsResults;
}

// Method to Get the Distribution Results of the Special Rooms
int *Dungeons::getSpecialRooms(int numberRooms)
{
  bool occupied, levelRange[numberRooms];
  int *distResults = new int[3];
  int index;

  // Fill Arrays with 'False'
  fill(levelRange, levelRange + numberRooms, false);

  // Create Distributions
  uniform_int_distribution<int> distLevel(dungeons::firstNodeId, dungeons::firstNodeId + numberRooms - 1);

  // Get Key, Entrance and Exit Room ID
  for (int i = 0; i < 3; i++)
    do
    {
      // Get Random Number
      index = distLevel(rd) - dungeons::firstNodeId;

      // Store Random Index
      occupied = levelRange[index];
      if (!occupied)
      {
        distResults[i] = index;
        levelRange[index] = true;
      }
    } while (occupied);

  return distResults;
}

// Method to Get the Dungeon Rooms ID for a Given Level
QueueLinkedList<int> *Dungeons::getDungeonRoomsId(int numberRooms)
{
  int levelRoomsId[numberRooms];
  int index, toSwap, n;

  // Initialize Dungeon Rooms ID Queue
  QueueLinkedList<int> *dungeonRoomsId = new QueueLinkedList<int>(-1);

  // Fill Level Rooms ID
  for (int i = 0; i < numberRooms; i++)
    levelRoomsId[i] = i;

  // Get Dungeon Room in Random Order
  for (int i = 0; i < numberRooms; i++)
  {
    n = numberRooms - i - 1;
    uniform_int_distribution<int> distLevel(dungeons::firstNodeId, dungeons::firstNodeId + n);

    // Get Random Number
    index = distLevel(rd) - dungeons::firstNodeId;

    // Store Random Index
    dungeonRoomsId->enqueue(levelRoomsId[index]);

    // Remove the Given Room ID from Level Rooms ID
    toSwap = levelRoomsId[n];
    levelRoomsId[n] = -1;
    levelRoomsId[index] = toSwap;
  }

  return dungeonRoomsId;
}

// Method to Get the Dungeon Rooms for a Given Level
QueueLinkedList<DungeonRoomPtr> *Dungeons::getDungeonRooms(QueueLinkedList<int> *dungeonRoomsIds, int *distResults)
{
  int dungeonRoomId;
  DungeonRoomPtr dungeonRoom;
  bool hasKey, isEntrance, isExit;

  // Initialize Dungeon Rooms Queue
  QueueLinkedList<DungeonRoomPtr> *dungeonRooms = new QueueLinkedList<DungeonRoomPtr>(NULL);

  // Create Each Dungeon Room
  while (!dungeonRoomsIds->isEmpty())
  {
    hasKey = isEntrance = isExit = false;

    // Get Dungeon Room ID
    dungeonRoomId = dungeonRoomsIds->dequeue();

    // Check if the Given Dungeon Room is Special
    for (int i = 0; i < 3; i++)
      if (distResults[i] == dungeonRoomId)
      {
        // Check which Type of Special Room is
        switch (i)
        {
        case dungeons::keyIndex:
          hasKey = true;
          break;

        case dungeons::entranceIndex:
          isEntrance = true;
          break;

        case dungeons::exitIndex:
          isExit = true;
          break;
        }

        break;
      }

    // Create Dungeon Room
    dungeonRoom = new DungeonRoom(hasKey, isEntrance, isExit);

    // Add Dungeon Room
    dungeonRooms->enqueue(dungeonRoom);
  }

  // Deallocate Memory
  delete dungeonRoomsIds;

  return dungeonRooms;
}

// Method to Get Random Dungeon Rooms Connections
QueueLinkedList<WeightedNodeEdgesPtr> *Dungeons::getDungeonRoomsConns(SingleLinkedList<int> *dungeonNodesIds, int *distResults, int numberRooms)
{
  NumberSingleLinkedList<int> *nodesEdges[numberRooms];
  WeightedNodeEdgesPtr dungeonEdges;
  int srcNodeId, dstNodeId, numberEdges, srcIndex, dstIndex, entranceId, exitId;
  bool isEntrance, isExit;

  // Get Entrance and Exit Node ID
  entranceId = distResults[dungeons::entranceIndex];
  exitId = distResults[dungeons::exitIndex];

  // Initialize Dungeon Rooms Connections Queue
  QueueLinkedList<WeightedNodeEdgesPtr> *dungeonRoomsConns = new QueueLinkedList<WeightedNodeEdgesPtr>(NULL);

  // Initialize Nodes Edges Queues
  for (int i = 0; i < numberRooms; i++)
    nodesEdges[i] = new NumberSingleLinkedList<int>(-1);

  // Get 1-3 Connections for Each Dungeon Room
  while (!dungeonNodesIds->isEmpty())
  {
    isEntrance = isExit = false;

    // Get Dungeon Node ID
    srcNodeId = dungeonNodesIds->pop();
    srcIndex = srcNodeId - dungeons::firstNodeId;

    // Get the Number of Nodes Edges to Set
    uniform_int_distribution<int> distNumberEdges(dungeons::minRoomEdge, dungeons::maxRoomEdge);
    numberEdges = distNumberEdges(rd);

    // Distribution of Nodes IDs
    uniform_int_distribution<int> distNodesIds(dungeons::firstNodeId, dungeons::firstNodeId + numberRooms - 1);

    // Check if the Node Already have Enough Edges
    while (nodesEdges[srcIndex]->getLength() < numberEdges)
    {
      // Get a Random Node ID
      dstNodeId = distNodesIds(rd);
      dstIndex = dstNodeId - dungeons::firstNodeId;

      // Check if It's the Same Node
      if (srcNodeId == dstNodeId)
        continue;

      // Check if the Given Node ID has Already been Connected with the Source Node ID
      if (nodesEdges[srcIndex]->linearSearch(dstNodeId))
        continue;

      // Check if the Source Dungeon Room is the Entrance and the Destination Dungeon Room is the Exit
      isEntrance = entranceId == srcNodeId || entranceId == dstNodeId;
      isExit = exitId == srcNodeId || exitId == dstNodeId;

      if (isEntrance && isExit)
        continue;

      // Insert Node Edge to its Corresponding Queues
      nodesEdges[srcIndex]->pushBack(dstNodeId);
      nodesEdges[dstIndex]->pushBack(srcNodeId);
    }

    // Create Dungeon Edges
    dungeonEdges = new WeightedNodeEdges(dungeons::edgeWeight, srcNodeId, nodesEdges[srcIndex]);

    // Add Dungeon Room Connections
    dungeonRoomsConns->enqueue(dungeonEdges);
  }

  // Deallocate Memory
  for (int i = 0; i < numberRooms; i++)
    delete nodesEdges[i];
  delete dungeonNodesIds;

  return dungeonRoomsConns;
}

#endif