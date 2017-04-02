#include <iostream>
#include "Scheduler.h"

using namespace std;





int main()
{
	Scheduler *s = new Scheduler();
	PCB *p = new PCB;
	int nPID = 0;

	int pom;
	for (;;)
	{
	
		cout << "1 - Dodaj p" << endl;
		cout << "2 - Pokaz active" << endl;
		cout << "3 - Pokaz expired" << endl;
		cout << "4 - Pierwsza nie pusta" << endl;
		cout << "5 - Pokaz obecny" << endl;
		cout << "6 - Wybierz proces" << endl;
		cout << "7 - Zmiana epok" << endl;
		cout << "8 - Result" << endl;
		cout << "9 - Wyczysc ekran" << endl;
		cin >> pom;
		switch (pom)
		{

		case 1:
		{
			int prio;
			int pom;
			cout << "Podaj priorytet: ";
			cin >> prio;
			PCB *p = new PCB;
			p->PID = nPID;
			p->priorytet = prio;
			cout << "1 - stan: active" << endl;
			cout << "2 - stan: waiting" << endl;
			cout << "3 - stan: zombie" << endl;
			cout << "4 - stan: ended" << endl;
			cin >> pom;
			switch (pom)
			{
			case 1:
				p->stan = PCB::stan_procesu::ACTIVE;
				break;
			case 2:
				p->stan = PCB::stan_procesu::WAITING;
				break;
			case 3:
				p->stan = PCB::stan_procesu::ZOMBI;
				break;
			case 4:
				p->stan = PCB::stan_procesu::ENDED;
				break;
			default:
				break;
			}
			system("cls");
			s->add_to_active_array(p);
			nPID++;
		}
			break;
		case 2:
			s->show_active_array();
			break;
		case 3:
			s->show_expired_array();
			break;
		case 4:
			cout << "Pierwsza niepusta kolejka: " << s->first_not_empty() << endl;
			break;
		case 5:
		{
			if (s->current == nullptr)
				cout << "Brak aktualnego procesu" << endl;
			else
			{
				s->show_current_process(s->current);
			}
		}
		break;
		case 6:
			s->select_process();
			break;
		case 7:
			s->change_era();
			break;
		case 8:
			s->result(1, s->current);
			break;
		case 9:
			system("cls");
			break;

		}
	}

	system("pause");
	return 0;
}