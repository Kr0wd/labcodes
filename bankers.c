#include<stdio.h>
#define MAX 20
void display(int allocated[MAX][MAX],int need[MAX][MAX],int max[MAX][MAX],int available[MAX],int n,int m)
{
	int i,j;
		printf("Process\tAllocated\tMaximum\t\tNeed\t\tAvailable\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t", i);
        for(j = 0; j < m; j++) {
            printf("%d ", allocated[i][j]);
        }
        printf("\t\t");
        for(j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        for(j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\t\t");
        if(i == 0) {
            for(j = 0; j < m; j++) {
                printf("%d ", available[j]);
            }
        }
        printf("\n");
    }
}
void main()
{
	int allocated[MAX][MAX],i,need[MAX][MAX],max[MAX][MAX],j,q=0,n,m,k,p,f=0,req[MAX],finish[MAX],w[MAX],count=0,t[20][3],available[MAX];
	printf("Enter the number of processes:");
	scanf("%d",&n);
	printf("Enter the number of resources :");
	scanf("%d",&m);
	printf("ALLOCATION Table\n");
	for(i=0;i<n;i++)
	{
		finish[i] = 0;
		printf("Enter  Allocation  of Process %d : \n",i);
		for(j=0;j<m;j++)
			scanf("%d",&allocated[i][j]);
	}
	printf("MAX Table\n");
	for(i=0;i<n;i++)
	{
		printf("Enter  Max  of Process %d : \n",i);
		for(j=0;j<m;j++)
			scanf("%d",&max[i][j]);
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			need[i][j]=max[i][j]-allocated[i][j];
	}
	printf("Enter Available array :");
	for(j=0;j<m;j++)
			scanf("%d",&available[j]);
	printf("\n-------------------Resource Allocation Table----------------------\n");
	display(allocated,need,max,available,n,m);
	printf("\nEnter the requesting process number : ");
    scanf("%d",&p);
    printf("\nEnter the requesting instances : \n");
    for(f=0,i=0; i<m; i++) {
        scanf("%d",&req[i]);
        if(req[i]>available[i] && req[i]>need[p][i])
            f++;
    }
    if(f==0)
    {
        printf("Request Status : Successfull\n");
        for(i=0; i<m; i++)
        {
            available[i]-=req[i];
            need[p][i]-=req[i];
            allocated[p][i]+=req[i];
        }
        printf("\n----------Modified Resource allocation table----------\n");
        display(allocated,need,max,available,n,m);
        int c=0;
        f=0;
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(finish[j]==0)
                {
                    for(k=0; k<m; k++) {
                        if(available[k]<need[j][k]) {
                            f=1;
                            break;
                        }
                    }
                    if(f==0) {
                        printf("\n[Process %d] : Executed\n",j);
                        w[c]=j;
                        c++;
                        finish[j]=1;
                        count++;
                        printf("Available : ");
                        for(k=0; k<m; k++) {
                            available[k]=available[k]+allocated[j][k];
                            printf("%d ",available[k]);
                        }
                    }
                }
                f=0;
            }
        }
        if(count==n) {
            printf("\n------DeadLock Free-------");
            printf("\nSafety Sequence : ");
            printf("p%d",w[0]);
            for(i=1; i<c; i++) {
                printf(" --> p%d ",w[i]);
            }
        }
        else {
            printf("\n------DeadLock Condition-------\n");
        }
        printf("\n");
    }
    else
        printf("\nRequest status : Fail\n");
}