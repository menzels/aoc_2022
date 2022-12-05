export module puzzle_05;

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

std::istream &operator>>(std::istream &is, char const *pat)
{

  char ch;
  while (isspace(static_cast<unsigned char>(is.peek())))
    is.get(ch);

  while (*pat && is && *pat == is.peek() && is.get(ch))
  {
    ++pat;
  }

  // if we didn't reach the end of the pattern, matching failed (mismatch, premature EOF, etc.)
  if (*pat)
  {
    is.setstate(std::ios::failbit);
  }

  return is;
}

auto into_string = [](auto range)
{
  auto common = range | std::views::common;
  return std::string(common.begin(), common.end());
};

using Crate = char;

using Stack = std::stack<Crate>;
using Deck = std::array<Stack, 9>;

auto parse_crate = [](auto input) -> char
{
  auto crate = input | std::views::drop(1) | std::views::take(1);
  return crate.front();
};

auto parse_crate_lines = [](auto input) -> std::string
{
  auto res = input | std::views::chunk(4) //
             | std::views::transform(parse_crate);

  return into_string(res);
};

auto crate_not_empty = [](char value)
{
  return value != ' ';
};

void FillStack(auto &stack, auto range)
{
  for (auto const &el : range)
    stack.push(el);
}

Deck ParseDeck(auto deck_input)
{
  auto deck_rows = deck_input                                 //
                   | std::views::reverse                      //
                   | std::views::drop(1)                      //
                   | std::views::transform(parse_crate_lines) //
                   | std::views::join;

  Deck deck;
  for (auto i : std::views::iota(0, 9))
    FillStack(deck[i], deck_rows                   //
                           | std::views::drop(i)   //
                           | std::views::stride(9) //
                           | std::views::filter(crate_not_empty));

  return deck;
}

struct Move
{
  int from;
  int to;
  int amount;
};

void MoveCrates(Deck &deck, Move const &move)
{
  for (auto i : std::views::iota(0, move.amount))
    deck[move.to].push(deck[move.from].top()), deck[move.from].pop();
}

void MoveCratesAtOnce(Deck &deck, Move const &move)
{
  Stack temp;
  for (auto i : std::views::iota(0, move.amount))
    temp.push(deck[move.from].top()), deck[move.from].pop();
  for (auto i : std::views::iota(0, move.amount))
    deck[move.to].push(temp.top()), temp.pop();
}

std::istream &operator>>(std::istream &lhs, Move &move)
{
  return lhs >> "move" >> move.amount >> "from" >> move.from >> "to" >> move.to;
}

auto parse_moves_row = [](auto row) -> Move
{
  std::istringstream stream(row);
  Move move;
  stream >> move;
  move.from--;
  move.to--;
  return move;
};

void ApplyMoves(Deck &deck, auto moves_input)
{
  auto moves = moves_input | std::views::transform(parse_moves_row);
  for (Move move : moves)
    MoveCrates(deck, move);
}

void ApplyMoves9001(Deck &deck, auto moves_input)
{
  auto moves = moves_input | std::views::transform(parse_moves_row);
  for (Move move : moves)
    MoveCratesAtOnce(deck, move);
}

std::string GetTops(Deck const &deck)
{
  auto tops = deck | std::views::transform([](Stack stack)
                                           { return stack.top(); });
  return into_string(tops);
}

export std::string CratesOnTop()
{
  auto input_range = ReadInput("source/05/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto parts = input_vector             //
               | std::views::split(""); //

  auto it = parts.begin();
  auto deck_input = *it;
  auto moves_input = *++it;

  auto deck = ParseDeck(deck_input);

  ApplyMoves(deck, moves_input);

  return GetTops(deck);
}

export std::string CratesOnTop9001()
{
  auto input_range = ReadInput("source/05/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto parts = input_vector             //
               | std::views::split(""); //

  auto it = parts.begin();
  auto deck_input = *it;
  auto moves_input = *++it;

  auto deck = ParseDeck(deck_input);

  ApplyMoves9001(deck, moves_input);

  return GetTops(deck);
}
