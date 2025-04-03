#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCS 10
#define TIME_QUANTUM 2

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority;  // 0-system, 1-user
    int waiting;
    int turnaround;
    int response_time;
    int started;
} Process;

void round_robin(Process procs[], int n, int *time, float *total_waiting, float *total_turnaround, float *total_response) {
    int remaining = n;
    int i = 0;

    while (remaining > 0) {
        if (procs[i].remaining > 0) {
            if (!procs[i].started) {
                procs[i].response_time = *time - procs[i].arrival;
                procs[i].started = 1;
                *total_response += procs[i].response_time;
            }

            if (procs[i].remaining > TIME_QUANTUM) {
                *time += TIME_QUANTUM;
                procs[i].remaining -= TIME_QUANTUM;
            } else {
                *time += procs[i].remaining;
                procs[i].waiting = *time - procs[i].burst - procs[i].arrival;
                procs[i].turnaround = procs[i].burst + procs[i].waiting;

                *total_waiting += procs[i].waiting;
                *total_turnaround += procs[i].turnaround;

                procs[i].remaining = 0;
                remaining--;
            }
        }
        i = (i + 1) % n;
    }
}

void fcfs(Process procs[], int n, int *time, float *total_waiting, float *total_turnaround, float *total_response) {
    for (int i = 0; i < n; i++) {
        if (*time < procs[i].arrival) {
            *time = procs[i].arrival; // Wait for process to arrive
        }

        procs[i].response_time = *time - procs[i].arrival;
        procs[i].waiting = *time - procs[i].arrival;

        *total_response += procs[i].response_time;

        *time += procs[i].burst;

        procs[i].turnaround = *time - procs[i].arrival;

        *total_waiting += procs[i].waiting;
        *total_turnaround += procs[i].turnaround;
    }
}

int main() {
    Process system_procs[MAX_PROCS], user_procs[MAX_PROCS];
    int sys_count = 0, user_count = 0;
    int total_time = 0;

    float total_waiting = 0.0, total_turnaround = 0.0, total_response = 0.0;

    int n;
    printf("Enter total processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        printf("\nEnter arrival time, burst time, and priority (1-system/2-user) for Process %d: ", i + 1);
        scanf("%d %d %d", &p.arrival, &p.burst, &p.priority);
        p.remaining = p.burst;
        p.waiting = p.turnaround = p.response_time = 0;
        p.started = 0;
        p.pid = i + 1;

        if (p.priority == 1)
            system_procs[sys_count++] = p;
        else
            user_procs[user_count++] = p;
    }

    // Process system queue (Round Robin)
    if (sys_count > 0) {
        round_robin(system_procs, sys_count, &total_time, &total_waiting, &total_turnaround, &total_response);
    }

    // Process user queue (FCFS)
    if (user_count > 0) {
        fcfs(user_procs, user_count, &total_time, &total_waiting, &total_turnaround, &total_response);
    }

    // Calculate averages and throughput
    float avg_waiting_time = total_waiting / n;
    float avg_turnaround_time = total_turnaround / n;
    float avg_response_time = total_response / n;
    float throughput = (float)n / total_time;

    // Display results
    printf("\nSystem Processes (Round Robin):\n");
    printf("PID\tResponse\tWaiting\tTurnaround\n");
    for (int i = 0; i < sys_count; i++) {
        printf("%d\t%d\t\t%d\t%d\n",
               system_procs[i].pid,
               system_procs[i].response_time,
               system_procs[i].waiting,
               system_procs[i].turnaround);
    }

    printf("\nUser Processes (FCFS):\n");
    printf("PID\tResponse\tWaiting\tTurnaround\n");
    for (int i = 0; i < user_count; i++) {
        printf("%d\t%d\t\t%d\t%d\n",
               user_procs[i].pid,
               user_procs[i].response_time,
               user_procs[i].waiting,
               user_procs[i].turnaround);
    }

    // Display averages and throughput
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
    printf("Throughput: %.2f processes/unit time\n", throughput);

    return 0;
}
