#include "ConverterJSON.h"

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

void ConverterJSON::loadConfigFile() {
	std::ifstream configFile("config.json");
	nlohmann::json data;
	resourcesFiles.clear();
	if (configFile.is_open()) {
		configFile >> data;
		if (data.contains("config")) {
			nameSearchEngine = data["config"]["name"];
			versionSearchEngine = data["config"]["version"];
			if (data["config"].contains("max_responses")) {
				maxResponses = data["config"]["max_responses"];
			}
			if (data["config"].contains("time")) {
				timeForUpdate = data["config"]["time"];
			}
			for (auto& it : data["files"]) {
				resourcesFiles.emplace_back(it);
			}
			std::cout << "name: " << nameSearchEngine << " version: " << versionSearchEngine << " time update: " << timeForUpdate <<
				" max_responses: " << maxResponses << std::endl;
		}
		else {
			std::cerr << "Config file is empty" << std::endl;
		}
		configFile.close();
	}
	else {
		std::cerr << "Config file is missing" << std::endl;
	}
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
	textDocuments.clear();
	for (auto& it : resourcesFiles) {
		std::ifstream textFile(it);
		if (textFile.is_open()) {
			std::string buffer = "";
			while (!textFile.eof())
			{
				std::string b = "";
				textFile >> b;
				buffer += b;
				buffer += " ";
			}
			textDocuments.push_back(buffer);
			textFile.close();
		}
		else {
			textDocuments.push_back("");
			std::cout << "file: " << it << " is missing" << std::endl;
		}
	}
	return textDocuments;
}

int ConverterJSON::GetResponsesLimit() {
	return maxResponses;
}

std::vector<std::string> ConverterJSON::GetRequests() {
	std::ifstream requestsFile("requests.json");
	nlohmann::json data;
	requests.clear();
	if (requestsFile.is_open()) {
		requestsFile >> data;
		if (data.contains("requests")) {
			for (auto& it : data["requests"]) {
				requests.emplace_back(it);
			}
		}
		else {
			std::cout << "Requests file is empty" << std::endl;
		}
		requestsFile.close();
	}
	else {
		std::cout << "Requests file is missing" << std::endl;
	}
	return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
	nlohmann::json answerDictionary;
	int count = 1;
	for (auto& currentAnswer : answers) {
		std::string requestNumber = "request";
		if(count < 10)	// Creating a request field name
		{
			requestNumber += "00";
		}
		else if(count < 100)
		{
			requestNumber += "0";
		}
		requestNumber += std::to_string(count);
		answerDictionary["answers"][requestNumber]["result"] = !currentAnswer.empty();	// The presence of a search result that is stored as a boolean
		if (!currentAnswer.empty())
		{
			if(currentAnswer.size() > 1 && GetResponsesLimit() > 1)
			{
				auto currentDocResultArray = nlohmann::json::array();	// Creating an array of search results values
				int response = 1;
				for (auto& it : currentAnswer)
				{
					if (response > GetResponsesLimit())	// Checking the number of responses to a request
					{
						break;
					}
					auto currentDocResult = nlohmann::json::object();
					currentDocResult["docid"] = it.first;
					currentDocResult["rank"] = it.second;
					currentDocResultArray.push_back(currentDocResult);
					++response;
				}
				answerDictionary["answers"][requestNumber]["relevance"] = currentDocResultArray;
			}
			else // If the search value is single
			{
				answerDictionary["answers"][requestNumber]["docId"] = currentAnswer[0].first;
				answerDictionary["answers"][requestNumber]["rank"] = currentAnswer[0].second;
			}
			
		}
		++count;
	}
	std::ofstream answerFile("answers.json", std::ios_base::trunc);
	if (answerFile.is_open()) {
		answerFile << answerDictionary.dump(4);
		answerFile.close();
	}
	else {
		std::cout << "Answers file is missing" << std::endl;
	}
	
}
