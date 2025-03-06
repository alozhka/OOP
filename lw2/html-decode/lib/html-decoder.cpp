#include "html-decoder.h"

#include <ostream>

std::string HtmlDecodeString(std::string const& html)
{
	std::string result;
	result.reserve(html.size());

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] == '&')
		{
			if (html.compare(i, 6, "&quot;"))
			{
				result += '"';
				i += 6;
			}
			else if (html.compare(i, 6, "&apos;"))
			{
				result += '\'';
				i += 6;
			}
			else if (html.compare(i, 6, "&lt;"))
			{
				result += '<';
				i += 6;
			}
			else if (html.compare(i, 6, "&gt;"))
			{
				result += '>';
				i += 6;
			}
			else if (html.compare(i, 6, "&amp;"))
			{
				result += '&';
				i += 6;
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