#include "gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
GameParameters::GameParameters()
    : m_iGridSize(4)
    , m_dRatio_NodeCountVsGridSpotCount(0.5)
    , m_dRatio_EdgeCountVsGridSpotCount(0.5)
    , m_dRatio_ItemCountVsNodeCount(1.0)
    , m_iItemMaxWeight(10)
    , m_iItemMaxValue(10)
    , m_iPlayerWeightLimit(15)
    , m_iPlayerItemCountLimit(5)
{

}
GameParameters::~GameParameters()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Getters / Setters
//-----------------------------------------------------------------------------------------------------------------------

int GameParameters::itemMaxWeight() const
{
    return m_iItemMaxWeight;
}

int GameParameters::itemMinValue() const
{
    return m_iItemMinValue;
}

int GameParameters::itemMinWeight() const
{
    return m_iItemMinWeight;
}

bool GameParameters::setItemMaxWeight(int value)
{
    if (value <= m_iItemMinWeight)
        return false;

    m_iItemMaxWeight = value;
    return true;
}

int GameParameters::itemMaxValue() const
{
    return m_iItemMaxValue;
}


bool GameParameters::setItemMaxValue(int value)
{
    if (value <= m_iItemMinValue)
        return false;

    m_iItemMaxValue = value;
    return true;
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

double GameParameters::ratio_NodeCountVsGridSpotCount() const
{
    return m_dRatio_NodeCountVsGridSpotCount;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_NodeCountVsGridSpotCount(double value)
{
    if ((value<=0) || (value > 1))
        return false;
    m_dRatio_NodeCountVsGridSpotCount = value;
    return true;
}


double GameParameters::ratio_EdgeCountVsGridSpotCount() const
{
    return m_dRatio_EdgeCountVsGridSpotCount;
}

/**
 * Set the property, if the value is coherent.
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_EdgeCountVsGridSpotCount(double value)
{
    if (value<=0)
        return false;
    m_dRatio_EdgeCountVsGridSpotCount = value;
    return true;
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



int GameParameters::gridSideSize() const
{
    return m_iGridSize;
}

/**
 * Set the property, if the value is coherent
 * @param value
 * @return false if the value is not coherent
 */
bool GameParameters::setGridSideSize(int value)
{
    if (value<3 || value>40) // The algo start to be slow beyond 40, in my computer at least ;-)
        return false;

    m_iGridSize = value;
    return true;
}





//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Methods
//-----------------------------------------------------------------------------------------------------------------------
int GameParameters::nodeCount() const
{
    return static_cast<int>((m_iGridSize * m_iGridSize) * m_dRatio_NodeCountVsGridSpotCount);
}

int GameParameters::edgeTargetCount() const
{
    return static_cast<int>( (m_iGridSize * m_iGridSize) * m_dRatio_EdgeCountVsGridSpotCount);

}

int GameParameters::itemCount() const
{
   return static_cast<int>(m_dRatio_ItemCountVsNodeCount * this->nodeCount());
}
