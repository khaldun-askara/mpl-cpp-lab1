#pragma once
#include <string>
using namespace std;

//кухонная утварь
class Kitchenware
{
public:
	int inventory_number;
	string type_name;
	///Kitchenware() {};
	Kitchenware(int inventory_number);
	virtual ~Kitchenware() = 0 {};
	virtual string Print();
};

//плита
class Stove : virtual public Kitchenware
{
public:
	string color;
	Stove(int inventory_number, string color);
	string Print() override;
};

//кастрюля
class Pan : virtual public Kitchenware
{
public:
	int volume;
	Pan(int inventory_number, int volume);
	string Print() override;
};

// плита электрическая
class Electric_stove : public Stove
{
public:
	int power;
	Electric_stove(int inventory_number, string color, int power);
	string Print() override;
};

// плита газовая
class Gas_stove : public Stove
{
public:
	int gas_outgo;
	Gas_stove(int inventory_number, string color, int gas_outgo);
	string Print() override;
};

//мультиварка
class Slow_cooker : public Electric_stove, virtual public Pan
{
public:
	bool is_pressure_cooker;
	Slow_cooker(int inventory_number, string color, int power, int volume, bool is_pressure_cooker);
	string Print() override;
};