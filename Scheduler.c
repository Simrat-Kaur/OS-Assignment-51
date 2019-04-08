#include <stdio.h>
#define MAX_QUEUE_SIZE 100   //queue of size 100 is defined here
typedef struct Processes {
	int process_no;      
	int arrival_time;
	int burst_time;
} Process;
Process * queue[MAX_QUEUE_SIZE];
int front = 0, rear = -1, process1 = 0, current_time = 0, tq = 6;  //here tq is time quantum as the process is interrupted after 6 sec.
int l_front = 0, l_rear = -1;
void swap(Process * a, Process * b) {
	Process temp = * a;
	* a = * b;
	* b = temp;
}
void sort_process(Process p[], int n) {
	int i, j;
	short swapped;
	for (i = 0; i < n; ++i) {
		swapped = 0;
		for (j = 0; j < n-i-1; ++j)
		{
			if (p[j].arrival_time > p[j+1].arrival_time) 		// swap the processes if the arrival time of process p[j] is greater than the process p[j+1]
			{
				swap(&p[j], &p[j+1]);
				swapped = 1;
			}
		}
		if (swapped == 0)
			break;
	}
}

void execute_process() {
	int i;

	if (front-1 == rear) {
		printf("CPU idle for 1 second.\n");
		current_time += 1;
	}
	else {
		l_front = front;
		l_rear = rear;
		for (i = front; i <= rear; ++i, ++front)
		{
			if (queue[i]->burst_time > tq)
			{
				queue[i]->burst_time -= tq;
				current_time += tq;
				printf("Process number %d excuted till %d seconds.\n", queue[i]->process_no, current_time);
			}
			else if (queue[i]->burst_time > 0)
			{
				current_time += queue[i]->burst_time;
				queue[i]->burst_time = 0;
				printf("Process number %d excuted till %d seconds.\n", queue[i]->process_no, current_time);
				++process1;
			}
		}
	}
}
void enqueue(Process p[], int n) {
	int i, j, insert;
	for (i = 0; i < n; ++i)
	{
		insert = 1;

		if (p[i].arrival_time <= current_time && p[i].burst_time > 0)
		{
			if (front == 0) {
				queue[++rear] = &p[i];
			}
			else
			{
				for (j = l_front; j <= l_rear; ++j) {
					if (queue[j]->process_no == p[i].process_no)
						insert = 0;
				}
				if (insert == 1)
					queue[++rear] = &p[i];
			}
		}
	}
	for (i = l_front; i <= l_rear; ++i)
	{
		if (queue[i]->burst_time > 0)
			queue[++rear] = queue[i];
	}
}
int main() {
	int n, i;
	short err_flag = 0;
	do {
		if (err_flag == 1)
			fprintf(stderr,"\nNumber of processes should be greater than 1.\n");     //we have to enter more than one process
		printf("Enter the number of processes: ");             
		scanf("%d", &n);                         //we can take n number of inputs 
		err_flag = 1;
	} while (n < 1);
	err_flag = 0;
	Process p[n];
	for (i = 0; i < n; ++i) {
		printf("\n");
		printf("Enter Arrival time of process %d: ", i+1);      
		scanf("%d", &p[i].arrival_time);
		printf("Enter Burst time of process %d: ", i+1);
		scanf("%d", &p[i].burst_time);
		p[i].process_no = i+1;
	}
	sort_process(&p[0], n);                                              // sort_process the processes according to the arrival time of each process.
	while (1) {
		enqueue(p, n);
		printf("\nQueue: ");
		for (i = 0; i <= rear; ++i) {
			printf("%d ", queue[i]->process_no);
		}
		printf("\nFront = %d, Rear = %d.\n\n", front, rear);
		execute_process();
		                                                           // If all the processes have been process1, break from the loop.
		if (process1 == n)
			break;
	}
	return 0;
}

