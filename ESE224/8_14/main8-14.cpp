/*
 * File:   main8-14.cpp
 * Author: ilham
 *
 * Created on May 11, 2015, 1:43 AM
 */
#include<numeric>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include<string>
#include<vector>


using namespace std;
//Function Prototypes

double AvgVec(const vector<vector<double> > &x);

void inputVector(istream& in, vector<vector<double> > & vec);

int main()
{
	//Open input file
	ifstream fin("engine.dat");
	if (fin.fail())
	{
		cerr << "Could not open file engine.dat" << endl;
		exit(1);
	}

	int engine_count, temps_per_engine;
	fin >> engine_count >> temps_per_engine;
	vector<vector<double>> temps;
	temps.resize(engine_count);
	for (size_t i = 0; i < engine_count; ++i)
	{
		temps[i].resize(temps_per_engine);
	}

	inputVector(fin, temps);
	fin.close();
	const double avgTemp = AvgVec(temps);

	cout << "Average temperature of the engine:" << avgTemp << endl;

	return 0;
}
//Function Definition    
void inputVector(istream& in, vector<vector <double> >  & vec)
{
	const size_t r = vec.size();
	const size_t c = vec[0].size();

	for (size_t i = 0; i < r; ++i)
	{
		for (size_t j = 0; j < c; ++j)
		{
			in >> vec[i][j];
		}
	}
}

double AvgVec(const vector<vector<double> > &x)
{
	double sum = 0;
	size_t count = 0;
	for (size_t i = 0; i < x.size(); ++i)
	{
		count += x[i].size();
		sum = std::accumulate(x[i].begin(), x[i].end(), sum);
	}

	return sum / count;
}
