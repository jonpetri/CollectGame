#include "items.h"
#include <random>

#include "model/item/item.h"
#include "model/item/itemholder.h"
#include "model/game/gameparameters.h"
//-----------------------------------------------------------------------------------------------------------------------
// Items :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
Items::Items()
    : m_items()
{

}
Items::~Items()
{

}



//-----------------------------------------------------------------------------------------------------------------------
// Items :: Getters
//-----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Item> Items::item(unsigned int index)
{
    return this->m_items[index];
}

//-----------------------------------------------------------------------------------------------------------------------
// Items :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// Items :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Build and retrieve a collection of all the items of a holder
 * @param [in] itemHolder
 * @return the collection
 */
void Items::getItemBatchOfHolder(const std::shared_ptr<ItemHolder> &itemHolder, Items & batch) const
{
    batch.clear();
    for (const std::shared_ptr<Item> & item : m_items)
    {
        if (item->holder() == itemHolder)
            batch.addItem(item);
    }
}

/**
 * Create random items, following gameParameters limits.
 * @param [in] gameParameters Contain random distribution limits
 */
void Items::ceateRandomItems(const std::shared_ptr<GameParameters> &gameParameters)
{
    int iItemCount = gameParameters->itemCount();
    std::shared_ptr<Item> newItem;

    for (int i = 0 ; i < iItemCount ; ++i)
    {
        newItem = std::make_shared<Item>();
        newItem->setRandomWeightAndValue(gameParameters);
        this->m_items.push_back(newItem);
    }
}

/**
 * @return item quantity
 */
unsigned int Items::count() const
{
    return static_cast<unsigned int> (m_items.size());
}

/**
 * The total weight of all the items
 * @return total weight
 */
int Items::weight() const
{
    int iRet = 0;
    for (const std::shared_ptr<Item> & item : m_items)
        iRet += item->weight();

    return iRet;
}

/**
 * The total value of all the items
 * @return total weight
 */
int Items::value() const
{
    int iRet = 0;
    for (const std::shared_ptr<Item> & item : m_items)
        iRet += item->value();

    return iRet;
}

/**
 * Empty the container
 */
void Items::clear()
{
    this->m_items.clear();
}

/**
 * Add the item to the container
 * @param item
 */
void Items::addItem(std::shared_ptr<Item> item)
{
    this->m_items.push_back(item);
}

/**
 * Retrieve the string about items to be displayed in the console.
 * @return string to be print
 */
std::string Items::consolePrint() const
{
    // The return print is:

    //2 items(s).
    //   - Item 1: weight = 5 , value = 9
    //   - Item 2: weight = 9 , value = 10

    std::string sStringToPrint;

    sStringToPrint += std::to_string(m_items.size()) + " items(s).\n";

    for (unsigned int i = 0 ; i < m_items.size() ; ++i)
    {
         sStringToPrint += "    - Item " + std::to_string(i+1) + ": " + m_items[i]->consolePrint() + "\n";
    }
    return sStringToPrint;
}
