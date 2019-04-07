#include <stdio.h>
int main() 
{
 int a[10],b[10],z[10],p[10],i,bg,count=0,time,n,min;
 double avg=0,t=0,end=0;
 printf("Enter the number of Processes:\n");
 scanf("%d",&n); 
 printf("Enter Process Id of Students :\n");
 for(i=0;i<n;i++)
 scanf("%d",&p[i]);//array to enter the process id of Students
 printf("Enter their arrival time :\n");
 for(i=0;i<n;i++)
 scanf("%d",&a[i]);//array to enter the arrival time
 printf("Enter burst time :\n");
 for(i=0;i<n;i++)
 scanf("%d",&b[i]); //array to enter the burst time
 for(i=0;i<n;i++)
 z[i]=b[i];
 
 min=a[0];
 for(i=1;i<n-2;i++)
{
	if(min>a[i])
		min=a[i];
}

b[0]+=min;

for(time=0;count!=n;time++)
 {
   bg=0;
  for(i=0;i<n;i++)
  {
   if(a[i]<=time && b[i]>=b[bg] && b[i]>0)
   {
   		if(b[i]==b[bg])
   			if(p[i]<p[bg])
   				bg=i;
		if(b[i]>b[bg])
			bg=i;
   }
 
  }
  b[bg]--;
  if(b[bg]==0)
  {
   count++;
   end=time+1;
   t+=end-a[bg];
   avg+=end-a[bg]-z[bg];
  }
  
 }
 printf("\n\nAverage Waiting Time = %lf\n",avg/n);
 printf("Average Turnaround Time = %lf",t/n);
 return 0;
}

