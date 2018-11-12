/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: Items
 * The class contains a batch of Items.
 * It can calculate the sum of the weight and values.
 * Also can create random items according GameParameters,
 * and retrieve the batch of Item of an holder (ItemHolder).
 */
#ifndef ITEMS_H
#define ITEMS_H

// Includes:
#include <memory>
#include <vector>

class Item;
class ItemHolder;
class GameParameters;

/**
 * @typedef ItemVector
 * Item collection (std::vector)
 */
typedef std::vector<std::shared_ptr<Item>> ItemVector;



class Items
{
public:
    Items();
    ~Items();

    // Getters:
    std::shared_ptr<Item> item(unsigned int index) const;

    // Setters:

    // Methods:
    void getItemBatchOfHolder(const std::shared_ptr<ItemHolder> & itemHolder, Items & batch) const;
    void createRandomItems(const std::shared_ptr<GameParameters> & gameParameters);

    unsigned int count() const;
    unsigned int weight() const;
    unsigned int value() const;
    void clear();
    void addItem(std::shared_ptr<Item> item);
    std::string consolePrint() const;

private:
    // Methods:

    // Members:
    ItemVector m_items;
};

#endif // ITEMS_H
