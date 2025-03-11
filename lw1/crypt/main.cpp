#include <fstream>
#include <iostream>

struct Args
{
	bool isDecrypt;
	std::string inFilename, outFilename;
	uint8_t key;
};

void PrintHelp()
{
	std::cout << "Usage: crypt <crypt|decrypt> <input file> <output file> <key>";
}

bool IsNumericString(const std::string& s)
{
	for (const char c : s)
	{
		if (!std::isdigit(c) && c != '.' && c != '-')
		{
			return false;
		}
	}
	return true;
}

Args ParseArgs(const char* argv[])
{
	Args args;
	const std::string operation = argv[1];

	if (operation == "crypt")
	{
		args.isDecrypt = false;
	}
	else if (operation == "decrypt")
	{
		args.isDecrypt = true;
	}
	else
	{
		throw std::invalid_argument("Unsupported operation");
	}

	if (!IsNumericString(argv[4]))
	{
		throw std::invalid_argument("Invalid key");
	}

	const int key = std::stoi(argv[4]);
	if (key < 0 || key > 255)
	{
		throw std::out_of_range("Key must be in range [0, 255]");
	}

	args.inFilename = argv[2];
	args.outFilename = argv[3];
	args.key = static_cast<uint8_t>(key);
	return args;
}

uint8_t MixBits(uint8_t byte)
{
	return byte & 0b1000'0000 >> 2 | byte & 0b0110'0000 >> 5 | byte & 0b0001'1000 << 3 | byte & 0b0000'0111 << 2;
}

uint8_t CryptByte(uint8_t byte, uint8_t key)
{
	return MixBits(byte) ^ key;
}
uint8_t DecryptByte(uint8_t byte, uint8_t key)
{
	return MixBits(byte ^ key);
}

void CopyFileWithEncryption(const std::string& inFilename, const std::string& outFilename, uint8_t key, bool isDecrypt)
{
	std::ifstream in(inFilename, std::ios::binary);
	if (!in.is_open())
	{
		throw std::invalid_argument("Cannot open input file");
	}

	std::ofstream out(outFilename, std::ios::binary);
	if (!out.is_open())
	{
		throw std::invalid_argument("Cannot open output file");
	}

	char ch;
	while (in.get(ch))
	{
		uint8_t byte = isDecrypt ? DecryptByte(ch, key) : CryptByte(ch, key);
		out.put(byte);
	}

	in.close();
	out.close();
}

int main(const int argc, const char* argv[])
{
	if (argc < 5)
	{
		PrintHelp();
		return 1;
	}

	try
	{
		const Args args = ParseArgs(argv);
		CopyFileWithEncryption(args.inFilename, args.outFilename, args.key, args.isDecrypt);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
