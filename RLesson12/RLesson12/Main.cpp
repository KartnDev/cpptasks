#include <iostream>
using namespace std;

constexpr auto LINE = "=============================================================================\n";


class Buissness_math
{
public:
	 int purchase(int price, int wallet_bank)
	 {
		if (price < wallet_bank)
		{
			return wallet_bank - price;
		}
		else
		{
			purchase_exception(price, wallet_bank);
			return -1;
		}
	 }

private:

	void purchase_exception(int price, int wallet_bank)
	{
		cout << LINE;
		cout << "����� ������������ ��� ���������� ����������\n";
		cout << "���� ������ �������� (" << wallet_bank << ") ������ ��� ���� ����������� ���������� (" << price << ")\n";
		cout << LINE;
	}
protected:

	void deposit(int& inc_money, int& bank)
	{
		bank += inc_money;
	}
	void check_money(int bank)	// ��� - ���� 
	{
		cout << "��� ������ �����:" << bank << endl;
	}
};



class Cash : public Buissness_math
{
public:
	
	Cash()
	{
		wallet_money = 0;
	}

	void add_money(int inc_money)
	{
		deposit(inc_money, wallet_money);
		cout << "�� �������� � �������:" << inc_money << "�����\n";
	}
	void check_money()
	{

	}

private:
	int wallet_money;
};

class Card_pay : public Buissness_math
{
public:
	void send_money(&)
	{

	}
	Card_pay()
	{
		card_money = 0;
	}

private:
	int card_money;
};


int main()
{
	setlocale(LC_ALL, "Ru");



	system("pause");
}