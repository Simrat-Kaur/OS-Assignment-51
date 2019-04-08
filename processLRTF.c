#include<stdio.h>
int main()
{
//initializing arrival time,burst time and process queue
 int a[10],b[10],z[10],p[10],i,bg,count=0,time,n,min;  //bg stands for biggest/longest process
 double avg=0,t=0,end=0;
 //user will enter the number of processes
  printf("Enter the number of Processes:\n");
  scanf("%d",&n);
  //creating processes
  printf("Enter Process Id of Students :\n");
 for(i=0;i<n;i++)
 scanf("%d",&p[i]);
 //assigning arrival time to each process
 printf("Enter their Arrival time :\n");
 for(i=0;i<n;i++)
 scanf("%d",&a[i]);
 //Assigning burst time to each process
 printf("Enter Burst time :\n");
 for(i=0;i<n;i++)
 scanf("%d",&b[i]);
 for(i=0;i<n;i++) //storing burst time in a separate queue
 z[i]=b[i];
 //let min arrival time value be the first arrival time
 min=a[0];
 //check for other process whether they are having less arrival time or not
 for(i=1;i<n-2;i++)
{
	if(min>a[i])

		min=a[i];//if found less then assign it to minimum
}

b[0]+=min;


 for(time=0;count!=n;time++)
 {
   bg=0; //assigning bg equal to 0
  for(i=0;i<n;i++)
  {
   if(a[i]<=time && b[i]>=b[bg] && b[i]>0)//checking arrival time and burst time of each process and finding the largest burst time with respect to arrival time of each processes.
   {
   		if(b[i]==b[bg])//checking whether burst time of current process is equal to  burst time of all the processes
   			if(p[i]<p[bg])//comparing process id of current process with first burst time process
   				bg=i;
		if(b[i]>b[bg])//if burst time of current process is greater than burst time of first process then
			bg=i;//assigning current index value to bg
   }

  }
  b[bg]--;//decrementing the value of current bg process
  if(b[bg]==0) //if burst time of bg process is 0 then it has completed its task
  {
   count++;
   end=time+1;
   t+=end-a[bg];
   avg+=end-a[bg]-z[bg]; 
  }

 }
 printf("\n\nAverage Waiting Time = %lf\n",avg/n);//calculated average waiting time of total processes
    printf("Average Turnaround Time = %lf",t/n);//calculated turn around time of each processes.
    return 0;
}


