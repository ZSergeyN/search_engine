#include "ConverterJSON.h"

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
			/*std::cout << "Resources:" << std::endl;
			for (auto& it : resourcesFiles) {
				std::cout << it << std::endl;
			}*/
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
			/*for (auto& it : data["requests"]) {
				std::cout << it << std::endl;
			}*/
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
	std::ofstream answerFile("answers.json");
	for (auto& it : answers) {
		//to do
	}
	answerFile.close();
}