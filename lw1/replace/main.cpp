#include <fstream>
#include <iostream>

constexpr ushort ARGS_AMOUNT = 5;
const std::string HELP_IDENTIFIER = "-h";

struct Input
{
  std::string inFile, outFile, searchString, replaceString, signleLine;
};

void ParseInputFromCommandLine(const char *argv[], Input &input)
{
  input.inFile = argv[1];
  input.outFile = argv[2];
  input.searchString = argv[3];
  input.replaceString = argv[4];
}

bool TryParseInputFromStdIn(Input &input)
{
  std::cin >> input.searchString;
  std::cin >> input.replaceString;
  return !!(std::cin >> input.signleLine);
}

std::string ReplaceSingleLine(const std::string& line, const std::string &searchStr, const std::string &replaceStr)
{
  size_t pos = 0;
  std::string result;

  while (pos < line.length())
  {
    const size_t foundPos = line.find(searchStr, pos);
    if (foundPos < line.length())
    {
      result.append(line, pos, foundPos - pos);
      result.append(replaceStr);
      pos = foundPos + searchStr.length();
    }
    else
    {
      result.append(line, pos);
      pos = std::string::npos;
    }
  }
  return result;

}

bool TryReplaceInFile(
  const std::string &inFilename,
  const std::string &outFilename,
  const std::string &searchStr,
  const std::string &replaceStr
)
{
  std::ifstream inFile(inFilename);
  if (!inFile.is_open())
  {
    return false;
  }
  std::ofstream outFile(outFilename);
  if (!outFile.is_open())
  {
    return false;
  }

  std::string line;
  while (!getline(inFile, line))
  {
    std::string replacedLine = ReplaceSingleLine(line, searchStr, replaceStr);
    outFile << replacedLine;
  }

  inFile.close();
  outFile.close();
  return true;
}


void PrintHelp()
{
  std::cout << "Usage: replace <input_file> <output_file> <search_string> <replace_string>\n";
}


int main(const int argc, const char *argv[])
{
  setlocale(LC_ALL, "rus");
  Input input;

  if (argc == 1)
  {
    if (!TryParseInputFromStdIn(input))
    {
      std::cout << "ERROR\n";
      return 0;
    }
    std::cout << ReplaceSingleLine(input.signleLine, input.searchString, input.replaceString) << std::endl;
  } else
  {
    if (argv[1] == HELP_IDENTIFIER)
    {
      std::cout << "Usage: replace <input_file> <output_file> <search_string> <replace_string>\n";
      return 0;
    }
    if (argc < ARGS_AMOUNT)
    {
      std::cout << "ERROR\n";
      return 1;
    }
    ParseInputFromCommandLine(argv, input);
    if (!TryReplaceInFile(input.inFile, input.outFile, input.searchString, input.replaceString))
    {
      std::cout << "ERROR\n";
      return 1;
    }
  }

  return 0;
}
