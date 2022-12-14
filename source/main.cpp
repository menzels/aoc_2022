import puzzle_01;
import puzzle_02;
import puzzle_03;
import puzzle_04;
import puzzle_05;
import puzzle_06;
import puzzle_07;
import puzzle_08;

import std.core;

auto CallTimed(auto &&f, auto &&...args)
{
  auto t1 = std::chrono::high_resolution_clock::now();
  auto ret = f(args...);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t2 - t1) << " ";
  return std::move(ret);
}

auto Print(auto &&string)
{
  std::cout << string << std::flush;
}

int main()
{
  Print(std::format("AOC 2022 01_a: The Elf with the most calories carries {0} calories!\n", CallTimed(MaxCalories)));
  Print(std::format("AOC 2022 01_b: The 3 Elves carrying most calories carry {0} calories!\n", CallTimed(SumCaloriesTop3Elves)));
  Print(std::format("AOC 2022 02_a: My score playing RPS by the strategy guide will be {0}!\n", CallTimed(RockPaperScissorsScore)));
  Print(std::format("AOC 2022 02_b: My score playing the correct strategy will be {0}!\n", CallTimed(RockPaperScissorsScoreCorretcStrategy)));
  Print(std::format("AOC 2022 03_a: The combined priority of common items in rucksacks is {0}!\n", CallTimed(DuplicatedItemPrioritySum)));
  Print(std::format("AOC 2022 03_b: The combined priority of badge items in rucksacks is {0}!\n", CallTimed(BadgePrioritySum)));
  Print(std::format("AOC 2022 04_a: The number of fully redundant work assignments is {0}!\n", CallTimed(FullyRedundantWorkAssignmentCount)));
  Print(std::format("AOC 2022 04_b: The number of work assignments with overlap is {0}!\n", CallTimed(WorkAssignmentsWithOverlapCount)));
  Print(std::format("AOC 2022 05_a: The crates on top are {0}!\n", CallTimed(CratesOnTop)));
  Print(std::format("AOC 2022 05_b: For the 9001 version, the crates on top are {0}!\n", CallTimed(CratesOnTop9001)));
  Print(std::format("AOC 2022 06_a: Chars received before sync {0}!\n", CallTimed(CharsBeforeSync, 4)));
  Print(std::format("AOC 2022 06_b: Chars received before message {0}!\n", CallTimed(CharsBeforeSync, 14)));
  Print(std::format("AOC 2022 07_a: Total size of Directories < 100000 {0}!\n", CallTimed(SizeOfDirsMax100000)));
  Print(std::format("AOC 2022 07_b: Size of Directory that should be deleted {0}!\n", CallTimed(SizeOfDirToBeDeleted)));
  Print(std::format("AOC 2022 08_a: Number of visible trees is {0}!\n", CallTimed(NuberOfTreesVisible)));
  Print(std::format("AOC 2022 08_b: Best scenic score is {0}!\n", CallTimed(BestScenicScore)));
  Print(std::format("AOC 2022 08_b: Best scenic score is {0}!\n", CallTimed(BestScenicScore2)));
  return 0;
}
