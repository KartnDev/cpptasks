#include <iostream>
#include <string>
#include <conio.h>

int main()
{	
	setlocale(LC_ALL, "ru");

	//считывем строку из консоли, испульзуя getline
	//cin недопустим, тк он будет игнорировать всё после пробела(1 слово прочтет)
	std::string inputStr; 
	std::getline(std::cin, inputStr);

	unsigned WordCnt = 1; //WordCount


	//посчитаем число пробелов в прочитанной строчек(WordCount)
	//число слов в сторке = число пробелов +1  
	//потому вордкаунт будет начинатсья с 1 
	for (unsigned i = 0; i < inputStr.length(); i++) 
	{
		if (inputStr.at(i) == *" ")
		{
			WordCnt++;
		}
	}

	//создаем (динамически выделяем) массив(WordArr) типа string, куда будем записывать слова из считанной строки (inputStr)
	std::string *WordArr = new std::string[WordCnt]();

	//переменная целочисленных беззнаковых чисел для перехода между словами (лежит от нуля до WordCount)
	unsigned label = 0;
	
	//пробегаем по всем символам строки
	//записываем те символы WordArr(массив слов) 
	//если встречается пробел, то перепрыгиваем на новое слово 
	for (unsigned i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) == *" ") //эквивалентно записи inputStr[i]
		{
			label++;
		}
		else
		{
			WordArr[label] += inputStr[i];
		}
	}
	//счет начитается с WordCount-1(всего слов N, а массив от 0 до N-1)
	//начинаем с WordCount и заканчиваем на 0
	for (unsigned i = WordCnt; i > 0; i--)
		std::cout << WordArr[i - 1] << " ";

	//удалить экземпляр массива слов 
	delete[] WordArr;

	system("pause"); //конец первый половины
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
		words[counter] = token1; // токен без ссылки * имеет значение всего слова, а со ссылкой лишь 1ый символ
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