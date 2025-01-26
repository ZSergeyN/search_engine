#include "ConverterJSON.h"

#include "nlohmann/json.hpp"

void ConverterJSON::loadConfigFile() {
    std::ifstream configFile("config.json");
	nlohmann::json data;
	if (configFile.is_open()) {
		configFile >> data;
		if (data.contains("config")) {
			nameSearchEngine = data["config"]["name"];
			versionSearchEngine = data["config"]["version"];
			if (data.contains("max_responses")) {
				maxResponses = data["config"]["max_responses"]; // not change value
			}
			if (data.contains("time")) {
				timeForUpdate = data["config"]["time"];
			}
			for (auto& it : data["files"]) {
				resourcesFiles.emplace_back(it);
			}
			std::cout << "name: " << nameSearchEngine << " version: " << versionSearchEngine << " time update: " << timeForUpdate <<
				" max_responses: " << maxResponses << std::endl << "Resources:" << std::endl;
			for (auto& it : resourcesFiles) {
				std::cout << it << std::endl;
			}
		}
		else {
			std::cerr << "Config file is empty" << std::endl;
		}
	}
	else {
		std::cerr << "Config file is missing" << std::endl;
	}
}