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
public:
	int purchase_or_pay(int price)
	{
		if (price < wallet)
		{
			spent_money += price;
			return wallet - price;
		}
		else
		{
			purchase_exception(price);
			return -1;
		}
	}
	void purchase_exception(int price)
	{
		cout << LINE;
		cout << "Äåíåã íåäîñòàòî÷íî äëÿ ñîâåðøåíèÿ òðàíçàêöèè\n";
		cout << "Áàíê âàøåãî êîøåëüêà (" << wallet << ") ìåíüøå ÷åì öåíà ñîâåðøàåìîé òðàíçàêöèè (" << wallet << ")\n";
		cout << LINE;
	}
	void deposit(int inc_money)
	{
		wallet += inc_money;
	}
	void check_money()	// ðèä - îíëè 
	{
		cout << "Âàø áàëàíñ äåíåã:" << wallet << endl;
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
			wallet = purchase_or_pay(price);
		}
		else
		{
			purchase_exception(price);
		}
	}
	void add_money(int inc_money)
	{
		deposit(inc_money);
		cout << "Âû ïîëîæèëè â êîøåëåê:" << inc_money << "äåíåã\n";
	}
	void view_money()
	{
		check_money();
	}

};

class Card_pay : public Buissness_math
{
public:
	void pay(int price)
	{
		if (price < wallet)
		{
			wallet = purchase_or_pay(price);
		}
		else
		{
			purchase_exception(price);
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
			purchase_exception(money);
		}
	}
	void add_money(int money)
	{
		deposit(money);
	}
	void view_money()
	{
		check_money();
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
	cout << "Äîáàâèì íà ñáåðáàíê :";
	sbercard.add_money(1000);
	sbercard.view_money();
	cout << LINE;
	cout << "Äîáàâèì íà ýëåêòðàêàðòó :";
	eletracard.add_money(500);
	eletracard.view_money();
	cout << LINE;
	cout << "îòïðàâèì 100 íà åëåêòðàêàðòó ñ êàðòû ñáåðáàíêà: \n";
	sbercard.send_money(eletracard, 100);
	cout << LINE;
	cout << "Íà ñáåðáàíêå: ";
	sbercard.view_money();
	cout << endl;
	cout << "Íà ýëåêòðîêàòå: ";
	eletracard.view_money();
	cout << LINE;
	cout << "çàïëàòèì çà ïîêóïêó ñ ñáåðáàíêà íà 500\n";
	sbercard.pay(500);
	cout << LINE;
	cout << "Íà ñáåðáàíêå îñòàëîñü: ";
	sbercard.view_money();
	cout << LINE;
	system("pause");
	cout << "\n\n\n\n\n\n";
	Cash WALLET;
	WALLET.add_money(1000);
	WALLET.view_money();
	cout << LINE;
	cout << "êóïèì íà 600: \n";
	WALLET.purchase(600);
	WALLET.view_money();
	*/

	Buissness_math* sells = new Buissness_math[10];

	for (int i = 0; i < 10; i++)
	{
		(i % 2) == 0 ? sells[i] = Card_pay() : sells[i] = Cash();
	}
	for (int i = 0; i < 10; i++)
	{
		sells[i].deposit(1000);
	}

	
	sells[1].check_money();
	sells[1].purchase_or_pay(45);
	sells[1].purchase_or_pay(341);
	sells[1].purchase_or_pay(245);
	cout << "\n" << sells[1].get_spent_money();

	//ñêîëüêî âñåãî âûïëàò áûëî?


	system("pause");
}