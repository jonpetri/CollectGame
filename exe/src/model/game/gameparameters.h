/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: GameParameters
 * The class generate game's parameters.
 *
 * The class calculate :  nodeCount, edgeTargetCount, itemCount from the grid size.
 * The ratios used to make the calcules can be modified.
 *
 * The other parameters has to be set. (also default values available)
 */
#ifndef GameParameters_H
#define GameParameters_H

// Includes:

class GameParameters
{
public:
    GameParameters();

    ~GameParameters();

    // Getters:
    unsigned int gridSideSize() const;
    unsigned int itemMaxValue() const;
    unsigned int itemMaxWeight() const;
    unsigned int itemMinValue() const;
    unsigned int itemMinWeight() const;
    unsigned int playerWeightLimit() const;
    unsigned int playerItemCountLimit() const;
    float ratio_NodeCountVsGridSpotCount() const;
    float ratio_EdgeCountVsGridSpotCount() const;
    float ratio_ItemCountVsNodeCount() const;


    // Setters:
    bool setGridSideSize(unsigned int value);
    bool setItemMaxWeight(unsigned int value);
    bool setItemMaxValue(unsigned int value);
    bool setPlayerWeightLimit(unsigned int value);
    bool setPlayerItemCountLimit(unsigned int value);
    bool setRatio_NodeCountVsGridSpotCount(float value);
    bool setRatio_EdgeCountVsGridSpotCount(float value);
    bool setRatio_ItemCountVsNodeCount(float value);

    // Methods:

    unsigned long nodeCount() const;
    unsigned long edgeTargetCount() const;
    unsigned int itemCount() const;

private:
    // Methods:

    // Members:
    unsigned int m_iGridSize;
    float m_dRatio_NodeCountVsGridSpotCount;
    float m_dRatio_EdgeCountVsGridSpotCount;
    float m_dRatio_ItemCountVsNodeCount;
    unsigned int m_iItemMaxWeight;
    unsigned int m_iItemMaxValue;

    unsigned int m_iPlayerWeightLimit;
    unsigned int m_iPlayerItemCountLimit;

    const unsigned int m_iItemMinWeight = 1;
    const unsigned int m_iItemMinValue = 1;
    const float m_floatLimit = 9999.0;
    const unsigned int m_intLimit = 9999;
    const unsigned long m_longLimit = 9999;

};

#endif // GameParameters_H
