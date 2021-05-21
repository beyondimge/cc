#include "../include/utils.hpp"

#include <stdexcept>

namespace ccpp {
// Returns random integer with uniform distribution [0, num).
// E.g. RandomDiscrete(2) returns 0 or 1.
bool RandomDiscrete(unsigned int num) {
  std::random_device get_rand_dev;
  std::mt19937_64 get_rand_mt(get_rand_dev());  // seedに乱数を指定

  std::uniform_int_distribution<int> dist(0, num - 1);

  return dist(get_rand_mt);
}

}  // namespace ccpp