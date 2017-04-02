#include "Scheduler.h"
#include <vector>

PCB * Scheduler::current = nullptr;
Scheduler::Scheduler()
{

	for (int i = 0; i < 15; i++)
	{
		Active_Array.push_back(vector<PCB*>());
		Expired_Array.push_back(vector<PCB*>());
	}
}
Scheduler::~Scheduler()
{
}



void Scheduler::count_credit(PCB * p)
{
	p->kredyt = p->kredyt / 2 + p->priorytet;
}

void Scheduler::change_era()
{
	auto Secondary_Array = Active_Array;
	Active_Array = Expired_Array;
	Expired_Array = Secondary_Array;
	cout << "=========================" << endl;
	cout << "Nastapila zmiana epok" << endl;
	cout << "=========================" << endl;
}

void Scheduler::add_to_active_array(struct PCB *p)
{
	if (p->stan != PCB::stan_procesu::READY)
		Active_Array[p->priorytet].push_back(p);
	else
	{
		p->stan = PCB::stan_procesu::ACTIVE;
		count_credit(p);
		Active_Array[p->priorytet].push_back(p);
	}
}

void Scheduler::add_to_expired_array(struct PCB *p)
{
	Expired_Array[p->priorytet].push_back(p);
}

void Scheduler::show_active_array()
{
	bool isEmpty = true;
	cout << "Kolejka procesow aktywnych." << endl;
	cout << "===========================" << endl << endl;
	for (int i = 0; i < 15; i++)
	{
		auto vector = Active_Array[i];
		for (auto elem : vector)
		{
			cout << "Nr. PID: " << elem->PID << endl;
			cout << "Nr. Kolejki:  " << i << endl;
			cout << "Priorytet: " << elem->priorytet << endl;
			cout << "Kredyt: " << elem->kredyt << endl;
			cout << "Kwant: " << elem->kwant << endl;
			if (elem->stan == PCB::stan_procesu::ACTIVE)
				cout << "Stan procesu: ACTIVE." << endl;
			else if (elem->stan == PCB::stan_procesu::WAITING)
				cout << "Stan procesu: WAITING." << endl;
			else if (elem->stan == PCB::stan_procesu::WAIT)
				cout << "Stan procesu: WAITING." << endl;
			else if (elem->stan == PCB::stan_procesu::ZOMBI)
				cout << "Stan procesu: ZOMBIE." << endl;
			else if (elem->stan == PCB::stan_procesu::INIT)
				cout << "Stan procesu: INIT" << endl;
			else if (elem->stan == PCB::stan_procesu::ENDED)
				cout << "Stan procesu: ENDED." << endl;
			cout << "Rejestr A:" << elem->A << endl;
			cout << "Rejestr B:" << elem->B << endl;
			cout << "Rejestr C:" << elem->C << endl;
			cout << "Rejestr D:" << elem->D << endl;
			cout << "Licznik rozkazow:" << elem->licznik << endl << endl;
			isEmpty = false;
		}
	}
	if (isEmpty)
		cout << "Kolejka jest pusta." << endl << endl;
	cout << "===========================" << endl << endl;
}

void Scheduler::show_expired_array()
{
	bool isEmpty = true;
	cout << "Kolejka procesow o wyczerpanym kwancie czasu." << endl;
	cout << "=============================================" << endl << endl;
	for (int i = 0; i < 15; i++)
	{
		auto vector = Expired_Array[i];
		for (auto elem : vector)
		{
			cout << "Nr. PID: " << elem->PID << endl;
			cout << "Nr. Kolejki:  " << i << endl;
			cout << "Priorytet: " << elem->priorytet << endl;
			cout << "Kredyt: " << elem->kredyt << endl;
			cout << "Kwant: " << elem->kwant << endl;
			if (elem->stan == PCB::stan_procesu::ACTIVE)
				cout << "Stan procesu: ACTIVE." << endl;
			else if (elem->stan == PCB::stan_procesu::WAITING)
				cout << "Stan procesu: WAITING." << endl;
			else if (elem->stan == PCB::stan_procesu::WAIT)
				cout << "Stan procesu: WAITING." << endl;
			else if (elem->stan == PCB::stan_procesu::ZOMBI)
				cout << "Stan procesu: ZOMBIE." << endl;
			else if (elem->stan == PCB::stan_procesu::INIT)
				cout << "Stan procesu: INIT" << endl;
			else if (elem->stan == PCB::stan_procesu::ENDED)
				cout << "Stan procesu: ENDED." << endl;
			cout << "Rejestr A:" << elem->A << endl;
			cout << "Rejestr B:" << elem->B << endl;
			cout << "Rejestr C:" << elem->C << endl;
			cout << "Rejestr D:" << elem->D << endl;
			cout << "Licznik rozkazow:" << elem->licznik << endl << endl;
			isEmpty = false;
		}
	}
	if (isEmpty)
		cout << "Kolejka jest pusta." << endl << endl;
	cout << "=============================================" << endl << endl;
}

int Scheduler::first_not_empty()
{
	for (int i = 0; i < 15; i++)
	{
		if (!Active_Array[i].empty())
		{
			return i;
		}
	}
	return -1;
}

int Scheduler::first_not_empty_e()
{
	for (int i = 0; i < 15; i++)
	{
		if (!Expired_Array[i].empty())
		{
			return i;
		}
	}
	return -1;
}

void Scheduler::select_process()
{
	current = nullptr;
	int index;
	int i = 0;
	if (first_not_empty() == -1 && first_not_empty_e() == -1)
	{
		cout << "Brak procesow w kolejkach" << endl;
	}
	else if (is_there_active() == 0 && is_there_active_e() == 0)
	{
		cout << "Brak procesow aktywnych. Wykonaj 'run'" << endl;
	}
	else if (first_not_empty() == -1 && first_not_empty_e() != -1)
	{
		change_era();
		select_process();
	}
	else if (is_there_active() == 0 && is_there_active_e() == 1)
	{
		transfer_process();
		change_era();
		select_process();
	}
	else if (is_there_active() == 1)
	{
		for (i = 0; i < 15; i++)
		{
			index = 0;
			if (!Active_Array[i].empty())
			{
				if (Active_Array[i][index]->stan != PCB::stan_procesu::ACTIVE)
				{
					while (Active_Array[i].size() > index)
					{
						if (Active_Array[i][index]->stan == PCB::stan_procesu::ACTIVE)
						{
							current = Active_Array[i][index];
							break;
						}
						else
						{
							index++;
						}
					}
				}
				else
				{
					current = Active_Array[i][index];
					Active_Array[i].erase(Active_Array[i].begin());
					break;
				}
			}
			if (current != nullptr)
			{
				Active_Array[i].erase(Active_Array[i].begin() + index);
				break;
			}
		}
	}
}

void Scheduler::show_current_process(struct PCB *p)
{
	if (current != nullptr) {
		cout << "Wybrany proces." << endl;
		cout << "===============" << endl << endl;
		cout << "Nr. PID: " << p->PID << endl;
		cout << "Nr. Kolejki:  " << p->priorytet << endl;
		cout << "Priorytet: " << p->priorytet << endl;
		cout << "Kredyt: " << p->kredyt << endl;
		cout << "Kwant: " << p->kwant << endl;
		if (p->stan == PCB::stan_procesu::ACTIVE)
			cout << "Stan procesu: ACTIVE." << endl;
		else if (p->stan == PCB::stan_procesu::WAITING)
			cout << "Stan procesu: WAITING." << endl;
		else if (p->stan == PCB::stan_procesu::WAIT)
			cout << "Stan procesu: WAITING." << endl;
		else if (p->stan == PCB::stan_procesu::ZOMBI)
			cout << "Stan procesu: ZOMBIE." << endl;
		else if (p->stan == PCB::stan_procesu::INIT)
			cout << "Stan procesu: INIT" << endl;
		else if (p->stan == PCB::stan_procesu::ENDED)
			cout << "Stan procesu: ENDED." << endl;
		cout << "Rejestr A:" << p->A << endl;
		cout << "Rejestr B:" << p->B << endl;
		cout << "Rejestr C:" << p->C << endl;
		cout << "Rejestr D:" << p->D << endl;
		cout << "Licznik rozkazow:" << p->licznik << endl << endl;

	}
	else
		cout << "Brak procesu" << endl << endl;
	cout << "===============" << endl << endl;
}

PCB *Scheduler::execute()
{
	return current;
}

void Scheduler::result(int result)
{
	if (current != nullptr)
	{
		if (result == 1)
		{
			count_credit(current);
			set_time_quantum(current);
			add_to_expired_array(current);
			current = nullptr;
		}
		else if (result == 0)
		{
			current->stan = PCB::stan_procesu::WAIT;
			add_to_active_array(current);
			current = nullptr;
		}
		else if (result == 2)
		{
			current->eexit(0);
			current = nullptr;
		}
		else if (result == 3)
		{
			current->waitpid();
			add_to_active_array(current);
			current = nullptr;
		}
	}
	else
		cout << "Brak procesu!" << endl << endl;

}

int Scheduler::is_there_active()
{
	int index;
	int i;
	for (i = 0; i < 15; i++)
	{
		index = 0;
		if (!Active_Array[i].empty())
		{
			if (Active_Array[i][index]->stan != PCB::stan_procesu::ACTIVE)
			{
				while (Active_Array[i].size() > index)
				{
					if (Active_Array[i][index]->stan == PCB::stan_procesu::ACTIVE)
					{
						return 1;
					}
					else
					{
						index++;
					}
				}
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

int Scheduler::is_there_active_e()
{
	int index;
	int i;
	for (i = 0; i < 15; i++)
	{
		index = 0;
		if (!Expired_Array[i].empty())
		{
			if (Expired_Array[i][index]->stan != PCB::stan_procesu::ACTIVE)
			{
				while (Expired_Array[i].size() > index)
				{
					if (Expired_Array[i][index]->stan == PCB::stan_procesu::ACTIVE)
					{
						return 1;
					}
					else
					{
						index++;
					}
				}
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

void Scheduler::transfer_process()
{
	for (int i = 0; i < 15; i++)
	{
		auto secondary_vector = Active_Array[i];
		for (auto *elem : secondary_vector)
		{
			int j = 0;
			if (Active_Array[i][j]->stan == PCB::stan_procesu::WAIT)
			{
				count_credit(Active_Array[i][j]);
				set_time_quantum(Active_Array[i][j]);
				Active_Array[i][j]->stan = PCB::stan_procesu::ACTIVE;
			}
			add_to_expired_array(Active_Array[i][j]);
			Active_Array[i].erase(Active_Array[i].begin() + j);
			j++;
		}
	}
}

void Scheduler::set_time_quantum(struct PCB *p)
{
	p->kwant = (p->kredyt / 3) + 1;
}

void Scheduler::add_from_list(struct PCB *p)
{
	bool add = false;
	while (p->nastepnyp)
	{
		p = p->nastepnyp;
		if (p->stan == PCB::stan_procesu::READY)
		{
			set_time_quantum(p);
			add_to_active_array(p);
			add = true;
		}
	}
	if (add == true)
		cout << "Dodano procesy do kolejki" << endl;
	else
		cout << "Brak procesow ktore mozna dodac do kolejki" << endl;
}

void Scheduler::show_both_arrays()
{
	show_active_array();
	show_expired_array();
}

void Scheduler::kill_scheduler(PCB *p)
{
	int index;
	int i = 0;
	int pom = 0;
	for (i = 0; i < 15; i++)
	{
		index = 0;
		if (!Active_Array[i].empty())
		{
			if (Active_Array[i][index]->PID != p->PID)
			{
				while (Active_Array[i].size() > index)
				{
					if (Active_Array[i][index]->PID == p->PID)
					{
						Active_Array[i].erase(Active_Array[i].begin() + index);
						pom = 1;
						break;
					}
					else
					{
						index++;
					}
				}
			}
			else
			{
				Active_Array[i].erase(Active_Array[i].begin());
				pom = 1;
				break;
			}
		}
	}
	if (pom != 1)
	{
		for (i = 0; i < 15; i++)
		{
			index = 0;
			if (!Expired_Array[i].empty())
			{
				if (Expired_Array[i][index]->PID != p->PID)
				{
					while (Expired_Array[i].size() > index)
					{
						if (Expired_Array[i][index]->PID == p->PID)
						{
							Expired_Array[i].erase(Expired_Array[i].begin() + index);
							break;
						}
						else
						{
							index++;
						}
					}
				}
				else
				{
					Expired_Array[i].erase(Expired_Array[i].begin());
					break;
				}
			}
		}
	}
}

void Scheduler::kill_all()
{
	for (int i = 0; i < 15; i++)
	{
		auto secondary_vector = Active_Array[i];
		for (auto *elem : secondary_vector)
		{
			int j = 0;
			Active_Array[i].erase(Active_Array[i].begin() + j);
			j++;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		auto secondary_vector = Expired_Array[i];
		for (auto *elem : secondary_vector)
		{
			int j = 0;
			Expired_Array[i].erase(Expired_Array[i].begin() + j);
			j++;
		}
	}
}

