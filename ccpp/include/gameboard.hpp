#ifndef CCPP_GAMEBOARD_HPP
#define CCPP_GAMEBOARD_HPP

#include <array>
#include <memory>
#include <vector>

#include "game.hpp"
#include "observer.hpp"
#include "player.hpp"
#include "utils.hpp"

namespace ccpp {
namespace game {

class Game;
class Person;
class Player;
class Opponent;
class Hand;

// Base class
class Place {
 public:
  virtual ~Place() = 0;
  const Card& operator[](std::size_t position) const;
  Card& operator[](std::size_t position);
  std::size_t Size() const { return container.size(); }

  void AddCard(std::unique_ptr<Card> card);
  void RemoveCard(std::size_t position);

  void Update();

 private:
  std::vector<std::unique_ptr<Card>> container;
  Location location;
};

class Graveyard : public Place {
 public:
  Graveyard(Person& person_) : person(person_) {}
  ~Graveyard() override;

 private:
  Person& person;
};

class Hand : public Place {
 public:
  Hand(Person& person_) : person(person_) {}
  ~Hand() override;

 private:
  Person& person;
};

// This class doesn't inherit from Place.
class Bench {
 public:
  Bench(Person& person_) : person(person_) {}
  const Card& operator[](std::size_t position) const;
  Card& operator[](std::size_t position);
  // Add a card in order from bench_first to bench_third.
  void AddCard(std::unique_ptr<Card> card);

  // Removes a card from the position. Bench::PackCards() will be called
  // afterwards. Throws std::runtime_error if card does not exist on the
  // position.
  void RemoveCard(std::size_t position);

  // Returns number of non-nullptr elements in bench
  int GetNumBench() const;

 private:
  std::array<std::unique_ptr<Card>, 3> bench = {nullptr, nullptr, nullptr};

  // If there is a gap in the bench, packs the cards in order from bench[0] to
  // bench[2]
  void PackCards();

  Person& person;
};

// This class doesn't inherit from Place.
class Field {
 public:
  // Getters
  // todo - handle the case when nullptr is passed to these functions.
  const bool IsPlayerAttacker() const { return player_attacker != nullptr; }
  const bool IsOpponentAttacker() const { return opponent_attacker != nullptr; }
  inline const Card& GetPlayerAttacker() const { return *player_attacker; }
  inline Card& GetPlayerAttacker() { return *player_attacker; }
  inline const Card& GetOpponentAttacker() const { return *opponent_attacker; }
  inline Card& GetOpponentAttacker() { return *opponent_attacker; }

  // Setters
  inline void SetPlayerAttacker(Card& card) { *player_attacker = card; }
  inline void SetOpponentAttacker(Card& card) { *opponent_attacker = card; }

  inline void RemovePlayerAttacker() { player_attacker = nullptr; }
  inline void RemoveOpponentAttacker() { opponent_attacker = nullptr; }

  void Update();

 private:
  std::unique_ptr<Card> player_attacker = nullptr;
  std::unique_ptr<Card> opponent_attacker = nullptr;
};

class Gameboard {
 public:
  Gameboard(Game& game_);

  // Getters.
  inline const Player& GetPlayer() const { return *player; }
  inline const Opponent& GetOpponent() const { return *opponent; }
  inline const Field& GetField() const { return *field; }
  inline const Bench& GetPlayerBench() const { return *player_bench; }
  inline const Bench& GetOpponentBench() const { return *opponent_bench; }
  inline const bool GetInitiative() const { return initiative; }
  inline Player& GetPlayer() { return *player; }
  inline Opponent& GetOpponent() { return *opponent; }
  inline Field& GetField() { return *field; }
  inline Bench& GetPlayerBench() { return *player_bench; }
  inline Bench& GetOpponentBench() { return *opponent_bench; }
  inline bool GetInitiative() { return initiative; }
  inline void ChangeInitiative() { initiative = 1 - initiative; }

  void AddCard(std::unique_ptr<Card> card);
  void Update();

 private:
  Game& game;
  bool initiative;  // true if player has initiative, false if not.
  std::unique_ptr<Player> player;
  std::unique_ptr<Opponent> opponent;
  std::unique_ptr<Field> field;
  std::unique_ptr<Bench> player_bench;
  std::unique_ptr<Bench> opponent_bench;
  std::unique_ptr<Graveyard> player_graveyard;
  std::unique_ptr<Graveyard> opponent_graveyard;
};

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_GAMEBOARD_HPP