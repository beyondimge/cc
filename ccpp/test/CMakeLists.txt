cmake_minimum_required(VERSION 3.1.0)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(card_test card_test.cpp ../src/card.cpp)
add_executable(event_test event_test.cpp ../src/event.cpp)
add_executable(deck_test deck_test.cpp ../src/deck.cpp ../src/card.cpp)
target_link_libraries(card_test GTest::GTest GTest::Main)
target_link_libraries(event_test GTest::GTest GTest::Main)
target_link_libraries(deck_test GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})

# Google Testの各テストケースごとにCTestのテストを作成する
gtest_add_tests(TARGET card_test)
gtest_add_tests(TARGET event_test)
gtest_add_tests(TARGET deck_test)

# CTestのテストをひとつだけ作成する
#add_test(NAME AllTests COMMAND TestSample1)