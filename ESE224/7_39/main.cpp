/* 
 * File:   main.cpp
 * Author: ilham
 *
 * Created on August 30, 2015, 2:22 AM
 */

#include <cstdlib>
#include "Date.h"
#include <fstream>

using namespace std;

int main()
{
	ifstream input_file;
	input_file.open("Date");
	if (input_file.fail())
	{
		cerr << "input file failed :";
		exit(1);
	}
	ofstream output_file;
	output_file.open("Date.out");
	if (output_file.fail())
	{
		cerr << "output file failed to open:";
		exit(1);
	}
	while (!input_file.eof())
	{
		Date tomorrow_obj(1, 1, 1);
		input_file >> tomorrow_obj;
		tomorrow_obj.PrintSlashed(output_file);
		output_file << "\t";
		tomorrow_obj.PrintNamed(output_file);
		output_file << endl;
	}

	
	try{
		Date test_date(1, 10, 2016);
		test_date.SetDay(31);
		test_date.PrintSlashed(cout);
		test_date.SetMonth(4);
	}
	catch (const logic_error & err)
	{
		cout << "Error " << err.what();
	}
	cout << endl;

	try{
		Date test_date(1, 10, 2016);
		test_date.SetDay(29);
		test_date.PrintSlashed(cout);
		cout << "\t";
		test_date.SetMonth(2);
		test_date.PrintSlashed(cout);
		cout << "\t";
		test_date.SetYear(2015);
	}
	catch (const logic_error & err)
	{
		cout << "Error " << err.what();
	}
	cout << endl;

	try{
		Date test_date(1, 10, 2016);
		test_date.SetDay(29);
		test_date.PrintSlashed(cout);
		cout << "\t";
		test_date.SetMonth(2);
		test_date.PrintSlashed(cout);
		cout << "\t";
		test_date.SetYear(2020);
		test_date.PrintSlashed(cout);
	}
	catch (const logic_error & err)
	{
		cout << "Error " << err.what();
	}
	cout << endl;

	return 0;
}