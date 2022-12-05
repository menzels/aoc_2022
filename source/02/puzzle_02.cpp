export module puzzle_02;

import StringGenerator;

import std.core;

auto ReadInput(std::string filename) -> Generator<std::string>
{
  std::ifstream in(filename, std::ios_base::in);

  std::string line;
  while (getline(in, line))
  {
    co_yield line;
  }
}

std::map<std::string, int> strategy1 = {
    {"B X", 1},
    {"C Y", 2},
    {"A Z", 3},
    {"A X", 4},
    {"B Y", 5},
    {"C Z", 6},
    {"C X", 7},
    {"A Y", 8},
    {"B Z", 9},
};

int score1(std::string const &game)
{
  return strategy1[game];
}

export int RockPaperScissorsScore()
{
  auto results = ReadInput("source/02/input.txt") //
                 | std::views::transform(&score1) //
                 | std::views::common;

  return std::accumulate(std::begin(results), std::end(results), 0); // need std::ranges::accumulate !!!
}

std::map<std::string, int> strategy2 = {
    {"B X", 1},
    {"C Y", 6},
    {"A Z", 8},
    {"A X", 3},
    {"B Y", 5},
    {"C Z", 7},
    {"C X", 2},
    {"A Y", 4},
    {"B Z", 9},
};

int score2(std::string const &game)
{
  return strategy2[game];
}

export int RockPaperScissorsScoreCorretcStrategy()
{
  auto results = ReadInput("source/02/input.txt") //
                 | std::views::transform(&score2) //
                 | std::views::common;

  return std::accumulate(std::begin(results), std::end(results), 0); // need std::ranges::accumulate !!!
}
