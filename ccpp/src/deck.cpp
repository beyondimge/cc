#include "../include/deck.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../include/card.hpp"

namespace ccpp {
namespace game {

// Constructor takes json file path as argument.
Deck::Deck(std::string json_file_path) { 
  std::vector<std::string> deck;

  boost::property_tree::ptree pt;
  boost::property_tree::read_json(json_file_path, pt);

  std::cout << "Loading deck:" << std::endl;
  for (const auto e : pt.get_child("List")) {
    std::string card_name;
    int card_num;
    const boost::property_tree::ptree &info = e.second;
    if (boost::optional<std::string> name = info.get_optional<std::string>("name"))
    {
      std::cout << "name: " << name.get() << std::endl;
      card_name = name.get();
    } else {
      std::cout << "name is nothing" << std::endl;
    }

    if (boost::optional<int> num = info.get_optional<int>("num"))
    {
      std::cout << "num: " << num.get() << std::endl;
      card_num = num.get();
    } else {
      std::cout << "num is nothing" << std::endl;
    }

    for (int i = 0; i < card_num; ++i)
    {
      decklist.push_back(std::move(MakeCard(card_name)));
    }
  }
}


bool Deck::IsValid() {
  bool is_valid_deck = true;
  bool is_at_most_3same_cards = true;

  std::map<std::string, int> deck_by_name;
  std::set<Color> color_count;
  std::size_t decksize = decklist.size();

  for (const auto &card : decklist) {
    std::string cardname = card->GetName();
    deck_by_name[cardname] += 1;
    color_count.insert(card->GetColor());
    if (deck_by_name[cardname] > 3) {
      is_at_most_3same_cards = false;
    }
  }

  // Checks if at most 2 colors are used or not.
  if (color_count.size() > 3) {
    is_valid_deck = false;
    std::cout << "ERROR - A deck must have less than or equal to 2 colors." << std::endl;
  }

  // Checks if at most 3 copies of same card are used or not.
  if (!is_at_most_3same_cards) {
    is_valid_deck = false;
    std::cout << "ERROR - A deck must have same cards at most 3." << std::endl;
  }

  // Checks if number of cards is 27 or not.
  if (decksize != 27) {
    is_valid_deck = false;
    std::cout << "ERROR - A deck must have 27 cards but " << decksize
              << " was given." << std::endl;
  }

  return is_valid_deck;
}

/*
Library::Library(Deck &deck) {
  for (const auto &card : deck.GetDecklist()) {
    pile.push_back(std::move(card));
  }
  Library::Shuffle();
}
*/


std::unique_ptr<Card> Deck::Draw() {
  if (decklist.size() > 0) {
    std::unique_ptr<Card> deck_top = std::move(decklist.at(decklist.size() - 1));
    decklist.pop_back();
    return deck_top;
  } else {
    is_library_out = true;
  }
}


void Deck::Shuffle() {
  std::random_device get_rand_dev;
  std::mt19937_64 get_rand_mt(get_rand_dev());  // seedに乱数を指定
  std::shuffle(decklist.begin(), decklist.end(), get_rand_mt);
}

void Deck::Insert(std::unique_ptr<Card> card, std::size_t position) {
  if (position >= decklist.size()) {
    throw std::out_of_range("out of range");
  } else {
    decklist.insert(decklist.begin() + position, std::move(card));
  }
}

}  // namespace game
}  // namespace ccpp