#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


struct Entry
{
    size_t doc_id, count;
    // ƒанный оператор необходим дл€ проведени€ тестовых сценариев
    bool operator==(const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};
class InvertedIndex
{
private:
    std::vector<std::string> docs;                             // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный
public:
    InvertedIndex() = default;
    /**
    * ќбновить или заполнить базу документов, по которой будем совершать
    поиск
    * @param texts_input содержимое документов
    */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    void UpdateFrequencyDictionary();

    /*** ћетод определ€ет количество вхождений слова word в загруженной базе
    документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> GetWordCount(const std::string& word);
};