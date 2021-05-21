#ifndef CCPP_PLAYER_HPP
#define CCPP_PLAYER_HPP

#include <map>
#include <memory>
#include <string>

#include "deck.hpp"
#include "gameboard.hpp"

namespace ccpp {
namespace game {

class Game;
class Hand;
class Graveyard;

/*
// This class holds basic information of player's account.
// An instance of `Player` class are created based on the class `Account`
instance at every match. class Account
{

private:
    const std::string account_name;
    int ladder_rate;
    int win_count;
    int lose_count;
    std::map<std::string, int> own_cards;
    std::vector<Deck> own_decks;
    Deck active_deck; // Deck to be used for game.

public:
    // Constructor.
    Account();
};
*/

enum Num_Initial_Hand { HAS_INITIATIVE = 5, NO_INITIATIVE = 6 };

// Base class for Player and Opponent.
class Person{
 public:
  Person();
  virtual ~Person();

  // virtual void Update();
  virtual void Draw() = 0;

  // Getters.

  const unsigned int GetLife() const { return life; }
  const unsigned int GetMana() const { return mana; }
  const unsigned int GetManaIncrease() const { return mana_increase; }

  // Setters.

  void SetLife(int new_life);
  void AddLife(int change);
  void SetMana(int new_mana);
  // Add `change` to Person::mana. Person::mana must be non-negative.
  void AddMana(int change);
  void SetManaIncrease(int new_mana_increase);
  // Adds `change` to Person::mana_increase. Person::mana_increase must be
  // non-negative.
  void AddManaIncrease(int change);
  void IncreaseMana();

  //  virtual void Update() = 0;
  //  virtual void Draw() = 0;

 private:
  const std::string player_name;

  static const unsigned int init_life = 4;
  static const unsigned int init_mana_increase = 2;
  static const unsigned int init_mana = 1;
  unsigned int life = init_life;
  unsigned int mana = init_mana;
  unsigned int mana_increase = init_mana_increase;

 protected:
  bool is_library_out = false;

  //////////////////////////////////////////////////////////////////////////////////////////
  // Members for card specific effect.
  //////////////////////////////////////////////////////////////////////////////////////////

  // (スキュラ) If true, mana will not be increased at the beginning of next
  // turn.
  bool skip_mana_increase;
  // (スキュラ) If true, draw will be skipped at the beginning of next turn.
  bool skip_draw;
  // (催眠術師)
  std::string card_forced_to_use;
};

class Player : public Person {
 public:
  // Constructor.
  Player();
  // Player(const Account &account);

  // Getters.
  const Deck& GetDeck() const;
  Deck& GetDeck();
  const Hand& GetHand() const;
  Hand& GetHand();
  const bool GetWonLastTurn() const;
  const bool GetLostLastTurn() const;

  // virtual void Update();

  void Draw();

  // Cast card in num-th element.
  bool CastCard(std::size_t position);

 private:

  // Flag to be used by Game::MoveInitiative()
  bool won_last_turn = false;
  // Flag to be used by Game::MoveInitiative()
  bool lost_last_turn = false;

  std::unique_ptr<Hand> player_hand;
  std::unique_ptr<Deck> player_library;
  std::unique_ptr<Graveyard> player_graveyard;

  //////////////////////////////////////////////////////////////////////////////////////////
  // Members for card specific effect.
  //////////////////////////////////////////////////////////////////////////////////////////

};

class Opponent : public Person {

 public:
  // Constructor.
  Opponent();

  // virtual void Update();

  void Draw();

 private:

  unsigned int num_opp_library;  // Player's client doesn't have to know cards in
                        // opponent library but how many it is.
  unsigned int num_opp_hand;  // Player's client doesn't have to know cards in opponent
                     // hand but how many it is.
  Hand *revealed_opponent_hand;
  
  //////////////////////////////////////////////////////////////////////////////////////////
  // Members for card specific effect.
  //////////////////////////////////////////////////////////////////////////////////////////

};

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_PLAYER_HPP