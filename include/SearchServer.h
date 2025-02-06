#pragma once

#include <vector>

#include "InvertedIndex.h"

struct FoundWord
{
    std::string word;
    int frequency = 0;
    std::vector<Entry> freq_dictionary;
};

struct RelativeIndex
{
    size_t doc_id;
    float rank;
    bool operator==(const RelativeIndex &other) const
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer
{
private:
    InvertedIndex _index;
    std::vector<FoundWord> uniqueWordsQuery;
    std::vector<std::vector<RelativeIndex>> searchResult;
public:
    /**
    * @param idx a reference to the class is passed to the class constructor
    InvertedIndex,
    * so that the SearchServer can find out the frequency of words found in
    request
    */
    SearchServer(InvertedIndex &idx) : _index(idx){};
    /**
    * The method of processing search queries
    * @param queries_input search queries taken from the file
    requests.json
    * @return a sorted list of relevant responses for
    the specified queries
    */
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string> &queries_input);
    
    /**
    * The method splits the search query into individual
    * words and generates a list of unique ones from them.
    * @param queries_input search queries taken from the file
    requests.json
    */
    void SeparatRequest(const std::string &queries_input);

    /**
    * The method sorts words in order of increasing frequency of occurrence
    */
    void SortWords();

    /**
    * The method finds all documents in which the words occur
    * @param absoluteRelevanceMax the maximum absolute relevance
    * value for all found words
    * @return the list of documents and the absolute relevance
    * value for these documents
    */
    std::vector<RelativeIndex> SearchDocs(float& absoluteRelevanceMax);

    /**
    * The method calculates the relative relevance for each document. 
    * Sorts documents in descending order of relevance
    * @param list of documents and the absolute relevance
    *  and the maximum absolute relevance
    */
    void SortDocs(std::vector<RelativeIndex> &result, const float& absoluteRelevanceMax);
    };