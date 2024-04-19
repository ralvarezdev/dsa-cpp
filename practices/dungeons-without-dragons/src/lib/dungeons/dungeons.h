#include <algorithm>
#include <sstream>
#include <random>
#include <iostream>

#include "../../../../../data-structures/undirected-graphs/base.h"
#include "../../../../../data-structures/single-linked-lists/number.h"
#include "../terminal/ansiEsc.h"
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

    // Get First Node
    while (!this->nodes->isEmpty())
    {
      // Deallocate Node's Data
      node = this->nodes->remove();
      delete node->data, node;
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
  NumberSingleLinkedList<int> *nodesIds[3];
  SingleLinkedList<WeightedNodeEdgesPtr> *roomsConns[3];
  int **specialRooms;
  ostringstream *dungeonsInfo = new ostringstream;

  // Private Methods
  int *getSpecialRooms(int);
  QueueLinkedList<int> *getDungeonRoomsId(int);
  QueueLinkedList<DungeonRoomPtr> *getDungeonRooms(QueueLinkedList<int> *, int *);
  SingleLinkedList<WeightedNodeEdgesPtr> *getDungeonRoomsConns(NumberSingleLinkedList<int> *, int *, int);

public:
  // Constructors
  Dungeons();

  // Destructor
  virtual ~Dungeons()
  {
    // Deallocate Memory
    delete level1, level2, level3, dungeonsInfo;

    for (int i = 0; i < 3; i++)
    {
      // Deallocate Dungeon Special Rooms Nodes ID
      delete[] specialRooms[i];

      // Deallocate Dungeon Rooms Nodes and Edges
      delete nodesIds[i], roomsConns[i];
    }
    delete[] specialRooms;
  }

  // Public Methods
  void playGame();
  void printDungeonsInfo() { cout << this->dungeonsInfo->str(); };
};

// DUNGEON ROOM CLASS

// Dungeon Room Class Constructors
DungeonRoom::DungeonRoom(bool hasKey, bool isEntrance, bool isExit)
{
  this->hasKey = hasKey;
  this->isEntrance = isEntrance;
  this->isExit = isExit;
}

// DUNGEON CLASS

// Dungeon Class Constructors
Dungeons::Dungeons()
{
  UndirGraphPtr<DungeonRoomPtr> dungeonLevels[3] = {this->level1, this->level2, this->level3};
  QueueLinkedList<int> *dungeonsRoomsId[3];
  QueueLinkedList<DungeonRoomPtr> *dungeonsRooms[3];
  SingleLinkedList<WeightedNodeEdgesPtr> *dungeonsRoomsConns[3];
  NumberSingleLinkedList<int> *dungeonsNodesIds[3];
  int **distsResults;
  int numberRooms[3] = {dungeons::level1Rooms, dungeons::level2Rooms, dungeons::level3Rooms};

  distsResults = new int *[3];

  // Create Dungeon Levels
  for (int i = 0; i < 3; i++)
  {
    // Get Key, Entrance and Exit Room ID
    distsResults[i] = this->getSpecialRooms(numberRooms[i]);

    // Get Random Dungeon Rooms ID
    dungeonsRoomsId[i] = this->getDungeonRoomsId(numberRooms[i]);
    dungeonsRooms[i] = this->getDungeonRooms(dungeonsRoomsId[i], distsResults[i]);

    // Set Special Rooms
    this->specialRooms[i] = distsResults[i];
  }

  for (int i = 0; i < 3; i++)
  {
    // Add Dungeon Rooms to its Given Graph
    dungeonsNodesIds[i] = dungeonLevels[i]->addNodes(dungeonsRooms[i]);

    // Get Random Dungeon Rooms Connections
    dungeonsRoomsConns[i] = this->getDungeonRoomsConns(dungeonsNodesIds[i], distsResults[i], numberRooms[i]);

    // Add Dungeon Rooms Connections to its Given Graph
    dungeonLevels[i]->addEdges(dungeonsRoomsConns[i]);

    // Set Dungeon Nodes ID and Rooms Connections
    this->nodesIds[i] = dungeonsNodesIds[i];
    this->roomsConns[i] = dungeonsRoomsConns[i];
  }

  // Print Dungeons Levels
  if (setup::debugMode)
  {
    int key, entrance, exit, nRooms, roomLength, dstsIdsLength, edge;
    WeightedNodeEdgesPtr nodeEdges;
    QueueLinkedList<int> *dstsIds;
    ostringstream *dungeonsInfo = this->dungeonsInfo;

    // Save Dungeons Info
    for (int j = 0; j < 3; j++)
    {
      // Get Dungeon Data
      key = distsResults[j][dungeons::keyIndex];
      entrance = distsResults[j][dungeons::entranceIndex];
      exit = distsResults[j][dungeons::exitIndex];
      nRooms = dungeonsRooms[j]->getLength();

      // Add Dungeon Level General Data to Stream
      *dungeonsInfo << "Level [" << j + 1 << "]\n"
                    << "Key Room: " << key << '\n'
                    << "Entrance Room: " << entrance << '\n'
                    << "Exit Room: " << exit << '\n'
                    << "Total Rooms: " << nRooms << '\n'
                    << "Non-special Rooms: " << nRooms - 3 << '\n'
                    << "Rooms Connections: ";

      // Add Dungeon Level Rooms Connections Data to Stream
      roomLength = dungeonsRoomsConns[j]->getLength();

      while (roomLength > 0)
      {
        // Get First Node Edges and Push it Back
        nodeEdges = dungeonsRoomsConns[j]->removeBack();

        // Get Destinations IDs for the Given Source Node ID
        dstsIds = nodeEdges->getDstsId();
        dstsIdsLength = dstsIds->getLength();

        while (dstsIdsLength > 0)
        {
          // Get First Edge and Push it Back
          edge = dstsIds->removeBack();

          // Add Node Edge Data to Stream
          *dungeonsInfo << nodeEdges->getSrcId() << " -> " << edge;

          if (!(dstsIdsLength == 1 && roomLength == 1))
            *dungeonsInfo << ", ";

          dstsIdsLength--;
        }
        roomLength--;
      }

      *dungeonsInfo << "\n\n";
    }
  }
}

// Method to Get the Distribution Results of the Special Rooms
int *Dungeons::getSpecialRooms(int numberRooms)
{
  bool occupied, *levelRange;
  int *distResults, index;

  levelRange = new bool[numberRooms];
  distResults = new int[3];

  // Fill Arrays with 'False'
  fill(levelRange, levelRange + numberRooms, false);

  // Create Distributions
  uniform_int_distribution<int> distLevel(0, numberRooms - 1);

  // Get Key, Entrance and Exit Room ID
  for (int i = 0; i < 3; i++)
    do
    {
      // Get Random Number
      index = distLevel(rd);

      // Store Random Index
      occupied = levelRange[index];
      if (!occupied)
      {
        distResults[i] = index;
        levelRange[index] = true;
      }
    } while (occupied);

  // Deallocate Memory
  delete[] levelRange;

  return distResults;
}

// Method to Get the Dungeon Rooms ID for a Given Level
QueueLinkedList<int> *Dungeons::getDungeonRoomsId(int numberRooms)
{
  int *levelRoomsId, index, toSwap, n;

  levelRoomsId = new int[numberRooms];

  // Initialize Dungeon Rooms ID Queue
  QueueLinkedList<int> *dungeonRoomsId = new QueueLinkedList<int>(-1);

  // Fill Level Rooms ID
  for (int i = 0; i < numberRooms; i++)
    levelRoomsId[i] = i;

  // Get Dungeon Room in Random Order
  for (int i = 0; i < numberRooms; i++)
  {
    n = numberRooms - i - 1;
    uniform_int_distribution<int> distLevel(0, n);

    // Get Random Number
    index = distLevel(rd);

    // Store Random Index
    dungeonRoomsId->enqueue(levelRoomsId[index]);

    // Remove the Given Room ID from Level Rooms ID
    toSwap = levelRoomsId[n];
    levelRoomsId[n] = -1;
    levelRoomsId[index] = toSwap;
  }

  // Deallocate Memory
  delete[] levelRoomsId;

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
SingleLinkedList<WeightedNodeEdgesPtr> *Dungeons::getDungeonRoomsConns(NumberSingleLinkedList<int> *dungeonNodesIds, int *distResults, int numberRooms)
{
  NumberSingleLinkedList<int> **nodesEdges;
  WeightedNodeEdgesPtr dungeonEdges;
  int **possibleEdges, *possibleEdgesCounter, dungeonNodesIdsLength, srcNodeId, dstNodeId, *numberEdges, srcNodeIdIndex, dstNodeIdIndex, possibleEdgeIndex, entranceId, exitId, entranceIdIndex, exitIdIndex, n;
  bool isEntrance, isExit;

  nodesEdges = new NumberSingleLinkedList<int> *[numberRooms];
  possibleEdges = new int *[numberRooms];
  possibleEdgesCounter = new int[numberRooms];
  numberEdges = new int[numberRooms];

  dungeonNodesIdsLength = dungeonNodesIds->getLength();

  // Get Entrance and Exit Node ID
  entranceId = distResults[dungeons::entranceIndex];
  entranceIdIndex = entranceId - dungeons::firstNodeId;

  exitId = distResults[dungeons::exitIndex];
  exitIdIndex = exitId - dungeons::firstNodeId;

  // Initialize Dungeon Rooms Connections Queue
  SingleLinkedList<WeightedNodeEdgesPtr> *dungeonRoomsConns = new SingleLinkedList<WeightedNodeEdgesPtr>(NULL);

  // Distribution of the Number of Edges per Node
  uniform_int_distribution<int> distNumberEdges(dungeons::minRoomEdge, dungeons::maxRoomEdge);

  for (int i = 0; i < numberRooms; i++)
  {
    possibleEdgesCounter[i] = 0;

    // Initialize Node Edges Queues
    nodesEdges[i] = new NumberSingleLinkedList<int>(-1);

    // Get the Number of Nodes Edges to Set
    numberEdges[i] = distNumberEdges(rd);

    // Initialize the Given Dynamic Array
    possibleEdges[i] = new int[numberRooms];

    // Fill Possible Edges with '-1'
    fill(possibleEdges[i], possibleEdges[i] + numberRooms, -1);

    // Get the Possible Edges per Node
    for (int j = 0; j < numberRooms; j++)
    {
      // Node can not be Connected with Itself
      if (i == j)
        continue;

      // Entrance Node can not be Connected with the Exit Node
      else if (i == entranceIdIndex && j == exitIdIndex)
        continue;

      else if (i == exitIdIndex && j == entranceIdIndex)
        continue;

      // Set Possible Node Connection ID
      possibleEdges[i][possibleEdgesCounter[i]] = j + dungeons::firstNodeId;
      possibleEdgesCounter[i]++;
    }
  }

  // Move Entrance and Exit Node ID First
  dungeonNodesIds->linearSearch(entranceId);
  dungeonNodesIds->linearSearch(exitId);

  // Get 1-3 Connections for Each Dungeon Room
  while (dungeonNodesIdsLength > 0)
  {
    // Get Dungeon Node ID and Push it Back
    srcNodeId = dungeonNodesIds->removeBack();
    srcNodeIdIndex = srcNodeId - dungeons::firstNodeId;

    // Check if the Node Already have Enough Edges
    while (nodesEdges[srcNodeIdIndex]->getLength() < numberEdges[srcNodeIdIndex])
    {
      // Distribution of Nodes IDs
      uniform_int_distribution<int> distNodesIdIndexes(0, possibleEdgesCounter[srcNodeIdIndex] - 1);

      // Get a Random Node ID
      possibleEdgeIndex = distNodesIdIndexes(rd);
      dstNodeId = possibleEdges[srcNodeIdIndex][possibleEdgeIndex];
      dstNodeIdIndex = dstNodeId - dungeons::firstNodeId;

      // Check if the Destination Node ID Already has the Maximum Number Enough Connections
      if (nodesEdges[dstNodeIdIndex]->getLength() >= dungeons::maxRoomEdge)
        continue;

      // Check if the Given Node ID has Already been Connected with the Source Node ID
      if (nodesEdges[srcNodeIdIndex]->linearSearch(dstNodeId))
        continue;

      // Insert Node Edge to its Corresponding Queues
      nodesEdges[srcNodeIdIndex]->pushBack(dstNodeId);
      nodesEdges[dstNodeIdIndex]->pushBack(srcNodeId);

      // Move Possible Edges
      for (int i = possibleEdgeIndex; i < possibleEdgesCounter[srcNodeIdIndex]; i++)
        possibleEdges[srcNodeIdIndex][i] = possibleEdges[srcNodeIdIndex][i + 1];

      possibleEdges[srcNodeIdIndex][possibleEdgesCounter[srcNodeIdIndex]] = -1;
      possibleEdgesCounter[srcNodeIdIndex]--;
    }
  }

  for (int i = 0; i < numberRooms; i++)
  {
    // Create Dungeon Edges
    dungeonEdges = new WeightedNodeEdges(dungeons::edgeWeight, i + dungeons::firstNodeId, nodesEdges[i]);

    // Add Dungeon Room Connections
    dungeonRoomsConns->pushBack(dungeonEdges);
  }

  // Deallocate Memory
  for (int i = 0; i < numberRooms; i++)
    delete[] nodesEdges[i], possibleEdges[i];

  delete[] possibleEdges, possibleEdgesCounter, numberEdges;

  return dungeonRoomsConns;
}

// Method to Play the Dungeons Without Dragons Game
void Dungeons::playGame()
{
  SingleLinkedList<int> *conns;
  int currLevel = 0, currRoom = this->specialRooms[currLevel][dungeons::entranceIndex];
  bool hasKey = false;

  while (currLevel < 4)
  {
    ostringstream title, msg;

    // Get Dungeon Title
    title << "Dungeon " << currLevel + 1 << ". Room " << currRoom;

    // Get Possible Connections
    printTitle(title.str());

    msg << "\nPossible Connections: ";
  }
}

#endif