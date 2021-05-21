#ifndef CCPP_CARD_HPP
#define CCPP_CARD_HPP

#include <memory>
#include <string>

namespace ccpp {
namespace game {

enum class Speed { Fast = 2, Normal = 1, Slow = 0 };
enum class Color { Red, Blue, Black, Green };
enum class Location {
  PlayerLibrary,
  PlayerHand,
  PlayerBench,
  PlayerField,
  PlayerGraveyard,
  OpponentLibrary,
  OpponentHand,
  OpponentBench,
  OpponentField,
  OpponentGraveyard,
  DUMMY,
};

Color StrToColor(const std::string &color_str);
Speed StrToSpeed(const std::string &speed_str);


// Class for card.
class Card {
 public:

  Card(const std::string &card_name_, const Color &color_,
       const unsigned int level_, const unsigned attack_, const int hp_,
       const Speed &speed_, const std::string &race_);

  Card(const Card &card);

  // Method to be called by Game::Update(). This method lets the card take
  // necessary reaction.
  void Update();

  // Getters.
  const std::string GetName() const;
  const Color GetColor() const;
  const unsigned int GetLevel() const;
  const unsigned int GetAttack() const;
  const unsigned int GetHP() const;
  const Speed GetSpeed() const;
  const std::string GetRace() const;
  const bool GetDelete() const;

  std::string GetName();
  Color GetColor();
  unsigned int GetLevel();
  unsigned int GetAttack();
  unsigned int GetHP();
  Speed GetSpeed();
  std::string GetRace();
  bool GetDelete();

  // Setters.
  void SetName(std::string card_name_);
  void SetColor(Color color_);
  void SetLevel(unsigned int level_);
  void SetAttack(unsigned int attack_);
  void SetHP(unsigned int hp_);
  void SetSpeed(Speed speed_);
  void SetRace(std::string race_);
  void SetFaceUp(bool is_face_up_);
  void SetLocation(Location location_);
  void SetDelete(bool flag);

 private:
  std::string card_name;
  Color color;
  unsigned int level;
  unsigned int attack;
  unsigned int hp;
  Speed speed;
  std::string race;
  bool is_vanilla;

  // todo 使用効果
  // todo 勝利効果
  // todo 敗北効果
  // todo 待機効果
  // todo 手札にある時の効果
  // todo デッキにある時の効果
  // todo 墓地にあるときの効果
  // todo image

  // Location represents where the card is. It should be updated whenever it
  // moves to different location.
  Location location;

  // Flag to indicate if it's known what card is or not from player
  // perspective (e.g. if player have seen a card in opponent hand by some
  // effect, this should be true).
  bool is_face_up;

  // Flag to indicate if this card should be deleted once Game::Update() went
  // through all the card objects.
  bool to_be_deleted;
};

std::unique_ptr<Card> MakeCard(const std::string &card_name);

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_CARD_HPP
