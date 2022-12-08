export module puzzle_07;

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

struct Dir
{
  using Ptr = std::unique_ptr<Dir>;
  Dir() = default;
  Dir(std::string name, Dir *parent_dir) : name(name), parent_dir(parent_dir) {}
  static Ptr Create(std::string name, Dir &parent_dir)
  {
    return std::make_unique<Dir>(name, &parent_dir);
  }

  int Size() const { return size + subdirs_size; }

  std::string name;
  Dir *parent_dir = nullptr;
  std::unordered_map<std::string, Ptr> subdirs;
  int size = 0;
  int subdirs_size = 0;
};

void FillDir(auto range, Dir &dir)
{
}

Dir &FindRoot(Dir &current_dir)
{
  auto ref = std::ref(current_dir);
  while (ref.get().parent_dir != nullptr)
    ref = std::ref(*current_dir.parent_dir);

  return ref;
}

Dir &Cd(std::string name, Dir &current_dir)
{
  if (name == "..")
    return *current_dir.parent_dir;

  if (name == "/")
    return FindRoot(current_dir);

  return *current_dir.subdirs[name];
}

Dir &AddSubdir(std::string name, Dir &current_dir)
{
  current_dir.subdirs.emplace(std::make_pair(name, Dir::Create(name, current_dir)));
  return current_dir;
}

Dir &AddFile(int size, Dir &current_dir)
{
  current_dir.size += size;
  return current_dir;
}

int ParseFileSize(std::string line)
{
  return std::stoi(line.substr(0, line.find(' ')));
}

auto parse_command = [](std::string line, Dir &current_dir) -> Dir &
{
  if (line.substr(2, 2) == "cd")
    return Cd(line.substr(5), current_dir);

  return current_dir;
};

auto parse_output = [](std::string line, Dir &current_dir) -> Dir &
{
  if (line.substr(0, 3) == "dir")
    return AddSubdir(line.substr(4), current_dir);

  return AddFile(ParseFileSize(line), current_dir);
};

auto parse_line = [](std::string line, Dir &current_dir) -> Dir &
{
  if (line[0] == '$')
    return parse_command(line, current_dir);

  return parse_output(line, current_dir);
};

Dir BuildDirTree(auto input)
{
  Dir root;
  auto current_dir = std::ref(root);

  for (auto line : input)
    current_dir = parse_line(line, current_dir.get());

  return root;
}

int CollectSizes(Dir &current_dir)
{
  if (current_dir.subdirs.empty())
    return current_dir.size;

  for (auto &[name, dir] : current_dir.subdirs)
  {
    current_dir.subdirs_size += CollectSizes(*dir);
  }
  return current_dir.Size();
}

int SizeIfNotOver100000(Dir &current_dir)
{
  if (current_dir.Size() > 100000)
    return 0;

  return current_dir.Size();
}

int SumDirSizeMax100000(Dir &current_dir)
{
  int size = SizeIfNotOver100000(current_dir);
  if (current_dir.subdirs.empty())
    return size;

  for (auto &[name, dir] : current_dir.subdirs)
    size += SumDirSizeMax100000(*dir);

  return size;
}

export int SizeOfDirsMax100000()
{
  auto input_range = ReadInput("source/07/input.txt");

  Dir root = BuildDirTree(input_range);

  CollectSizes(root);

  return SumDirSizeMax100000(root);
}

int SmallestDirAbove(int low_limit, int high_limit, Dir &current_dir)
{
  if (current_dir.Size() > low_limit)
    high_limit = std::min(current_dir.Size(), high_limit);

  for (auto &[name, dir] : current_dir.subdirs)
    high_limit = std::min(high_limit, SmallestDirAbove(low_limit, high_limit, *dir));

  return high_limit;
}

export int SizeOfDirToBeDeleted()
{
  auto input_range = ReadInput("source/07/input.txt");

  Dir root = BuildDirTree(input_range);

  int total_used = CollectSizes(root);
  int total_space = 70000000;
  int needed = 30000000;
  int space_needed = needed - (total_space - total_used);

  return SmallestDirAbove(space_needed, total_used, root);
}
