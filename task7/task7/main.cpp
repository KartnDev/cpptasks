#include "Header.h"
#include <algorithm>



std::string* get_keys_in_str(std::string keys_str, unsigned &return_counter)
{
	unsigned word_count = 1;
	for (unsigned i = 0; i < keys_str.length(); i++)
	{
		if (keys_str[i] == ' ')
		{
			word_count++;
		}
	}

	std::string *key_words = new std::string[word_count]();

	unsigned count = 0;
	for (unsigned i = 0; i < keys_str.length(); i++)
	{

		if (keys_str[i] != ' ')
		{
			key_words[count] += keys_str[i];
		}
		else
		{
			count++;
		}

	}
	return_counter = word_count;
	return key_words;
}




std::string read_file(const char *filename)
{
	std::ifstream fs(filename);
	std::string line;
	std::string text;

	if (fs.is_open())
	{
		for (unsigned i = 0; !fs.eof(); i++)
		{
			getline(fs, line);
			text += line;
		}
	}
	else
	{
		//exception 
		std::cout << "Something went wrong...\n";
		return NULL;
	}
	return text;
}




std::string find_word_and_index(std::string str, std::string key_word, unsigned &index) 
{
	unsigned flag = 0;
	for (unsigned i = 0; i < str.length() -key_word.length(); i++)
	{
		for (unsigned j = 0; j < key_word.length(); j++)
		{
			if (str[i + j] == key_word[j])
			{
				flag++;
				if (flag == key_word.length())
				{
					index = i;
					return key_word;
				}
			}
		}
	}
}  




int main()
{
	setlocale(LC_ALL, "Ru");

	std::string keys;
	getline(std::cin, keys);
	
	
	unsigned key_counter;


	std::string str = read_file("main.cpp");
	std::string *arr = get_keys_in_str(keys, key_counter);
	
	unsigned *numerat_arr = new unsigned[key_counter];


	unsigned index =0;
	for (unsigned i = 0; i < key_counter; i++) 
	{
		find_word_and_index(str, arr[i], index);
		numerat_arr[i] = index;
		index;
	}
	std::sort(numerat_arr, numerat_arr + key_counter);

	for (unsigned i = 0; i < key_counter; i++)
	{
		
	}
	delete[] arr;
	
	_getch();


	return 0;
}
