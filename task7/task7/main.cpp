#include "Header.h"


void recieve(std::string str, std::string *key_words, unsigned key_lenght)
{


	unsigned temp = 0;
	bool flag_ignore = false;
	for (unsigned i = 0; i < str.length()-temp; i++)
	{
		for (unsigned key = 0; key < key_lenght; key++)
		{
			temp = key_words[key].length();
			if (str[i] == key_words[key].at(0))
			{
				unsigned flag = 0;
				for (unsigned j = 0; j < key_words[key].length(); j++)
				{
					if (str[i + j] == *"/" && str[i + j + 1] == *"*")
					{
						flag_ignore = true;
					}
					if (str[i + j] == *"*" && str[i + j + 1] == *"/")
					{
						flag_ignore = true;
					}
					if (str[i + j] == *"/" && str[i + j + 1] == *"/")
					{
						flag_ignore = true;
					}
					if (str[i + j] == *"/n")
					{
						//flag_ignore = false;
					}
					if (str[i + j] == key_words[key].at(j) && !flag_ignore)
					{
						flag++;
					}
					if (flag == key_words[key].length() && key_words[key] != "NULL" && !flag_ignore)
					{
						std::cout << key_words[key] << std::endl;
						key_words[key] = "NULL";
					}
				}
			}
		}
	}


	delete[] key_words;
}





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



//ôóíêöèÿ, êîòîðàÿ äîëæíà çàìåíèòü recieve
std::string find_word_and_index(std::string str, std::string key_word, unsigned &index) 
{
	
	std::string result;
	for (unsigned i = 0; i < str.length()- key_word.length(); i++)
	{
		if (str[i] == key_word[0])
		{
			for (unsigned j = 0; j < key_word.length(); j++)
			{
			

				if (str[i + j] == key_word[j])
				{
					result = key_word;
					index = j+i;
				}
			}
		}
	}

	return result;
}  




int main()
{
	setlocale(LC_ALL, "Ru");

	std::string keys;
	getline(std::cin, keys);
	
	
	unsigned key_counter, indexing;


	std::string str = read_file("main.cpp");
	std::string *arr = get_keys_in_str(keys, key_counter);
	
	
	recieve(str, arr, key_counter);
	

	delete[] arr;
	
	_getch();


	return 0;
}