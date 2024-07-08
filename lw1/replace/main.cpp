#include <iostream>

struct Input
{
    std::string in_file, out_file, search_string, replace_string;
};

void parse_input(const char* argv[], Input& input)
{
    input.in_file = argv[1];
    input.out_file = argv[2];
    input.search_string = argv[3];
    input.replace_string = argv[4];
}

int main(const int argc, const char* argv[])
{
    setlocale(LC_ALL, "rus");
    Input input;

    if(argc < 5)
    {
        std::cout << "Недостаточно аргументов\n";
        return 1;
    }

    parse_input(argv, input);

    return 0;
}
