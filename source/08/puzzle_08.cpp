export module puzzle_08;

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

int ctoi(char c)
{
  return c - '0';
}

struct Pos
{
  int col = 0;
  int row = 0;
  auto operator<=>(Pos const &other) const = default;
};

auto AbsPos(Pos pos) -> Pos
{
  return {std::abs(pos.col), std::abs(pos.row)};
}

auto TransposePos(Pos pos) -> Pos
{
  return {pos.row, pos.col};
}

struct Ctx
{
  Pos current_pos;
  int current_max = 0;
  std::set<Pos> visible_trees;
};

auto update_visibility = [](auto ctx, auto c)
{
  if (c > ctx.current_max)
  {
    ctx.visible_trees.emplace(AbsPos(ctx.current_pos));
    ctx.current_max = c;
  }
  ctx.current_pos.col++;

  return ctx;
};

auto FindVisibleTreesOneDirection(auto input_range, Ctx ctx, bool reverse = false) -> Ctx
{
  ctx.current_pos.row = -1;
  return std::accumulate(std::begin(input_range), std::end(input_range), ctx, [reverse](auto ctx, auto line)
                         {
                           ctx.current_pos.row++;
                           ctx.current_pos.col = reverse ? -line.size() + 1 : 0;
                           ctx.current_max = 0;
                           if (reverse)
                             return std::accumulate(std::rbegin(line), std::rend(line), ctx, update_visibility);
                           return std::accumulate(std::begin(line), std::end(line), ctx, update_visibility); //
                         });
}

auto into_string = [](auto range)
{
  auto common = range | std::views::common;
  return std::string(common.begin(), common.end());
};

auto Transpose(auto input_vector)
{
  int line_length = static_cast<int>(input_vector.size());
  auto one_view = input_vector | std::views::join;
  std::vector<std::string> columns;
  columns.reserve(line_length);
  for (auto i : std::views::iota(0, line_length))
    columns.emplace_back(into_string(one_view              //
                                     | std::views::drop(i) //
                                     | std::views::stride(line_length)));
  return columns;
}

void RecursiveTranspose(std::vector<std::string> &mat, int i0, int i1, int j0, int j1)
{
  int di = i1 - i0, dj = j1 - j0;
  const int LEAFSIZE = 32; // well ok caching still affects this one here
  if (di >= dj && di > LEAFSIZE)
  {
    int im = (i0 + i1) / 2;
    RecursiveTranspose(mat, i0, im, j0, j1);
    RecursiveTranspose(mat, im, i1, j0, j1);
  }
  else if (dj > LEAFSIZE)
  {
    int jm = (j0 + j1) / 2;
    RecursiveTranspose(mat, i0, i1, j0, jm);
    RecursiveTranspose(mat, i0, i1, jm, j1);
  }
  else
  {
    for (int i = i0; i < i1; i++)
      for (int j = j0; j < j1; j++)
        mat[j][i] = mat[i][j];
  }
}

template <class InIt, class OutIt>
void transpose(InIt const input, OutIt output,
               size_t const rows, size_t const columns,
               size_t const r1 = 0, size_t const c1 = 0,
               size_t r2 = ~(size_t)0, size_t c2 = ~(size_t)0,
               size_t const leaf = 0x20)
{
  if (!~c2)
  {
    c2 = columns - c1;
  }
  if (!~r2)
  {
    r2 = rows - r1;
  }
  size_t const di = r2 - r1, dj = c2 - c1;
  if (di >= dj && di > leaf)
  {
    transpose(input, output, rows, columns, r1, c1, (r1 + r2) / 2, c2);
    transpose(input, output, rows, columns, (r1 + r2) / 2, c1, r2, c2);
  }
  else if (dj > leaf)
  {
    transpose(input, output, rows, columns, r1, c1, r2, (c1 + c2) / 2);
    transpose(input, output, rows, columns, r1, (c1 + c2) / 2, r2, c2);
  }
  else
  {
    for (ptrdiff_t i1 = (ptrdiff_t)r1, i2 = (ptrdiff_t)(i1 * columns);
         i1 < (ptrdiff_t)r2; ++i1, i2 += (ptrdiff_t)columns)
    {
      for (ptrdiff_t j1 = (ptrdiff_t)c1, j2 = (ptrdiff_t)(j1 * rows);
           j1 < (ptrdiff_t)c2; ++j1, j2 += (ptrdiff_t)rows)
      {
        output[j2 + i1] = input[i2 + j1];
      }
    }
  }
}

export int NuberOfTreesVisible()
{
  auto input_range = ReadInput("source/08/input.txt");

  auto common = std::views::common(input_range);
  auto input_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto ctx = FindVisibleTreesOneDirection(input_vector, Ctx{});
  ctx = FindVisibleTreesOneDirection(input_vector, ctx, true);

  auto columns = Transpose(input_vector);

  auto ctx_cols = FindVisibleTreesOneDirection(columns, Ctx{});
  ctx_cols = FindVisibleTreesOneDirection(columns, ctx_cols, true);

  for (auto pos : ctx_cols.visible_trees | std::views::transform(&TransposePos))
    ctx.visible_trees.emplace(pos);

  return ctx.visible_trees.size();
}

auto view_distance = [](int our_height, auto range) -> int
{
  auto line_of_sight = range                                                //
                       | std::views::take_while([our_height](auto height) { //
                           return height < our_height;                      //
                         });
  return std::min(std::ranges::distance(range), std::ranges::distance(line_of_sight) + 1);
};

auto view_distance_opt = [](int our_height, auto range) -> int
{
  size_t cnt = 1;
  for (auto const v : range)
    if (v < our_height)
      cnt++;
    else
      break;

  return std::min(range.size(), cnt);
};

export int BestScenicScore()
{

  auto t1 = std::chrono::high_resolution_clock::now();

  auto input_range = ReadInput("source/08/input.txt");

  auto common = std::views::common(input_range);
  auto row_vector = std::vector(std::ranges::begin(common), std::ranges::end(common));

  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t2 - t1) << "\n";

  auto column_vector = Transpose(row_vector);

  auto t3 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t3 - t2) << "\n";

  int max_score = 0;
  for (int row = 1; row < row_vector.size() - 1; row++)
  {
    std::string_view row_data = row_vector[row];
    for (int col = 1; col < row_data.size() - 1; col++)
    {
      auto height = row_data[col];
      std::string_view column_data = column_vector[col];
      auto east = row_data.substr(col + 1);
      auto west = row_data.substr(0, col);
      auto south = column_data.substr(row + 1);
      auto north = column_data.substr(0, row);

      auto score = view_distance(height, east)                          //
                   * view_distance(height, west | std::views::reverse)  //
                   * view_distance(height, north | std::views::reverse) //
                   * view_distance(height, south);
      max_score = std::max(max_score, score);
    }
  }

  auto t4 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t4 - t3) << std::endl;

  return max_score;
}

export int BestScenicScore2()
{
  auto t1 = std::chrono::high_resolution_clock::now();

  std::ifstream in("source/08/input.txt", std::ios_base::in);

  int size = 0;
  std::vector<char> input;
  std::string line;
  while (getline(in, line))
  {
    size = line.size();
    input.insert(std::end(input), std::begin(line), std::end(line));
  }

  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t2 - t1) << "\n";

  auto column_vector = input;
  transpose(input.data(), column_vector.data(), size, size);

  auto t3 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t3 - t2) << "\n";

  int max_score = 0;
  for (int row = 1; row < size - 1; row++)
  {
    auto row_data = std::span(&input[row * size], size);
    for (int col = 1; col < size - 1; col++)
    {
      auto height = input[row * size + col];
      auto column_data = std::span(&column_vector[col * size], size);
      auto east = row_data.subspan(col + 1);
      auto west = row_data.subspan(0, col);
      auto south = column_data.subspan(row + 1);
      auto north = column_data.subspan(0, row);

      auto score = view_distance_opt(height, east)                          //
                   * view_distance_opt(height, west | std::views::reverse)  //
                   * view_distance_opt(height, north | std::views::reverse) //
                   * view_distance_opt(height, south);
      max_score = std::max(max_score, score);
    }
  }

  auto t4 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(t4 - t3) << std::endl;

  return max_score;
}
