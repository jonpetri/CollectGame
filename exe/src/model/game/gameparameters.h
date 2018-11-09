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
    int gridSideSize() const;
    int itemMaxValue() const;
    int itemMaxWeight() const;
    int playerWeightLimit() const;
    int playerItemCountLimit() const;
    double ratio_NodeCountVsGridSpotCount() const;
    double ratio_EdgeCountVsGridSpotCount() const;
    double ratio_ItemCountVsNodeCount() const;


    // Setters:
    bool setGridSideSize(int value);
    void setItemMaxWeight(int value);
    void setItemMaxValue(int value);
    bool setPlayerWeightLimit(int value);
    bool setPlayerItemCountLimit(int value);
    bool setRatio_NodeCountVsGridSpotCount(double value);
    bool setRatio_EdgeCountVsGridSpotCount(double value);
    bool setRatio_ItemCountVsNodeCount(double value);

    // Methods:

    int nodeCount() const;
    int edgeTargetCount() const;
    int itemCount() const;

private:
    // Methods:

    // Members:
    int m_iGridSize;
    double m_dRatio_NodeCountVsGridSpotCount;
    double m_dRatio_EdgeCountVsGridSpotCount;
    double m_dRatio_ItemCountVsNodeCount;
    int m_iItemMaxWeight;
    int m_iItemMaxValue;
    int m_iPlayerWeightLimit;
    int m_iPlayerItemCountLimit;

};

#endif // GameParameters_H
