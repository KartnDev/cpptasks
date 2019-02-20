#include <iostream>
#include <conio.h>
#include <fstream>

bool foo(int &arr, int lenght)
{
	//algorithm of bool : if(true) ->  returns false AND break;
	for (int i = 0; i < lenght - 1; i++)
	{
		if ((*(&arr + i) == 0) || (*(&arr + i) > 0 && *(&arr + i+1) > 0) || (*(&arr + i) < 0 && *(&arr + i + 1) < 0))
		{
			return false;
		}
	}
	
	return true;
}

/*bool foo(int arr[],const int size)
{
	bool t = true; //starts from true 

	//algorithm of bool : if(true) -> t equals false AND break;
	for (int i = 0; i < size - 1; i++)
	{
		if ((arr[i] == 0) || (arr[i] > 0 && arr[i+1] > 0) || (arr[i] < 0 && arr[i + 1] < 0))
		{
			t = false;
			break;
		}
	}

	return t;
}*/

int main()
{
	setlocale(LC_ALL, "ru");

	bool t;

	// N - lenght of array
	// a[n] - array of num(int)

	const int N = 6;
	int Array[N];

	//inputs nums of array from file
	std::ifstream fReader("Test1.txt");
	if (!fReader.is_open())
	{
		std::cout << "FileReadException!" << std::endl;
	}
	else
	{
		for (int i=0;i<N;i++)
			fReader >> Array[i];
	}
	fReader.close();

	t = foo(*Array, N); 

	std::cout <<"ваше t = " << t <<'\n';
	std::cout << "1 == True, \t 0 == False \n";
	_getch();
	return 0;
}