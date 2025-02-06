#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
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
	

	auto index = new InvertedIndex();
	index->UpdateDocumentBase(files->GetTextDocuments());

	auto words = new SearchServer(*index);
	std::vector<std::vector<RelativeIndex>> searchResult;
	searchResult = words->Search(files->GetRequests());
	
	std::vector<std::vector<std::pair<int, float>>> answers;

	for (auto& currentResult : searchResult)	// Сonvert vector searchResult for module putAnswers(ConvertJSON) 
	{
		std::vector<std::pair<int, float>> result;
		result.clear();
		for (auto& it : currentResult)
		{
			if (it.rank > INT_MAX)	// Overflow error. If the Doc ID is too large.
			{
				throw std::overflow_error("Doc ID is larger than INT_MAX");
			}
			result.emplace_back(std::pair(it.doc_id, static_cast<int>(it.rank)));
		}
		answers.push_back(result);
	}
	files->putAnswers(answers);
}
