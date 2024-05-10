#include<stdio.h>
#define MAX 100
int q[MAX],front = -1, rear = -1;
struct process
{
	int at,bt,ct,no,tt,wt,rbt;
};
void enqueue(int item)
{
	if (front == -1)
		front = 0;
	q[++rear] = item;
}
int dequeuemin(struct process p[])
{
	int i=front,loc=front,id=-1;
	if(front!=-1){
		for(id=q[front];i<=rear;i++)
		{
			if(p[id].rbt>p[q[i]].rbt){
				id=q[i];
				loc=i;
			}
		}
		if(loc!=front){
			q[loc]=q[front];
			q[front]=id;
		}
		id = q[front];
		if (front == rear)
			front = rear = -1;
		else
			front = front + 1;
	}
	return id;
}
void main()
{
	int time=0,nextp=-1,i,n,temp,j=0,g=0,tq=1;
	float tat=0,twt=0;
	struct process temp1,p[MAX],key,gant[MAX],idle;
	printf("Enter the number of processes :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter Arrival time and Burst Time of process %d : \n",i+1);
		scanf("%d%d",&p[i].at,&p[i].bt);
		p[i].no=i+1;
        p[i].rbt=p[i].bt;
	}
	for (i = 0; i < n-1; i++) 
	{
        	for (j = 0; j < n-1; j++) 
		{
        		if(p[j].at>p[j+1].at)
        		{
        			temp1=p[j];
        			p[j]=p[j+1];
        			p[j+1]=temp1;
        		}
        	}
    	}
	idle.bt=0;
	j=0;
	while(front >=0 || j < n||(nextp!=-1&&p[nextp].rbt!=0) )
    	{
        	for(;j<n&&p[j].at<=time;j++)
    			enqueue(j);
    		if(nextp!=-1&&p[nextp].rbt!=0)
        	    enqueue(nextp);
        	if(front >= 0){
        	    nextp=dequeuemin(p);
        	    gant[g]=p[nextp];
        	    time+=tq;
        	    p[nextp].rbt-=tq;
    			gant[g++].ct=time;
        	    p[nextp].ct=time;
        	}
        	else
        	{
        	    gant[g]=idle;
        	    gant[g++].ct=time=p[j].at;
        	}   
    	}	
	for(i=0;i<n;i++)
	{
		p[i].tt=p[i].ct-p[i].at;
		p[i].wt=p[i].tt-p[i].bt;
		twt=twt+p[i].wt;
		tat=tat+p[i].tt;
	}
	printf("Gantt chart:\n");
    for(i=0;i<g-1;i++)
	{
		if(gant[i].bt==0)
			printf("| Idle   ");
		else if(gant[i].no!=gant[i+1].no)
			printf("| p%d    ",gant[i].no);
	}
	printf("| p%d    |\n",gant[i].no);
	printf("0\t");  
	for(i=0;i<g-1;i++)
	{
		if(gant[i].no!=gant[i+1].no)
			printf("%2d\t",gant[i].ct);
	}
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