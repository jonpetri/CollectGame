/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: GameParameters
 *
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
    int gridSize() const;
    int itemMaxValue() const;
    int itemMaxWeight() const;
    int playerWeightLimit() const;
    int playerItemCountLimit() const;
    double ratio_NodeCountVsGridSize() const;
    double ratio_EdgeCountVsGridSize() const;
    double ratio_ItemCountVsNodeCount() const;


    // Setters:
    bool setGridSize(int value);
    void setItemMaxWeight(int value);
    void setItemMaxValue(int value);
    bool setPlayerWeightLimit(int value);
    bool setPlayerItemCountLimit(int value);
    bool setRatio_NodeCountVsGridSize(double value);
    bool setRatio_EdgeCountVsGridSize(double value);
    bool setRatio_ItemCountVsNodeCount(double value);

    // Methods:

    int nodeCount();
    int edgeTargetCount();
    int itemCount();



private:
    // Methods:

    // Members:
    int m_iGridSize;
    double m_dRatio_NodeCountVsGridSize;
    double m_dRatio_EdgeCountVsGridSize;
    double m_dRatio_ItemCountVsNodeCount;
    int m_iItemMaxWeight;
    int m_iItemMaxValue;
    int m_iPlayerWeightLimit;
    int m_iPlayerItemCountLimit;

};

#endif // GameParameters_H
