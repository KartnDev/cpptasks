#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>




using namespace std;

int main()
{




	map<string, size_t> animal_populatin
	{
		{"humans", 7000000000},
		{"chiken", 23132433332},
		{"camels", 32323232},
		{"sheep",  1232323342}
	};

	//foreach 
	for (auto& [species, count] : animal_populatin)
	{
		cout << "There are " << count << " " << species << " on this planet.\n";
	}

	// disabling vision of if
	if (auto itr(0); false)
	{

	}

	// initialize 
	int a (110);
	int b {110};
	vector<int> v1 = { 1, 2, 3 };
	vector<int> v2	 { 1, 2, 3 };
	vector<int> v3	 (1, 2);


	// auto initialize

	auto v{ 10 };
	  //    auto w { 20, 30 }; - ERROR

	auto x = { 1, 2, 3, 4, 5 };


	// auto check template

	pair my_pair(123, "dsds");		// auto definition of T
	tuple my_tuple(132, 12.3, "zxc");	// auto definition of T

	//how it works:
	//check region AUTODEFINITION !!!!!!!!!!!!!!!!!!


	return 0;
}

#pragma region AutoDefinion
template <typename T1, typename T2, typename T3>
class my_wrapper
{
	T1 t1;
	T2 t2;
	T3 t3;
public:
	explicit my_wrapper(T1 t1_, T2 t2_, T3 t3_) : t1{ t1_ }, t2{ t2_ }, t3{ t3_ }
	{
		/*
		* SOME CODe
		*
		*/
	}
};

void foo1()
{
	//***********************************************************************
	//
	//						MAGIC!
	//
	//***********************************************************************





	my_wrapper<int, double, const char* > wrapperT{ 1, 2.1, "dsds" };
	my_wrapper wrapper{ 1, 2.3, "zxc" };
}




#pragma endregion





#pragma region MultiTemplate


template<typename T>
struct sum
{
	T value;

	template <typename ... Ts>
	sum(Ts&& values) : value{ (value + ...) };
};




template<typename ... Ts>
sum(Ts&& ...ts) -> sum<common_type_t<Ts...>>;

#pragma endregion
