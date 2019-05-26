/*наследование : платеж(суперкласс) -> 
-наследники:
-платеж по карте, 
-платеж по кэшу(наличными)
по карте имеет реквизиты
по наличными сдачу и те
*/
#include <iostream>
using namespace std;

constexpr auto LINE = "=============================================================================\n";


class Buissness_math
{
public:
	Buissness_math()
	{
		wallet = 0;
		spent_money = 0;
	}
	int get_spent_money()
	{
		return spent_money;
	}
protected:
	int purchase_or_pay(int price, int wallet_bank)
	{
		if (price < wallet_bank)
		{
			spent_money += price;
			return wallet_bank - price;
		}
		else
		{
			purchase_exception(price, wallet_bank);
			return -1;
		}
	}
	void purchase_exception(int price, int wallet_bank)
	{
		cout << LINE;
		cout << "Денег недостаточно для совершения транзакции\n";
		cout << "Банк вашего кошелька (" << wallet_bank << ") меньше чем цена совершаемой транзакции (" << price << ")\n";
		cout << LINE;
	}
	void deposit(int& inc_money, int& bank)
	{
		bank += inc_money;
	}
	void check_money(int &bank)	// рид - онли 
	{
		cout << "Ваш баланс денег:" << bank << endl;
	}
protected:
	int wallet;
private:
	int spent_money;
};



class Cash : public Buissness_math
{
public:

	Cash()
	{
		wallet = 0;
	}
	void purchase(int price)
	{
		if (price < Buissness_math::wallet)
		{
			wallet = purchase_or_pay(price, wallet);
		}
		else
		{
			purchase_exception(price, wallet);
		}
	}
	void add_money(int inc_money)
	{
		deposit(inc_money, wallet);
		cout << "Вы положили в кошелек:" << inc_money << "денег\n";
	}
	void view_money()
	{
		check_money(wallet);
	}

};

class Card_pay : public Buissness_math
{
public:
	void pay(int price)
	{
		if (price < wallet)
		{
			wallet = purchase_or_pay(price, wallet);
		}
		else
		{
			purchase_exception(price, wallet);
		}
	}
	void send_money(Card_pay& other_card, int money)
	{
		if (money < wallet)
		{
			other_card.add_money(money);
			wallet -= money;
		}
		else
		{
			purchase_exception(money, wallet);
		}
	}
	void add_money(int money)
	{
		deposit(money, wallet);
	}
	void view_money()
	{
		check_money(wallet);
	}
	Card_pay()
	{
		wallet = 0;
	}
};


int main()
{
	setlocale(LC_ALL, "Ru");
	/*
	Card_pay eletracard, sbercard;
	cout << "Добавим на сбербанк :";
	sbercard.add_money(1000);
	sbercard.view_money();
	cout << LINE;

	cout << "Добавим на электракарту :";
	eletracard.add_money(500);
	eletracard.view_money();
	cout << LINE;

	cout << "отправим 100 на електракарту с карты сбербанка: \n";
	sbercard.send_money(eletracard, 100);
	cout << LINE;
	cout << "На сбербанке: ";
	sbercard.view_money();
	cout << endl;
	cout << "На электрокате: ";
	eletracard.view_money();
	cout << LINE;


	cout << "заплатим за покупку с сбербанка на 500\n";
	sbercard.pay(500);
	cout << LINE;
	cout << "На сбербанке осталось: ";
	sbercard.view_money();
	cout << LINE;

	system("pause");
	cout << "\n\n\n\n\n\n";
	Cash WALLET;
	WALLET.add_money(1000);
	WALLET.view_money();

	cout << LINE;
	cout << "купим на 600: \n";
	WALLET.purchase(600);
	WALLET.view_money();
	*/

	Buissness_math *sells = new Buissness_math[10];

	for (int i = 0; i < 10; i++)
	{
		(i % 2) == 0 ? sells[i] = Card_pay() : sells[i] = Cash();
	}
	for (int i = 0; i < 10; i++)
	{
		if (i % 2)
		{
			(Card_pay)sells[i].Card_pay::add_money(1000);
		}
	}


	//сколько всего выплат было?


	system("pause");
}