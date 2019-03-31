#include "pch.h"
#include <filesystem>
namespace fs = std::experimental::filesystem;
#include <cstdlib>

std::string const TestDataHome= SOLUTION_DIR "TestData";

TEST(FileSystemTests, WeHaveATestDataFolder)
{
	EXPECT_TRUE(fs::is_directory(fs::path(TestDataHome)));
}