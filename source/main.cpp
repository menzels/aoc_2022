import puzzle_01;
import puzzle_02;

import std.core;

int main()
{
  std::cout << std::format("AOC 2022 01_a: The Elf with the most calories carries {0} calories!\n", MaxCalories());
  std::cout << std::format("AOC 2022 01_b: The 3 Elves carrying most calories carry {0} calories!\n", SumCaloriesTop3Elves());
  std::cout << std::format("AOC 2022 02_a: My score playing RPS by the strategy guide will be {0}!\n", RockPaperScissorsScore());
  std::cout << std::format("AOC 2022 02_b: My score playing the correct strategy will be {0}!\n", RockPaperScissorsScoreCorretcStrategy());
  return 0;
}
