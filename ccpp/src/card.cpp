#include "../include/card.hpp"

#include <iostream>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>

namespace ccpp {
namespace game {

// todo - hardcoded to full path
std::string data_json = "ccpp/data/cards/card_data.json";

Color StrToColor(const std::string& color_str) {
  Color color;
  if (color_str == "Red") color = Color::Red;
  if (color_str == "Blue") color = Color::Blue;
  if (color_str == "Black") color = Color::Black;
  if (color_str == "Green") color = Color::Green;
  return color;
}

Speed StrToSpeed(const std::string& speed_str) {
  Speed speed;
  if (speed_str == "Normal") speed = Speed::Normal;
  if (speed_str == "Fast") speed = Speed::Fast;
  if (speed_str == "Slow") speed = Speed::Slow;
  return speed;
}

Card::Card(const std::string &card_name, const Color &color,
           const unsigned int level, const unsigned int attack, const int hp,
           const Speed &speed, const std::string &race)
    : card_name(card_name),
      color(color),
      level(level),
      attack(attack),
      hp(hp),
      speed(speed),
      race(race) {}

Card::Card(const Card &card)
    : card_name(card.card_name),
      color(card.color),
      level(card.level),
      attack(card.attack),
      hp(card.hp),
      speed(card.speed),
      race(card.race),
      is_vanilla(card.is_vanilla) {}


std::unique_ptr<Card> MakeCard(const std::string &target_card) {
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(data_json, pt);

  for (const auto e: pt.get_child("card")){
    const boost::property_tree::ptree &card = e.second;
    if (boost::optional<std::string> card_name_ = card.get_optional<std::string>("cardname")){
      if (card_name_.get() == target_card) {
        std::string color_str;
        Color color;
        unsigned int level;
        unsigned int attack;
        unsigned int hp;
        std::string speed_str;
        Speed speed;
        std::string race;

        if (boost::optional<std::string> color_ = card.get_optional<std::string>("color"))
          color_str = color_.get();
          color = StrToColor(color_str);

        if (boost::optional<unsigned int> level_ = card.get_optional<unsigned int>("level"))
          level = level_.get();

        if (boost::optional<unsigned int> attack_ = card.get_optional<unsigned int>("attack"))
          attack = attack_.get();

        if (boost::optional<unsigned int> hp_ = card.get_optional<unsigned int>("hp"))
          hp = hp_.get();

        if (boost::optional<std::string> speed_ = card.get_optional<std::string>("speed"))
          speed_str = speed_.get();
          speed = StrToSpeed(speed_str);

        if (boost::optional<std::string> race_ = card.get_optional<std::string>("race"))
          race = race_.get();

        return std::make_unique<Card>(target_card, color, level, attack, hp, speed, race);
        break;
      }
    }
  }
  // todo - raise an exception if target_card was not found
}



void Card::Update(){
  // todo
}

const std::string Card::GetName() const { return card_name; }
const Color Card::GetColor() const { return color; }
const unsigned int Card::GetLevel() const { return level; }
const unsigned int Card::GetAttack() const { return attack; }
const unsigned int Card::GetHP() const { return hp; }
const Speed Card::GetSpeed() const { return speed; }
const std::string Card::GetRace() const { return race; }
const bool Card::GetDelete() const { return to_be_deleted; }

std::string Card::GetName() { return card_name; }
Color Card::GetColor() { return color; }
unsigned int Card::GetLevel() { return level; }
unsigned int Card::GetAttack() { return attack; }
unsigned int Card::GetHP() { return hp; }
Speed Card::GetSpeed() { return speed; }
std::string Card::GetRace() { return race; }
bool Card::GetDelete() { return to_be_deleted; }

  // Setters.

void Card::SetName(std::string card_name_) { card_name = card_name_; }
void Card::SetColor(Color color_) { color = color_; }
void Card::SetLevel(unsigned int level_) { level = level_; }
void Card::SetAttack(unsigned int attack_) { attack = attack_; }
void Card::SetHP(unsigned int hp_) { hp = hp_; }
void Card::SetSpeed(Speed speed_) { speed = speed_; }
void Card::SetRace(std::string race_) { race = race_; }
void Card::SetFaceUp(bool is_face_up_) { is_face_up = is_face_up; }
void Card::SetLocation(Location location_) { location = location_; }
void Card::SetDelete(bool flag) { to_be_deleted = flag; }

}  // namespace game
}  // namespace ccpp