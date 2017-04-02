#pragma once
//#include "Zarzadca_procesami.h"
#include <iostream>
#include <vector>
#include <array>
#include<list>
using namespace std;

struct PCB
{
public:
int PID;
int priorytet, rt_priorytet, kredyt, nice, stary_kredyt, kwant;
enum class stan_procesu { NEW, READY, ACTIVE, WAITING, ZOMBI, ENDED, INIT };
stan_procesu stan;
};

class Scheduler
{
public:

	vector<vector<PCB*>>Active_Array;
	vector<vector<PCB*>>Expired_Array;
	static PCB *current;


	Scheduler();
	~Scheduler();

	void count_credit(struct PCB *p);
	void change_era();
	void add_to_active_array(struct PCB *p);
	void add_to_expired_array(struct PCB *p);
	void show_active_array();
	void show_expired_array();
	int first_not_empty();
	int first_not_empty_e();
	void select_process();
	void show_current_process(struct PCB *p);
	PCB * execute();
	void result(int result);
	int is_there_active();
	int is_there_active_e();
	void transfer_process();
	void set_time_quantum(struct PCB *p);
	void add_from_list(struct PCB *p);
	void show_both_arrays();
	void kill_scheduler(PCB *p);
	void kill_all();

};