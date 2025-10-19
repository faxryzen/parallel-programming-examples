#include <thread>
#include <iostream>
#include <vector>
#include <boost/hash2/xxhash.hpp>
#include "boost-hash-wrapper.hpp"
#include "shapes.hpp"

void thread_func(const size_t tries, sav::Tile tile)
{
  sav::HashWrapper< size_t, boost::hash2::xxhash_64 > prng;
  for (size_t i = 0; i < tries; ++i)
  {
    std::cout << prng(i) % tile.getBoundingBox().height;
  }
}

int main(int argc, char * argv[])
{
  using namespace sav;

  if (argc < 2 || argc > 3)
  {
    std::cerr << "Usage: ./prog [TRIES] [SEED = 0]\n";
    return 1;
  }
  if (argv[1][0] == '-')
  {
    std::cerr << "[TRIES] should be positive number\n";
    return 1;
  }
  if (argc == 3 && argv[2][0] == '-')
  {
    std::cerr << "[SEED] should be positive number\n";
    return 1;
  }

  const size_t tries = std::stoull(argv[1]);
  const size_t seed = argc == 3 ? std::stoull(argv[2]) : 0;

  size_t radius = 0, threads = 0;
  std::cin >> radius >> threads;
  if (!std::cin)
  {
    std::cerr << "kldsf\n";
    return 1;
  }





  //std::vector< bb_t > tiles;

  sav::HashWrapper< size_t, boost::hash2::xxhash_64 > seed_gen;
  size_t res = seed_gen(seed);
  std::cout << tries << ' ' << res << '\n';
  return 0;
}
