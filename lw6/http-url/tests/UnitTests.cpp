#include "CHttpUrl.h"
#include "СUrlParsingError.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/internal/catch_preprocessor_internal_stringify.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/internal/catch_section.hpp>
#include <catch2/internal/catch_test_macro_impl.hpp>
#include <catch2/internal/catch_test_registry.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

TEST_CASE("Constructs HTTP URL", "[url][ctor]")
{
	SECTION("From specified components")
	{
		CHttpUrl url{ "ya.ru", "/images/image.webp", Protocol::HTTPS, 9884 };

		CHECK("https://ya.ru:9884/images/image.webp" == url.GetUrl());
		CHECK("ya.ru" == url.GetDomain());
		CHECK("/images/image.webp" == url.GetDocument());
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK(9884 == url.GetPort());
	}

	SECTION("Form components with no port")
	{
		CHttpUrl http{ "ya.ru", "/images/image.webp" };

		CHECK("http://ya.ru/images/image.webp" == http.GetUrl());
		CHECK("ya.ru" == http.GetDomain());
		CHECK("/images/image.webp" == http.GetDocument());
		CHECK(Protocol::HTTP == http.GetProtocol());
		CHECK(80 == http.GetPort());

		CHttpUrl https{ "ya.ru", "/images/image.webp", Protocol::HTTPS };

		CHECK("https://ya.ru/images/image.webp" == https.GetUrl());
		CHECK("ya.ru" == https.GetDomain());
		CHECK("/images/image.webp" == https.GetDocument());
		CHECK(Protocol::HTTPS == https.GetProtocol());
		CHECK(443 == https.GetPort());
	}

	SECTION("From URL string")
	{
		CHttpUrl https{ "https://ya.ru:9443/images/image.webp" };

		CHECK("https://ya.ru:9443/images/image.webp" == https.GetUrl());
		CHECK("ya.ru" == https.GetDomain());
		CHECK("/images/image.webp" == https.GetDocument());
		CHECK(Protocol::HTTPS == https.GetProtocol());
		CHECK(9443 == https.GetPort());

		CHttpUrl http{ "http://ya.ru/images/image.webp" };

		CHECK("http://ya.ru/images/image.webp" == http.GetUrl());
		CHECK("ya.ru" == http.GetDomain());
		CHECK("/images/image.webp" == http.GetDocument());
		CHECK(Protocol::HTTP == http.GetProtocol());
		CHECK(80 == http.GetPort());
	}
}

TEST_CASE("Cannot construct HTTP URL with invalid data", "[negative][url][ctor]")
{
	SECTION("Invalid url")
	{
		CHECK_THROWS_MATCHES(
			CHttpUrl{"htt://ya.ru/images/image.webp"},
			СUrlParsingError,
			Catch::Matchers::Message("Invalid URL format"));
		CHECK_THROWS_MATCHES(
			CHttpUrl{"http://ya.ru:99999/images/image.webp"},
			std::invalid_argument,
			Catch::Matchers::Message("Port must be in [1, 65535]"));
	}
	SECTION("Invalid domain")
	{
		CHECK_THROWS_MATCHES(
			CHttpUrl("", "/images/image.webp"),
			std::invalid_argument,
			Catch::Matchers::Message("Domain cannot be empty"));
	}
	SECTION("Invalid port")
	{
		CHECK_THROWS_MATCHES(
			CHttpUrl("ya.ru", "", Protocol::HTTPS, 0),
			std::invalid_argument,
			Catch::Matchers::Message("Port must be in [1, 65535]"));
	}
}

// проверка на разные регистры протокола
// добавление / в конец
// разные символы в документе в домене (@, #)