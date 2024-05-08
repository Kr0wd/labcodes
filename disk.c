#include<stdio.h>
#include<stdlib.h>
#define MAX 20
int temp;
void fcfs(int a[],int n)
{
	int i,total=0;
	printf("Sequence : %d ",a[0]);
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i+1]);		
		temp=abs(a[i+1]-a[i]);
		total+=temp;
	}
	printf("\nTotal head movement = %d \n",total);
}
void main() {
	int i,n,a[MAX],ch,start;
	printf("Enter the number of requests :");
	scanf("%d",&n);
	for(i=1;i<n+1;i++)
		scanf("%d",&a[i]);
	printf("Enter the starting position :");
	scanf("%d",&start);
	a[0]=start;
	fcfs(a,n);
}
