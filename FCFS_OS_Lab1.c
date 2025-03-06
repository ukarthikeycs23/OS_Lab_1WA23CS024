#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void findWaitingTime(struct Process processes[], int n) {
    processes[0].waiting_time = 0;
    
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
}

void findTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void findCompletionTime(struct Process processes[], int n) {
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    
    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
    }
}

void findAverageTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_completion_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_completion_time += processes[i].completion_time;
    }

    printf("Average waiting time: %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average completion time: %.2f\n", (float)total_completion_time / n);
}

void printProcessTable(struct Process processes[], int n) {
    printf("Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time \n");
    printf("--------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%10d | %12d | %10d | %12d | %15d | %15d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time,processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
    }

    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);
    findCompletionTime(processes, n);
    printProcessTable(processes, n);
    findAverageTimes(processes, n);

    return 0;
}
