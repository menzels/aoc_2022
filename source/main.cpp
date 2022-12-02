import puzzle_01;
import puzzle_02;

import std.core;

auto CallTimed(auto &&f)
{
  auto t1 = std::chrono::high_resolution_clock::now();
  auto ret = f();
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t2 - t1) << " ";
  return std::move(ret);
}

int main()
{
  std::cout << std::format("AOC 2022 01_a: The Elf with the most calories carries {0} calories!\n", CallTimed(MaxCalories));
  std::cout << std::format("AOC 2022 01_b: The 3 Elves carrying most calories carry {0} calories!\n", CallTimed(SumCaloriesTop3Elves));
  std::cout << std::format("AOC 2022 02_a: My score playing RPS by the strategy guide will be {0}!\n", CallTimed(RockPaperScissorsScore));
  std::cout << std::format("AOC 2022 02_b: My score playing the correct strategy will be {0}!\n", CallTimed(RockPaperScissorsScoreCorretcStrategy));
  return 0;
}
