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