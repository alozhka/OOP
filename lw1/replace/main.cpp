#include <fstream>
#include <iostream>

constexpr ushort ARGS_AMOUNT = 5;
const std::string HELP_IDENTIFIER = "-h";

struct Input
{
  std::string inFile, outFile, searchString, replaceString;
};

void ParseInput(const char *argv[], Input &input)
{
  input.inFile = argv[1];
  input.outFile = argv[2];
  input.searchString = argv[3];
  input.replaceString = argv[4];
}

void ParseInputFromStdIn(Input &input)
{
  std::cin >> input.searchString;
  std::cin >> input.replaceString;
}

bool Replace(
  const std::string &inFilename, const std::string &outFilename,
  const std::string &searchStr, const std::string &replaceStr)
{
  std::ifstream inFile(inFilename);
  if (!inFile.is_open())
  {
    std::cerr << "Ошибка при открытии входного файла\n";
    return false;
  }
  std::ofstream outFile(outFilename);

  size_t pos = 0;
  std::string line;
  while (!inFile.eof())
  {
    getline(inFile, line);
    while (pos = line.find(searchStr, pos), pos != std::string::npos)
    {
      line.replace(pos, searchStr.length(), replaceStr);
      pos += replaceStr.length();
    }
    outFile << line;
  }

  inFile.close();
  outFile.close();
  return true;
}


int main(const int argc, const char *argv[])
{
  setlocale(LC_ALL, "rus");
  Input input;

  if (argc == 1)
  {
    ParseInputFromStdIn(input);
    Replace(input.searchString, input.replaceString);
  } else
  {
    if (argv[1] == HELP_IDENTIFIER)
    {
      std::cout << "Usage\n";
      return 0;
    }
    if (argc < 5)
    {
      std::cout << "ERROR\n";
      return 1;
    }
    ParseInput(argv, input);
    if (!Replace(input.inFile, input.outFile, input.searchString, input.replaceString))
    {
      return 1;
    }
  }
  return 0;
}
