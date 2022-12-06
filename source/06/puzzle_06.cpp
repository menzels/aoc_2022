export module puzzle_06;

import std.core;

auto ReadInput(std::string filename) -> std::string
{
  std::ifstream in(filename, std::ios_base::in);

  std::string line;
  getline(in, line);
  return line;
}

auto GetSyncer(int count)
{
  return [count](auto string)
  {
    std::set<char> set{string.begin(), string.end()};
    return set.size() != count;
  };
}

export int CharsBeforeSync(int count)
{
  auto input_range = ReadInput("source/06/input.txt");

  auto res = input_range                //
             | std::views::slide(count) //
             | std::views::take_while(GetSyncer(count));

  auto num = std::ranges::distance(res);
  return num + count;
}
