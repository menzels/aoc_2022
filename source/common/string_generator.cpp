export module StringGenerator;

import std.core;

export template <typename T>
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
