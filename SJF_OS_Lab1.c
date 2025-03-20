#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rt;         // Response Time
    int completed;  // Completion flag
} Process;

void inputProcesses(Process p[], int n);
void sortByArrival(Process p[], int n);
void computeSJF(Process p[], int n);
void displayProcesses(Process p[], int n);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    inputProcesses(p, n);
    sortByArrival(p, n);
    computeSJF(p, n);
    displayProcesses(p, n);

    return 0;
}

// Function to take input for processes
void inputProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }
}

// Function to sort processes by Arrival Time (AT)
void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to compute Completion Time, TAT, WT, and RT using SJF
void computeSJF(Process p[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int shortestIndex = -1;
        int minBT = 1e9; // Setting to a large value

        // Find the shortest job available at currentTime
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    shortestIndex = i;
                }
            }
        }

        // If no process is ready, move time forward
        if (shortestIndex == -1) {
            currentTime++;
        } else {
            Process *proc = &p[shortestIndex];

            proc->ct = currentTime + proc->bt;
            proc->tat = proc->ct - proc->at;
            proc->wt = proc->tat - proc->bt;
            proc->rt = proc->wt; // Since non-preemptive, RT = WT

            proc->completed = 1;
            completed++;
            currentTime = proc->ct; // Move current time to completion time
        }
    }
}

// Function to display results
void displayProcesses(Process p[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
}
