#include <stdio.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Remaining Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    int st; // Start Time
    int completed; // Completion flag
} Process;

void inputProcesses(Process p[], int n);
void sortByArrival(Process p[], int n);
void computeSRTF(Process p[], int n);
void displayProcesses(Process p[], int n);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    inputProcesses(p, n);
    sortByArrival(p, n);
    computeSRTF(p, n);
    displayProcesses(p, n);

    return 0;
}

// Function to take input for processes
void inputProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Initialize remaining time with burst time
        p[i].completed = 0;
        p[i].st = -1;
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

// Function to compute scheduling using SRTF
void computeSRTF(Process p[], int n) {
    int currentTime = 0, completed = 0;
    int shortestIndex = -1;

    while (completed < n) {
        int minRT = INT_MAX;
        shortestIndex = -1;

        // Find process with shortest remaining time at current time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                shortestIndex = i;
            }
        }

        // If no process is ready, move time forward
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Update start time if process is executed for the first time
        if (p[shortestIndex].st == -1) {
            p[shortestIndex].st = currentTime;
        }

        // Process execution
        p[shortestIndex].rt--;
        currentTime++;

        // If process is completed
        if (p[shortestIndex].rt == 0) {
            p[shortestIndex].ct = currentTime;
            p[shortestIndex].tat = p[shortestIndex].ct - p[shortestIndex].at;
            p[shortestIndex].wt = p[shortestIndex].tat - p[shortestIndex].bt;
            p[shortestIndex].completed = 1;
            completed++;
        }
    }
}

// Function to display results
void displayProcesses(Process p[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].st - p[i].at);
    }
}
