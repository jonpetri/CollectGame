#include "item.h"

#include <random>

#include "model/item/itemholder.h"
#include "model/game/gameparameters.h"
//-----------------------------------------------------------------------------------------------------------------------
// Item :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
Item::Item()
    : m_holder(nullptr)
    , m_iWeight(0)
    , m_iValue(0)
{

}
Item::~Item()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// Item :: Getters
//-----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<ItemHolder> Item::holder() const
{
    return m_holder;
}

unsigned int Item::weight() const
{
    return m_iWeight;
}

unsigned int Item::value() const
{
    return m_iValue;
}


//-----------------------------------------------------------------------------------------------------------------------
// Item :: Setters
//-----------------------------------------------------------------------------------------------------------------------

void Item::setHolder(const std::shared_ptr<ItemHolder> &holder)
{
    m_holder = holder;
}

void Item::setWeight(unsigned int value)
{
    m_iWeight = value;
}

void Item::setValue(unsigned int value)
{
    m_iValue = value;
}

//-----------------------------------------------------------------------------------------------------------------------
// Item :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Set random values to weight and value properties, following gameParameters limits
 * @param [in] gameParameters Contain weight and value maximums
 */
void Item::setRandomWeightAndValue(const std::shared_ptr<GameParameters> &gameParameters)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<unsigned int> randomDistributionWeight(gameParameters->itemMinWeight(), gameParameters->itemMaxWeight());
    std::uniform_int_distribution<unsigned int> randomDistributionValue(gameParameters->itemMinValue(), gameParameters->itemMaxValue());

    m_iWeight =  randomDistributionWeight(gen);
    m_iValue =  randomDistributionValue(gen);
}

/**
 * Retrieve the string about the item to be displayed in the console.
 * @return string to be print
 */
std::string Item::consolePrint() const
{
    // The return print is:
    // weight = 5 , value = 10
    return "weight = " + std::to_string(m_iWeight) + " , value = " + std::to_string(m_iValue);
}
