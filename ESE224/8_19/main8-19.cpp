/*
 * File:   main8-19.cpp
 * Author: ilham
 *
 * Created on May 11, 2015, 2:09 AM
 */

#include<iostream>
#include<cstdlib>
#include <algorithm>
#include<cmath>
#include<string>
#include<vector>

using namespace std;

const int cols = 8;
const int rows = 6;

int main()
{

	vector <vector<double> > grid(rows);
	for (size_t i = 0; i < grid.size(); ++i)
	{
		grid[i].resize(cols, 0.0);
	}
	//grid(6,8);

	double rightTemp;
	double leftTemp;
	double bottomTemp;
	double upTemp;
	double tolerance;

	cout << "Please enter the upper row temperature:" << endl;
	cin >> upTemp;
	cout << "Please enter the bottom row temperature:" << endl;
	cin >> bottomTemp;
	cout << "Please enter the right column temperature:" << endl;
	cin >> rightTemp;
	cout << "Please enter the left column temperature:" << endl;
	cin >> leftTemp;

	cout << "Please enter the tolerance:" << endl;
	cin >> tolerance;
	tolerance = abs(tolerance);

	for (size_t r = 1; r < rows - 1; ++r)
	{
		grid[r][0] = leftTemp;
		grid[r][cols - 1] = rightTemp;
	}

	for (size_t c = 0; c < cols; ++c)
	{
		grid[0][c] = upTemp;
		grid[rows - 1][c] = bottomTemp;
	}

	double max_temperature_delta = 1e100;
	while (max_temperature_delta > tolerance)
	{
		max_temperature_delta = 0;

		for (size_t r = 1; r < rows - 1; ++r)
		{
			for (size_t c = 1; c < cols - 1; ++c)
			{
				const double new_temperature = (grid[r + 1][c] + grid[r - 1][c] + grid[r][c - 1] + grid[r][c + 1]) / 4;
				const double temperature_delta = abs(new_temperature - grid[r][c]);
				max_temperature_delta = max(temperature_delta, max_temperature_delta);
				grid[r][c] = new_temperature;
			}
		}
	}
	cout << "Values across the grid: " << endl;
	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			cout << grid[r][c] << "\t";
		}
		cout << endl;
	}

	return 0;

}








