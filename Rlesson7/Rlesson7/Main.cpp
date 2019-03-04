#include <iostream>
#include <string>
#include <conio.h>

int main()
{	
	setlocale(LC_ALL, "ru");

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

	//������� (����������� ��������) ������(WordArr) ���� string, ���� ����� ���������� ����� �� ��������� ������ (inputStr)
	std::string *WordArr = new std::string[WordCnt]();

	//���������� ������������� ����������� ����� ��� �������� ����� ������� (����� �� ���� �� WordCount)
	unsigned label = 0;
	
	//��������� �� ���� �������� ������
	//���������� �� ������� WordArr(������ ����) 
	//���� ����������� ������, �� ������������� �� ����� ����� 
	for (unsigned i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) == *" ") //������������ ������ inputStr[i]
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

	//������� ��������� ������� ���� 
	delete[] WordArr;

	system("pause"); //����� ������ ��������
	std::cout << "-------------------------------------------------\n";
	
	
	
	char *str = new char[inputStr.length()];
	std::string *words = new std::string[WordCnt];
	


	for (int i = 0; i < inputStr.length(); i++)
	{
		str[i] = inputStr[i];
	}
	
	char *next_token, *token1 = strtok_s(str, " ", &next_token);

	for(unsigned counter = 0; token1 != NULL; counter++)
	{
		if (WordCnt == counter) break;
		words[counter] = token1; // ����� ��� ������ * ����� �������� ����� �����, � �� ������� ���� 1�� ������
		std::cout  << "token at (" << counter << ") : "<< token1 <<std::endl;
		token1 = strtok_s(NULL, " ", &next_token);
	}
	std::cout << "-------------------------------------------------\n";
	std::cout << "result:\n";

	for (unsigned i = WordCnt; i > 0; i--)
		std::cout << words[i - 1] << " ";

	system("pause");





	delete[] str;
	delete[] words;
	_getch();
	return EXIT_SUCCESS;
}