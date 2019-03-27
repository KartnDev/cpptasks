#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// реализация односвязного списка(как в STL)
template<class T>
class List
{
public:
	List(); // конструктор с вынесеным телом (реализацией)
	~List(); // деструктор ---||---

						//		МЕТОДЫ
	void display_data(); // метод показа всех элементов списка в консоль
	void push_back(T data); // метод добавления элемента назад (листа)
	void push_front(T data); // метод добавления элемента в начало(головную часть)
	void insert(T data, int index); // метод добавления по индексу в список
	void pop_back(); // метод удаления последнего элемента (последнего)
	void pop_front(); // метод удаления головного элемента(первого)
	void remove_at(int index); // удаление элемента по индексу в списке
	void clear(); // полное удаления списка
	int getsize() { return SIZE; } //геттер(получатель) размерности списка



	// перегружаем оператор [] 
	// для того, чтобы можно было получать элементы с помощью оператора [] 
	// реализация находится в main.cpp
	T& operator[](const int index);

private:
	// класс (вложеный) нода (узел)
	// нода - примитив списка (его объект), то из чего состоит сам список
	// класс шаблонный, чтобы была возможность хранить любой тип данных 
	template<class T> // typename?????????
	class Node
	{
	public:
		Node *p_next;
		T data;

		//		КОНСТРУКТОР НОДЫ: 
		// при передачи в конструктор ноды мы должны по дефолту обозначитьь их(во избежание мусора)
		// так указатель на след. ноду будет иметь нулл-ссылку
		// передаваемый тип данных (дата) будет по дефолту :
		// если класс то вызван конструктор по умолчанияю
		// если же примитивный тип данных, то присвоено дефолтное значение примитивного типа
		// все это делается во избежания мусора(ненужных неправильных данных) в неуказаных полях
		Node(T data = T(), Node *p_next = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
		}
	};
	int SIZE; // длина списка
	Node<T> *head; // головной член списка
};

// опередление конструктора
// при создании экземпляра все внутренние поля должны будут 
// определены дефолтными(стандартными для типа) значениями
template <class T>
List<T>::List()
{
	SIZE = 0;
	head = nullptr;
}



// при конце работы списка (вызове деструктора) 
// список должен будет быть стёрт
template <class T>
List<T>::~List()
{
	clear();
}



// тело метода показа в консоль всех данных в списке
// в каррент запишем ссылку на головную ноду
// сразу выведем данные из каррент ноды
// после чего в цикле будем в каррент будем передавать
// ссылку на следеющую ноду
// получится что каждый раз вы будем попадать в следующую ноду 
// будучи в переменной каррент
// и сразу выводить данные из ноды
template<class T>
void List<T>::display_data()
{
	Node<T> *current = this->head;

	cout << current->data << endl;

	while (current->p_next != nullptr)
	{
		current = current->p_next;
		cout << current->data << endl;
	} 
	//cout << current->data << endl;
}




// тело метода добавления в конец списка 
// 
template<class T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T> *current = this->head;

		while (current -> p_next != nullptr)
		{
			current = current-> p_next;
		}
		current->p_next = new Node<T>(data);
	}
	SIZE++;
}

template<class T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	SIZE++;
}


// метод внесения элемента на индексированное место
// 
template<class T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* p_prev = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			p_prev = p_prev->p_next;
		}

		Node<T>* new_node = new Node<T>(data, p_prev->p_next);

		p_prev->p_next = new_node;

		SIZE++;
	}
}

template<class T>
void List<T>::pop_back()
{
	remove_at(SIZE - 1);
}

template<class T>
void List<T>::pop_front()
{	 //переносим головную ноду на следующую ноду, а данную(бывшую головную) 
	 //записываем в временную переменную temp 
	Node<T> *temp = head;
	head = head->p_next;
	delete temp;
	SIZE--;
}

template<class T>
void List<T>::remove_at(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* p_prev = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			p_prev = p_prev->p_next;
		}

		Node<T>* p_removed = p_prev -> p_next;

		p_prev->p_next = p_removed -> p_next;

		delete p_removed;
		SIZE--;
	}


}




// метод полной отчистки памяти от списка
// суть в том, чтобы вызвать функция стирания первого элемента
// при высове метода поп_фронт удаляется элемент(нода) (головной)
// там после уменьшения SIZE--  
// тогда можем сделать выражение явного приведения от целогочисленного до булева
// любое ненулевое число == True 
// 0 == False 
template<class T>
void List<T>::clear()
{
	while ((bool)SIZE) // size > 0
	{
		pop_front();
	}

}


// реализация перегрузки оператора	[]
// смысл реализации: передается константное число и записываем счетчик(каунтер)
// создается нода(узел) которая является ссылкой на головную часть списка
// потом в цикле мы записываем в созданную ноду ссылку на следующую ноду
// если получается так, что каунтер будет равен переданному константному числу
// мы нашли тот самый индексированный элемент
// возвращаем его
template<class T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T> *p_current = this->head;

	while(p_current != nullptr)
	{
		if (counter == index)
		{
			return p_current -> data;
		}
		p_current = p_current->p_next;

		counter++;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	List<int> list;

	list.push_back(5);
	list.push_front(7);
	list.push_back(100);
	list.display_data();
	cout << endl;
	list.insert(77, 2);
	list.display_data();

	_getch(); // Серьезность	Код	Описание	Проект	Файл	Строка	Состояние подавления Предупреждение	C6031	Возвращаемое значение пропущено : "_getch".RLesson10	
		

	return EXIT_SUCCESS;
}