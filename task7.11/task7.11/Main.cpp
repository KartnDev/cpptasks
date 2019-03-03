#include <iostream>
#include <fstream>
#include <conio.h>
#include <string> 



int main()
{
	setlocale(LC_ALL, "Ru");
	std::string inputStr;
	std::getline(std::cin, inputStr);


	int word_counter = 1;
	for (int i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) == *" ")
		{
			word_counter++;
		}
	}


	std::string *word_arr = new std::string[word_counter];
	int words = 0;

	for (int i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) != *" ")
		{
			word_arr[words] += inputStr.at(i);
		}
		else
		{
			words++;
		}
	} 

	

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
