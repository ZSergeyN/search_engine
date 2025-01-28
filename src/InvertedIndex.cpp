#include "InvertedIndex.h"
#include <sstream>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    if (!input_docs.empty())
    {
        docs.clear();
        for (auto& it : input_docs) {
            docs.emplace_back(it);
        }
    }
    else {
        std::cerr << "Indexing: no content in docs content base" << std::endl;
    }
}

void InvertedIndex::UpdateFrequencyDictionary() {
    freq_dictionary.clear();
    for (auto& it : docs) {
        std::stringstream textStream(it);
        std::string word;
        while (textStream >> word) {
            auto checkWord = freq_dictionary.find(word);
            if (checkWord != freq_dictionary.end()) {
                std::vector<Entry> wordCount;
                wordCount.clear();
                wordCount = GetWordCount(word);
                freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(word, wordCount));
            }
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::vector<Entry> wordCount;
    wordCount.clear();
    size_t docId = 0;
    for (auto& it : docs) {
        size_t count = 0;       // количество вхождений
        size_t index{}; // начальный индекс
        while ((index = it.find(word, index)) != std::string::npos) {
            ++count;
            index += word.length(); // перемещаем индекс на позицию после завершения слова в тексте
        }
        if (count > 0) {
            wordCount.push_back({ docId, count }); //Why??????????
            ++docId;
        }
    }
    return wordCount;
}