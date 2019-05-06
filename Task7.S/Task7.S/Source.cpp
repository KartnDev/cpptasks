#include <iostream>

using namespace std;

const char* LINE = "=====================================================================================================";

bool check_c(char ch)
{
	if (ch == *"\n" || ch == *"\t" || ch == *" ")
	{
		return true;
	}
	else
	{
		return false;
	}
}


void delete_simbol_by_index(char* &string,int len ,int index)
{
	
}





void split_from_start(char* &string,int &string_lenght ,int n)
{
	if (check_c(string[n]) && check_c(string[n + 1]))
	{
		split_from_start(string, string_lenght, n + 1);
	}
	else
	{
		for (int i = 0; i < n+1; i++)
		{
			cout << "Встречен пробел\n";
		}


		char* temp = string;

		string_lenght = string_lenght - n - 1;

		string = new char[string_lenght];
		for (int i = 0; i < string_lenght; i++)
		{
			string[i] = temp[i + n + 1];
		}
	}
}

void split_from_end(char string[], int string_lenght, int n)
{

}


void split(char string[])
{

}


int main()
{


	setlocale(LC_ALL, "Ru");

	char* word = (char*)"          dfdfdfdfd";
	int n = 14;

	split_from_start(word, n, 0);
	cout << word;

	system("pause");
	return 0;
}







