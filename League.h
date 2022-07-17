#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "Team.h"
#include "Game.h"
#include "Schedule.h"

class League {
	std::vector<Team> teams;
	std::vector<Game> games;

	static const int number = 20;

	bool nameExists(const std::string& name) {
		for (const Team& team : teams) {
			if (team.getName() == name) {
				return true;
			}
		}

		return false;
	}

	void randTeams() {
		std::random_device rd{};
		std::mt19937 gen(rd());
		std::normal_distribution<> d(0.5, 0.2);

		char charset[] = "abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);

		while (teams.size() < number) {
			std::string name = "";
			for (int i = 0; i < 5; i++) {
				name += charset[rand() % 26];
			}

			if (nameExists(name)) {
				continue;
			}

			double level = d(gen);
			if (level < 0) {
				level = 0;
			}
			if (level > 1) {
				level = 1;
			}

			teams.push_back(Team(name, level));
		}
	}

public:
	League(std::vector<Team> teams) {
		for (unsigned int i = 0; i < teams.size() && i < number; i++) {
			if (nameExists(teams[i].getName())) {
				continue;
			}
			this->teams.push_back(teams[i]);
		}

		randTeams();
	}

	League() {
		randTeams();
	}

	void play() {
		Schedule schedule(number);
		
		for (std::pair<int, int> p : schedule.get()) {
			Game game(teams[p.first], teams[p.second]);
			games.push_back(game);
		}

		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number - 1; j++) {
				if ((teams[j].getGamesRatio() < teams[j + 1].getGamesRatio()) ||
					(teams[j].getGamesRatio() == teams[j + 1].getGamesRatio() && teams[j].getPointsRatio() < teams[j + 1].getPointsRatio())) {
					Team temp = teams[j];
					teams[j] = teams[j + 1];
					teams[j + 1] = temp;
				}
			}
		}
	}

	void table() {
		std::cout << "Final results table:" << std::endl;
		std::cout << "Name | Games ratio | Points ratio" << std::endl;
		for (int i = 0; i < number; i++) {
			std::cout << teams[i].getName() << " | " << teams[i].getGamesRatio() << " | " << teams[i].getPointsRatio() << std::endl;
		}
		std::cout << std::endl;
	}

	void statistics(int top) {
		std::cout << "1. Top teams:" << std::endl;
		for (int i = 0; i < top; i++) {
			std::cout << teams[i].getName() << std::endl;
		}
		std::cout << std::endl;

		int longest_row = 0;
		for (int i = 0; i < number; i++) {
			if (teams[i].getRow(true) > longest_row) {
				longest_row = teams[i].getRow(true);
			}
		}
		std::cout << "2. Longest winning row: " << longest_row << std::endl << std::endl;

		longest_row = 0;
		for (int i = 0; i < number; i++) {
			if (teams[i].getRow(false) > longest_row) {
				longest_row = teams[i].getRow(false);
			}
		}
		std::cout << "3. Longest losing row: " << longest_row << std::endl << std::endl;

		int num_positive = 0;
		for (int i = 0; i < number; i++) {
			if (teams[i].getPointsRatio() > 0) {
				num_positive++;
			}
		}
		std::cout << "4. Number of teams with positive points ratio: " << num_positive << std::endl << std::endl;
	}
};
