#include "HtmlDecoder.h"

#include <map>

namespace Html::Decode
{
const std::map<std::string, char> ENCODED_HTML_ENTITIES = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};
}

void ReplaceHtmlEntity(const std::string& s, size_t& pos, std::string& output)
{
	bool replaced = false;
	for (const auto& [encoded, symbol] : Html::Decode::ENCODED_HTML_ENTITIES)
	{
		if (s.compare(pos, encoded.size(), encoded) == 0)
		{
			output += symbol;
			pos += encoded.size() - 1;
			replaced = true;
			break;
		}
	}

	if (!replaced)
	{
		output += s[pos];
	}
}

std::string HtmlDecode(const std::string& html)
{
	std::string result;

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] != '&')
		{
			result += html[i];
			continue;
		}

		ReplaceHtmlEntity(html, i, result);
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