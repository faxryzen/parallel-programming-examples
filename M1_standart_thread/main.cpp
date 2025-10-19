#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <boost/hash2/xxhash.hpp>
#include "boost-hash-wrapper.hpp"
#include "shapes.hpp"

void thread_func(const size_t tries, const size_t seed, sav::Segment seg)
{
  sav::HashWrapper< size_t, boost::hash2::xxhash_64 > prng;
  size_t count = 0;
  for (size_t i = 0; i < tries; ++i)
  {
    size_t res = prng(i + seed);
    long double x = (res % (seg.getBBox().width * 1000)) * 0.001 + seg.getBBox().center.x;
    long double y = ((res / 1000000) % (seg.getBBox().height * 1000)) * 0.001 + seg.getBBox().center.y;
    count += seg.isPointIn({x, y}) ? 1 : 0;
  }
  std::cout << static_cast< double >(count) / tries * 4 << '\n';
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

  size_t radius = 0, threads_amount = 0;
  std::cin >> radius >> threads_amount;
  if (!std::cin || radius <= 0)
  {
    std::cerr << "kldsf\n";
    return 1;
  }

  std::cout << "Let's do this\n";

  std::vector< std::thread > threads;
  //std::vector< long double > results(threads_amount);

  size_t seg_width = radius * 2.0 / threads_amount;
  for (size_t i = 0; i < threads_amount; ++i)
  {
    Segment segment({seg_width, radius * 2, {-1.0 * radius + seg_width * i, -1.0 * radius}}, radius);
    threads.push_back(std::thread{&thread_func, tries, seed, segment});
  }

  for (auto & th : threads)
  {
    th.join();
  }

  //std::cout << std::accumulate(results.begin(), results.end(), 0);

  return 0;
}
