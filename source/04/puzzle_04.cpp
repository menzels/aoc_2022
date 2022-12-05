export module puzzle_04;

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

struct Assignment
{
  int from;
  int to;
};

constexpr bool AssignmentContains(Assignment const &ass, int val)
{
  return val == std::clamp(val, ass.from, ass.to);
}

constexpr bool HasOverlap(Assignment const &a, Assignment const &b)
{
  return AssignmentContains(b, a.from)    //
         || AssignmentContains(b, a.to)   //
         || AssignmentContains(a, b.from) //
         || AssignmentContains(a, b.to);
}

constexpr bool AssignmentContains(Assignment a, Assignment b)
{
  return AssignmentContains(b, a.from) //
         && AssignmentContains(b, a.to);
}

constexpr bool IsRedundant(Assignment const &a, Assignment const &b)
{
  return AssignmentContains(a, b) || AssignmentContains(b, a);
}

static void test()
{
  static_assert(!AssignmentContains({2, 4}, 5));
  static_assert(AssignmentContains({2, 4}, 3));
  static_assert(AssignmentContains({2, 4}, 2));
  static_assert(AssignmentContains({2, 4}, 4));
  static_assert(!AssignmentContains({2, 4}, 1));

  static_assert(!HasOverlap({2, 4}, {5, 5}));
  static_assert(HasOverlap({2, 4}, {4, 5}));
  static_assert(HasOverlap({2, 4}, {3, 5}));
  static_assert(HasOverlap({2, 4}, {2, 5}));
  static_assert(HasOverlap({2, 4}, {1, 5}));

  static_assert(!IsRedundant({2, 4}, {1, 3}));
  static_assert(IsRedundant({2, 4}, {2, 3}));
  static_assert(IsRedundant({2, 3}, {2, 4}));
}

auto my_stoi = [](auto string)
{
  return std::stoi(string);
};

auto into_string = [](auto range)
{
  auto common = range | std::views::common;
  return std::string(common.begin(), common.end());
};

auto parse_assignment = [](auto str)
{
  auto range =
      str                                  //
      | std::views::lazy_split('-')        //
      | std::views::transform(into_string) //
      | std::views::transform(my_stoi);

  auto it = range.begin();
  return Assignment{.from = *it, .to = *++it};
};

auto parse_assignment_pair = [](std::string &line)
{
  auto r = line                          //
           | std::views::lazy_split(',') //
           | std::views::transform(parse_assignment);

  auto it = r.begin();
  auto ass_a = *it;
  auto ass_b = *++it;
  return std::make_pair(ass_a, ass_b);
};

auto is_redundant = [](auto ass_pair)
{
  auto [a, b] = ass_pair;
  return IsRedundant(a, b);
};

export int
FullyRedundantWorkAssignmentCount()
{
  auto input_range = ReadInput("source/04/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto assignment_pairs = input_vector                                    //
                          | std::views::transform(parse_assignment_pair); //

  return std::ranges::count_if(assignment_pairs, is_redundant);
}

auto has_overlap = [](auto ass_pair)
{
  auto [a, b] = ass_pair;
  return HasOverlap(a, b) || HasOverlap(b, a);
};

export int
WorkAssignmentsWithOverlapCount()
{
  auto input_range = ReadInput("source/04/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto assignment_pairs = input_vector                                    //
                          | std::views::transform(parse_assignment_pair); //

  return std::ranges::count_if(assignment_pairs, has_overlap);
}
