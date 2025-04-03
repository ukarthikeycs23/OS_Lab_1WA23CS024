#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int burst_time;
    int period;
    int deadline;
    int remaining_time;
} Task;

int find_lcm(int periods[], int n) {
    int lcm = periods[0];
    for (int i = 1; i < n; i++) {
        int a = lcm, b = periods[i];
        while (a != b) {
            if (a > b)
                a -= b;
            else
                b -= a;
        }
        lcm = (lcm * periods[i]) / a;
    }
    return lcm;
}

bool is_schedulable_edf(Task tasks[], int n, int lcm) {
    for (int t = 0; t <= lcm; t++) {
        int total_workload = 0;
        for (int i = 0; i < n; i++) {
            int arrival_time = 0;
            int num_jobs = (t / tasks[i].period);

            total_workload += num_jobs * tasks[i].burst_time;
        }
        if (total_workload > t) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Task tasks[n];
    int periods[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].burst_time);
        tasks[i].pid = i + 1;
    }

    printf("Enter the time periods (deadlines):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].period);
        tasks[i].deadline = tasks[i].period; // For EDF, deadline = period for simplicity
        periods[i] = tasks[i].period;
        tasks[i].remaining_time = tasks[i].burst_time;
    }

    int lcm = find_lcm(periods, n);
    printf("LCM=%d\n", lcm);

    printf("Earliest Deadline First Scheduling:\n");
    printf("PID\tBurst\tDeadline\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", tasks[i].pid, tasks[i].burst_time, tasks[i].deadline);
    }

    bool schedulable = is_schedulable_edf(tasks, n, lcm);
    printf("System is schedulable: %s\n", schedulable ? "true" : "false");

    return 0;
}
