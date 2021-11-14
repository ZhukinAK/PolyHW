#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int position(double x0, double y0, double x, double y)
{
	if (x0 * y - y0 * x > 0)
	{
		return 0;   //лево
	}
	else
	{
		return 1;//право
	}
}

double take_x(string str) {
	int probel = str.find(" ");
	double x = stoi(str.substr(0, probel));
	return x;
}

double take_y(string str) {
	int probel = str.find(" ");
	double y = stoi(str.substr(probel+1, str.length()));
	return y;
	return 0;
}

float cosvec(double x0, double y0, double x, double y)
{
	float cosvector = (x * x0 + y0 * y) / sqrt((x0 * x0 + y0 * y0) * (x * x + y * y));
	return cosvector;
}

int main()
{
	ifstream i_file;
	i_file.open("in.txt");

	int a = 0;

	double x0;
	double y0;

	double x;
	double y;

	double leftx;
	double lefty;

	double rightx;
	double righty;

	double csl=1;
	double csr = 1;

	string str;

	while (getline(i_file, str))
	{
		if (a == 0)
		{
			x0=take_x(str);
			y0=take_y(str);
			a = 1;
		}
		else
		{
			x = take_x(str);
			y = take_y(str);
			int pos = position(x0, y0, x, y);
			if (pos == 0)
			{
				
				if (csl >= cosvec(x0,y0,x,y))
				{
					csl = cosvec(x0, y0,x,y);
					leftx = x;
					lefty = y;
				}
			}
			else
			{
				
				if (csr >= cosvec(x0, y0, x, y))
				{
					csr = cosvec(x0, y0, x, y);
					rightx = x;
					righty = y;
				}
			}
		}
	}
	cout << "Leftmost: " << leftx << " " << lefty << endl;
	cout << "Rightmost: " << rightx << " " << righty << endl;
	return 0;
}
