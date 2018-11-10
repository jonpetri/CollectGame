/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: Item
 * Represent an item, which is located in a node and collectable by the player.
 * It has a weight and a value.
 * When is located in a node, the member m_holder is that node,
 * and when the player pick it, m_holder is the player.
 */
#ifndef ITEM_H
#define ITEM_H

// Includes:
#include <memory>

class ItemHolder;
class GameParameters;

class Item
{
public:
    Item();

    ~Item();

    // Getters:
    unsigned int weight() const;
    unsigned int value() const;
    std::shared_ptr<ItemHolder> holder() const;

    // Setters:
    void setWeight(unsigned int value);
    void setValue(unsigned int value);
    void setHolder(const std::shared_ptr<ItemHolder> &holder);

    // Methods:
    void setRandomWeightAndValue(const std::shared_ptr<GameParameters> & gameParameters);
    std::string consolePrint () const;


private:
    // Methods:

    // Members:
    std::shared_ptr<ItemHolder> m_holder;
    unsigned int m_iWeight;
    unsigned int m_iValue;
};

#endif // ITEM_H
