#include <stdio.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int pr; // Priority
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    int completed; // Completion flag
} Process;

void inputProcesses(Process p[], int n);
void sortByArrival(Process p[], int n);
void computePriorityScheduling(Process p[], int n);
void displayProcesses(Process p[], int n);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    inputProcesses(p, n);
    sortByArrival(p, n);
    computePriorityScheduling(p, n);
    displayProcesses(p, n);

    return 0;
}

// Function to take input for processes
void inputProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
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

// Function to compute scheduling using Non-Preemptive Priority Scheduling
void computePriorityScheduling(Process p[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                if (p[i].pr < highestPriority) { // Lower value means higher priority
                    highestPriority = p[i].pr;
                    highestPriorityIndex = i;
                }
            }
        }

        // If no process is ready, move time forward
        if (highestPriorityIndex == -1) {
            currentTime++;
            continue;
        }

        // Process execution
        Process *proc = &p[highestPriorityIndex];
        proc->ct = currentTime + proc->bt;
        proc->tat = proc->ct - proc->at;
        proc->wt = proc->tat - proc->bt;
        proc->completed = 1;
        completed++;
        currentTime = proc->ct; // Move current time to completion time
    }
}

// Function to display results
void displayProcesses(Process p[], int n) {
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }
}
