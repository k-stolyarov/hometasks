/* 
 * File:   Date.h
 * Author: ilham
 *
 * Created on August 30, 2015, 2:24 AM
 */

#ifndef DATE_H
#define	DATE_H
#include <iostream>

class Date
{
private:
	Date();

	int mDay;  // Day for the Date class
	int mMonth;  // Month for the Date class
	int mYear;  // Year for the Date class
	
	// validate entered combination of day,month and year. IF this date is not allowed then throw an exception
	void validate(int m, int d, int y);
	// check if year is leap
	bool is_leap(int year);
public:
	Date(int m, int d, int y);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

	// Setters. If somebody try to set and invalid value then exception will be thrown.
	void SetDay(int d);
	void SetMonth(int m);
	void SetYear(int y);

	void PrintSlashed(std::ostream & os);
	void PrintNamed(std::ostream & os);
};

std::istream& operator >> (std::istream& in, Date & d);

#endif	/* DATE_H */

