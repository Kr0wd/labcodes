#include<stdio.h>
void main() {
    int available[10], allocated[30][30], need[30][30], max[30][30], m, n, finish[20], req[20], w[10], i, j, temp[10],p,k,f=0,count=0;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("\nEnter the number of resource types: ");
    scanf("%d", &m);
    printf("\nEnter the allocation matrix:\n");
    for(i = 0; i < n; i++) {
        finish[i] = 0;
        printf("Process %d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }
    printf("\nEnter the Maximum Resource matrix:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the max resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    //Here, the program calculates the available resources by 
    //subtracting the allocated resources from the maximum available resources for each resource type.
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            available[i]-=allocated[j][i];
        }
    }
    //This loop calculates the need matrix by 
    //subtracting the allocated resources from the maximum resources for each process and resource type.
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    // Display table
    printf("\n-------------------Resource Allocation Table----------------------\n");
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
    printf("\nEnter the requesting process number : ");
    scanf("%d",&p);
    printf("\nEnter the requesting instances : \n");
    for(i=0; i<m; i++) {
        scanf("%d",&req[i]);
    }
    //This loop checks if the request can be granted without leading to deadlock.
    // It ensures that the request does not exceed the available resources and the maximum need of the process.
    f=0;
    for(i=0; i<m; i++)
    {
        if(req[i]>available[i] && req[i]>need[p][i])
        {
            f++;
            break;
        }
    }
    //If the request is valid, this block of code 
    //updates the allocation, need, and available matrices accordingly.
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
        //This block of code checks for deadlock by attempting to find a safe sequence of processes to execute.
        // If a safe sequence is found, it executes the processes and updates the available resources.
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

//1. **Initialization**: `c` is initialized to 0 to track the number of processes executed in a safe sequence, and `f` is set to 0 to indicate no resource-request conflicts initially.

//2. **Nested Loops**: Two nested loops are used to iterate over each process (`i`) and each process again (`j`). This is done to ensure that all processes are considered for execution.

//3. **Check if Process can be Executed**: Within the nested loops, the code checks if the process `j` can be executed. This is determined by whether the process `j` has already finished (`finish[j]==0`) and if the available resources are sufficient for the process's needs.

//4. **Inner Loop**: Inside the nested loops, another loop iterates through each resource type (`k`) to compare the available resources (`available[k]`) with the resource needs of process `j` (`need[j][k]`).

//5. **Check for Resource Availability**: If any resource type lacks sufficient availability to fulfill process `j`'s needs, `f` is set to 1, indicating a conflict.

//6. **Execute Process if No Conflict**: If `f` remains 0 after checking all resource types, it means that process `j` can be executed safely. The program then updates the available resources, marks process `j` as finished (`finish[j]=1`), increments the count of executed processes (`count`), and stores the executed process index in the `w` array.

//7. **Update Available Resources**: The available resources are updated by adding the allocated resources of the executed process `j`.

//8. **Print Execution Status**: It prints the execution status of process `j` along with the updated available resources.

//9. **Reset `f`**: After each inner loop iteration (checking all resources for process `j`), `f` is reset to 0 to prepare for the next process iteration.

//10. **Safety Sequence**: The array `w` stores the indices of the processes executed in a safe sequence.

//11. **Print Safety Sequence**: If all processes can be executed safely (`count==n`), it prints the safety sequence along with the status "Deadlock Free". Otherwise, it indicates a deadlock condition.

//This block of code is crucial for determining whether the system is in a safe state and finding a safe sequence of processes to execute, thereby preventing deadlocks.