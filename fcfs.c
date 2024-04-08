#include <stdio.h>
#include <sys/types.h>


struct process
{
    pid_t pid;
    int ArriveTime, BurstTime, CompleteTime, TurnaroundTime, WaitTime;   
};


typedef struct process process_t;


void get_process_list(process_t *list, int num_of_processes);
void sort_processes(process_t *list, int num_of_processes);
void queify(process_t *list, int num_of_processes);
void print_hr(int cols);
void print_process_table(process_t *list, int num_of_processes);
void print_gantt_chart(process_t *list, int num_of_processes);


int main(int argc, char *argv[]) 
{
    int num_of_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_of_processes);
    process_t process_list[num_of_processes];
    get_process_list(process_list, num_of_processes);
    sort_processes(process_list, num_of_processes);
    queify(process_list, num_of_processes);
    print_process_table(process_list, num_of_processes);
    print_gantt_chart(process_list, num_of_processes);
    int total_wt = 0, total_tt = 0;
    for (int i = 0; i < num_of_processes; i++) 
    {
        total_tt += process_list[i].TurnaroundTime;
        total_wt += process_list[i].WaitTime;
    }
    double avg_tt = (double)total_tt / num_of_processes;
    double avg_wt = (double)total_wt / num_of_processes;
    printf("Average turn-around time: %f\n"
           "Average waiting time: %f\n",        
           avg_tt, avg_wt);
    return 0;
}


void get_process_list(process_t *list, int num_of_processes)
{
    for (int i = 0; i < num_of_processes; i++) 
    {
        printf("Enter the details of 'Process-%d':\n", i + 1);
        list[i].pid = i + 1;
        printf("Enter the arrival time: ");
        scanf("%d", &list[i].ArriveTime);
        printf("Enter the burst time: ");
        scanf("%d", &list[i].BurstTime);
    }   
}

void sort_processes(process_t *list, int num_of_processes) 
{
    for (int i = 0; i < num_of_processes - 1; i++)
    {
        int swap = 0;
        for (int j = 0; j < num_of_processes - i - 1; j++)
        {
            if (list[j].ArriveTime > list[j + 1].ArriveTime)
            {
                process_t temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
                swap = 1;
            }
        }   
        if (!swap)
            return;
    }
}

void queify(process_t *list, int num_of_processes) 
{
    for (int i = 0, CpuTime = 0; i < num_of_processes; i++) 
    {
        int IdleTime = list[i].ArriveTime - CpuTime;
       	if (IdleTime > 0) 
    		CpuTime += IdleTime;
 	else 
    		CpuTime += 0;
        CpuTime += list[i].BurstTime;
        list[i].CompleteTime = CpuTime;
        list[i].TurnaroundTime = CpuTime - list[i].ArriveTime;
        list[i].WaitTime = list[i].TurnaroundTime - list[i].BurstTime;
    }
}

void print_hr(int cols) 
{
    for (int i = 0; i < cols; i++) 
    {
        printf("--------");
    }
    printf("\n");
}

void print_process_table(process_t *list, int num_of_processes) 
{
    if (!num_of_processes)
        return;
    printf("Process table:\n");
    print_hr(6);
    printf("|  PID  |  AT   |  BT   |  CT   |  TT   |  WT   |\n");
    print_hr(6);
    for (int i = 0; i < num_of_processes; i++) 
    {
        printf("|%d   |%d   |%d   |%d   |%d   |%d   |\n", list[i].pid,
               list[i].ArriveTime, list[i].BurstTime, list[i].CompleteTime,
               list[i].TurnaroundTime, list[i].WaitTime);
        print_hr(6);
    }
    printf("\n");
}

void print_gantt_chart(process_t *list, int num_of_processes) 
{
    printf("Gantt chart:\n");
    print_hr(num_of_processes);
    printf("|");
    for (int i = 0, CpuTime = 0; i < num_of_processes; i++) 
    {
        int IdleTime = list[i].ArriveTime - CpuTime;
        if (IdleTime > 0) 
        {
            CpuTime += IdleTime;
            printf("  idle  |");
        }
        CpuTime += list[i].BurstTime;
        printf("   P%d|", list[i].pid);
    }
    printf("\n");
    printf("0        ");
    for (int i = 0, CpuTime = 0; i < num_of_processes; i++) 
    {
        int IdleTime = list[i].ArriveTime - CpuTime;
        if (IdleTime > 0) 
        {
            CpuTime += IdleTime;
            printf("%d\t", CpuTime);
        }
        CpuTime += list[i].BurstTime;
        printf("%d\t", CpuTime);
    }
    printf("\n");
}

