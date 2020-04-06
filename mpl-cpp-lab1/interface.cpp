#include <iostream>
#include "kitchenware.h"
using namespace std;


//структура дерева
struct avl_tree
{
	Kitchenware* data;
	int height;
	avl_tree* left;
	avl_tree* right;

	avl_tree(Kitchenware * something)
	{
		data = something;
		left = right = nullptr;
		height = 1;
	}
};

avl_tree* tree = nullptr;
bool exit1;

//вспомогательные функции
int height(avl_tree* p)
{
	return p ? p->height : 0;
}
int balfac(avl_tree* p)
{
	return height(p->right) - height(p->left);
}
void newheight(avl_tree* p)
{
	int hleft = height(p->left);
	int hright = height(p->right);
	p->height = hleft > hright ? hleft + 1 : hright + 1;
}
avl_tree* R_rotate(avl_tree* p)
{
	avl_tree* q = p->left;
	p->left = q->right;
	q->right = p;
	newheight(p);
	newheight(q);
	return q;
}
avl_tree* L_rotate(avl_tree* p)
{
	avl_tree* q = p->right;
	p->right = q->left;
	q->left = p;
	newheight(p);
	newheight(q);
	return q;
}
avl_tree* balance(avl_tree* p)
{
	newheight(p);
	if (balfac(p) == 2)
	{
		if (balfac(p->right) < 0)
			p->right = R_rotate(p->right);
		return L_rotate(p);
	}
	if (balfac(p) == -2)
	{
		if (balfac(p->left) > 0)
			p->left = L_rotate(p->left);
		return R_rotate(p);
	}
	return p;
}
avl_tree* findmin(avl_tree* p)
{
	return p->left ? findmin(p->left) : p;
}
avl_tree* removemin(avl_tree* p)
{
	if (p->left == nullptr)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

//провер€ет, есть ли элемент с таким инвентарным номером
bool find(avl_tree* p, int inventory_number)
{
	if (!p) return false;
	if (inventory_number < p->data->inventory_number) { return find(p->left, inventory_number); }
	if (inventory_number > p->data->inventory_number) { return find(p->right, inventory_number); }
	if (inventory_number == p->data->inventory_number) { return true; }
}

//вставка
avl_tree* insert(avl_tree* p, Kitchenware* data)
{
	if (!p) return new avl_tree(data);
	if (data->inventory_number < p->data->inventory_number)
		p->left = insert(p->left, data);
	else
		p->right = insert(p->right, data);
	return balance(p);
}

//удаление
avl_tree* remove(avl_tree* p, Kitchenware* data)
{
	if (!p) return nullptr;
	if (data->inventory_number < p->data->inventory_number)
		p->left = remove(p->left, data);
	else if (data->inventory_number > p->data->inventory_number)
		p->right = remove(p->right, data);
	else
	{
		avl_tree* q = p->left;
		avl_tree* r = p->right;
		delete p->data;
		delete p;
		if (!r) return q;
		avl_tree* mintree = findmin(r);
		mintree->right = removemin(r);
		mintree->left = q;
		return balance(mintree);
	}
	return balance(p);
}

//удаление всего дерева
void clear(avl_tree* p) 
{
	if (!p) return;
	clear(p->left);
	clear(p->right);
	delete p->data;
	delete p;
}

// пр€мой обход
void NLR(avl_tree* p)
{
	if (!p) return;
	cout << p->data->Print() << endl;
	NLR(p->left);
	NLR(p->right);
}

// обратный обход 
void LRN(avl_tree* p)
{
	if (!p) return;
	LRN(p->left);
	LRN(p->right);
	cout << p->data->Print() << endl;
}

// симметричный обход
void LNR(avl_tree* p)
{
	if (!p) return;
	LNR(p->left);
	cout << p->data->Print() << endl;
	LNR(p->right);
}

void AddStove()
{
	string answer;
	int invent_number;
	string color;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try 
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (find(tree, invent_number))
		{
			cout << "Ќомер уже используетс€" << endl;
			continue;
		}
		cout << "¬ведите цвет" << endl;
		cin >> color;
		break;
	}
	tree = insert(tree, new Stove(invent_number, color));
	cout << "ѕлита добавлена" << endl;
}

void AddPan()
{
	string answer;
	int invent_number;
	int volume;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (find(tree, invent_number))
		{
			cout << "Ќомер уже используетс€" << endl;
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "¬ведите объЄм:" << endl;
		cin >> answer;
		try
		{
			volume = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		break;
	}
	tree = insert(tree, new Pan(invent_number, volume));
	cout << " астрюл€ добавлена" << endl;
}

void AddElStove()
{
	string answer;
	int invent_number;
	string color;
	int power;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (find(tree, invent_number))
		{
			cout << "Ќомер уже используетс€" << endl;
			continue;
		}
		break;
	}
	cout << "¬ведите цвет" << endl;
	cin >> color;
	while (true)
	{
		cout << "¬ведите мощность:" << endl;
		cin >> answer;
		try
		{
			power = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		break;
	}
	tree = insert(tree, new Electric_stove(invent_number, color, power));
	cout << "Ёлектрическа€ плита добавлена" << endl;
}

void AddGasStove()
{
	string answer;
	int invent_number;
	string color;
	int gasout;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (find(tree, invent_number))
		{
			cout << "Ќомер уже используетс€" << endl;
			continue;
		}
		break;
	}
	cout << "¬ведите цвет" << endl;
	cin >> color;
	while (true)
	{
		cout << "¬ведите потребление газа:" << endl;
		cin >> answer;
		try
		{
			gasout = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		break;
	}
	tree = insert(tree, new Gas_stove(invent_number, color, gasout));
	cout << "√азова€ плита добавлена" << endl;
}

void AddSlowCooker()
{
	string answer;
	int invent_number;
	string color;
	int power;
	int volume;
	bool cookfunc;
	int temp;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (find(tree, invent_number))
		{
			cout << "Ќомер уже используетс€" << endl;
			continue;
		}
		break;
	}
	cout << "¬ведите цвет" << endl;
	cin >> color;
	while (true)
	{
		cout << "¬ведите мощность:" << endl;
		cin >> answer;
		try
		{
			power = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "¬ведите объЄм:" << endl;
		cin >> answer;
		try
		{
			volume = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "ћультиварка имеет функцию скороварки? 1/0" << endl;
		cin >> answer;
		try
		{
			temp = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число";
			continue;
		}
		if (temp == 1 || temp == 0)
		{
			cookfunc = temp == 1;
			break;
		}
		else 
			cout << "¬ведено некорректное число" << endl;
	}
	tree = insert(tree, new Slow_cooker(invent_number, color, power, volume, cookfunc));
	cout << "ћультиварка добавлена" << endl;
}

void AddKWDoialog()
{
	string answer;
	while (true)
	{
		cout << "¬ыберите вид куханой утвари: 1 Ч ѕлита, 2 Ч  астрюл€, 3 Ч Ёлектрическа€ плита, 4 Ч √азова€ плита, 5 Ч ћультиварка, 0 Ч ¬ыход" << endl;
		cin >> answer;
		if (answer == "" || answer[0] == '0')
		{
			exit1 = false;
			break;
		}
		Kitchenware* temp = nullptr;
		int invent_number;
		if (answer[0] == '1')
			AddStove();
		if (answer[0] == '2')
			AddPan();
		if (answer[0] == '3')
			AddElStove();
		if (answer[0] == '4')
			AddGasStove();
		if (answer[0] == '5')
			AddSlowCooker();
		break;
	}
}

void DelByInvNUmberDialog()
{
	string answer;
	int invent_number;
	int volume;
	while (true)
	{
		cout << "¬ведите инвентарный номер:" << endl;
		cin >> answer;
		try
		{
			invent_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "¬ведено не число" << endl;
			continue;
		}
		if (!find(tree, invent_number))
		{
			cout << "Ќомер не найден" << endl;
			continue;
		}
		break;
	}
	
	tree = remove(tree, new Stove(invent_number, "dljeljf"));
}

void OutputDialog()
{
	string answer;
	while (true)
	{
		cout << "¬ыберите тип вывода: 1 Ч пр€мой, 2 Ч обратный, 3 Ч симметричный, 0 Ч выход";
		cin >> answer;
		if (answer == "" || answer[0] == '0')
		{
			exit1 = false;
			break;
		}
		if (answer[0] == '1')
			NLR(tree);
		if (answer[0] == '2')
			LRN(tree);
		if (answer[0] == '3')
			LNR(tree);
		break;
	}

}

void MainDialog()
{
	avl_tree* tree = nullptr;
	string answer;

	while (true)
	{
		exit1 = false;
		cout << "¬ыберите действие: 1 Ч добавить кухонную утварь, 2 Ч удаление по инвентарному номеру, 3 Ч ¬ывод данных, 0 Ч выход" << endl;
		cin >> answer;
		if (answer == "" || answer[0] == '0')
			break;
		if (answer[0] == '1')
			AddKWDoialog();
		if (exit1) break;
		if (answer[0] == '2')
			DelByInvNUmberDialog();
		if (exit1) break;
		if (answer[0] == '3')
			OutputDialog();
		if (exit1) break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	MainDialog();
	clear(tree);

	return 0;
}