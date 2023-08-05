# Scheduling-CPU
Simulation in c++ of the 4 cpu scheduling algorithms used in Linux environments or in general in the administration of operating systems:
1) FCFS (First come first served)
2) SJF (Shortest Job First) based on the cpu burst of each process.
3) Priority, based on an arbitrary priority (integer number) assigned to each process.
4) RR (Round Robin) based on a slice of time given at each process.

The program works by showing the order of execution of the processes given in input as a txt file and the average waiting time obtained.

main.cpp is where you can find the main code and the logic behind this simulation of the scheduling algorithms.
item.h is the header file containing the definition of the generic object, represented by me as a generic process with its relative burst time required for execution.
There are also 2 text files used as examples to verify the correct behavior of the program.
The program also compiles correctly on Linux, using gcc.
