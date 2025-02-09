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
        size_t docId = 0;
        for (auto& it : input_docs) {
            docs.emplace_back(it);
            //Print doc
            //std::cout << it << std::endl;
            std::thread threadDoc([this, docId, it]() {UpdateFrequencyDictionary(docId, it);});
            threadDoc.join();   // or detach???????????
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
        //std::cout << "\tInvertedIndex::UpdateDocumentBase - finish" << std::endl;
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

    //std::cout << "\tInvertedIndex::UpdateFrequencyDictionary - finish" << std::endl;
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