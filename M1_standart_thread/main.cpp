#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <boost/hash2/xxhash.hpp>
#include <boost-hash-wrapper.hpp>
#include "shapes.hpp"

bool is_point_in(const sav::point_t p, size_t radius)
{
  long double dist = std::sqrt(std::pow(p.x, 2) + std::pow(p.y, 2));
  if (dist > radius)
  {
    return false;
  }
  return true;
}

template < typename PRNG >
sav::point_t get_random_point(size_t rad, size_t seed, PRNG prng)
{
  sav::bb_t bb = {rad * 2, rad * 2, {0, 0}};
  size_t res = prng(seed);
  long double x = (res % (bb.width * 1000)) * 0.001 + bb.center.x;
  long double y = ((res / 1000000) % (bb.height * 1000)) * 0.001 + bb.center.y;
  return {x, y};
}

void calc_monte_carlo(double * res, size_t id, size_t tries, size_t seed, size_t rad)
{
  size_t count = 0;
  sav::HashWrapper< size_t, boost::hash2::xxhash_64 > prng;
  for (size_t i = id * tries; i < (id + 1) * tries; ++i)
  {
    count += is_point_in(get_random_point(rad, i + seed, prng), rad) ? 1 : 0;
  }
  *res = static_cast< double >(count) / tries;
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

  std::cout << "Now type circle radius and number of threads for calculation\n";
  std::vector< std::pair< size_t, size_t > > tasks = {};
  size_t radius = 0, threads_amount = 0;
  while (std::cin >> radius >> threads_amount)
  {
    if (radius == 0 || threads_amount == 0)
    {
      std::cerr << "Radius/threads amount can't be equal zero\n";
      return 1;
    }
    tasks.push_back({radius, threads_amount});
  }

  if (tasks.empty())
  {
    std::cerr << "No tasks to complete\n";
    return 2;
  }

  std::cout << "Let's do this\n";

  std::vector< std::vector< double > > tasks_results(tasks.size());
  std::vector< std::vector< std::thread > > threads;

  for (size_t i = 0; i < tasks.size(); ++i)
  {
    std::vector< std::thread > threads;
    tasks_results[i].resize(threads_amount);
    size_t current_tries = tries / threads_amount;
    if (!current_tries)
    {
      std::cerr << "Very small amount of tries of thread amount to big\n";
      return 3;
    }

    for (size_t j = 0; j < threads_amount; ++j)
    {
      threads.push_back(std::thread{&calc_monte_carlo, &tasks_results[i][j], j, current_tries, seed, tasks[i].first});
    }
  }

  //for (auto & th : threads)
  //{
  //  th.join();
  //}

  //std::cout << std::accumulate(results.begin(), results.end(), 0);

  return 0;
}
