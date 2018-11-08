#include "gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// GameProperties :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
GameParameters::GameParameters()
    : m_iGridSize(5)
    , m_dRatio_NodeCountVsGridSize(3.0)
    , m_dRatio_EdgeCountVsGridSize(4.0)
    , m_dRatio_ItemCountVsNodeCount(1)
    , m_iItemMaxWeight(10)
    , m_iItemMaxValue(10)
    , m_iPlayerWeightLimit(15)
    , m_iPlayerItemCountLimit(3)
{

}
GameParameters::~GameParameters()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// GameProperties :: Getters / Setters
//-----------------------------------------------------------------------------------------------------------------------

int GameParameters::itemMaxWeight() const
{
    return m_iItemMaxWeight;
}

void GameParameters::setItemMaxWeight(int value)
{
    m_iItemMaxWeight = value;
}

int GameParameters::itemMaxValue() const
{
    return m_iItemMaxValue;
}


void GameParameters::setItemMaxValue(int value)
{
    m_iItemMaxValue = value;
}

int GameParameters::playerWeightLimit() const
{
    return m_iPlayerWeightLimit;
}
/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setPlayerWeightLimit(int value)
{
    if (value >= this->itemCount() * this->m_iItemMaxWeight)
        return false;

    m_iPlayerWeightLimit = value;
    return true;
}

int GameParameters::playerItemCountLimit() const
{
    return m_iPlayerItemCountLimit;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setPlayerItemCountLimit(int value)
{
    if (value > this->itemCount())
        return false;

    m_iPlayerItemCountLimit = value;
    return true;
}

double GameParameters::ratio_NodeCountVsGridSize() const
{
    return m_dRatio_NodeCountVsGridSize;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_NodeCountVsGridSize(double value)
{
    if ((value<=0) || (value > (m_iGridSize*m_iGridSize)))
        return false;
    m_dRatio_NodeCountVsGridSize = value;
    return false;
}


double GameParameters::ratio_EdgeCountVsGridSize() const
{
    return m_dRatio_EdgeCountVsGridSize;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_EdgeCountVsGridSize(double value)
{
    if (value<=0)
        return false;
    m_dRatio_EdgeCountVsGridSize = value;
    return false;
}

double GameParameters::ratio_ItemCountVsNodeCount() const
{
    return m_dRatio_ItemCountVsNodeCount;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_ItemCountVsNodeCount(double value)
{
    if (value<=0)
        return false;
    m_dRatio_ItemCountVsNodeCount = value;
    return true;
}



int GameParameters::gridSize() const
{
    return m_iGridSize;
}

/**
 * Set the property, if the vaue is coherent
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setGridSize(int value)
{
    if (value<3)
        return false;

    m_iGridSize = value;
    return true;
}





//-----------------------------------------------------------------------------------------------------------------------
// GameProperties :: Methods
//-----------------------------------------------------------------------------------------------------------------------
int GameParameters::nodeCount()
{
    return static_cast<int>(m_dRatio_NodeCountVsGridSize * m_iGridSize);
}

int GameParameters::edgeTargetCount()
{
    return static_cast<int>(m_dRatio_EdgeCountVsGridSize * m_iGridSize);

}

int GameParameters::itemCount()
{
   return static_cast<int>(m_dRatio_ItemCountVsNodeCount * this->nodeCount());
}
