#include "CHttpUrl.h"

#include "СUrlParsingError.h"

#include <regex>
#include <sstream>

namespace
{
constexpr unsigned short MIN_PORT = 1;
constexpr unsigned short MAX_PORT = 65535;
const std::regex URL_REGEX(R"((http|https)://([^/:]+)(:(\d+))?(/.*)?)", std::regex_constants::icase);
// может будут косяки в регулярке

unsigned short GetDefaultPort(const Protocol& protocol)
{
	return protocol == Protocol::HTTPS ? 443 : 80;
}

Protocol ParseProtocol(std::string_view protocolStr)
{
	std::string str = protocolStr.data();
	std::ranges::transform(str, str.begin(), tolower);

	if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}

	throw std::invalid_argument("Invalid protocol");
}

unsigned short ParsePort(std::string_view portStr, const Protocol& protocol)
{
	if (portStr.empty())
	{
		return GetDefaultPort(protocol);
	}

	// может быть исключение
	int port = std::stoi(portStr.data());

	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::invalid_argument("Port must be in [1, 65535]");
	}

	return port;
}
} // namespace

CHttpUrl::CHttpUrl(const std::string& url)
{
	std::smatch match;
	if (!std::regex_match(url, match, URL_REGEX))
	{
		throw СUrlParsingError("Invalid URL format");
	}

	m_protocol = ParseProtocol(match[1].str());
	m_domain = match[2];
	m_document = match[5];
	m_port = ParsePort(match[4].str(), m_protocol);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}

	// проверка на документ и домен
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}
	if (port < MIN_PORT)
	{
		throw std::invalid_argument("Port must be in [1, 65535]");
	}

	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetUrl() const
{
	std::ostringstream url;
	url << (m_protocol == Protocol::HTTP ? "http" : "https") << "://" << m_domain;

	if (m_port != GetDefaultPort(m_protocol))
	{
		url << ":" << m_port;
	}

	url << m_document;

	return url.str();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
