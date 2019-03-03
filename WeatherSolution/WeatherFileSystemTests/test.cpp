#include "pch.h"
#include <filesystem>
namespace fs = std::experimental::filesystem;

TEST(FileSystemTests, WeHaveACurrentFolder)
{
	auto currentPath=fs::current_path();
  //EXPECT_EQ("here", currentPath.string());
	EXPECT_TRUE(true);
}