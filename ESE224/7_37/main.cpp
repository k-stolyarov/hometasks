#include "Line.h"
#include <iostream>
using namespace std;

int main()
{
	Point start;
	Point end;

	cout << "Enter first line point X and Y coordinates:" << endl;	
	cin >> start;
	cout << "Enter second line point X and Y coordinates:" << endl;
	cin >> end;

	Line l(start, end);
	cout << "You've entered the line " << l << endl;

	Vector translation_direction;
	cout << "Please enter translation vector direction X and Y coordinates: " << endl;
	cin >> translation_direction;

	double distance;
	cout << "Please enter translation distance: " << endl;
	cin >> distance;
	
	l.translate(translation_direction, distance);
	cout << "Translated line is " << l << endl;

	cout << "Please enter line scaling coefficient: " << endl;
	double scale;
	cin >> scale;
	l.resize(scale);
	cout << "Scaled line is " << l;

	return 0;
}