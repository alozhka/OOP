#pragma once
#include "Protocol.h"

#include <string>

class CHttpUrl
{
public:
	explicit CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	[[nodiscard]] std::string GetUrl() const;
	[[nodiscard]] std::string GetDomain() const;
	[[nodiscard]] std::string GetDocument() const;
	[[nodiscard]] Protocol GetProtocol() const;
	[[nodiscard]] unsigned short GetPort() const;

private:
	Protocol m_protocol;
	unsigned short m_port;
	std::string m_domain, m_document;
};