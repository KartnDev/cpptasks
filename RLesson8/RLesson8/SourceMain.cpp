#include <iostream>
#include <fstream>

void FileReader(std::string FileName, const int N, int &Arr)
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