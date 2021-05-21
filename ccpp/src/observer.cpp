#include "../include/observer.hpp"

namespace ccpp {
namespace game {

void Subject::AddObserver(Observer* observer) { observers.insert(observer); }

void Subject::RemoveObserver(Observer* observer) { observers.erase(observer); }

void Subject::NotifyObservers(const Card& card, const Event& event) {
  for (auto observer : observers) {
    observer->onNotify(card, event);
  }
}

}  // namespace game
}  // namespace ccpp