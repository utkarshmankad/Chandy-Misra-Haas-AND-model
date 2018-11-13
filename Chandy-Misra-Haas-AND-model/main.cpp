#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>

using namespace std;

//Function to detect deadlock
void detectDeadlock(vector<std::vector<int>> &graph, int init, int dest);

//Function to display graph
void displayGraph(vector<vector<int>> mat);

//Number of proccesses in the system
int no_proccesses;

//Deadlock flag - 0 for false, 1 for true
bool deadlock_flag = 0;

// The main - The program execution starts from here
int main() {

	//Proccess ID of the proccess initiating the probe
	int pid_probe;
	
	//Enter the number of proccesses in the system
	cout << "Enter the number of processes (minimum value greater than 1)" << endl;
	cin >> no_proccesses;
	
	if (no_proccesses > 1) 
	{
		//Enter the wait-graph. (nxn) matrix.
		cout << "Enter the wait graph" << endl;

		vector<vector<int>> wait_graph(no_proccesses);		

		//Input the wait graph values
		for (int from = 0; from < no_proccesses; from++)
		{
			for (int to = 0; to < no_proccesses; to++)
			{
				int temp;
				cin >> temp;
				wait_graph.at(from).push_back(temp);
			}
		}

		cout << endl;
		cout << "The wait-for graph is : " << endl << endl;

		//display wait for graph
		displayGraph(wait_graph);
		cout << endl;

		//Enter the proccess initiating the probe
		cout << "Enter the proccess initiating the probe (Betwwen 1 and no. of proccesses)" << endl;
		cin >> pid_probe;
		cout << endl;
		pid_probe = pid_probe - 1;

		//Initializing the probe to detect deadlock
		cout << "Initiating Probe....." << endl << endl;
		cout << "DIRECTION" << "\t" << "PROBE" << endl;

		//Detecting deadlock
		for (int col = 0; col < no_proccesses; col++)
		{
			if (wait_graph.at(pid_probe).at(col) == 1)
			{
				cout << " S" << (pid_probe + 1) << " --> S" << (col + 1) << "     (" << (pid_probe + 1) << "," << (pid_probe + 1) << "," << (col + 1) << ")" << endl;
				detectDeadlock(wait_graph, pid_probe, col);
			}
		}
	}
	else {
		cout << "Deadlock detection not possbile. No proccess running in the system" << endl;
	}

	return 0;
}

void displayGraph(vector<vector<int>> wait_graph)
{
	int n = wait_graph.at(0).size();
	int m = wait_graph.size();
	
	//Top Column
	cout << "\t";
	for (int j = 0; j < m; j++) {
		cout << "S" << (j + 1) << "\t";
	}
	cout << endl;	
	//Side column and values
	for (int i = 0; i<m; i++)
	{
		cout << "S" << (i + 1) << "\t";
		for (int j = 0; j<n; j++)
		{
			cout << wait_graph.at(i).at(j) << "\t";
		}
		cout << "\n";
	}
}

void detectDeadlock(vector<std::vector<int>> &graph, int init, int dest)
{
	int end = no_proccesses;
	for (int col = 0; col < end; col++)
	{
		if (graph[dest][col] == 1)
		{
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col + 1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " --------> DEADLOCK DETECTED HERE" << endl;
				deadlock_flag = 1;
				break;
			}
			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << endl;
			detectDeadlock(graph, init, col);
		}
	}
}
