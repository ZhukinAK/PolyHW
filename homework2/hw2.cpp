#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

int def_oblast(double x,vector<double> X) {
	int sector=0;
	if (x < X.front()) {
		sector = 0;
	}
	 else{
		for (int i = 0; i < X.size(); ++i) {
			if (x >= X[i]) sector = i+1;
		}
	}
	return sector;
}

void phys_right(vector<double> X, vector<double> H, double t, double dt, double& y, double& x, double& vy, double& vx, double oblast) {
	double g = 9.81;
	double y1;
	
	vy = vy - g * dt;
	x = x + vx * dt;
	y1 = y;
	y = y + vy * dt - g * dt * dt / 2;
	if (oblast < X.size()) {
		if (x >= X[oblast] && y1 <= H[oblast]) {
			vx = -vx;
			x = X[oblast] - 0.00000001;
		}
	}
}

void phys_left(vector<double> X, vector<double> H, double t, double dt, double& y, double& x, double& vy, double& vx, double oblast) {
	double g = 9.81;
	double y1;

	vy = vy - g * dt;
	x = x + vx * dt;
	y1 = y;
	y = y + vy * dt - g * dt * dt / 2;
	if (oblast >0) {
		if (x <= X[oblast - 1] && y1 <= H[oblast - 1]) { 
			vx = -vx;
			x = X[oblast - 1] + 0.00000000001;
		}
	}
}

int main(int argc, char** argv)
{
	if (argc < 2 || argc > 2) {
		cout << "аргументов нет или их больше чем мы ожидаем" << endl;
	}
	else{
	ifstream i_file;
	i_file.open(argv[1]);
	int a = 0;
    int b=0;
	double y=0;
	double x=0;
	double vx=0;
	double vy=0;
	int oblast=0;
	vector<double> X;
	vector<double> H;
	double t = 0;
	double dt = 0.0001;
	string str;
	while (getline(i_file, str))
	{
		if (a == 0)
		{
			y = stoi(str);
			a = 1;
		}
		else if (a==1)
		{
            b = str.find(" ");
			vx = stod(str.substr(0, b));
			vy = stod(str.substr(b + 1, str.length()));
			a = 2;
		}
		else
		{
			if(str.length()>2){
            b = str.find(" ");
			X.push_back(stod(str.substr(0, b)));
			H.push_back(stod(str.substr(b + 1, str.length())));
			}
		}
	}   
	while (y>0)
	{
		oblast=def_oblast(x,X);
		if (vx >= 0) phys_right(X, H, t, dt, y, x, vy, vx, oblast);
		if (vx < 0) phys_left(X, H, t, dt, y, x, vy, vx, oblast);
	}
	oblast=def_oblast(x, X);
	cout << oblast;
	return 0;
}
}
