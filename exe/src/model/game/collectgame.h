/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: CollectGame
 *
 */
#ifndef COLLECTGAME_H
#define COLLECTGAME_H

// Includes:
#include <memory>

class GameParameters;
class Player;
class Map;
class Items;

/**
 * @enum E_MOVE
 * The different values that can be applied to a move along the X axis or the Y axis of the grid.
 */
enum class E_MOVE { BEGIN = -1,
                  BACKWARD = BEGIN,
                  HOLD_ON,
                  FORWARD,
                  END = FORWARD
                };


class CollectGame
{
public:
    CollectGame();
    ~CollectGame();

    // Getters:
    std::shared_ptr<GameParameters> gameParameters() const;
    std::shared_ptr<Player> player() const;
    std::shared_ptr<Map> map() const;
    std::shared_ptr<Items> items() const;

    // Setters:

    // Methods:
    void createNewGame();
    bool movePlayer (E_MOVE xMove, E_MOVE yMove);
    bool playerPickItem(unsigned int iItem);
    void getConsolePrint(std::string & sStringToPrint) const;


private:
    // Methods:

    // Members:
    std::shared_ptr<GameParameters> m_grameParameters;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Items> m_items;

};

#endif // COLLECTGAME_H
