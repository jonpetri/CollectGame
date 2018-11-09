/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: Player
 * Represent the player, witch is located in the node "currentNode".
 * When the player switch from a node to another he is in charge of change nodes "HostThePlayer" status.
 * The class doesn't know which item had collected the player.
 */
#ifndef PLAYER_H
#define PLAYER_H

// Includes:
#include "model/item/itemholder.h"
#include <memory>

class Node;
class Player : public ItemHolder
{
public:
    Player();

    ~Player();

    // Getters:
    std::shared_ptr<Node> currentNode() const;

    // Setters:
    void setCurrentNode(const std::shared_ptr<Node> &value);

    // Methods:


private:
    // Methods:

    // Members:
    std::shared_ptr<Node> m_currentNode;

};

#endif // PLAYER_H
