/*include*/
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

/*main*/
/*char*/
using namespace std;


int get_file_len(const char* filename)
{
	int len = 0;
	char temp;
	ifstream fs(filename);

	if (fs.is_open())
	{
		while (!fs.eof())
		{
			fs >> temp;
			len++;
		}
	}
	else
	{
		//exception 
		cout << "Something went wrong...\n";
		return NULL;
	}
	fs.close();

	return len;
}
const char* read_file(const char* filename)
{
	ifstream fs(filename);

	char* str;
	if (fs.is_open())
	{
		int len = get_file_len(filename);
		str = new char[len];
		for (int i = 0; i < len; i++)
		{
			fs >> str[i];
		}
	}
	else
	{
		//exception 
		cout << "Something went wrong...\n";
		return NULL;
	}
	fs.close();

	return str;
}





const char* find_word_and_index(const char* str, const char* key_word, int& index)
{
	int str_len = sizeof(str), key_len = sizeof(key_word), flag = 0;
	for (int i = 0; i < str_len-key_len; i++)
	{
		for (int j = 0; j < key_len; j++)
		{
			if (str == key_word)
			{
				cout << key_word;
			}
			else
			{
				flag = 0;
			}
			if (flag == key_len)
			{
				cout << key_word;
			}
		}
	}
	index = -1;
	return "fail";
}


int main()
{
	setlocale(LC_ALL, "Ru");


	int key_counter=0;


	const char* str = read_file("main.cpp");
	
	

	int temp_index=0;
	
	cout << find_word_and_index("char", "char", temp_index);
	cout << temp_index;
	

	
	

	return 0;
}