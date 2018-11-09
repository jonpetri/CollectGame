/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: Player
 *
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
