export module puzzle_03;

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

auto print = [](auto const &view)
{
  for (std::cout << "{ "; auto const &element : view)
    std::cout << element << ' ';
  std::cout << "} \n";
};

auto priority = [](char c) constexpr
{
  return c <= 90 ? c - 65 + 27 : c - 96;
};

static auto test()
{
  static_assert(priority('a') == 1);
  static_assert(priority('l') == 12);
  static_assert(priority('z') == 26);
  static_assert(priority('A') == 27);
  static_assert(priority('Z') == 52);
}

auto is_equal = [](char a, char b)
{ return a == b; };

auto sort = [](auto item)
{
  std::ranges::sort(item);
  return item;
};

auto find_common = [](auto group) -> char
{
  auto common = group                         //
                | std::views::transform(sort) //
                | std::views::common;

  auto first = std::begin(common);
  auto ints = std::accumulate(++first, std::end(common), *first, [](std::string accu, auto v) { //
    std::string out;
    std::ranges::set_intersection(accu, v, std::back_inserter(out)); //
    return out;
  });
  return ints[0];
};

auto find_common_in_halves = [](auto line)
{
  auto bucket_size = line.size() / 2;

  auto buckets = line                                                                      //
                 | std::views::chunk(bucket_size) | std::views::transform([](auto range) { //
                     auto common = range | std::views::common;
                     return std::string(common.begin(), common.end());
                     // somehow i need to store into string here.
                     // meanwhile for puzzle 03 b it works directly
                   });

  return find_common(buckets);
};

export int
DuplicatedItemPrioritySum()
{
  auto input_range = ReadInput("source/03/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto results = input_vector                                   //
                 | std::views::transform(find_common_in_halves) //
                 | std::views::transform(priority)              //
                 | std::views::common;

  return std::accumulate(std::begin(results), std::end(results), 0); // need std::ranges::accumulate !!!
}

export int
BadgePrioritySum()
{
  auto input_range = ReadInput("source/03/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto results = input_vector                         //
                 | std::views::chunk(3)               //
                 | std::views::transform(find_common) //
                 | std::views::transform(priority)    //
                 | std::views::common;

  return std::accumulate(std::begin(results), std::end(results), 0); // need std::ranges::accumulate !!!
}
