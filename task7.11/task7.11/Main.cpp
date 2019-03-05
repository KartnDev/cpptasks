#include <iostream>
#include <fstream>
#include <conio.h>
#include <string> 

//function takes string line and returns array of words(strings)

std::string *split_string_by_words(std::string string_name)
{
	int word_counter = 1;
	for (int i = 0; i < string_name.length(); i++)
	{
		if (string_name.at(i) == *" ")
		{
			word_counter++;
		}
	}

	std::string *word_arr = new std::string[word_counter];

	int count_of_words = 0;

	for (int i = 0; i < string_name.length(); i++)
	{
		if (string_name.at(i) != *" ")
		{
			word_arr[count_of_words] += string_name.at(i);
		}
		else
		{
			count_of_words++;
		}
	}

	return word_arr;
}



	/*
	@	function takes first arg as ARRAY OF STRINGS (that strings is words)
	@   and second arg is flag-simbol
	@	if word have first simbol == argument_simbol
	@	this word will override by 'null_string'
	@	after all result_arr(string) will be returned
	@	result_arr have only words which starts from 'argument_simbol'
	*/

std::string *sort_words_by_simbol(std::string word_arr[], char argument_simbol)	 
{	

	int word_counter = word_arr->length();


	for (int i = 0; i < word_counter; i++)
	{
		if (word_arr[i].at(0) != argument_simbol)
		{
			word_arr[i] = "null";
		}
	}
	for (int i = 0; i < word_counter; i++)
	{
		for (int j = 0; j < word_counter; j++)
		{
			if (word_arr[i] != "null")
			{

				if (word_arr[i] == word_arr[j] && i != j)
				{
					word_arr[i] = "null";
				}
			}
		}
	}

	int result_words_counter=0;

	for (int i = 0; i < word_counter; i++)
	{
		if (word_arr[i] != "null")
		{
			result_words_counter++;
		}
	}
	std::string *resulting_string = new std::string[word_counter];

	for (int i=0, counter=0; i < word_counter; i++)
	{
		if (word_arr[i] != "null")
		{
			resulting_string[counter] = word_arr[i]; 
			counter++;
		}
	}


	return resulting_string;
}

//funtion which taking file name and reading file then returning converted string
std::string convert_text_to_string(std::string file_name)		
{
	


	return "";
}




//TODO: is (simbol+word is end-word -> crash 



int main()
{
	setlocale(LC_ALL, "Ru");

	std::string inputStr;
	char simbol;

	std::cout << "Enter the string\n";
	std::getline(std::cin, inputStr);

	std::cout << "Enter the simbol\n";
	std::cin >> simbol;

	std::string *end_str = sort_words_by_simbol(split_string_by_words(inputStr), simbol);
	
	for(int i =0; i < end_str->length();i++)
	{
		std::cout << end_str[i] << std::endl;
	}


	delete[] end_str;
	
	_getch();
	return EXIT_SUCCESS;	//define EXIT_SUCCESS as 0 (in iostream)
}
