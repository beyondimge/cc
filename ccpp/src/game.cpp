#include "../include/game.hpp"

#include <iostream>
#include <string>

#include "../include/gameboard.hpp"
#include "../include/input.hpp"


namespace ccpp {
namespace game {

// Game::Initialize() returns `true` if initialization succeeds and `false`
// otherwise. It creates `Gameboard` object which contains all components of
// game (e.g. Player, Library etc.).
bool Game::Initialize() {
  IsRunning = true;
  
  // Create Gameboard instance.
  gameboard = std::make_unique<Gameboard>(*this);
  event_que = std::make_unique<EventQue>(*this);
  input_handler = std::make_unique<InputHandler>(*this);

  return true;
}

void Game::Shutdown() {
  std::cout << "Game is shutdown." << std::endl;
}

void Game::RunLoop() {
  event_que->push(Event(EventType::FIRST_TURN_BEGIN));

  while (IsRunning) {
    // Process Inputs from user command.
    if (!event_que->empty()) {
      ProcessEvent(event_que->top());
      event_que->pop();
    }

    // Update all components of Game.
    Update();

    // Generate Outputs.
    Render();
  }
}


void Game::ProcessEvent(Event event) {
  EventType type = event.GetType();
  switch (type) {
    case EventType::FIRST_TURN_BEGIN:
      ProcessFirstTurnStart();
      break;
    
    case EventType::TURN_BEGIN:
      ProcessTurnStart();
      break;

    case EventType::CHOOSE_ATTACKER: 
      ProcessAttackerSelect();
      break;

    case EventType::CAST_CARD: 
      ProcessCastSelect();
      break;
    
    case EventType::COMBAT_START:
      ProcessCombatStart();
      break;

    case EventType::COMBAT:
      ProcessCombat();
      break;

    case EventType::COMBAT_END:
      ProcessCombatEnd();
      break;

    case EventType::TURN_END:
      ProcessTurnEnd();
      break;

    case EventType::CARD_WIN:
      // todo
      break;

    case EventType::CARD_LOSE:
      // todo
      break;

    case EventType::CARD_DRAW:
      // todo
      break;

    case EventType::CARD_DAMAGED:
      // todo
      break;

    case EventType::CARD_DEAL_DAMEGE:
      // todo
      break;

    case EventType::CARD_BOUNCED:
      // todo
      break;

    case EventType::CARD_SEARCHED:
      // todo
      break;

    case EventType::CARD_DISCARD:
      // todo
      break;

    case EventType::CARD_DESTROYED:
      // todo
      break;

    default:
      std::cout << "ERROR: Invalid Event" << std::endl;
      break;
  }
}


void Game::Update() { gameboard->Update(); }

void Game::MoveInitiative(){
  // todo - LockDragon
  if (gameboard->GetPlayer().GetWonLastTurn() || gameboard->GetPlayer().GetLostLastTurn()){
    gameboard->ChangeInitiative();
  }
}


void Game::DisplayNumTurn() { 
  std::cout << "---------- Turn " << num_turn << " ----------" << std::endl;
}


void Game::ProcessTurnStart() { 
  DisplayNumTurn();

  Player& player = gameboard->GetPlayer();
  Opponent& opponent = gameboard->GetOpponent();

  MoveInitiative();

  player.Draw();
  opponent.Draw();

  player.IncreaseMana();
  opponent.IncreaseMana();

  if (GetNumTurn() == 5)
  {
    player.AddManaIncrease(1);
    opponent.AddManaIncrease(1);
  }

  event_que->push(Event(EventType::CHOOSE_ATTACKER));
}


void Game::ProcessFirstTurnStart() {
  Player& player = gameboard->GetPlayer();
  Opponent& opponent = gameboard->GetOpponent();

  if (gameboard->GetInitiative()) {
    for (int i = 0; i < HAS_INITIATIVE; ++i) {
      player.Draw();
    }
    for (int i = 0; i < NO_INITIATIVE; ++i) {
      opponent.Draw();
    }
  } else {
    for (int i = 0; i < NO_INITIATIVE; ++i) {
      player.Draw();
    }
    for (int i = 0; i < HAS_INITIATIVE; ++i) {
      opponent.Draw();
    } 
  }

  DisplayNumTurn();
  event_que->push(Event(EventType::CHOOSE_ATTACKER));
}


void Game::ProcessAttackerSelect() {
  // Only when the player's bench has more than 1 cards, asks input to the player.
  if (gameboard->GetPlayerBench().GetNumBench() != 0) {
    input_handler->ProcessInputChooseAttacker();
  }
  event_que->push(Event(EventType::CAST_CARD));
}


void Game::ProcessCastSelect() {
  bool cancel_choose_attacker = false;
  input_handler->ProcessInputCastCard(cancel_choose_attacker);
  if (!cancel_choose_attacker) {
    event_que->push(Event(EventType::COMBAT_START));
  } else {
    // Player can cancel the attacker selection, and turn processing goes back if that's chosen.
    event_que->push(Event(EventType::CHOOSE_ATTACKER));
  }
}


void Game::ProcessCombatStart() {
  // combat can be forced skip by cast effect of 雪女.
  if (skip_combat) {
    skip_combat = false;
    event_que->push(Event(EventType::TURN_END));
  }
  else {
    event_que->push(Event(EventType::COMBAT));
  }
}


void Game::ProcessCombat() { 
  // todo - 

  event_que->push(Event(EventType::COMBAT_END)); 
}


void Game::ProcessCombatEnd() { 
  // todo - if player's attacker win
  // todo - if player's attacker lose
  // todo - if player's attacker draw 
  event_que->push(Event(EventType::TURN_END));
}


void Game::ProcessTurnEnd() {
  Field& field = gameboard->GetField();
  Card& player_attacker = field.GetPlayerAttacker();
  Card& opponent_attacker = field.GetOpponentAttacker();

  if (gameboard->GetInitiative()) {
    // todo - what if PlayerAttacker is null?
    if (field.IsPlayerAttacker() && player_attacker.GetHP() <= 0) {
      event_que->push(Event(EventType::CARD_DESTROYED, EventArgs(Location::PlayerField)));
    }
    // It is possible both PlayerAttacker and OpponentAttacker become HP = 0 and get destroyed (e.g. Draw, some LoseEffect like カエル).
    if (field.IsOpponentAttacker() && opponent_attacker.GetHP() <= 0) {
      event_que->push(Event(EventType::CARD_DESTROYED, EventArgs(Location::OpponentField)));
    }
  } else {
    if (field.IsOpponentAttacker() && opponent_attacker.GetHP() <= 0) {
      event_que->push(Event(EventType::CARD_DESTROYED, EventArgs(Location::OpponentField)));
    }
    if (field.IsPlayerAttacker() && player_attacker.GetHP() <= 0) {
      event_que->push(Event(EventType::CARD_DESTROYED, EventArgs(Location::PlayerField)));
    }
  }

  num_turn++;
  event_que->push(Event(EventType::TURN_BEGIN));
}


void Game::Render() {
    // todo - once GUI is setup.
}


}  // namespace game
}  // namespace ccpp