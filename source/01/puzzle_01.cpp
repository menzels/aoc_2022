export module puzzle_01;

import std.core;

#include "puzzle_01_export.h"

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

export PUZZLE_01_EXPORT int MaxCalories()
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

  auto max = std::ranges::max(elves_sum_range, [](auto a, auto b)
                              { return a < b; });

  return max;

  // auto input_range = ReadInput("source/01/input.txt");

  // return std::ranges::max(input_range
  //       | std::views::lazy_split("")
  //       | std::views::transform([](auto subrange) {
  //   return std::accumulate(subrange
  //         | std::views::transform(std::stoi));
  // }));
}
