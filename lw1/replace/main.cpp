#include <fstream>
#include <iostream>

struct Input
{
  std::string in_file, out_file, search_string, replace_string;
};

void parse_input(const char *argv[], Input &input)
{
  input.in_file = argv[1];
  input.out_file = argv[2];
  input.search_string = argv[3];
  input.replace_string = argv[4];
}

std::optional<std::ifstream> setup_file(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
    return std::nullopt;

  return file;
}

bool replace(
  const std::string &in_filename, const std::string &out_filename,
  const std::string &search_str, const std::string &replace_str)
{
  std::ifstream in_file(in_filename);
  if (!in_file.is_open())
  {
    std::cerr << "Ошибка при открытии входного файла\n";
    return false;
  }
  std::ofstream out_file(out_filename);

  size_t pos = 0;
  std::string line;
  while (!in_file.eof())
  {
    getline(in_file, line);
    while (pos = line.find(search_str, pos), pos != std::string::npos)
    {
      line.replace(pos, search_str.length(), replace_str);
      pos += replace_str.length();
    }
    out_file << line;
  }

  in_file.close();
  out_file.close();
  return true;
}

int main(const int argc, const char *argv[])
{
  setlocale(LC_ALL, "rus");
  Input input;

  if (argc < 5)
  {
    std::cout << "Недостаточно аргументов\n";
    return 1;
  }

  parse_input(argv, input);

  if (!replace(input.in_file, input.out_file, input.search_string, input.replace_string))
  {
    return 1;
  }
  return 0;
}
