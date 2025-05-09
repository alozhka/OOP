#include "CHttpUrl.h"
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
	SECTION("From all data specified")
	{
		CHttpUrl url{ "ya.ru", "/images/image.webp", Protocol::HTTPS, 9884 };

		CHECK("https://ya.ru:9884/images/image.webp" == url.GetUrl());
		CHECK("ya.ru" == url.GetDomain());
		CHECK("/images/image.webp" == url.GetDocument());
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK(9884 == url.GetPort());
	}
}

TEST_CASE("Cannot construct HTTP URL with invalid data", "[negative][url][ctor]")
{
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