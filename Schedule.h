#pragma once

#include <iostream>
#include <vector>

class Schedule {
	std::vector<std::pair<int, int>> indices;

public:
	Schedule(int number) {
		for (int i = 0; i < number; i++) {
			for (int j = i + 1; j < number; j++) {
				indices.push_back(std::pair<int, int>(i, j));
			}
		}

		for (int i = 0; i < number; i++) {
			for (int j = i + 1; j < number; j++) {
				indices.push_back(std::pair<int, int>(j, i));
			}
		}
	}

	std::vector<std::pair<int, int>> get() {
		return indices;
	}
};
