#include<stdio.h>
#include<unistd.h>
#define MAX 10
struct process
{
	int at,bt,ct,no,tt,wt;
};
void main()
{
	int loc,min,time,i,n,j,g;
	float tat=0,twt=0;
	struct process p[MAX],key,gant[MAX],idle;
	printf("Enter the number of processes :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter Arrival time and Burst Time of process %d : \n",i+1);
		scanf("%d%d",&p[i].at,&p[i].bt);
		p[i].no=i+1;
	}
	for (i = 1; i < n; i++) {
        key = p[i];
        j = i - 1;
        while (j >= 0 && p[j].at > key.at) {
            p[j + 1] = p[j];
            j = j - 1;
        }
        p[j + 1] = key;
    }
	idle.bt=0;
	for(i=0,g=0,time=0;i<n;i++)
	{
		if(time<p[i].at)
		{
			gant[g]=idle;
    		gant[g++].ct=time=p[i].at;
		}
    	time+=p[i].bt;
    	p[i].ct=time;
    	gant[g++]=p[i];
	}
	for(i=0;i<n;i++)
	{
		p[i].tt=p[i].ct-p[i].at;
		p[i].wt=p[i].tt-p[i].bt;
		twt=twt+p[i].wt;
		tat=tat+p[i].tt;
	}
	printf("Gantt chart:\n");
    for(i=0;i<g;i++)
	{
		if(gant[i].bt==0)
			printf("| Idle   ");
		else
			printf("| p%d    ",gant[i].no);
	}
	printf("|\n");
	printf("0\t");  
	for(i=0;i<g;i++)
		printf("%2d\t",gant[i].ct);
	printf("\nTable :\n");
	printf(" _________________________________\n");
	printf("|Process| AT | BT | CT | TT | WT |\n");
	printf("|--------------------------------|\n");
	for(i=0;i<n;i++)
	{
		printf("|p%d \t| %2d | %2d | %2d | %2d | %2d |\n",p[i].no,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
	}
	printf(" _________________________________\n");
	twt=twt/n;
	tat=tat/n;
	printf("\nAverage WT:%f\n",twt);	
	printf("Average TT:%f\n",tat);		
}