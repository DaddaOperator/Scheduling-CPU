//Davide Reverberi Matr: 332781

//Simulazione algoritmi di scheduling

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#include "item.h" //Basic process structure

float basic_medium_time1(vector<Item> v, int num) {
	int sum = 0;
	float waiting_time = 0;
	vector<Item>::iterator it;
	for (it = v.begin(); it != (v.end()-1); it++) {
		sum += (*it).get_burst_cpu();
		waiting_time += sum;
	}
	return waiting_time / num;
}

void process_ordered(vector<Item> v, int num) {
	vector<Item>::iterator it;
	it = v.begin();
	cout << (*it).get_process_name();
	for (it = (v.begin()+1); it != v.end(); it++) {
		cout << "->" << (*it).get_process_name();
	}
}

bool comparator_SJF(const Item& i1, const Item& i2) {
	return i1.get_burst_cpu() < i2.get_burst_cpu();
}

bool comparator_priority(const Item& i1, const Item& i2) {
	return i1.get_priority() < i2.get_priority();
}

int remove_to_total(vector<Item> v, int q) {
	//Additional time to remove from total
	int rep = 0;
	vector<Item>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		int count = 0; //count if burst_CPU is perfectly divisible with quantum lenght
		int temp_burst = (*it).get_burst_cpu();
		if (temp_burst % q == 0) {
			count++;
		}
		rep += (temp_burst / q) - count;
	}
	return rep * q;
}

int main(int argc, char** argv) {

	if (!argv[1]) {
		cout << "File di testo non valido o non inserito" << endl;
	}
	
	ifstream myfile(argv[1]);

	//ifstream myfile("processi-linux.cfg.txt");
	//ifstream myfile("provaproc.txt");

	vector<Item> process;
	queue<Item> RR;

	char null; int ProcNum; int quantum_lenght;  //Input-file utility variables
	string nome_processo; int burst_cpu; int priority;

	if (myfile.is_open()) {

		myfile >> null >> ProcNum >> quantum_lenght;

		while (myfile >> nome_processo >> burst_cpu >> priority) {
			Item it(nome_processo, burst_cpu, priority);
			process.push_back(it);
			RR.push(it);
		}
	}
	else
	{
		cout << "Errore di apertura del file" << endl;
		return -1;
	}
	myfile.close();


	//FCFS working:
	cout << "FCFS:	  ";
	process_ordered(process, ProcNum);
	cout << ", TMA " << basic_medium_time1(process, ProcNum) << endl;
	
	//SJF working:
	cout << "SJF:	  ";
	sort(process.begin(), process.end(), &comparator_SJF);
	process_ordered(process, ProcNum);
	cout << ", TMA " << basic_medium_time1(process, ProcNum) << endl;

	//Priority working:
	cout << "Priorita: ";
	sort(process.begin(), process.end(), &comparator_priority);
	process_ordered(process, ProcNum);
	cout << ", TMA " << basic_medium_time1(process, ProcNum) << endl;

	//Round Robin working:
	int rm = remove_to_total(process, quantum_lenght);
	float sum = 0;
	float tot_waiting_time = 0;
	process.clear();
	int remaining;
	while (!RR.empty()) {
		Item temp = RR.front();
		RR.pop();
		remaining = temp.get_burst_cpu() - quantum_lenght;
		if (remaining > 0) {
			temp.set_new_burst(remaining);
			sum += quantum_lenght;
			RR.push(temp);
		}
		else {
			sum += temp.get_burst_cpu();
			tot_waiting_time += sum - temp.get_burst_cpu();
		}
		process.push_back(temp);
	}
	cout << "RR:	  ";
	process_ordered(process, ProcNum);
	cout << ", TMA " <<(float)(tot_waiting_time-rm)/ProcNum<< endl;

	system("PAUSE");
	return 0;
  }
