#include <iostream>
#include <string>
#include <conio.h>

int main()
{	
	//�������� ������ �� �������, ��������� getline
	//cin ����������, �� �� ����� ������������ �� ����� �������(1 ����� �������)
	std::string inputStr; 
	std::getline(std::cin, inputStr);

	unsigned WordCnt = 1; //WordCount


	//��������� ����� �������� � ����������� �������(WordCount)
	//����� ���� � ������ = ����� �������� +1  
	//������ ��������� ����� ���������� � 1 
	for (unsigned i = 0; i < inputStr.length(); i++) 
	{
		if (inputStr.at(i) == *" ")
		{
			WordCnt++;
		}
	}

	//������� ������(WordArr) ���� string, ���� ����� ���������� ����� �� ��������� ������ (inputStr)
	std::string *WordArr = new std::string[WordCnt]();

	//���������� ������������� ����������� ����� ��� �������� ����� ������� (����� �� ���� �� WordCount)
	unsigned label = 0;
	
	//��������� �� ���� �������� ������
	//���������� �� ������� WordArr(������ ����) 
	//���� ����������� ������, �� ������������� �� ����� ����� 
	//������� �� ������ � �����
	for (unsigned i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) == *" ")
		{
			label++;
		}
		else
		{
			WordArr[label] += inputStr[i];
		}
	}
	//���� ���������� � WordCount-1(����� ���� N, � ������ �� 0 �� N-1)
	//�������� � WordCount � ����������� �� 0
	for (unsigned i = WordCnt; i > 0; i--)
		std::cout << WordArr[i - 1] << " ";
	
	_getch();
}