#include "../include/event.hpp"

#include "../include/card.hpp"

namespace ccpp{
namespace game{

EventArgs::EventArgs(Location target_, int num_) : target(target_), num(num_){};
EventArgs::EventArgs(Location target_) : target(target_), num(-1) {};
EventArgs::EventArgs(int num_) : target(Location::DUMMY), num(-2) {};
EventArgs::EventArgs() : target(Location::DUMMY), num(-3) {};

Event::Event(int epriority, EventType etype, EventArgs eargs) : priority(epriority), type(etype), args(eargs){};
Event::Event(int epriority, EventType etype) : priority(epriority), type(etype), args() {};
Event::Event(EventType etype, EventArgs eargs) : priority(-1), type(etype), args(eargs){};
Event::Event(EventType etype) : priority(-1), type(etype), args(){};

EventQue::EventQue(Game& game_) : game(game_) {}

const Event& EventQue::top() { return queue.top(); }
void EventQue::pop() { queue.pop(); }
bool EventQue::empty() { return queue.empty(); }
void EventQue::push(Event event) { queue.push(event); }

} // namespace game
} // namespace ccpp