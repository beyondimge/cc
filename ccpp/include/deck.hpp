#ifndef CCPP_DECK_HPP
#define CCPP_DECK_HPP

#include <memory>
#include <string>
#include <vector>

#include "card.hpp"

namespace ccpp {
namespace game {

// Aggregator of Card objects which must satisfy below 3 rules.
// - A deck must be 27 cards.
// - A deck can have only 3 cards of the same name at most.
// - No more than 2 colors of cards in the deck at max.
class Deck {
public:
  // Constructor using JSON file.
  Deck(std::string json_file_path);

  // Validates if decklist satisfies above rule or not.

  inline std::size_t size() { return decklist.size(); }

  void AddCard(std::unique_ptr<Card> card);
  void RemoveCard(std::unique_ptr<Card> card);

  void Insert(std::unique_ptr<Card> card, std::size_t position);

  bool IsValid();
  // Shuffles the order of cards in library.
  void Shuffle();


  std::unique_ptr<Card> Draw();

private:
  std::vector<std::unique_ptr<Card>> decklist;
  bool is_library_out = false;
};

/*
class Library {
  // Aggregator of the class `Card`.
  // An instance of `Library` is created based on the class `Deck` instance at
  // every match.

 public:
  // Constructor using `Deck.decklist`.
  // Shuffles the order of cards afterward.
  Library(Deck &deck);


    // Inserts a card at index (begins with 0).
    // todo - need to think if Card or Card*
  void Insert(Card card, std::size_t position);

 private:
  std::vector<std::unique_ptr<Card>> pile;
};
*/

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_DECK_HPP