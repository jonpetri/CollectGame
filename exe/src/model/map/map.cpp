#include "map.h"

#include <random>


#include "model/game/gameparameters.h"
#include "model/node/node.h"

//-----------------------------------------------------------------------------------------------------------------------
// Map :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
Map::Map()
    : m_grid(std::make_shared<NodeGrid>())
    , m_graph(std::make_shared<NodeGraph>())
    , m_candidateNodes()
{

}
Map::~Map()
{

}
/**
 * The class has enable_shared_from_this,
 * so we have to make sure the class will always be stored in a std::shared_ptr<>.
 * The constructor is private, must use that method instead.
 * @return properly build Class
 */
std::shared_ptr<Map> Map::createObject()
{
    struct make_shared_enabler : public Map {};
    return std::make_shared<make_shared_enabler>();
}

//-----------------------------------------------------------------------------------------------------------------------
// Map :: Getters
//-----------------------------------------------------------------------------------------------------------------------

const std::shared_ptr<Array2d<std::shared_ptr<Node> > > Map::grid() const
{
    return m_grid;
}

const std::shared_ptr<NodeGraph> Map::graph() const
{
    return m_graph;
}

//-----------------------------------------------------------------------------------------------------------------------
// Map :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// Map :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Create a new random map, according the parameters of gameParameters
 * @param [in] gameParameters
 */
void Map::createNewMap(const std::shared_ptr<GameParameters> & gameParameters)
{
    int iGridSize =  gameParameters->gridSideSize();

    // clean of former game
    // -------------
    m_candidateNodes.clear();
    m_graph->clear();
    m_grid->clear();

    // Grid creation + Insertion off all the node in the graph
    // ------------------------------------------------------
    // The grid is a square of gridSize x gridSize

    m_grid->redimColSize(iGridSize);
    m_grid->redimRowSize(iGridSize);
    for (int x = 0 ; x < iGridSize ; ++x)
    {
        for (int y = 0 ; y < iGridSize ; ++y)
        {
            std::shared_ptr<Node> newNode = Node::create();
            newNode->setAdjacentsAsCandidate.connect( boost::bind( &NodeGraph::setAdjacentsCandidate,  m_graph, _1));
            newNode->addToCandidateList.connect( boost::bind( &Map::addToCandidatesNodes, shared_from_this(), _1));
            newNode->removeFromCandidateList.connect( boost::bind( &Map::remomoveFromCandidatesNodes, shared_from_this(), _1));
            newNode->setX(x);
            newNode->setY(y);

            m_grid->set(x, y, newNode);
            m_graph->addIsolateNode(newNode);
        }
    }

    // Connection of the physically adjacent nodes
    // ------------------------------------------------------
    // The adjacent nodes in the grid are linked in the graph
    // e.g. (x=0, y=0) with (x=1, y=0)

    for (int x = 0 ; x < iGridSize ; ++x)
    {
        for (int y = 0 ; y < iGridSize ; ++y)
        {
            if (y > 0)
                m_graph->connectNodes(m_grid->get(x, y), m_grid->get(x, y - 1));

            if (x > 0)
            {
                m_graph->connectNodes(m_grid->get(x, y), m_grid->get(x - 1, y));

                if ( y > 0) // and x > 0
                {
                    m_graph->connectNodes(m_grid->get(x, y), m_grid->get(x - 1, y -1));

                    //if (y < iGridSize -1) // and x > 0, y > 0
                    m_graph->connectNodes(m_grid->get(x -1 , y), m_grid->get(x, y - 1));
                }
            }
        }
    }

//    std::cout << this->consolePrint(true) << std::endl;
//    std::cout << "edge count= " << m_graph->edgeCount() << std::endl;


    // Choice of the first existing node randomly
    // ------------------------------------------------------
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> randomDistributionXY(0, iGridSize-1);
    int iXFirstNode =  randomDistributionXY(gen);
    int iYFirstNode =  randomDistributionXY(gen);
    m_grid->get(iXFirstNode, iYFirstNode)->setIntoExistingState(); // this changes the adjacent nodes into the 'Candidate' state, thought node's signal

    // Creation of X existing nodes
    // ---------------------
    // In order to make sure that all the created nodes can be connected (neighbour from each other)
    // the nodes to be created are chosen among the candidate nodes.
    // The candidate nodes are the nodes at the cliff / limit between created nodes and absent nodes.
    for (int i = 0 ; i < gameParameters->nodeCount() - 1 ; ++i)
    {
        std::uniform_int_distribution<> randomDistributionCandidates(0, static_cast<int>(m_candidateNodes.size()) - 1);
        m_candidateNodes[static_cast<unsigned int>(randomDistributionCandidates(gen))]->setIntoExistingState();
            // -> this changes the adjacent nodes into the 'Candidate' state, thought node's signal
    }



    // Remove of edges linked to absent and candidate nodes in the graph
    // -----------------------------------------------------------------
    m_graph->removeAbsentNodesAndEdges();



    // Remove of random edges
    // ----------------------
    // Edges are removed to try to reach the number target.
    // The removable edges count is limited because the graph has to remain connected.
    m_graph->removeNonBridgeEdges(gameParameters->edgeTargetCount());

}

/**
 * Retrieve the string to be displayed in the console in order to show the graph to the user.
 * @param [in] bPrintNodeIds If true, don ot print "O" for nodes, but ID's (useful for debug)
 * @return string of the view
 */
std::string Map::consolePrint(bool bPrintNodeIds) const
{
    /* The return print is:

      X 1   2   3   4         //<- sXindex  (header)
    Y  ----------------> X    //<- sXLine   (header)
    1 |     O   O – @         //<- sNodeLine y=1  (grid)
      |     | X | /           //<- sEdgeLine y=1  (grid)
    2 | O – O – O             //<- sNodeLine y=2  (grid)
      |     |    \            //<- sEdgeLine y=2  (grid)
    3 |     O     O           // ++y  ...
      ▽
      Y                         */

    std::string sConsolePrint("");
    std::string sXindex("");
    std::string sXLine("");
    std::string sNodeLine("");
    std::string sEdgeLine("");

    if (bPrintNodeIds)
        m_graph->updateNodeIds();

    // the header
    // ----------
    sXindex += "  X ";
    sXLine  += "Y  -";
    for (int x = 0 ; x < m_grid->size() ; ++x)
    {
        sXindex += getNumberInTwoChar(x+1) + "  ";
        sXLine += "----";
    }
    sXLine  += "> X";

    sConsolePrint += sXindex + "\n";
    sConsolePrint += sXLine + "\n";

    // the grid
    // ----------
    std::shared_ptr<Node> node;

    for (int y = 0 ; y < m_grid->size() - 1 ; ++y)
    {
        sNodeLine.clear();
        sEdgeLine.clear();
        sNodeLine += getNumberInTwoChar(y+1) + "| ";
        sEdgeLine  += "  | ";
        for (int x = 0 ; x < m_grid->size() -1 ; ++x)
        {
            node = m_grid->get(x,y);

            if (bPrintNodeIds)
                sNodeLine += getNumberInTwoChar(static_cast<int>(node->graphIndex()))  + edgeCharacterRightOfNode(node);
            else
                sNodeLine += node->consolePrintCharacter()  + edgeCharacterRightOfNode(node);

            sEdgeLine += edgeCharacterBelowOfNode(node) + edgeCharacterDiagonaleOfNode(node);
        }
        node = m_grid->get(m_grid->size() - 1 , y);

        if (bPrintNodeIds)
            sNodeLine += getNumberInTwoChar(static_cast<int>(node->graphIndex())) ;
        else
            sNodeLine += node->consolePrintCharacter() ;

        sEdgeLine += edgeCharacterBelowOfNode(node);

        sConsolePrint += sNodeLine + "\n";
        sConsolePrint += sEdgeLine + "\n";
    }

    // last row of node
    // -----------------
    int y = static_cast<int>(m_grid->size() - 1);
    sNodeLine.clear();
    sNodeLine += getNumberInTwoChar(y + 1) + "| ";

    for (int x = 0 ; x < m_grid->size() -1 ; ++x)
    {
        node = m_grid->get(x,y);

        if (bPrintNodeIds)
            sNodeLine += getNumberInTwoChar(static_cast<int>(node->graphIndex()))  + edgeCharacterRightOfNode(node);
        else
            sNodeLine += node->consolePrintCharacter()  + edgeCharacterRightOfNode(node);
    }
    node = m_grid->get(m_grid->size() - 1 , y);

    if (bPrintNodeIds)
        sNodeLine +=getNumberInTwoChar(static_cast<int>(node->graphIndex())) ;
    else
        sNodeLine += node->consolePrintCharacter() ;

    // end arrow of Y index
    // ---------------------
    sConsolePrint += sNodeLine + "\n";
    sConsolePrint += "  ▽\n";
    sConsolePrint += "  Y\n";

    return sConsolePrint;
}

/**
 * Add the node to the member list m_candidateNodes.
 * The candidate nodes are the nodes at the cliff / limit between created nodes and absent nodes.
 * the nodes to be created are chosen among the candidate nodes.
 * @param [in] n node
 */
void Map::addToCandidatesNodes(const std::shared_ptr<Node> &n)
{
    m_candidateNodes.push_back(n);
}

/**
 * remoce the node from the member list m_candidateNodes.
 * The candidate nodes are the nodes at the cliff / limit between created nodes and absent nodes.
 * the nodes to be created are chosen among the candidate nodes.
 * @param [in] n node
 */
void Map::remomoveFromCandidatesNodes(const std::shared_ptr<Node> &n)
{
    std::vector<std::shared_ptr<Node>>::iterator it;
    for(it = m_candidateNodes.end()-1; it+1 != m_candidateNodes.begin(); it-- )
    {
        if(*it == n)
            m_candidateNodes.erase(it);
    }
}

/**
 * (private)
 * Retrieve the edge character to be displayed right to a node.
 * @param [in] n node
 * @return " - " or "   "
 */
std::string Map::edgeCharacterRightOfNode(const std::shared_ptr<Node> &n) const
{
    std::shared_ptr<Node> adjacentRightNode = m_grid->get(n->x() + 1, n->y());
    if(m_graph->edgeExists(n, adjacentRightNode) == true)
        return " - ";
    else
        return "   ";
}
/**
 * (private)
 * Retrieve the edge character to be displayed below a node
 * @param [in] n node
 * @return "|" or " "
 */
std::string Map::edgeCharacterBelowOfNode(const std::shared_ptr<Node> &n) const
{
    std::shared_ptr<Node> adjacentBelowNode = m_grid->get(n->x(), n->y() + 1);
    if(m_graph->edgeExists(n, adjacentBelowNode) == true)
        return "|";
    else
        return " ";
}

/**
 * (private)
 * Retrieve the edge character to be displayed at the right/below a node
 * @param [in] n node
 * @return " X ", " / ", " \ " or "   "
 */
std::string Map::edgeCharacterDiagonaleOfNode(const std::shared_ptr<Node> &n) const
{
    std::shared_ptr<Node> adjacentDiagonalNode = m_grid->get(n->x() + 1, n->y() + 1);
    std::shared_ptr<Node> adjacentBelowNode = m_grid->get(n->x(), n->y() + 1);
    std::shared_ptr<Node> adjacentRightNode = m_grid->get(n->x() + 1, n->y());

    bool bNeedAntiSlash = m_graph->edgeExists(n, adjacentDiagonalNode);
    bool bNeedSlash = m_graph->edgeExists(adjacentBelowNode, adjacentRightNode);
    if( bNeedSlash and bNeedAntiSlash)
        return " X ";
    else if( bNeedSlash )
        return " / ";
    else if( bNeedAntiSlash )
        return " \\ ";
    else
        return "   ";
}

/**
 * (private)
 * Retrieve the number in string of 2 characters
 * @param [in] iNumber
 * @return string
 */
std::string Map::getNumberInTwoChar(int iNumber)
{
    std::string sResult;
    sResult = std::to_string(iNumber);
    while (sResult.length() < 2)
    {
        sResult= sResult + " " ;
    }
    return sResult;
}


