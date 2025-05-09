#include "CHttpUrl.h"

#include <sstream>

namespace
{
constexpr unsigned short MIN_PORT = 1;

unsigned short GetDefaultPort(const Protocol& protocol)
{
	return protocol == Protocol::HTTPS ? 443 : 80;
}
} // namespace

CHttpUrl::CHttpUrl(const std::string& url)
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}

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
