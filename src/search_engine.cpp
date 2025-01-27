#include "ConverterJSON.h"
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test)
{
	EXPECT_EQ(1, 1);
}

int main()
{
	auto files = new ConverterJSON();
	files->loadConfigFile();
	files->GetTextDocuments();
	files->GetRequests();
}
