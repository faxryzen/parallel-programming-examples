#include <thread>
#include <iostream>
#include <boost/hash2/xxhash.hpp>
#include "boost-hash-wrapper.hpp"

int main(int argc, char * argv[])
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Usage: ./prog [TRIES] [SEED = 0]\n";
    return 1;
  }
  if (!std::isdigit(argv[1][0]))
  {
    std::cerr << "[TRIES] and [SEED] should be positive\n";
    return 1;
  }
  //const size_t tries = std::atoi(argv[1]);
  sav::HashWrapper< size_t, boost::hash2::xxhash_64 > seed_gen;
  size_t res = seed_gen(45);
  std::cout << res << '\n';
  return 0;
}
