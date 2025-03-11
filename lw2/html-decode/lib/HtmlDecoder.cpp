#include "HtmlDecoder.h"

#include <map>

namespace Html::Decode
{
const std::map<std::string, char> ENCODED_HTML_SYMBOLS = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};
}

std::string HtmlDecode(const std::string& html)
{
	std::string result;
	result.reserve(html.size());

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] != '&')
		{
			result += html[i];
			continue;
		}

		bool replaced = false;
		for (const auto& [encoded, symbol] : Html::Decode::ENCODED_HTML_SYMBOLS)
		{
			if (html.compare(i, encoded.size(), encoded) == 0)
			{
				result += symbol;
				i += encoded.size() - 1;
				replaced = true;
				break;
			}
		}

		if (!replaced)
		{
			result += html[i];
		}
	}
	return result;
}

void HtmlDecode(std::istream& in, std::ostream& out)
{
	std::string line;
	while (std::getline(in, line))
	{
		out << HtmlDecode(line) << std::endl;
	}
}