#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>




class ConverterJSON {
private:
    std::string nameSearchEngine = "";
    std::string versionSearchEngine = "";
    int timeForUpdate = 10000;
    int maxResponses = 5;
    std::vector<std::string> resourcesFiles;
    std::vector<std::string> textDocuments;
    std::vector<std::string> requests;

public:
    ConverterJSON() = default;

    void loadConfigFile();
    /*
     *  Метод получения содержимого файлов
     *  @return Возвращает список с содержимым файлов перечисленных
     *  в config.json
     */
    std::vector<std::string> GetTextDocuments();

    /*
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();
    /*
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();
    /*
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};