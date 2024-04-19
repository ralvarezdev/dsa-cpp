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
    DungeonRoomPtr data;

    // Get First Node
    while (!this->nodes->isEmpty())
    {
      // Deallocate Node's Data
      node = this->nodes->remove();
      data = node->getData();

      delete data, node;
    }
  }
};

// DungeonsGraphPtr Definition
using DungeonsGraphPtr = DungeonsGraph *;

// DUNGEONS CLASS

class Dungeons
{
private:
  // Dungeon Levels
  DungeonsGraphPtr level1 = new DungeonsGraph(dungeons::firstNodeId);
  DungeonsGraphPtr level2 = new DungeonsGraph(dungeons::firstNodeId);
  DungeonsGraphPtr level3 = new DungeonsGraph(dungeons::firstNodeId);
  int numberRooms[3] = {dungeons::level1Rooms, dungeons::level2Rooms, dungeons::level3Rooms};

  // Nodes and Edges
  NumberSingleLinkedList<int> *nodesIds[3];
  SingleLinkedList<Edges> *roomsConns[3];
  int **specialRooms = new int *[3];

  // Dungeon-related Information
  ostringstream *dungeonsInfo = new ostringstream;

  // Private Methods
  SingleLinkedList<int> *getShortestPath(int, int, int);
  int *getSpecialRooms(int);
  QueueLinkedList<int> *getDungeonRoomsId(int);
  QueueLinkedList<DungeonRoomPtr> *getDungeonRooms(QueueLinkedList<int> *, int *);
  SingleLinkedList<Edges> *getDungeonRoomsConns(NumberSingleLinkedList<int> *, int *, int);

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
  // void playGame();
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
  SingleLinkedList<Edges> *dungeonsRoomsConns[3];
  NumberSingleLinkedList<int> *dungeonsNodesIds[3];
  int **distsResults;

  distsResults = new int *[3];

  // Create Dungeon Levels
  for (int i = 0; i < 3; i++)
  {
    // Get Key, Entrance and Exit Room ID
    distsResults[i] = this->getSpecialRooms(this->numberRooms[i]);

    // Get Random Dungeon Rooms ID
    dungeonsRoomsId[i] = this->getDungeonRoomsId(this->numberRooms[i]);
    dungeonsRooms[i] = this->getDungeonRooms(dungeonsRoomsId[i], distsResults[i]);

    // Set Special Rooms
    this->specialRooms[i] = distsResults[i];
  }

  for (int i = 0; i < 3; i++)
  {
    // Add Dungeon Rooms to its Given Graph
    dungeonsNodesIds[i] = dungeonLevels[i]->addNodes(dungeonsRooms[i]);

    // Get Random Dungeon Rooms Connections
    dungeonsRoomsConns[i] = this->getDungeonRoomsConns(dungeonsNodesIds[i], distsResults[i], this->numberRooms[i]);

    // Add Dungeon Rooms Connections to its Given Graph
    dungeonLevels[i]->addEdges(dungeonsRoomsConns[i]);

    // Set Dungeon Nodes ID and Rooms Connections
    this->nodesIds[i] = dungeonsNodesIds[i];
    this->roomsConns[i] = dungeonsRoomsConns[i];
  }

  // Print Dungeons Levels
  if (setup::debugMode)
  {
    int key, entrance, exit, nRooms, roomLength, edgesLength, shortestKeyLength, shortestExitLength, totalPathLength, nodeId;
    Edge edge;
    Edges nodeEdges;
    QueueLinkedList<Edge> *edges;
    SingleLinkedList<int> *shortestKey, *shortestExit, *currPath;
    ostringstream *dungeonsInfo = this->dungeonsInfo;

    // Save Dungeons Info
    for (int levelIndex = 0; levelIndex < 3; levelIndex++)
    {
      // Get Dungeon Data
      key = distsResults[levelIndex][dungeons::keyIndex];
      entrance = distsResults[levelIndex][dungeons::entranceIndex];
      exit = distsResults[levelIndex][dungeons::exitIndex];
      nRooms = dungeonsRooms[levelIndex]->getLength();

      // Add Dungeon Level General Data to Stream
      *dungeonsInfo << "Level [" << levelIndex + 1 << "]\n"
                    << "Key Room: " << key << '\n'
                    << "Entrance Room: " << entrance << '\n'
                    << "Exit Room: " << exit << '\n'
                    << "Total Rooms: " << nRooms << '\n'
                    << "Non-special Rooms: " << nRooms - 3 << '\n'
                    << "Rooms Connections: ";

      // Add Dungeon Level Rooms Connections Data to Stream
      roomLength = dungeonsRoomsConns[levelIndex]->getLength();

      while (roomLength > 0)
      {
        // Get First Node Edges and Push it Back
        nodeEdges = dungeonsRoomsConns[levelIndex]->removeBack();

        // Get Edges for the Given Source Node ID
        edges = nodeEdges->getEdges();
        edgesLength = edges->getLength();

        while (edgesLength > 0)
        {
          // Get First Edge and Push it Back
          edge = edges->dequeue();

          // Add Node Edge Data to Stream
          *dungeonsInfo << nodeEdges->getSrcId()
                        << " -> "
                        << edge->getDstId()
                        << " [" << edge->getWeight() << ']';

          if (!(edgesLength == 1 && roomLength == 1))
            *dungeonsInfo << ", ";

          // Deallocate Memory
          delete edge;
          edgesLength--;
        }
        roomLength--;
      }

      // Add Dungeon Level Shortest Paths
      *dungeonsInfo << "\nShortest Path: ";
      currPath = shortestKey = this->getShortestPath(levelIndex, entrance, key);
      shortestExit = this->getShortestPath(levelIndex, key, exit);

      // Add Dungeon Level Shortest Paths Data to Stream
      shortestKeyLength = shortestKey->getLength();
      shortestExitLength = shortestKey->getLength();
      totalPathLength = shortestKeyLength + shortestExitLength;

      while (totalPathLength > 0)
      {
        currPath = (totalPathLength > shortestKeyLength) ? shortestKey : shortestExit;

        // Get First Node ID
        nodeId = currPath->remove();

        // Add Node ID to Stream
        if (nodeId != entrance)
          *dungeonsInfo << " -> ";

        *dungeonsInfo << nodeId;

        totalPathLength--;
      }
      *dungeonsInfo << "\n\n";
    }

    // Deallocate Memory
    delete edges, shortestKey, shortestExit;
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
  QueueLinkedList<int> *dungeonRoomsId = new QueueLinkedList<int>(dungeons::notAssigned);

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
    levelRoomsId[n] = dungeons::notAssigned;
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
SingleLinkedList<Edges> *Dungeons::getDungeonRoomsConns(NumberSingleLinkedList<int> *dungeonNodesIds, int *distResults, int numberRooms)
{
  NumberSingleLinkedList<Edge> **nodesEdges;
  Edges dungeonEdges;
  Edge nodeEdge;
  int **possibleEdges, *possibleEdgesCounter, dungeonNodesIdsLength, srcNodeId, dstNodeId, *numberEdges, srcNodeIdIndex, dstNodeIdIndex, possibleEdgeIndex, entranceId, exitId, entranceIdIndex, exitIdIndex, n, nodeEdgesLength;
  bool isEntrance, isExit;

  nodesEdges = new NumberSingleLinkedList<Edge> *[numberRooms];
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
  SingleLinkedList<Edges> *dungeonRoomsConns = new SingleLinkedList<Edges>(NULL);

  // Distribution of the Number of Edges per Node
  uniform_int_distribution<int> distNumberEdges(dungeons::minRoomEdge, dungeons::maxRoomEdge);

  for (int i = 0; i < numberRooms; i++)
  {
    possibleEdgesCounter[i] = 0;

    // Initialize Node Edges Queues
    nodesEdges[i] = new NumberSingleLinkedList<Edge>(NULL);

    // Get the Number of Nodes Edges to Set
    numberEdges[i] = distNumberEdges(rd);

    // Initialize the Given Dynamic Array
    possibleEdges[i] = new int[numberRooms];

    // Fill Possible Edges with 'dungeons::notAssigned'
    fill(possibleEdges[i], possibleEdges[i] + numberRooms, dungeons::notAssigned);

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
      nodeEdgesLength = nodesEdges[srcNodeIdIndex]->getLength();
      while (nodeEdgesLength > 0)
      {
        // Get Edge and Push it Back
        nodeEdge = nodesEdges[srcNodeIdIndex]->removeBack();

        // Check the Given Edge
        if (nodeEdge->getDstId() == dstNodeId && nodeEdge->getWeight() == dungeons::edgeWeight)
          continue;

        nodeEdgesLength--;
      }

      // Insert Node Edge to its Corresponding Queues
      nodesEdges[srcNodeIdIndex]->pushBack(new WeightedNodeEdge(dstNodeId, dungeons::edgeWeight));
      nodesEdges[dstNodeIdIndex]->pushBack(new WeightedNodeEdge(srcNodeId, dungeons::edgeWeight));

      // Move Possible Edges
      for (int i = possibleEdgeIndex; i < possibleEdgesCounter[srcNodeIdIndex]; i++)
        possibleEdges[srcNodeIdIndex][i] = possibleEdges[srcNodeIdIndex][i + 1];

      possibleEdges[srcNodeIdIndex][possibleEdgesCounter[srcNodeIdIndex]] = dungeons::notAssigned;
      possibleEdgesCounter[srcNodeIdIndex]--;
    }

    dungeonNodesIdsLength--;
  }

  for (int i = 0; i < numberRooms; i++)
  {
    // Create Dungeon Edges
    dungeonEdges = new WeightedNodeEdges(i + dungeons::firstNodeId, nodesEdges[i]);

    // Add Dungeon Room Connections
    dungeonRoomsConns->pushBack(dungeonEdges);
  }

  // Deallocate Memory
  for (int i = 0; i < numberRooms; i++)
  {
    delete nodesEdges[i];
    delete[] possibleEdges[i];
  }

  delete[] possibleEdges, possibleEdgesCounter, numberEdges;

  return dungeonRoomsConns;
}

// Method to Get the Shortest Path between Two Nodes
SingleLinkedList<int> *Dungeons::getShortestPath(int levelIndex, int startNodeId, int endNodeId)
{
  bool *currVisitedNodes;
  int *currUnvisitedNodesId, currIndex, index, nodeId, prevNodeId, unvisitedNodeId, nRooms, currNodeId, currDstId, currWeight, visitedNode, nodeEdgesLength, currEdgesLength, visitedNodesLength, unvisitedNodesLength, counter;
  Edge currEdge;
  Edges currNodeEdges;
  SingleLinkedList<Edges> *nodeEdges;
  QueueLinkedList<Edge> *currEdges;
  SingleLinkedList<int> *path;
  SingleLinkedList<int> *unvisitedNodes, *visitedNodes, *prevNodeIds;
  SingleLinkedList<Edge> *shortestDistances;

  nRooms = this->numberRooms[levelIndex];
  nodeEdges = this->roomsConns[levelIndex];

  // Initialize Required Queues
  unvisitedNodes = new SingleLinkedList<int>(dungeons::notAssigned);
  visitedNodes = new SingleLinkedList<int>(dungeons::notAssigned);
  path = new SingleLinkedList<int>(dungeons::notAssigned);
  shortestDistances = new SingleLinkedList<Edge>(NULL);
  prevNodeIds = new SingleLinkedList<int>(dungeons::notAssigned);

  // Fill Shortest Distances, Visited, Unvisited Nodes
  visitedNodes->pushBack(startNodeId);
  shortestDistances->pushBack(new WeightedNodeEdge(startNodeId, 0));

  currNodeId = startNodeId;
  currWeight = 0;
  currIndex = 0;

  for (int i = 0; i < nRooms; i++)
  {
    nodeId = this->nodesIds[levelIndex]->removeBack();

    if (nodeId != startNodeId)
      unvisitedNodes->push(nodeId);
  }

  // Apply Dijkstra's Algoritm
  while (currNodeId != endNodeId)
  {
    nodeEdgesLength = nodeEdges->getLength();

    // Get Current Node Edges
    for (int i = 0; i < nodeEdgesLength; i++)
    {
      currNodeEdges = nodeEdges->removeBack();

      if (currNodeEdges->getSrcId() == currNodeId)
        break;
    }

    // Get Edges
    currEdges = currNodeEdges->getEdges();
    currEdgesLength = currEdges->getLength();

    // Check All Nodes as Unvisited
    currVisitedNodes = new bool[currEdgesLength];
    fill(currVisitedNodes, currVisitedNodes + currEdgesLength, false);

    visitedNodesLength = visitedNodes->getLength();
    counter = 0;

    while (visitedNodesLength > 0)
    {
      visitedNode = visitedNodes->removeBack();

      // Check if there's a Visited Node
      for (int i = 0; i < currEdgesLength; i++)
      {
        if (currVisitedNodes[i])
          continue;

        currEdge = currEdges->removeBack();

        if (visitedNode == currEdge->getDstId())
        {
          currVisitedNodes[i] = true;
          counter++;
        }
      }

      visitedNodesLength--;

      // Deallocate Memory
      delete[] currVisitedNodes;
    }

    currUnvisitedNodesId = new int[counter];
    counter = 0;

    for (int i = 0; i < currEdgesLength; i++)
    {
      if (currVisitedNodes[i])
        continue;

      // Add Unvisited Nodes
      currEdge = currEdges->removeBack();
      currDstId = currEdge->getDstId();
      currUnvisitedNodesId[counter++] = currDstId;

      // Add as Visited Nodes
      visitedNodes->push(currDstId);
      shortestDistances->push(new WeightedNodeEdge(currDstId, currEdge->getWeight() + currWeight));
      prevNodeIds->push(currNodeId);
    }

    // Removed Unvisited Nodes
    unvisitedNodesLength = unvisitedNodes->getLength();
    index = 0;

    while (unvisitedNodesLength > 0)
    {
      unvisitedNodeId = unvisitedNodes->removeBack();

      for (int i = 0; i < counter; i++)
        if (unvisitedNodeId == currUnvisitedNodesId[i])
        {
          unvisitedNodes->removeAt(index++);
          break;
        }

      unvisitedNodesLength--;
    }

    // Get Current and Previous Node ID
    currNodeId = visitedNodes->get(++currIndex);
    prevNodeId = visitedNodes->get(currIndex);

    // Get Current Weight
    currWeight = shortestDistances->get(currIndex)->getWeight();

    // Deallocate Memory
    delete[] currUnvisitedNodesId;
  }

  // Get Path
  path->push(currNodeId);

  while (currIndex > 0)
  {
    // Add Nodes that are Part of the Shortest Path
    nodeId = visitedNodes->pop();
    prevNodeId = prevNodeIds->pop();

    if (nodeId == prevNodeId)
    {
      // Add Node
      path->push(nodeId);
      currNodeId = nodeId;
    }
    currIndex--;
  }

  // Deallocate Memory
  delete unvisitedNodes, shortestDistances, prevNodeIds;

  return path;
}

/*
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
*/

#endif