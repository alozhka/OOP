#include "CHttpUrl.h"

#include <iostream>

void PrintUrl(std::ostream& os, const CHttpUrl& url)
{
	os << "URL: " << url.GetUrl() << "\n";
	os << "Domain: " << url.GetDomain() << "\n";
	os << "Document: " << url.GetDocument() << "\n";
	os << "Protocol: " << (url.GetProtocol() == Protocol::HTTP ? "HTTP" : "HTTPS") << "\n";
	os << "Port: " << url.GetPort() << "\n\n";
}

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintUrl(std::cout, url);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return EXIT_SUCCESS;
}