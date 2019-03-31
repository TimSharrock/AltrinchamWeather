#include <catch.hpp>
#include <experimental/filesystem>
#include <algorithm>
#include <iterator>

namespace fs = std::experimental::filesystem;

TEST_CASE("C++ std filesystem availability","[filesystem]")
{
	SECTION("We can create a path")
	{
		REQUIRE_NOTHROW(fs::path());
	}
	SECTION("We are running in the development environment")
	{
		fs::path pathOfThisTestFile{ __FILE__ };
		CHECK_THAT(pathOfThisTestFile.string(), Catch::EndsWith(".cpp"));
		CHECK(fs::is_regular_file(pathOfThisTestFile));
		REQUIRE_FALSE(fs::is_directory(pathOfThisTestFile));
	}
	SECTION("We can detect a non-existent folder")
	{
		fs::path pathOfNonExistentFolder{ __FILE__ "/invalid"};
		REQUIRE_FALSE(fs::is_directory(pathOfNonExistentFolder));
	}
	SECTION("We can get a sorted list of files of a given type in a given folder")
	{
		fs::path pathOfThisTestFile{ __FILE__ };
		fs::path pathOfThisFolder{ pathOfThisTestFile.parent_path() };
		REQUIRE(fs::is_directory(pathOfThisFolder));

		std::vector<fs::path> selectedPaths{};
		selectedPaths.push_back(fs::path("zzz.cpp"));
		selectedPaths.push_back(fs::path("aaa.cpp"));
		std::string extension(".cpp");
		std::copy_if(
			fs::directory_iterator(pathOfThisFolder), 
			fs::directory_iterator(),
			std::back_inserter(selectedPaths),
			[extension](const fs::path & p)
			{
			  return fs::is_regular_file(p) && (p.extension()==extension);
			});
		CHECK(selectedPaths.size() > 2);
		std::sort(std::begin(selectedPaths), std::end(selectedPaths));
		for (auto& p : selectedPaths)
		{
			CHECK_THAT(p.string(), Catch::EndsWith(".cpp"));
		}
		CHECK(std::is_sorted(std::begin(selectedPaths), std::end(selectedPaths)));
	}
}