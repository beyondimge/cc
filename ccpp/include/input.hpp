#ifndef CCPP_INPUT_HPP
#define CCPP_INPUT_HPP

namespace ccpp {
namespace game {

class Game;

enum class InputChooseAttacker {
  // Inputs to get information.
  LOOK_PLAYER_HAND,
  LOOK_PLAYER_GRAVEYARD,
  LOOK_OPPONENT_GRAVEYARD,

  // Inputs to proceed game at "SELECT_BENCH" Phase.
  CHOOSE_ATTACKER_FROM_BENCH1,
  CHOOSE_ATTACKER_FROM_BENCH2,
  CHOOSE_ATTACKER_FROM_BENCH3,
  CHOOSE_NO_ATTACKER,

  // todo - Once GUI is setup, this inputs should be processed when cursor
  // hovers on a card.
  SEE_CARD_INFO,
};

enum class InputCastCard {
  // Inputs to get information.
  LOOK_PLAYER_HAND,
  LOOK_PLAYER_GRAVEYARD,
  LOOK_OPPONENT_GRAVEYARD,

  // Inputs to proceed game at "PLAY_CARD" Phase.
  PLAY_CARD,
  NO_PLAY_CARD,
  CANCEL_ATTACKER_CHOICE,
};

// Class to handle input from player.
class InputHandler {
 public:
  InputHandler(Game& game_);
  void ProcessInputCastCard(bool& cancel_choose_attacker);
  void ProcessInputChooseAttacker();

  //
  void ProcessInputChoosePlayerBench();
  void ProcessInputChooseOpponentBench();
  void ProcessInputChoosePlayerHand();
  void ProcessInputChooseOpponentHand();
  void ProcessInputChooseCardGraveyard();
  void ProcessInputChooseCardFromList();

 private:
  Game& game;
};

}  // namespace game
}  // namespace ccpp


#endif  // CCPP_INPUT_HPP