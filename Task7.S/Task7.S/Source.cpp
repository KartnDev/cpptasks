#include <iostream>

using namespace std;

const char* LINE = "\n=====================================================================================================\n";

bool check_c(char ch)
{
	return (ch == *"\n" || ch == *"\t" || ch == *" ");
}

void split_from_start(char*& string, int& string_lenght, int n)
{
	if (check_c(string[n]) && check_c(string[n + 1]))
	{
		split_from_start(string, string_lenght, n + 1);
	}
	else
	{
		for (int i = 0; i < n + 1; i++)
		{
			cout << "Встречен пробел\n";
		}
		char* temp = string;

		string_lenght = string_lenght - n - 1;

		string = new char[string_lenght];

		for (int i = 0; i < string_lenght; i++)
		{
			string[i] = temp[i + n];
		}
	}
}

void split_from_end(char*& string, int& string_lenght, int n)
{
	if (check_c(string[n]) && check_c(string[n - 1]))
	{
		split_from_end(string, string_lenght, n - 1);
	}
	else
	{
		for (int i = 0; i < string_lenght - n; i++)
		{
			cout << "Встречен пробeл\n";
		}
		char* temp = string;

		string_lenght = n;

		string = new char[string_lenght];

		for (int i = 0; i < string_lenght; i++)
		{
			string[i] = temp[i];
		}
	}
}


void split(char*& string, int& string_lenght)
{
	split_from_start(string, string_lenght, 0);
	split_from_end(string, string_lenght, string_lenght - 1);
}


int main()
{


	setlocale(LC_ALL, "Ru");





	char* word = (char*)"   \nПривет, мир!   \n";
	int len = 20;
	
	cout << "Данное слово:";
	for (int i = 0; i < len; i++)
	{
		cout << word[i];
	}
	cout << "c длиной(числом символов) = " << len <<"\n"<< LINE;

	split(word, len);


	//вывод слова как массива чаров(без мусора)
	for (int i = 0; i < len; i++)
	{
		cout << word[i];
	}


	system("pause");
	return 0;
}







