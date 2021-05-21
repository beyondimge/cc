#include "../include/input.hpp"

#include <iostream>
#include "../include/gameboard.hpp"

namespace ccpp {
namespace game {

InputHandler::InputHandler(Game& game_) : game(game_) {}

void InputHandler::ProcessInputChooseAttacker() {
  // todo - Once GUI is setup, it should be replaced by mouse click event
  std::cout << "Enter a command" << std::endl;
  std::cout << "0: Do not choose an attacker" << std::endl;
  std::cout << "1: Choose bench 1 as attacker," << std::endl;
  std::cout << "2: Choose bench 2 as attacker," << std::endl;
  std::cout << "3: Choose bench 3 as attacker," << std::endl;
  // std::cout << "4: Look at Player's graveyard," << std::endl;
  // std::cout << "5: Look at Opponent's graveyard." << std::endl;
  // todo - if 海神 is in player's bench, player can look at the top of player's
  // library.

  int input;
  std::cin >> input;

  InputChooseAttacker command = static_cast<InputChooseAttacker>(input);

  switch (command) {
    case InputChooseAttacker::LOOK_PLAYER_GRAVEYARD:
      break;

    case InputChooseAttacker::LOOK_OPPONENT_GRAVEYARD:
      break;

    case InputChooseAttacker::CHOOSE_NO_ATTACKER:
      // todo
      break;

    case InputChooseAttacker::CHOOSE_ATTACKER_FROM_BENCH1:
      // todo
      break;

    case InputChooseAttacker::CHOOSE_ATTACKER_FROM_BENCH2:
      // todo
      break;

    case InputChooseAttacker::CHOOSE_ATTACKER_FROM_BENCH3:
      // todo
      break;

    default:
      std::cout << "Invalid command:" << input << std::endl;
      break;
  }
}


void InputHandler::ProcessInputCastCard(bool& cancel_choose_attacker) {
  // todo - Once GUI is setup, it should be replaced by mouse click event
  std::cout << "Enter a command in integer." << std::endl;
  if (game.GetGameboard().GetPlayerBench().GetNumBench() > 0) {
    std::cout << "-1: Cancel the attacker choice," << std::endl;
  }
  std::cout << "0: Skip playing card this turn," << std::endl;

  Player& player = game.GetGameboard().GetPlayer();
  Hand& player_hand = player.GetHand();

  std::size_t num_cards_hand = player_hand.Size();
  int castable[num_cards_hand];
  int choice = 1;
  for (int position = 0; position < num_cards_hand; ++position) {
    const Card& card = player_hand[position];
    if (card.GetLevel() <= player.GetMana()) {
      std::cout << choice << ": Play \"" << card.GetName() << "\"," << std::endl;
      castable[choice] = position;
      choice++;
    }
  }

  int command;

  while (std::cin >> command) {
    if (command < -1 || command > num_cards_hand) {
      std::cout << "Input " << command << " is not valid." << std::endl;
      continue;
    } else {
      if (command == -1) {
        std::cout << "debug1" << std::endl;
        cancel_choose_attacker = true;
        break;
      } else if (command == 0) {
        // todo - once the program has network, it needs to send attacker choice and card to be casted.
        std::cout << "No card is played." << std::endl;
        break;
      } else if (command >= 1) {
        // todo - once the program has network, it needs to send attacker choice and card to be casted.
        std::cout << "debug3" << std::endl;
        player.CastCard(castable[command]);
        break;
      }
    }
  }
}

// todo - needs InputHandler's method to handle choosing attacker from fields
// (e.g. マジシャン) 


// todo - needs InputHandler's method to handle choosing card
// in bench (e.g. ビホルダー) 

// todo - needs InputHandler's method to choose A or B (e.g. 水使い)

// todo - needs InputHandler's method to handle
// choosing card from all card list (e.g. 蒐集王) 

// todo - needs InputHandler's method to handle choosing a card from opponent hand (e.g. 催眠術師

}  // namespace game
}  // namespace ccpp