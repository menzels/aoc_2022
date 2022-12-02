import puzzle_01;

import std.core;

int main()
{
  std::cout << std::format("AOC 2022 01_a: The Elf with the most calories carries {0} calories!\n", MaxCalories());
  std::cout << std::format("AOC 2022 01_b: The 3 Elves carrying most calories carry {0} calories!\n", SumCaloriesTop3Elves());
  return 0;
}
