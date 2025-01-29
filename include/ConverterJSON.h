#pragma once

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
    /*
     The method reads data from a file config.json
     returns parameters nameSearchEngin, versionSearchEngine,
     timeForUpdate, maxResponses
    */
    void loadConfigFile();
    /*
     *  The method of getting the contents of files
     *  @return a list with the contents of the files listed
     *  in config.json
     */
    std::vector<std::string> GetTextDocuments();
    /*
    * The method reads the field max_responses to determine the maximum number
    * of responses per request
    * @return
    */
    int GetResponsesLimit();
    /*
    * Method of getting requests from a file requests.json
    * @return list of requests from the file requests.json
    */
    std::vector<std::string> GetRequests();
    /*
    * Put it in a file answers.json search query results
    */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};