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
    int weight() const;
    int value() const;
    std::shared_ptr<ItemHolder> holder() const;

    // Setters:
    void setWeight(int value);
    void setValue(int value);
    void setHolder(const std::shared_ptr<ItemHolder> &holder);

    // Methods:
    void setRandomWeightAndValue(const std::shared_ptr<GameParameters> & gameParameters);

private:
    // Methods:

    // Members:
    std::shared_ptr<ItemHolder> m_holder;
    int m_iWeight;
    int m_iValue;
};

#endif // ITEM_H
