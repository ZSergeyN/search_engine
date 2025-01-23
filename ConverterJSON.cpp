
#include "ConverterJSON.h"


#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"


ConverterJSON::ConverterJSON() {
    std::ifstream file("config.json");
	nlohmann::json configFile;
	nlohmann::json configBlock;
	nlohmann::json filesBlock;
	file >> configFile;
	for (auto& it : configFile.items()) {
		//info_film = it.value();
        std::cout << "block: " << it.key() << "\tvalue: " << it.value() << std::endl;
		
		
	}
}

int main()
{}
/*
actors_film = *info_film.find("actors");
		for (auto& i : actors_film.items()) {
			std::string actor_in_film = i.value();
			if(actor_in_film.find(actor_name) != std::string::npos) {
				std::cout << "film: " << it.key() << "\trole: " << i.key() << std::endl;
			}
		}
        */