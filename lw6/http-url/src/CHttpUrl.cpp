#include "CHttpUrl.h"

#include <sstream>

namespace
{
unsigned short GetDefaultProtocolPort(const Protocol& protocol)
{
	return protocol == Protocol::HTTPS ? 443 : 80;
}
} // namespace

CHttpUrl::CHttpUrl(const std::string& url)
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetUrl() const
{
	std::ostringstream url;
	url << (m_protocol == Protocol::HTTP ? "http" : "https") << "://" << m_domain;

	if (m_port != GetDefaultProtocolPort(m_protocol))
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
