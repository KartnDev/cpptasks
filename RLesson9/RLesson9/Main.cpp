#include <iostream>
#include <fstream>
#include <string>
#include "Main.h"
#include <conio.h>

const int N = 20;

void FileReader(std::string FileName, const int N, int Arr[])
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
			fs >> Arr[i];
		}
	}
	fs.close();

}





class Rational: public math_functs_to_rational_nums
{
public:
	Rational(int numer, int denom)
	{
		this->denominator = denom;
		this->numerator = numer;
	}
	Rational()
	{
		//do_nothing
	}

	//������� ��������� ��������������� ���.����� (�����) � ����, ��� ���������� � ��������� �������
	void Equals(int next_numer, int next_denom) override
	{
		if (next_numer*denominator > next_denom*numerator)
		{
			std::cout << "���������(������): "<< next_numer << "/" << next_denom << " ������������ ����� ������ �������(�������): " << numerator << "/" <<denominator << " \n";
		}
		else
		{
			std::cout << "���������(������): " << next_numer << "/" << next_denom << "������������ ����� ������ �������(�������): " << numerator << "/" << denominator << " \n";
		}
	}


	//������������ � ��������� ������������ ������(�����)
	//��������� ����� �� ��������� 
	virtual double sum(int x, int y) override
	{
		return (x*denominator + y * numerator) / y / denominator;
	}
	virtual double decrim(int x, int y) override
	{
		return (x*denominator - y * numerator) / y / denominator;
	}
	virtual void PrintStack(int x, int y) override
	{
		std::cout << "������(������) ������������ �����: " << numerator << "/" << denominator << "\n";
		std::cout << "���������(������) ������������ �����: " << x << "/" << y << "\n";
	}

	//getters and setters for Denominator and numerator
	int get_numerator()
	{
		return this->numerator;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	int get_denominator()
	{
		return this->denominator;
	}
	void set_denominator(int denominator) 
	{
		this->denominator = denominator;
	}

private:
	int numerator;
	int denominator;

};



int main()
{
	setlocale(LC_ALL, "ru");
	Rational rational_nums[N];
	pair Rational_Pair;

	int tempArr[N];

	FileReader("numerator.txt", N, tempArr); //���������� ����������
	for (unsigned i = 0; i < N; i++)
	{
		rational_nums[i].set_numerator(tempArr[i]);
	}
	FileReader("denominator.txt", N, tempArr); //���������� ������������ 
	for (unsigned i = 0; i < N; i++)
	{
		rational_nums[i].set_denominator(tempArr[i]);
	}

	for (unsigned i = 0; i < N; i++)
	{
		std::cout << "������������ �����" << "[" << i << "]" << " = " << rational_nums[i].get_numerator() << "/" << rational_nums[i].get_denominator() << "\n";
	}

	std::cout << "�������� 2 ������������ �����\n";
	std::cout << "������ ������������ �����(������� ����� �� 0 �� 19)\n";
	std::cin >> Rational_Pair.first;
	std::cout << "������ ������������ �����(������� ����� �� 0 �� 19)\n";
	std::cin >> Rational_Pair.second;

	rational_nums[Rational_Pair.first].Equals(rational_nums[Rational_Pair.second].get_numerator(), rational_nums[Rational_Pair.second].get_denominator());

	
	_getch();
	return EXIT_SUCCESS;
}

