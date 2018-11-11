#include "gameparameters.h"

#include <cmath>
#include <climits>
#include <stdexcept>
#include <iomanip> // setprecision
#include <sstream> // stringstream
//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
GameParameters::GameParameters()
    : m_iGridSize(0)
    , m_dRatio_NodeCountVsGridSpotCount(0)
    , m_dRatio_EdgeCountVsGridSpotCount(0)
    , m_dRatio_ItemCountVsNodeCount(0)
    , m_iItemMaxWeight(0)
    , m_iItemMaxValue(0)
    , m_iPlayerWeightLimit(0)
    , m_iPlayerItemCountLimit(0)
{
    // Default values, which has to be coherent
    if (!this->setGridSideSize(4)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setRatio_NodeCountVsGridSpotCount(0.5)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setRatio_EdgeCountVsGridSpotCount(0.5)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setRatio_ItemCountVsNodeCount(1.0)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setItemMaxWeight(10)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setItemMaxValue(10)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setPlayerWeightLimit(15)) throw std::out_of_range("in GameParameters::GameParameters()");
    if (!this->setPlayerItemCountLimit(5)) throw std::out_of_range("in GameParameters::GameParameters()");
}
GameParameters::~GameParameters()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Getters / Setters
//-----------------------------------------------------------------------------------------------------------------------

unsigned int GameParameters::itemMaxWeight() const
{
    return m_iItemMaxWeight;
}

unsigned int GameParameters::itemMinValue() const
{
    return m_iItemMinValue;
}

unsigned int GameParameters::itemMinWeight() const
{
    return m_iItemMinWeight;
}

bool GameParameters::setItemMaxWeight(unsigned int value)
{
    if (value <= m_iItemMinWeight  || value > m_intLimit)
        return false;

    m_iItemMaxWeight = value;
    return true;
}

unsigned int GameParameters::itemMaxValue() const
{
    return m_iItemMaxValue;
}


bool GameParameters::setItemMaxValue(unsigned int value)
{
    if (value <= m_iItemMinValue || value > m_intLimit)
        return false;

    m_iItemMaxValue = value;
    return true;
}

unsigned int GameParameters::playerWeightLimit() const
{
    return m_iPlayerWeightLimit;
}
/**
 * Set the property, if the value is coherent.
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setPlayerWeightLimit(unsigned int value)
{
    if (value >= (this->itemCount() * this->m_iItemMaxWeight))
        return false;

    m_iPlayerWeightLimit = value;
    return true;
}

unsigned int GameParameters::playerItemCountLimit() const
{
    return m_iPlayerItemCountLimit;
}

/**
 * Set the property, if the value is coherent.
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setPlayerItemCountLimit(unsigned int value)
{
    if (value > this->itemCount())
        return false;

    m_iPlayerItemCountLimit = value;
    return true;
}

float GameParameters::ratio_NodeCountVsGridSpotCount() const
{
    return m_dRatio_NodeCountVsGridSpotCount;
}

/**
 * Set the property, if the value is coherent.
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_NodeCountVsGridSpotCount(float value)
{
    if ((value<=0) || (value > 1))
        return false;
    m_dRatio_NodeCountVsGridSpotCount = value;
    return true;
}


float GameParameters::ratio_EdgeCountVsGridSpotCount() const
{
    return m_dRatio_EdgeCountVsGridSpotCount;
}

/**
 * Set the property, if the value is coherent.
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_EdgeCountVsGridSpotCount(float value)
{
    if (value<=0 || value > m_floatLimit)
        return false;

    m_dRatio_EdgeCountVsGridSpotCount = value;
    return true;
}

float GameParameters::ratio_ItemCountVsNodeCount() const
{
    return m_dRatio_ItemCountVsNodeCount;
}

/**
 * Set the property, if the value is coherent.
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setRatio_ItemCountVsNodeCount(float value)
{
    if (value<=0 || value > m_floatLimit)
        return false;
    m_dRatio_ItemCountVsNodeCount = value;
    return true;
}



unsigned int GameParameters::gridSideSize() const
{
    return m_iGridSize;
}

/**
 * Set the property, if the value is coherent
 * @param [in] value
 * @return false if the value is not coherent
 */
bool GameParameters::setGridSideSize(unsigned int value)
{
    if (value<3 || value>40) // The algo start to be slow beyond 40, in my computer at least ;-)
        return false;

    m_iGridSize = value;
    return true;
}





//-----------------------------------------------------------------------------------------------------------------------
// GameParameters :: Methods
//-----------------------------------------------------------------------------------------------------------------------
unsigned long GameParameters::nodeCount() const
{
    float fRet = static_cast<float>(m_iGridSize * m_iGridSize) * m_dRatio_NodeCountVsGridSpotCount;

    // cast float -> int :
    // float could exceed int, but values are limited by GameParameters class getters so the throw shouldn't happen.
    // Just in case anyway:
    if (fRet > static_cast<float>(UINT_MAX))
        throw std::out_of_range("in GameParameters::nodeCount()");

    return static_cast<unsigned int>(std::round(fRet));
}

unsigned long GameParameters::edgeTargetCount() const
{
    float fRet = static_cast<float>(m_iGridSize * m_iGridSize) * m_dRatio_EdgeCountVsGridSpotCount;

    // cast float -> int :
    // float could exceed int, but values are limited by GameParameters class getters so the throw shouldn't happen.
    // Just in case anyway:
    if (fRet > static_cast<float>(UINT_MAX))
        throw std::out_of_range("in GameParameters::edgeTargetCount()");

    return static_cast<unsigned int>(std::round(fRet));
}

unsigned int GameParameters::itemCount() const
{
    float fRet = m_dRatio_ItemCountVsNodeCount * static_cast<float>(this->nodeCount());

    // cast float -> int :
    // float could exceed int, but values are limited by GameParameters class getters so the throw shouldn't happen.
    // Just in case anyway:
    if (fRet > static_cast<float>(UINT_MAX))
        throw std::out_of_range("in GameParameters::itemCount()");

    return static_cast<unsigned int>(std::round(fRet));
}

/**
 * Retrieves the string about parameters to be displayed in the console.
 * @return string to be print
 */
std::string GameParameters::getConsolePrint() const
{
    std::stringstream stream;

    std::string sConsolePrint("");
    sConsolePrint += "Grid width(the grid is a square) [3->40]:  " + std::to_string(m_iGridSize) + "\n";

    stream << std::fixed << std::setprecision(2) << m_dRatio_NodeCountVsGridSpotCount;
    sConsolePrint += "Node count / grid spot count ratio [0->1]: " +  stream.str() + "\n";
    stream.str("");

    stream << std::fixed << std::setprecision(2) << m_dRatio_EdgeCountVsGridSpotCount;
    sConsolePrint += "Edge count / grid spot count  ratio :      " + stream.str() + "\n";
    stream.str("");

    stream << std::fixed << std::setprecision(2) << m_dRatio_ItemCountVsNodeCount;
    sConsolePrint += "item count / node count  ratio:            " + stream.str() + "\n";
    stream.str("");

    sConsolePrint += "Item max weight during random generation:  " + std::to_string(m_iItemMaxWeight) + "\n";
    sConsolePrint += "Item max value during random generation:   " + std::to_string(m_iItemMaxValue) + "\n";
    sConsolePrint += "Player total Weight limit  (<max weight):  " + std::to_string(m_iPlayerWeightLimit) + "\n";
    sConsolePrint += "Player item count limit (<item count):     " + std::to_string(m_iPlayerItemCountLimit) + "\n";

    return sConsolePrint;
}
