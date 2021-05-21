#ifndef CCPP_GAME_HPP
#define CCPP_GAME_HPP

#include <memory>

#include "event.hpp"
#include "input.hpp"
#include "gameboard.hpp"

namespace ccpp {
namespace game {

class Gameboard;
class InputHandler;

// Class to handle event processing.
class Game {
 public:
  // Initializes the game.
  bool Initialize();
  // Runs the game loop until gameover.
  void RunLoop();
  // Shutdowns the game.
  void Shutdown();

  inline Gameboard& GetGameboard() const { return *gameboard; }

 private:
  std::unique_ptr<Gameboard> gameboard;
  std::unique_ptr<InputHandler> input_handler;
  std::unique_ptr<EventQue> event_que;

  // Helper functions for the game loop.
  void ProcessEvent(Event event);
  void Update();
  void Render();


  // Method to be called at beginning of turn 2 onwards.
  void ProcessTurnStart();
  // Method to be called at beginning of game (i.e. turn 1).
  void ProcessFirstTurnStart();
  void ProcessAttackerSelect();
  void ProcessCastSelect();
  void ProcessCombatStart();
  void ProcessCombat();
  void ProcessCombatEnd();
  void ProcessTurnEnd();

  void DisplayNumTurn();


  unsigned int GetNumTurn() { return num_turn; }

  // If initiative_change is true, it changes Gameboard::initiative to the other.
  void MoveInitiative();

  // Game should be quite once `IsRunning` became false.
  bool IsRunning;

  // Starts from num_turn = 1.
  unsigned int num_turn;

  bool skip_combat = false;
};


}  // namespace game
}  // namespace ccpp

#endif  // CCPP_GAME_HPP