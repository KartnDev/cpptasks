#include <conio.h>
#include "Main.h"

int main()
{
	setlocale(LC_ALL, "Ru");

	position Coords;

	std::cin >> Coords.x;
	std::cin >> Coords.y;

	const int N = 10;

	bool Matrix[1000][1000];


	Circle Circles[10];

	double tempArr[N];

	//заполнение из текстового файла структуры данных об окружност€х

	for (int i = 0; i < N; i++)
	{
		FileReader("PosX.txt", N, *tempArr);
		Circles[i].PosX = tempArr[i];
	}
	for (int i = 0; i < N; i++)
	{
		FileReader("PosY.txt", N, *tempArr);
		Circles[i].PosY = tempArr[i];
	}
	for (int i = 0; i < N; i++)
	{
		FileReader("Radius.txt", N, *tempArr);
		Circles[i].Radius = tempArr[i];
	}


	//вывод массива в консоль

	std::cout << "¬ывод массива: \n";
	std::cout << "=================\n";
	for (int i = 0; i < N; i++)
	{
		std::cout << Circles[i].PosX << ", ";
	
		std::cout << Circles[i].PosY << ", ";
	
		std::cout << Circles[i].Radius << ", \n";
	}
	std::cout << "=================\n";


	//пролистывание по 3м ос€м матрицы

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			for (int CCount = 0; CCount < N; CCount++)
			{
				if (sq(j - Circles[CCount].PosX) + sq(i - Circles[CCount].PosY) < sq(Circles[CCount].Radius))
				{
					Matrix[i][j] = true;
				}
				else
				{
					Matrix[i][j] = false;
				}
			}
		}
	}

	//int count = 0;

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			if (Matrix[i][j])
			{
				//count++;
				if (Coords.x = j && Coords.y)
				{
					std::cout << "ƒа, €вл€етс€! \n";
				}
				_getch();
				return EXIT_SUCCESS;
			}
			
		}
		//std::cout << "\n";
	}
	//std::cout <<count<< " \n";
	std::cout  << "Ќет, не €вл€етс€! \n";
	_getch();

	return 0;
}