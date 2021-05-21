#include <gtest/gtest.h>

#include "../include/event.hpp"

TEST(event, priority) {
  
  ccpp::game::EventQue que;  // todo - needs to mock out
  ccpp::game::Event event1(-1, ccpp::game::EventType::TURN_END);
  ccpp::game::Event event2(0, ccpp::game::EventType::CARD_DESTROYED);
  ccpp::game::Event event3(1, ccpp::game::EventType::CARD_BOUNCED);
  ccpp::game::Event event4(5, ccpp::game::EventType::CARD_LOSE);

  que.push(event1);
  que.push(event3);
  que.push(event4);
  que.push(event2);

  EXPECT_EQ(5, que.top().GetPriority());
  que.pop();
  EXPECT_EQ(1, que.top().GetPriority());
  que.pop();
  EXPECT_EQ(0, que.top().GetPriority());
  que.pop();
  EXPECT_EQ(-1, que.top().GetPriority());
  que.pop();
}