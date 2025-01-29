#include "InvertedIndex.h"

#include <iostream>
#include <fstream>
#include <sstream>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    if (!input_docs.empty())
    {
        docs.clear();
        for (auto& it : input_docs) {
            docs.emplace_back(it);
            //Print doc
            //std::cout << it << std::endl;
        }
        freq_dictionary.clear();    // Prepare (clean) frequency dictionary
        this->UpdateFrequencyDictionary();
        std::cout << "\tInvertedIndex::UpdateDocumentBase - finish" << std::endl;
    }
    else {
        std::cerr << "Indexing: no content in docs content base" << std::endl;
    }
}

void InvertedIndex::UpdateFrequencyDictionary() {
    size_t docId = 0;
    for (auto& it : docs) {
        std::stringstream textStream(it);
        std::string word;
        while (textStream >> word) {
            // Search for a word in the dictionary
            if (freq_dictionary.count(word)) {  // If the word has already been added to the dictionary
                auto dictionaryMeaning = freq_dictionary.at(word);
                bool addWordCount = true;
                for (auto& it : dictionaryMeaning) {
                    if (it.doc_id == docId) {
                        addWordCount = false;   // If this source has already been added to the dictionary
                        break;
                    }
                }
                // Update the dictionary (add this source)
                if (addWordCount) {
                    std::vector<Entry> wordCount;
                    wordCount.clear();
                    wordCount = GetWordCount(word);
                    freq_dictionary[word].emplace_back(wordCount[0]);
                }
            }
            else {
                // Add a word to the dictionary
                std::vector<Entry> wordCount;
                wordCount.clear();
                wordCount = GetWordCount(word);
                freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(word, wordCount));
            }
        }
        ++docId;
    }
    //Print frequency dictionary
    /*for (auto& it : freq_dictionary) {
        std::cout << "index[ " << it.first << " ] = ";
        for (auto& val : it.second) {
            std::cout << "{ " << val.doc_id << "; " << val.count << " } ";
        }
        std::cout << std::endl;
    }*/
    std::cout << "\tInvertedIndex::UpdateFrequencyDictionary - finish" << std::endl;
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::vector<Entry> wordCount;
    wordCount.clear();
    size_t docId = 0;
    for (auto& it : docs) {
        size_t count = 0;
        size_t index = 0;
        while ((index = it.find(word, index)) != std::string::npos) {
            ++count;
            index += word.length();
        }
        if (count > 0) {
            wordCount.push_back({ docId, count });
        }
        ++docId;
    }
    return wordCount;
}