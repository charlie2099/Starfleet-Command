#ifndef STARFLEET_COMMAND_PLAYERSTATS_HPP
#define STARFLEET_COMMAND_PLAYERSTATS_HPP

class PlayerStats // static?, GameData class?
{
 public:
    PlayerStats() = default;
    ~PlayerStats() = default;

    void setScore(int score){};
    void setKills(int kills){};

    void saveToFile(){};
    void loadFromFile(){};
 private:
};

#endif //STARFLEET_COMMAND_PLAYERSTATS_HPP
