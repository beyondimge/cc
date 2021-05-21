#include "../include/player.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "../include/gameboard.hpp"

namespace ccpp {
namespace game {

Person::Person(){}
Person::~Person(){}

void Person::Draw(){}
// void Person::Update(){} 

Player::Player() {
  // todo - hardcoded
  std::string json_file_path = "ccpp/data/decks/sample_valid_deck.json";
  
  player_library = std::make_unique<Deck>(json_file_path);
  player_hand = std::make_unique<Hand>(*this);
}


Opponent::Opponent() {
}

void Person::IncreaseMana() { 
  if (!skip_mana_increase) {
    mana += mana_increase; 
  } else {
    skip_mana_increase = false;
  }
}

void Person::AddManaIncrease(int change) {
  int new_mana_increase = mana_increase + change;
  new_mana_increase = std::max(new_mana_increase, 0);
  mana_increase = new_mana_increase;
}


void Player::Draw() {
  if (player_library->size() > 0){
    std::unique_ptr<Card> card_drawn = player_library->Draw();
    player_hand->AddCard(std::move(card_drawn));
  } else {
    is_library_out = true;
  }
}

bool Player::CastCard(std::size_t position) {
  if (position > GetHand().Size())
  {
    // todo - needs to raise necessary message.
    return false;
  }
  // todo - needs to check if player has sufficient mana to case the card.  <- this should be checked by the caller as well
  // todo - needs to check if the card has cast effect or not.
  // todo - needs to check if conditions of case effect is met or not.
  // todo - needs to move the ownership of the pointer to card from Hand to somewhere appropriate.
}

void Opponent::Draw() {
  if (num_opp_library > 0) {
    num_opp_hand++;
    num_opp_library--;
  } else {
    is_library_out = true;
  }
}

const Deck& Player::GetDeck() const { return *player_library; }
Deck& Player::GetDeck() { return *player_library; }
const Hand& Player::GetHand() const { return *player_hand; }
Hand& Player::GetHand() { return *player_hand; }
const bool Player::GetWonLastTurn() const { return won_last_turn; }
const bool Player::GetLostLastTurn() const { return lost_last_turn; }

}  // namespace game
}  // namespace ccpp