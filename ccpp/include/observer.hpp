#ifndef CCPP_OBSERVER_HPP
#define CCPP_OBSERVER_HPP

#include <set>

#include "card.hpp"
#include "event.hpp"
#include "game.hpp"

namespace ccpp {
namespace game {


class Observer {
 public:
  virtual ~Observer(){};
  virtual void onNotify(const Card& card, Event event) = 0;
};

// The class Subject holds the list of observers that are waiting for notification.
class Subject {
 public:

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);
  void UpdateCard(Card& card);

  // Method `NotifyObservers` should be called when an event occurs.
 protected:
  void NotifyObservers(const Card& card, const Event& event);

 private:
  // std::set is used given each observer(i.e. card) should be added only once
  // without duplication.
  std::set<Observer*> observers;
};

class BattlefieldEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);

 private:
};

class WinningEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);

 private:
};

class LosingEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

class BenchEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

class EnterBattlefieldEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

class HandEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

class IntoHandEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

class GraveyardEffect : public Observer {
 public:
  virtual void onNotify(const Card& card, Event event);
};

}  // namespace game
}  // namespace ccpp

#endif  // CCPP_OBSERVER_HPP