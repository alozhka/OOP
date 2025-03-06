#include "HtmlDecoder.h"

std::string HtmlDecodeString(const std::string& html)
{
	std::string result;
	result.reserve(html.size());

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] == '&')
		{
			if (html.compare(i, 6, "&quot;") == 0)
			{
				result += '"';
				i += 5;
			}
			else if (html.compare(i, 6, "&apos;") == 0)
			{
				result += '\'';
				i += 5;
			}
			else if (html.compare(i, 4, "&lt;") == 0)
			{
				result += '<';
				i += 3;
			}
			else if (html.compare(i, 4, "&gt;") == 0)
			{
				result += '>';
				i += 3;
			}
			else if (html.compare(i, 5, "&amp;") == 0)
			{
				result += '&';
				i += 4;
			}
			else
			{
				result += html[i];
			}
		}
		else
		{
			result += html[i];
		}
	}
	return result;
}

void HtmlDecodeFile(std::istream& in, std::ostream& out)
{
	std::string line;
	while (std::getline(in, line))
	{
		out << HtmlDecodeString(line) << std::endl;
	}
}