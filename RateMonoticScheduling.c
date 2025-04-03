#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int pid;
    int burst_time;
    int period;
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

float calculate_cpu_utilization(Task tasks[], int n) {
    float total_utilization = 0.0;
    for (int i = 0; i < n; i++) {
        total_utilization += (float)tasks[i].burst_time / tasks[i].period;
    }
    return total_utilization;
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

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].period);
        periods[i] = tasks[i].period;
    }

    int lcm = find_lcm(periods, n);
    printf("LCM=%d\n", lcm);

    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", tasks[i].pid, tasks[i].burst_time, tasks[i].period);
    }

    float cpu_utilization = calculate_cpu_utilization(tasks, n);
    float utilization_bound = (float)n * (pow(2.0, (1.0 / n)) - 1);

    printf("%f <= %f =>%s\n", cpu_utilization, utilization_bound, (cpu_utilization <= utilization_bound) ? "true" : "false");

    return 0;
}
