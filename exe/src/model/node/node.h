/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: Node
 * A node of map, where the player can find Items.
 * It can have 3 states: 1- Absent, 2- Candidate (Candidate to be existent) and  3- Existing
 *

 * The state diagram is:
 *
 * Absent -----> Candidate -----> Existing
 *     \____________________________^
 *
 * When it become existent, the signal setAdjacentsAsCandidate is called,
 * and :
 *   - all the adjacent absent nodes become Candidate.
 *   - The  adjacent candidate do not change of state
 *   - The existing's keep being existent, following the state diagram.
 *
 * When the class become candidate (that happen only once in it live time), the signal addToCandidateList is called.
 */
#ifndef NODE_H
#define NODE_H

// Includes:
#include "model/item/itemholder.h"
#include <memory>
#include <boost/signals2.hpp>
class NodeState;

class Node : public ItemHolder
           , public std::enable_shared_from_this<Node>
{
private:

    // The class has enable_shared_from_this,
    // so we have to make sure the class will always be stored in a std::shared_ptr<Node>.
    // use Node::create() instead.
    Node();
    ~Node();
public:
    static std::shared_ptr<Node> create();

    // Getters:
    int x() const;
    int y() const;
    unsigned long graphIndex() const;
    bool hostThePlayer() const;


    // Setters:
    void setX(int iX);
    void setY(int iY);
    void setGraphIndex(unsigned long value);
    void setHostThePlayer(bool bStatus);

    // Signals
    boost::signals2::signal<void (const std::shared_ptr<Node> &)> addToCandidateList;
    boost::signals2::signal<void (const std::shared_ptr<Node> &)> removeFromCandidateList;
    boost::signals2::signal<void (const std::shared_ptr<Node> &)> setAdjacentsAsCandidate;

    // Methods:
    void setIntoCandidateState();
    void setIntoExistingState();

    bool exists() const;
    bool isCandidate() const;
    bool isAbsent() const;

    std::string consolePrintCharacter() const;
private:
    // Methods:

    // Members:
    int m_iX;
    int m_iY;
    unsigned long m_lGraphIndex;
    bool m_bHostThePlayer;

    std::unique_ptr<NodeState> m_state;

    friend class AbsentNode;
    friend class CandidateNode;
    friend class ExistingNode;
    void setState(std::unique_ptr<NodeState> &state);

};

#endif // NODE_H
