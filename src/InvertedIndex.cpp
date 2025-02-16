#include "InvertedIndex.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>

std::mutex mutexAccessDictionary; // access to index map

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    if (!input_docs.empty())
    {
        docs.clear();
        freq_dictionary.clear();    // Prepare (clean) frequency dictionary
        std::vector<size_t> docId(input_docs.size());   // Vector with the document number for creating threads
        size_t num = 0;
        std::vector<std::thread> threadDoc;
        for (auto& it : input_docs) {
            docs.emplace_back(it);
            docId[num] = num;
            threadDoc.emplace_back();
            threadDoc.back() = std::thread(&InvertedIndex::UpdateFrequencyDictionary, this, std::cref(docId[num]), std::cref(it));
            ++num;
        }
        for (auto& threads : threadDoc) {
            threads.join();
        }
    }
    else {
        std::cerr << "Indexing: no content in docs content base" << std::endl;
    }
}

void InvertedIndex::UpdateFrequencyDictionary(const size_t &docId, const std::string &doc) {
    
    mutexAccessDictionary.lock();

    std::stringstream textStream(doc);
    std::string word;
    while (textStream >> word) {
        // Search for a word in the dictionary
        bool addWordCount = true;
        bool addWord = true;
        if (freq_dictionary.count(word)) {  // If the word has already been added to the dictionary
            addWord = false;
            for (auto& it : freq_dictionary.at(word)) {
                if (it.doc_id == docId) {   // If this source has already been added to the dictionary
                    ++it.count;
                    addWordCount = false;
                    break;
                }
            }
        }
        Entry newWordOrCount;
        newWordOrCount.doc_id = docId;
        newWordOrCount.count = 1;
        if (addWord) {  // Add a word to the dictionary
            addWordCount = false;
            freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(word, { newWordOrCount }));
        }
        if (addWordCount) { // Update the dictionary (add this source)
            freq_dictionary[word].emplace_back(newWordOrCount);
        }
    }

    mutexAccessDictionary.unlock();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    if(freq_dictionary.count(word))
    {
        return freq_dictionary.at(word);
    }
    else {
        std::vector<Entry> frequency;
        return frequency;
    }
    
}
