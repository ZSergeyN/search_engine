#include "SearchServer.h"

#include <iostream>
#include <sstream>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string> &queries_input)
{
    int queryId = 0;
    for (auto &query : queries_input)
    {
        float absoluteRelevanceMax = 0;
        uniqueWordsQuery.clear();
        SeparatRequest(query);
        SortWords();
        searchResult.emplace_back(SearchDocs(absoluteRelevanceMax));
        SortDocs(searchResult.back(), absoluteRelevanceMax);
        ++queryId;
    }
    return searchResult;
}

void SearchServer::SeparatRequest(const std::string &queries_text)
{
    std::stringstream text(queries_text);
    std::string wordInQuery;
    while (text >> wordInQuery)
    {
        bool addWord = true;
        FoundWord uniqueWord;
        // Search for unique words in a query
        for (auto &words : uniqueWordsQuery)
        {
            if (words.word == wordInQuery)
            {
                addWord = false;
                break;
            }
        }
        if (addWord)
        {
            uniqueWord.word = wordInQuery;
            uniqueWord.freq_dictionary = _index.GetWordCount(wordInQuery);
            if(uniqueWord.freq_dictionary.size() > 0)   // If this word is found in the dictionary
            {
                uniqueWordsQuery.emplace_back(uniqueWord); // Creating a vector of unique words with frequency
            }
        }
    }
}

void SearchServer::SortWords()
{
    for (auto &word : uniqueWordsQuery)
    {
        for (auto& wordCount : word.freq_dictionary)
        {
            word.frequency += wordCount.count;
        }
    }
    // Sorting a vector of unique words
    std::sort(begin(uniqueWordsQuery), end(uniqueWordsQuery),
              [](const FoundWord &left, const FoundWord &right)
              { return left.frequency < right.frequency; });
}

std::vector<RelativeIndex> SearchServer::SearchDocs(float& absoluteRelevanceMax)
{
    std::vector<RelativeIndex> searchDoc;
    if(uniqueWordsQuery.size() > 0) // If these words are not found in the documents
    {
        for (int y = 0; y < uniqueWordsQuery.size() - 1; ++y) {
            for (auto& foundDoc : uniqueWordsQuery[y].freq_dictionary)
            {
                for (int i = y + 1; i < uniqueWordsQuery.size(); ++i)
                    {
                        for (auto& it : uniqueWordsQuery[i].freq_dictionary)
                        {
                            if (foundDoc.doc_id == it.doc_id)
                            {
                                foundDoc.count += it.count;
                                break;
                            }
                        }
                    }
                bool addDoc = true;
                for (auto& it : searchDoc)
                {
                    if (it.doc_id == foundDoc.doc_id)   // If one word is found
                    {
                        addDoc = false;
                        break;
                    }
                }
                if (addDoc && responsesLimit > 0)   // If this document is missing and the response limit is not exceeded
                {
                    if (absoluteRelevanceMax < foundDoc.count) absoluteRelevanceMax = foundDoc.count;    // Finding absolute relevance
                    RelativeIndex newAnswer;
                    newAnswer.doc_id = foundDoc.doc_id;
                    newAnswer.rank = foundDoc.count;
                    searchDoc.emplace_back(newAnswer);  // Add an element to the result vector
                    --responsesLimit;
                }
            }
        }
    }
    return searchDoc;
}

void SearchServer::SortDocs(std::vector<RelativeIndex> &result, const float& absoluteRelevanceMax)
{
    for (auto &docs : result)
    {
        docs.rank = docs.rank / absoluteRelevanceMax;   // Calculating relative relevance
    }
    // Sorting a vector of documents
    std::sort(begin(result), end(result),
              [](const RelativeIndex &left, const RelativeIndex &right)
              { return left.rank > right.rank; });
}

void SearchServer::takeResponsesLimit(const int& _responsesLimit)
{
    responsesLimit = _responsesLimit;
}