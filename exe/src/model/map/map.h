/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: Map
 * The map is in charge of nodes position in a X/Y grid and the edges between them.
 * It creates a random map, give access to the nodes by them xy index, through Map::grid()->
 * It indicates if a move of the player is possible,
 * letting know if connection between 2 nodes exists, through Map::graph()->
 * It provide a string-view of the graph, printable in the console.
 */
#ifndef MAP_H
#define MAP_H

// Includes:
#include <vector>
#include <memory>

#include "model/node/node.h"
#include "array2d.h"
#include "nodegraph.h"

class GameParameters;

class Map : public std::enable_shared_from_this<Map>
{
public:

    // The class has enable_shared_from_this,
    // so we have to make sure the class will always be stored in a std::shared_ptr<>.
    // use Map::create() instead.
    Map();
    ~Map();
public:
    static std::shared_ptr<Map> createObject();

    // Getters:
    const std::shared_ptr<NodeGraph> graph() const;
    const std::shared_ptr<Array2d<std::shared_ptr<Node> >> grid() const;

    // Setters:

    // Methods:
    void createNewMap(const std::shared_ptr<GameParameters> & gameParameters);
    std::string getMapsConsolePrint();

    // slots
    void addToCandidatesNodes(const std::shared_ptr<Node> & n);

private:
    // Methods:
    std::string edgeCharacterRightOfNode(const std::shared_ptr<Node> & n);
    std::string edgeCharacterBelowOfNode(const std::shared_ptr<Node> & n);
    std::string edgeCharacterDiagonaleOfNode(const std::shared_ptr<Node> & n);
    static std::string getNumberInTwoChar(int iNumber);
    // Members:
    std::shared_ptr<Array2d<std::shared_ptr<Node>>> m_grid;
    std::shared_ptr<NodeGraph> m_graph;
    std::vector<std::shared_ptr<Node>> m_candidateNodes;
};

#endif // MAP_H
