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

std::string sort_words_by_simbol(std::string word_arr[], char argument_simbol)	 

{	



	return "";
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
	std::getline(std::cin, inputStr);




	std::string *word_arr = split_string_by_words(inputStr);
	
	int word_counter = word_arr->length();
	

	for (int i = 0; i < word_counter; i++)
	{
		if (word_arr[i].at(0) != *"t")
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
	std::cout << "========================================================\n";


	for (int i = 0; i < word_counter; i++)
	{
		if (word_arr[i] != "null")
		{
			std::cout << word_arr[i] << std::endl;
		}
	}

	delete[] word_arr;

	
	_getch();
	return EXIT_SUCCESS;	//define EXIT_SUCCESS as 0 (in iostream)
}
