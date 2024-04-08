#include<stdio.h>
#include<unistd.h>
#define MAX 10
struct process{
    int at,bt,wt,ct,no,tt;
};
void main()
{
    int loc,time, i, n, g,j;
    float tat=0,twt=0;
    struct process p[MAX],key,idle,min,gantt[MAX];
    printf("enter the number of process:");
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        printf("enter the arrival time burst time of the process %d : ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].no=i+1;
    }
    for (i=1;i<n;i++)
    {
        key=p[i];
        j=i-1;
        while(j>=0 && p[j].at>key.at){
            p[j+1]=p[j];
            j=j-1;
        }
        p[j+1]=key;
    }
    idle.bt=0;
    for (i=0,g=0,time=0;i<n;i++)
    {
        if(time<p[i].at){
            gantt[g]=idle ;
            gantt[g++].ct=time=p[i--].at ;
        }
        else{
            loc=i;
            for(j=i,min.bt=p[j].bt;j<n && p[j].at<=time;j++)
            {
                if(p[j].bt<min.bt){
                   min=p[j];
                   loc=j; 
                }
            }
            if(i!=loc)
            {
                p[loc]=p[i];
                p[i]=min;
            }
            time+=p[i].bt;
            p[i].ct=time;
            gantt[g++]=p[i];
        }
    }
    for(i=0;i<n;i++)
    {
        p[i].tt=p[i].ct-p[i].at;
        p[i].wt=p[i].tt-p[i].bt;
        tat=tat+p[i].tt;
        twt=twt+p[i].wt;
    }
    for(i=0;i<g;i++)
    {
        if(gantt[i].bt==0)
            printf("| Idle    ");
        else
            printf("| p%d    ",gantt[i].no);
    } 
    printf("|\n");
    printf("0\t");
    for(i=0;i<g;i++)
        printf("%2d\t",gantt[i].ct);
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
