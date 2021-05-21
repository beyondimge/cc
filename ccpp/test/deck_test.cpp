#include <string>
#include <gtest/gtest.h>

#include "../include/deck.hpp"

std::string valid_deck = "ccpp/data/decks/sample_valid_deck.json";
std::string invalid_deck1 = "ccpp/data/decks/sample_invalid_deck1.json";
std::string invalid_deck2 = "ccpp/data/decks/sample_invalid_deck2.json";
std::string invalid_deck3 = "ccpp/data/decks/sample_invalid_deck3.json";

TEST(deck, validation) {
    ccpp::game::Deck valid(valid_deck);
    ccpp::game::Deck invalid1(invalid_deck1);
    ccpp::game::Deck invalid2(invalid_deck2);
    ccpp::game::Deck invalid3(invalid_deck3);

    EXPECT_TRUE(valid.IsValid());
    EXPECT_FALSE(invalid1.IsValid());
    EXPECT_FALSE(invalid2.IsValid());
    EXPECT_FALSE(invalid3.IsValid());
}

TEST(deck, draw) { 
    ccpp::game::Deck deck(valid_deck); 
}