#include <string>
#include "kitchenware.h"
using namespace std;

Kitchenware::Kitchenware(int inventory_number)
{
	this->inventory_number = inventory_number;
}
string Kitchenware::Print()
{
	return "Инвентарный номер: "+ to_string(inventory_number) + ", тип: "+ type_name;
}

Stove::Stove(int inventory_number, string color) : Kitchenware(inventory_number)
{
	this->color = color;
	this->type_name = "Плита";
}

string Stove::Print()
{
	return Kitchenware::Print() + ", цвет: " + color;
}

Pan::Pan(int inventory_number, int volume) :Kitchenware(inventory_number)
{
	this->type_name = "Кастрюля";
	this->volume = volume;
}

string Pan::Print()
{
	return Kitchenware::Print() + ", объём: " + to_string(volume);
}

Electric_stove::Electric_stove(int inventory_number, string color, int power) : Kitchenware(inventory_number), Stove(inventory_number, color)
{
	this->power = power;
	this->type_name = "Электрическая плита";
}

string Electric_stove::Print()
{
	return Stove::Print() + ", мощность: " + to_string(power);
}

Gas_stove::Gas_stove(int inventory_number, string color, int gas_outgo) : Kitchenware(inventory_number), Stove(inventory_number, color)
{
	this->gas_outgo = gas_outgo;
	this->type_name = "Газовая плита";
}

string Gas_stove::Print()
{
	return Stove::Print() + ", потребление газа: " + to_string(gas_outgo);
}

Slow_cooker::Slow_cooker(int inventory_number, string color, int power, int volume, bool is_pressure_cooker) :
	Kitchenware(inventory_number), Pan(inventory_number, volume),
	Electric_stove(inventory_number, color, power) 
{
	this->is_pressure_cooker = is_pressure_cooker;
	this->Electric_stove::type_name = "Мультиварка";
}

string Slow_cooker::Print()
{
	return Electric_stove::Print() + ", мощность: " 
									+ to_string(power) 
									+ ", функиця скороварки: " 
									+ to_string(is_pressure_cooker);
}