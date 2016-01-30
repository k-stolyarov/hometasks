/* 
 * File:   Date.cpp
 * Author: ilham
 *
 * Created on August 30, 2015, 2:23 AM
 */

#include "Date.h"
#include <iostream>
#include<fstream>
#include<cmath>


using namespace std;

const char * month_names[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

const int leap_year_month_length[12] = {
	31,
	29,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

const int common_year_month_length[12] = {
	31,
	29,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

void Date::validate(int month, int day, int year)
{
	if (month < 1 || month > 12)
	{
		throw logic_error("Month value is invalid");
	}
	if (is_leap(year))
	{
		if (day < 1 || day > leap_year_month_length[month - 1])
		{
			throw logic_error("Day value is invalid");
		}
	}
	else
	{
		if (day < 1 || day > common_year_month_length[month - 1])
		{
			throw logic_error("Day value is invalid");
		}
	}
}

bool Date::is_leap(int year)
{
	if (0 == year % 400)
	{
		return true;
	}
	if (0 == year % 4 && 0 != year % 100)
	{
		return true;
	}
	return false;
}

Date::Date(int m, int d, int y)
{
	validate(m, d, y);
	mDay = d;
	mMonth = m;
	mYear = y;
}

int Date::GetDay() const
{
	return mDay;
}

int Date::GetMonth() const
{
	return mMonth;
}

int Date::GetYear() const
{
	return mYear;
}

void Date::SetDay(int d)
{
	validate(mMonth, d, mYear);
	mDay = d;
}

void Date::SetMonth(int m)
{
	validate(m, mDay, mYear);
	mMonth = m;
}

void Date::SetYear(int y)
{
	validate(mMonth, mDay, y);
	mYear = y;
}

void Date::PrintSlashed(std::ostream & os)
{
	os << mMonth << "/" << mDay << "/" << mYear;
}

void Date::PrintNamed(std::ostream & os)
{
	os << month_names[mMonth-1] << " " << mDay << ", " << mYear;
}

istream & operator >> (istream& in, Date & d)
{
	int month;
	int day;
	int year;
	in >> month >> day >> year;
	d = Date(month, day, year);
	return in;
}