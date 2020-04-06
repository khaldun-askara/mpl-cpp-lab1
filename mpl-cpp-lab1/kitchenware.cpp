#include <string>
#include "kitchenware.h"
using namespace std;

Kitchenware::Kitchenware(int inventory_number)
{
	this->inventory_number = inventory_number;
}
string Kitchenware::Print()
{
	return "����������� �����: "+ to_string(inventory_number) + ", ���: "+ type_name;
}

Stove::Stove(int inventory_number, string color) : Kitchenware(inventory_number)
{
	this->color = color;
	this->type_name = "�����";
}

string Stove::Print()
{
	return Kitchenware::Print() + ", ����: " + color;
}

Pan::Pan(int inventory_number, int volume) :Kitchenware(inventory_number)
{
	this->type_name = "��������";
	this->volume = volume;
}

string Pan::Print()
{
	return Kitchenware::Print() + ", �����: " + to_string(volume);
}

Electric_stove::Electric_stove(int inventory_number, string color, int power) : Kitchenware(inventory_number), Stove(inventory_number, color)
{
	this->power = power;
	this->type_name = "������������� �����";
}

string Electric_stove::Print()
{
	return Stove::Print() + ", ��������: " + to_string(power);
}

Gas_stove::Gas_stove(int inventory_number, string color, int gas_outgo) : Kitchenware(inventory_number), Stove(inventory_number, color)
{
	this->gas_outgo = gas_outgo;
	this->type_name = "������� �����";
}

string Gas_stove::Print()
{
	return Stove::Print() + ", ����������� ����: " + to_string(gas_outgo);
}

Slow_cooker::Slow_cooker(int inventory_number, string color, int power, int volume, bool is_pressure_cooker) :
	Kitchenware(inventory_number), Pan(inventory_number, volume),
	Electric_stove(inventory_number, color, power) 
{
	this->is_pressure_cooker = is_pressure_cooker;
	this->Electric_stove::type_name = "�����������";
}

string Slow_cooker::Print()
{
	return Electric_stove::Print() + ", ��������: " 
									+ to_string(power) 
									+ ", ������� ����������: " 
									+ to_string(is_pressure_cooker);
}