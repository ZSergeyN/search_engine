﻿#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

#include <stdexcept>


int main()
{
	auto files = new ConverterJSON();
	files->loadConfigFile();
	files->GetTextDocuments();
	

	auto index = new InvertedIndex();
	index->UpdateDocumentBase(files->GetTextDocuments());

	auto words = new SearchServer(*index);
	std::vector<std::vector<RelativeIndex>> searchResult;
	words->takeResponsesLimit(files->GetResponsesLimit());
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
			result.emplace_back(std::pair(static_cast<int>(it.doc_id), it.rank));
		}
		answers.push_back(result);
	}
	files->putAnswers(answers);
}
