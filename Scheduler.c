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
			 //if burst time is greater than time quantum i.e. 6 then decrement the value by 6
			{
				queue[i]->burst_time -= tq;
				current_time += tq;      //current time is incremented by 6
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
			if (front == 0)             
			 {
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
		printf("Enter the number of processes: ");             
		scanf("%d", &n);           // n number of processes entered by user           
	Process p[n];
	for (i = 0; i < n; ++i) {
		printf("\n");
		printf("Enter Arrival time of process %d: ", i+1);      
		scanf("%d", &p[i].arrival_time);
		printf("Enter Burst time of process %d: ", i+1);
		scanf("%d", &p[i].burst_time);
		p[i].process_no = i+1;
	}
	while (1) {
		enqueue(p, n);  //here enqueue function is called
		printf("\nQueue: ");
		for (i = 0; i <= rear; ++i) {
			printf("%d ", queue[i]->process_no);
		}
		printf("\nFront = %d, Rear = %d.\n\n", front, rear);
		execute_process();
		                                                           // If all the processes have been processed, break from the loop.
		if (process1 == n)
			break;
	}
	return 0;
}

