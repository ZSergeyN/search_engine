#include "ConverterJSON.h"

int main()
{
	// Make json file
/*
	std::ofstream file("film.json");
	nlohmann::json info1_2 = {
		{"Mark Watney", "Matt Damon"},
		{"Melissa Lewis", "Jessica Chastain"},
		{"Vincent Kapoor", "Chiwetel Ejiofor"},
		{"Annie Montrose", "Kristen Wiig"}
	};
	nlohmann::json info1_1 = {
		{"country", "USA, Great Britain"},
		{"date", 2015},
		{"studio", "20th Century Studios, Inc."},
		{"shown in Russia", true},
		{"screenwriter", "Drew Goddard, Andy Weir"},
		{"director", "Ridley Scott"},
		{"producer", "Howard Ellis, Drew Goddard, Adam Goodman"},
		{"actors", info1_2}
	};
	
	nlohmann::json info2_2 = {
		{"Ken Miles", "Christian Bale"},
		{"Carroll Shelby", "Matt Damon"},
		{"Mollie Miles", "Caitríona Balfe"},
		{"Henry Ford II", "Tracy Letts"}
	};
	nlohmann::json info2_1 = {
		{"country", "USA"},
		{"date", 2019},
		{"studio", "20th Century Studios, Inc."},
		{"shown in Russia", true},
		{"screenwriter", "Jez Butterworth, John-Henry Butterworth, Jason Keller"},
		{"director", "James Mangold"},
		{"producer", "John Bernard, Dani Bernfeld, Peter Chernin"},
		{"actors", info2_2}
	};
	
	nlohmann::json info3_2 = {
		{"Cooper", "Matthew McConaughey"},
		{"Brand", "Anne Hathaway"},
		{"Murph", "Jessica Chastain"},
		{"Mann", "Matt Damon"}
	};
	nlohmann::json info3_1 = {
		{"country", "USA, Great Britain, Canada"},
		{"date", 2014},
		{"studio", "Cinema Park Distribution"},
		{"shown in Russia", true},
		{"screenwriter", "Jonathan Nolan, Christopher Nolan"},
		{"director", "Christopher Nolan"},
		{"producer", "Christopher Nolan, Lynda Obst, Emma Thomas"},
		{"actors", info3_2}
	};
	
	nlohmann::json info4_2 = {
		{"Max", "Matt Damon"},
		{"Frey", "Alice Braga"},
		{"Kruger", "Sharlto Copley"},
		{"Delacourt", "Jodie Foster"}
	};
	nlohmann::json info4_1 = {
		{"country", "USA, Canada"},
		{"date", 2013},
		{"studio", "Columbia Pictures Industries, Inc."},
		{"shown in Russia", true},
		{"screenwriter", "Neill Blomkamp"},
		{"director", "Neill Blomkamp"},
		{"producer", "Bill Block, Neill Blomkamp, Simon Kinberg"},
		{"actors", info4_2}
	};
		
	nlohmann::json info5_2 = {
		{"Jason Bourne", "Matt Damon"},
		{"Heather Lee", "Alicia Vikander"},
		{"Robert Dewey", "Tommy Lee Jones"},
		{"Asset", "Vincent Cassel"}
	};
	nlohmann::json info5_1 = {
		{"country", "USA, China, Spain"},
		{"date", 2016},
		{"studio", "Universal Pictures"},
		{"shown in Russia", true},
		{"screenwriter", "Paul Greengrass, Christopher Rouse, Robert Ludlum"},
		{"director", "Paul Greengrass"},
		{"producer", "Matt Damon, Gregory Goodman, Paul Greengrass"},
		{"actors", info5_2}
	};
	nlohmann::json info_main = {{"The Martian", info1_1}, {"Ford v Ferrari", info2_1}, {"Interstellar", info3_1}, {"Elysium", info4_1}, {"Jason Bourne", info5_1}};
	file << info_main;
	

	// Find actor
	
	std::string actor_name = "";
	std::cout << "Enter the name of the actor: ";
	std::cin >> actor_name;
	std::ifstream file("film.json");
	nlohmann::json film;
	nlohmann::json info_film;
	nlohmann::json actors_film;
	file >> film;
	for (auto& it : film.items()) {
		info_film = it.value();
		actors_film = *info_film.find("actors");
		for (auto& i : actors_film.items()) {
			std::string actor_in_film = i.value();
			if(actor_in_film.find(actor_name) != std::string::npos) {
				std::cout << "film: " << it.key() << "\trole: " << i.key() << std::endl;
			}
		}
		
	}*/
ConverterJSON();
}
