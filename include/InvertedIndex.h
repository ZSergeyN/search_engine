#pragma once

#include <string>
#include <vector>
#include <map>

struct Entry
{
    size_t doc_id, count;
    // This operator is necessary for conducting test scenarios.
    bool operator==(const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};
class InvertedIndex
{
private:
    std::vector<std::string> docs;                             // List of document contents
    std::map<std::string, std::vector<Entry>> freq_dictionary; // Frequency dictionary
public:
    InvertedIndex() = default;
    /*
    * Update or fill in the database of documents that we will use to make transactions search
    * @param texts_input document contents
    */
    void UpdateDocumentBase(std::vector<std::string> input_docs);
    /*
    Adds a word and the number of occurrences in the document text to the frequency dictionary.
    */
    void UpdateFrequencyDictionary();
    /*
    * The method determines the number of occurrences of the word word in the uploaded document database
    * @param word the word, whose frequency of occurrence must be determined
    * @return returns a prepared list with the frequency of words
    */
    std::vector<Entry> GetWordCount(const std::string& word);
};