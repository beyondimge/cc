#include "../include/gameboard.hpp"
#include "../include/utils.hpp"

#include <iostream>
#include <random>
#include <memory>
#include <stdexcept>

namespace ccpp {
namespace game {

Gameboard::Gameboard(Game& game_) : game(game_) {
  // todo -
  // constructorでExceptionが発生すると困るので、Gameboard::Initialized()に移した方がいい？

  initiative = (bool)RandomDiscrete(2);

  // Creates gameboard components.
  player = std::make_unique<Player>();
  opponent = std::make_unique<Opponent>();
  field = std::make_unique<Field>();
  player_bench = std::make_unique<Bench>(*player);
  opponent_bench = std::make_unique<Bench>(*opponent);
  player_graveyard = std::make_unique<Graveyard>(*player);
  opponent_graveyard = std::make_unique<Graveyard>(*opponent);
}


void Gameboard::Update() {
  // todo
  field->Update();
}


Place::~Place() {}

const Card& Place::operator[](std::size_t position) const {
  if (position >= container.size()) {
    throw std::out_of_range("ERROR: argument of operator[] is out of range.");
  }

  return *container.at(position);
}

Card& Place::operator[](std::size_t position)
{
  return const_cast<Card&>(static_cast<const Place&>(*this)[position]);
}

void Place::AddCard(std::unique_ptr<Card> card) {
  if (!card) {
    // todo - throw an exception if card is nullptr.
  }

  card->SetLocation(location);
  container.push_back(std::move(card));
}

void Place::RemoveCard(std::size_t position) {
  if (position >= container.size()) {
    throw std::out_of_range("ERROR: argument of RemoveCard() is out of range.");
  }

  // todo - どこに移動させるか
  container.erase(container.begin() + position);
}

void Place::Update() { 
  for(int i = 0; i < container.size(); ++i) {
    container.at(i)->Update();
  }
}

Hand::~Hand() {};
Graveyard::~Graveyard() {}


const Card& Bench::operator[](std::size_t position) const {
  if (position >= bench.size())
  {
    throw std::out_of_range("");
  }
  return *bench[position];
}

Card& Bench::operator[](std::size_t position) {
  return const_cast<Card&>(static_cast<Bench&>(*this)[position]);
}

void Bench::AddCard(std::unique_ptr<Card> card) {
  for (int i = 0; i < 3; ++i) {
    if (bench[i] == nullptr) {
      bench[i] = std::move(card);
      return;
    }
  }
  // todo - Destroys the card if all 3 benches are already occupied.
}

void Bench::PackCards() {
  // Repeats i = 0 twice in case both bench_first and bench_second became
  // nullptr.
  if (bench[0] == nullptr) {
    for (int j = 0; j < 2; ++j) {
      bench[j] = std::move(bench[j + 1]);
    }
    bench[2] = nullptr;
  }

  for (int i = 0; i < 2; ++i) {
    if (bench[i] == nullptr) {
      for (int j = i; j < 2; ++j) {
        bench[j] = std::move(bench[j + 1]);
      }
      bench[2] = nullptr;
    }
  }
}

void Bench::RemoveCard(std::size_t position) {
  if (position >= 3)
  {
    throw std::out_of_range("position is not valid, it must be one of 0, 1, or 2.");
  }
  if (bench[position] != nullptr) {
    bench[position] = nullptr;
  } else {
    throw std::runtime_error(
        "Tried to remove card from bench but no card existed.");
  }
  PackCards();
}

int Bench::GetNumBench() const {

  int res = 0;
  for (int i = 0; i < 3; ++i) {
    if (bench[i] != nullptr) res++;
  }
  return res;
}


void Field::Update() {
  // todo
}

}  // namespace game
}  // namespace ccpp