#ifndef STARFLEET_COMMAND_PLAYER_HPP
#define STARFLEET_COMMAND_PLAYER_HPP

class Player
{
 public:
    Player() = default;
    ~Player() = default;

    void setCredits(int credits);
    int getCredits() const;

 private:
    int player_credits = 250;
    int points = 0; // ?
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
