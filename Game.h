#pragma once

#include <iostream>
#include <random>
#include "Team.h"

class Game {
	Team& home;
	Team& out;
	int result_home;
	int result_out;

public:
	Game(Team& home, Team& out) :
		home(home), out(out)
	{
		std::random_device rd{};
		std::mt19937 gen(rd());

		std::normal_distribution<> d1(77.5, 10);
		result_home = std::lround(d1(gen) + 10 * home.getLevel());
		if (result_home < 55) {
			result_home = 55;
		}
		if (result_home > 100) {
			result_home = 100;
		}

		std::normal_distribution<> d2(75, 10);
		result_out = std::lround(d2(gen) + 10 * out.getLevel());
		if (result_out < 50) {
			result_out = 50;
		}
		if (result_out > 100) {
			result_out = 100;
		}

		if (result_home >= result_out) {
			home.addWiningGame();
			out.addLosingGame();
		}
		else {
			home.addLosingGame();
			out.addWiningGame();
		}

		home.addWiningPoints(result_home);
		home.addLosingPoints(result_out);

		out.addWiningPoints(result_out);
		out.addLosingPoints(result_home);
	}
};