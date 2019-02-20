#include "Main.h"
#include <conio.h>
#include <iostream>
#include <fstream>
const unsigned N = 20;

//������� Equal ��������� ��� ���������
//���������� ��� 2 ���������
void Equal(rational FirstRational, rational SecondRational)
{
	if (FirstRational.numerator / (int)FirstRational.denominator > SecondRational.numerator / (int)SecondRational.denominator)
	{
		std::cout << "������������ ����� " << FirstRational.numerator << "/" << FirstRational.denominator <<
			" ������, ��� " << SecondRational.numerator << "/" << SecondRational.denominator << std::endl;
	}
	else
	{
		std::cout << "������������ ����� " << SecondRational.numerator << "/" << SecondRational.denominator <<
			" ������, ��� " << FirstRational.numerator << "/" << FirstRational.denominator << std::endl;
	}
	_getch();
}
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

int main()
{
	setlocale(LC_ALL, "ru");
	
	rational rational_nums[N];
	pair Rational_Pair;

	int tempArr[N];

	FileReader("numerator.txt", N, *tempArr);
	for (unsigned i = 0; i < N; i++)
	{
		rational_nums[i].numerator = tempArr[i];
	}
	FileReader("denominator.txt", N, *tempArr);
	for (unsigned i = 0; i < N; i++)
	{
		rational_nums[i].denominator = tempArr[i];
	}
	
	for (unsigned i = 0; i < N; i++)
	{
		std::cout << "������������ �����" << "[" << i << "]" << " = " << rational_nums[i].numerator << "/" << rational_nums[i].denominator << "\n";
	}

	std::cout << "�������� 2 ������������ �����\n";
	std::cout << "������ ������������ �����(������� ����� �� 0 �� 19)\n";
	std::cin >> Rational_Pair.first;
	std::cout << "������ ������������ �����(������� ����� �� 0 �� 19)\n";
	std::cin >> Rational_Pair.second;



	Equal(rational_nums[Rational_Pair.first], rational_nums[Rational_Pair.second]);
	_getch();
	return EXIT_SUCCESS;
}
