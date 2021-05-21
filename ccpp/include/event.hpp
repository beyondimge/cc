#ifndef CCPP_EVENT_HPP
#define CCPP_EVENT_HPP

#include <queue>
#include <tuple>

namespace ccpp {
namespace game {

class Game;

enum class Location;

enum class EventType {
  // Events related turn processing

  GAME_START,
  FIRST_TURN_BEGIN,
  TURN_BEGIN,
  CHOOSE_ATTACKER,
  CAST_CARD,
  COMBAT_START,
  COMBAT,
  COMBAT_END,
  TURN_END,

  CARD_WIN,
  CARD_LOSE,
  CARD_DRAW,         // 引き分け
  CARD_DAMAGED,      // ダメージを受ける
  CARD_DEAL_DAMEGE,  // ダメージを与える
  CARD_BOUNCED,      // 手札に戻る
  CARD_SEARCHED,
  CARD_DISCARD,      // 手札から墓地にカードを捨てる
  CARD_DESTROYED,
};


/*
template <typename ... Args>
class EventArgs {
 private:
  // パラメータパックを ... で展開して、
  // std::tupleクラステンプレートの引数として渡す
  std::tuple<Args...> values;
};
*/

class EventArgs {
 private:
  Location target;
  int num;

 public:
  EventArgs(Location target_, int num_);
  EventArgs(Location target_);
  EventArgs(int num_);
  EventArgs();
  inline Location GetTarget() { return target; }
  inline int GetNum() { return num; }
};

// 
class Event {
 public:
  Event(int priority, EventType etype, EventArgs eargs);
  Event(int priority, EventType etype);
  Event(EventType etype, EventArgs eargs);
  Event(EventType etype);

  inline const EventType GetType() const { return type; }
  inline const int GetPriority() const { return priority; }

  constexpr bool operator<(const Event& rhs) const {
    return priority < rhs.priority;
  }

 private:
  int priority;
  EventType type;
  EventArgs args;
};

// Class to store `Event` objects in priority queue.
// The higher the priority, the earlier it is processed.
class EventQue {
 public:
  EventQue(Game& game);
  // Remove the first element of the queue.
  void pop();
  // Returns true if the queue is empty.
  bool empty();
  // Returns const reference to the first element of the queue.
  const Event& top();
  // Push event to the queue.
  void push(Event event);

 private:
  std::priority_queue<Event> queue;
  Game& game;
};

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_EVENT_HPP