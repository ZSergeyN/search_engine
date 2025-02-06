#include "SearchServer.h"

#include <iostream>
#include <sstream>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string> &queries_input)
{
    //std::vector<std::vector<RelativeIndex>> searchResult;
    int queryId = 0;
    for (auto &query : queries_input)
    {
        float absoluteRelevanceMax = 0;
        uniqueWordsQuery.clear();
        std::cout << std::endl << queryId << " request: " << std::endl;
        SeparatRequest(query);
        SortWords();
        searchResult.emplace_back(SearchDocs(absoluteRelevanceMax));
        SortDocs(searchResult.back(), absoluteRelevanceMax);
        // Print requests
        for (auto &it : searchResult.back())
        {
            std::cout << "\t" << it.doc_id << " - " << it.rank << " | " << absoluteRelevanceMax << std::endl;
        }
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
            else
            {
                std::cout << "\tnot found: " << wordInQuery << std::endl;
            }
            
            
        }
    }
    std::cout << "\tSearchServer::SeparatRequest - finish" << std::endl;
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
    std::cout << "\tSearchServer::SortWords - finish " << std::endl;
}

std::vector<RelativeIndex> SearchServer::SearchDocs(float& absoluteRelevanceMax)
{
    std::vector<RelativeIndex> searchDos;
    if(uniqueWordsQuery.size() > 0) // If these words are not found in the documents
    {
        for(auto& foundDoc : uniqueWordsQuery[0].freq_dictionary)
        {
            bool addDoc = true; // If one word is found
            for(int i = 1; i < uniqueWordsQuery.size(); ++i)
            {
                addDoc = false;
                for(auto& it : uniqueWordsQuery[i].freq_dictionary)
                {
                    if(foundDoc.doc_id == it.doc_id)
                    {
                        foundDoc.count += it.count;
                        addDoc = true;
                        break;
                    }
                }
                if(!addDoc) // If there are no identical documents
                {
                    foundDoc.count = 0;
                    break;
                }
            }
            if(absoluteRelevanceMax < foundDoc.count) absoluteRelevanceMax = foundDoc.count;    // Finding absolute relevance
            if(addDoc)
            {
                RelativeIndex newAnswer;
                newAnswer.doc_id = foundDoc.doc_id;
                newAnswer.rank = foundDoc.count;
                searchDos.emplace_back(newAnswer);
            }
        }
    }
    std::cout << "\tSearchServer::SearchDocs - finish" << std::endl;
    return searchDos;
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
    std::cout << "\tSearchServer::SortDocs - finish " << std::endl;
}