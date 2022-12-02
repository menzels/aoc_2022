export module puzzle_02;

import std.core;

template <typename T>
struct Generator
{
  class iterator;
  struct promise_type
  {
    using value_type = T;
    value_type value_;
    bool done_ = false;

    value_type get_value()
    {
      return value_;
    }

    bool finished()
    {
      return done_;
    }

    Generator get_return_object()
    {
      return std::coroutine_handle<promise_type>::from_promise(*this);
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept
    {
      done_ = true;
      return {};
    }
    void unhandled_exception() {}
    std::suspend_always yield_value(T value)
    {
      value_ = value;
      return {};
    }
    void return_void() {}
  };

public:
  Generator() = default;
  Generator(std::coroutine_handle<promise_type> handle) : h_(handle){};
  auto begin() const
  {
    return iterator{h_};
  }
  std::default_sentinel_t end() const noexcept { return std::default_sentinel; }

private:
  std::coroutine_handle<promise_type> h_;
};

template <class T>
class Generator<T>::iterator
{
public:
  using value_type = Generator<T>::promise_type::value_type;
  using difference_type = ptrdiff_t;

  iterator() = default;
  iterator(std::coroutine_handle<promise_type> handle) : coroutine_(handle) {}

  value_type operator*() const
  {
    if (coroutine_)
    {
      auto v = coroutine_.promise().get_value();
      return v;
    }
    return {};
  }
  iterator &operator++()
  {
    if (coroutine_)
      coroutine_.resume();

    return *this;
  }
  void operator++(int _)
  {
    return ++(*this);
  }

  bool operator==(iterator const &other) const = default;
  bool operator==(std::default_sentinel_t) const
  {
    return coroutine_.promise().finished();
  }

private:
  std::coroutine_handle<promise_type> coroutine_;
};

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
