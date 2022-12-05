export module puzzle_01;

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

auto my_stoi = [](auto string)
{
  return std::stoi(string);
};

export int MaxCalories()
{
  static_assert(std::ranges::input_range<Generator<std::string>>);

  auto input_range = ReadInput("source/01/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto elves_sum_range = input_vector                 //
                         | std::views::lazy_split("") //
                         | std::views::transform(     //
                               [](auto view)
                               {
                                 auto common_view = view                             //
                                                    | std::views::transform(my_stoi) //
                                                    | std::views::common;

                                 return std::accumulate(std::begin(common_view), std::end(common_view), 0); // need std::ranges::accumulate !!!
                               });

  return std::ranges::max(elves_sum_range, [](auto a, auto b)
                          { return a < b; });

  // auto input_range = ReadInput("source/01/input.txt");

  // return std::ranges::max(input_range
  //       | std::views::lazy_split("")
  //       | std::views::transform([](auto subrange) {
  //   return std::accumulate(subrange
  //         | std::views::transform(std::stoi));
  // }));
}

export int SumCaloriesTop3Elves()
{
  static_assert(std::ranges::input_range<Generator<std::string>>);

  auto input_range = ReadInput("source/01/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto elves_sum_range = input_vector                 //
                         | std::views::lazy_split("") //
                         | std::views::transform(     //
                               [](auto view)
                               {
                                 auto common_view = view                             //
                                                    | std::views::transform(my_stoi) //
                                                    | std::views::common;

                                 return std::accumulate(std::begin(common_view), std::end(common_view), 0); // need std::ranges::accumulate !!!
                               });

  std::vector<int> top_3(3);
  std::ranges::partial_sort_copy(elves_sum_range, top_3, std::greater{});

  return std::accumulate(std::begin(top_3), std::end(top_3), 0);
}
