#include <iostream>
#include <string>
#include <conio.h>

int main()
{	
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

	//создаем массив(WordArr) типа string, куда будем записывать слова из считанной строки (inputStr)
	std::string *WordArr = new std::string[WordCnt]();

	//переменная целочисленных беззнаковых чисел для перехода между словами (лежит от нуля до WordCount)
	unsigned label = 0;
	
	//пробегаем по всем символам строки
	//записываем те символы WordArr(массив слов) 
	//если встречается пробел, то перепрыгиваем на новое слово 
	//пробелы не входят в слова
	for (unsigned i = 0; i < inputStr.length(); i++)
	{
		if (inputStr.at(i) == *" ")
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
	
	_getch();
}