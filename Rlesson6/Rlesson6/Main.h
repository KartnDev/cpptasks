#include <string>
#include <fstream>
#include <iostream>

struct Circle
{
	double Radius;
	double PosX;
	double PosY;
};

struct position
{
	int x, y;
};


void FileReader(std::string FileName, const int N, double &Arr)
{
	std::ifstream fs(FileName);

	if (!fs.is_open())
	{
		std::cout << "something went wrong!\n";
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			fs >> *(&Arr + i);
		}
	}
	fs.close();

}

int sq(int a)
{
	return a * a;
}
