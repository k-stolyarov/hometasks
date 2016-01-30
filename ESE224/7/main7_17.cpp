/* 
 * File:   main7_17.cpp
 * Author: ilham
 *
 * Created on May 9, 2015, 1:34 AM
 */
#include<iostream>
#include <cstdlib>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
using namespace std;

//function prototype
bool ordered(double x[], int num_pts);
void reorder(double x[], double y[], int num_pts);

//function main
int main()
{
	vector<double> coef;
	vector<double> angle;

    string infile;
    ifstream tunnel;
    cout<<"Enter the file name " << endl;
    cin>>infile;
    tunnel.open(infile);

    if(tunnel.fail())
    {
        cout<<"No name of this file founded "<<endl;
        exit(1);
    }    
    //open input file
    
    while(!tunnel.eof())
    {
		double a;
		double c;
		tunnel >> a >> c;
		angle.push_back(a);
		coef.push_back(c);
    }    
	
	if (angle.empty())
	{
		cout << "There is no angles specified: \n";
		return 0;
	}

    if( ordered(&angle[0], angle.size()) )
    {
        cout<<"The angles are in ascending order: \n";
    }  
    else
    {
		cout << "Angles need to be reordered." << endl;
		cout << "Ordered angles are:" << endl;
		reorder(&angle[0], &coef[0], angle.size());
		for (size_t i = 0; i < angle.size(); ++i)
		{
			cout << angle[i] << " " << coef[i] << endl;
		}
    }
	cout << "The angles are from " << angle.front() << " to " << angle.back() << endl;

	return 0;  
}

// Function that checks if given input array is sorted in ascending order
bool ordered(double x[], int num_pts)
{
	if (num_pts == 0)
	{
		return true;
	}

    bool ascend = true;
	for (int m = 1; m < num_pts; ++m)
	{
		if (x[m - 1] > x[m])
		{
			ascend = false;
		}
	}
    return ascend;
}

// Function that reorders two arrays. array @c x is key array to sort, arrays @c y is elements that should be arranged according to @c x.
void reorder(double x[], double y[], int num_pts)
{
	// simplest bubble sort. Quicker ones require more code.
    for(int i = 0; i < num_pts; ++i)
    {
		for (int j = 0; j < num_pts - 1 - i; ++j)
        {
			if (x[j] > x[j + 1])
			{
				// using standard library swap operation.
				swap(x[j], x[j + 1]);
				swap(y[j], y[j + 1]);
			}
		}
	}
	return;
}
