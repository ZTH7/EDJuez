#pragma once

#include <vector>


class polinomio {
public:

	polinomio(){}

	void insert(std::pair<int, int> elem);

	int calculate(int x) const;

private:
	std::vector<std::pair<int, int>> v;

	int find(const std::pair<int, int>& elem, int ini, int fin, bool& found) const;
};
