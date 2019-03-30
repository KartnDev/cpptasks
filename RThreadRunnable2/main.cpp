#include "main.h"


void DoWork(int &a)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "\n";
	std::cout << "ID потока: " << std::this_thread::get_id() << " ======================\tDoWork STARTED \t =======================" << std::endl;
	std::cout << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	a *= 2;
	std::cout << "\n";
	std::cout << "ID потока: " << std::this_thread::get_id() << " ======================\tDoWork ENDED \t ========================= "  << std::endl;
	std::cout << "\n";

}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	int q = 5;
	

	
	std::thread thr1(DoWork, std::ref(q));


	for (size_t i = 0; i < 10; i++)
	{
		std::cout << "ID потока: " << std::this_thread::get_id() << "\t   Ќомер операции: " << i <<   " \t main works \t" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	thr1.join();

	std::cout << "YOUR NUM: " << q << std::endl;
	std::cout << "\n";

	system("pause");

	return (0);
}