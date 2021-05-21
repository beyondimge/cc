#include <gtest/gtest.h>
#include <iostream>

#include "../include/card.hpp"


std::string data_json =
    "ccpp/data/cards/card_data.json";


// Test case for constructor by specifying all data members.
TEST(Card, constructor_all) {

  std::string expected_name = "サソリ";
  ccpp::game::Color expected_color = ccpp::game::Color::Red;
  unsigned int expected_level = 1;
  unsigned int expected_attack = 4;
  unsigned int expected_hp = 1;
  ccpp::game::Speed expected_speed = ccpp::game::Speed::Normal;
  std::string expected_race = "null";

  ccpp::game::Card c(expected_name, expected_color, expected_level, expected_attack, expected_hp, expected_speed, expected_race);

  EXPECT_EQ(expected_name, c.GetName());
  EXPECT_EQ(expected_color, c.GetColor());
  EXPECT_EQ(expected_level, c.GetLevel());
  EXPECT_EQ(expected_attack, c.GetAttack());
  EXPECT_EQ(expected_hp, c.GetHP());
  EXPECT_EQ(expected_speed, c.GetSpeed());
  EXPECT_EQ(expected_race, c.GetRace());
}


// Test case for constructor by name.
TEST(Card, constructor_name) {
  std::string expected_name = "サソリ";
  ccpp::game::Color expected_color = ccpp::game::Color::Red;
  unsigned int expected_level = 1;
  unsigned int expected_attack = 4;
  unsigned int expected_hp = 1;
  ccpp::game::Speed expected_speed = ccpp::game::Speed::Normal;
  std::string expected_race = "null";

  std::unique_ptr<ccpp::game::Card> c = ccpp::game::MakeCard(expected_name);

  EXPECT_EQ(expected_name, c->GetName());
  EXPECT_EQ(expected_level, c->GetLevel());
  EXPECT_EQ(expected_level, c->GetLevel());
  EXPECT_EQ(expected_attack, c->GetAttack());
  EXPECT_EQ(expected_hp, c->GetHP());
  EXPECT_EQ(expected_speed, c->GetSpeed());
  EXPECT_EQ(expected_race, c->GetRace());
}


// Test case for copy constructor.
TEST(Card, constructor_copy) {
  std::string expected_name = "サソリ";
  ccpp::game::Color expected_color = ccpp::game::Color::Red;
  unsigned int expected_level = 1;
  unsigned int expected_attack = 4;
  unsigned int expected_hp = 1;
  ccpp::game::Speed expected_speed = ccpp::game::Speed::Normal;
  std::string expected_race = "null";

  ccpp::game::Card c1 = ccpp::game::Card(expected_name, expected_color, expected_level, expected_attack, expected_hp, expected_speed, expected_race);
  ccpp::game::Card c2 = ccpp::game::Card(c1);

  EXPECT_EQ(expected_name, c2.GetName());
  EXPECT_EQ(expected_color, c2.GetColor());
  EXPECT_EQ(expected_level, c2.GetLevel());
  EXPECT_EQ(expected_attack, c2.GetAttack());
  EXPECT_EQ(expected_hp, c2.GetHP());
  EXPECT_EQ(expected_speed, c2.GetSpeed());
  EXPECT_EQ(expected_race, c2.GetRace());
}

// Test case for setters.
TEST(Card, setters) {
  std::string original_name = "サソリ";
  ccpp::game::Color original_color = ccpp::game::Color::Red;
  unsigned int original_level = 1;
  unsigned int original_attack = 4;
  unsigned int original_hp = 1;
  ccpp::game::Speed original_speed = ccpp::game::Speed::Normal;
  std::string original_race = "null";

  ccpp::game::Card c = ccpp::game::Card(original_name, original_color, original_level, original_attack, original_hp, original_speed, original_race);

  std::string expected_name = "黒の書";
  ccpp::game::Color expected_color = ccpp::game::Color::Black;
  unsigned int expected_level = 2;
  unsigned int expected_attack = 5;
  unsigned int expected_hp = 0;
  ccpp::game::Speed expected_speed = ccpp::game::Speed::Slow;
  std::string expected_race = "something";

  c.SetName(expected_name);
  c.SetColor(expected_color);
  c.SetLevel(expected_level);
  c.SetAttack(expected_attack);
  c.SetHP(expected_hp);
  c.SetSpeed(expected_speed);
  c.SetRace(expected_race);

  EXPECT_EQ(expected_name, c.GetName());
  EXPECT_EQ(expected_color, c.GetColor());
  EXPECT_EQ(expected_level, c.GetLevel());
  EXPECT_EQ(expected_attack, c.GetAttack());
  EXPECT_EQ(expected_hp, c.GetHP());
  EXPECT_EQ(expected_speed, c.GetSpeed());
  EXPECT_EQ(expected_race, c.GetRace());
}


// Test case for Card.Update().
TEST(Card, update) {
  // todo 

}