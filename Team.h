#pragma once

#include <iostream>

class Team {
	std::string name;
	double level;

	int winning_points;
	int losing_points;

	std::vector<bool> game_results;

public:
	Team(const std::string& name, double level) :
		name(name), level(level), winning_points(0), losing_points(0)
	{
		if (level < 0) {
			level = 0;
		}
		if (level > 1) {
			level = 1;
		}
	}

	std::string getName() const {
		return name;
	}

	double getLevel() const {
		return level;
	}

	void addWiningGame() {
		game_results.push_back(true);
	}

	void addLosingGame() {
		game_results.push_back(false);
	}

	void addWiningPoints(int points) {
		winning_points += points;
	}

	void addLosingPoints(int points) {
		losing_points += points;
	}

	int getGamesRatio() {
		int ratio = 0;
		for (bool result : game_results) {
			if (result) {
				ratio++;
			}
			else {
				ratio--;
			}
		}

		return ratio;
	}

	int getPointsRatio() {
		return winning_points - losing_points;
	}

	int getRow(bool winning) {
		int current_row = 0;
		int longest_row = 0;
		for (bool result : game_results) {
			if ((winning && result) || (!winning && !result)) {
				current_row++;
				if (current_row > longest_row) {
					longest_row = current_row;
				}
			}
			else {
				current_row = 0;
			}
		}

		return longest_row;
	}
};
