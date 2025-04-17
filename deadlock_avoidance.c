#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 // Maximum number of processes
#define MAX_R 10 // Maximum number of resources

void calculateNeed(int P, int R, int max[MAX_P][MAX_R], int allocation[MAX_P][MAX_R], int need[MAX_P][MAX_R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int P, int R, int available[], int max[MAX_P][MAX_R], int allocation[MAX_P][MAX_R]) {
    int work[MAX_R];
    bool finish[MAX_P] = {0};
    int safeSequence[MAX_P];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canProceed = true;
                for (int j = 0; j < R; j++) {
                    if (max[p][j] - allocation[p][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[p][j];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            // Print which processes are causing the unsafe state
            for (int i = 0; i < P; i++) {
                if (!finish[i]) {
                    printf("Process P%d cannot proceed.\n", i);
                }
            }
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int P, R;

    // Input number of processes and resources
    printf("Enter number of processes (max %d): ", MAX_P);
    scanf("%d", &P);
    printf("Enter number of resources (max %d): ", MAX_R);
    scanf("%d", &R);

    // Ensure P and R do not exceed maximum limits
    if (P > MAX_P || R > MAX_R) {
        printf("Error: Number of processes or resources exceeds maximum limit.\n");
        return 1;
    }

    int available[MAX_R];
    int max[MAX_P][MAX_R];
    int allocation[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];

    // Input available resources
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    // Input maximum demand matrix
    printf("Enter maximum demand matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate need matrix
    calculateNeed(P, R, max, allocation, need);

    // Check if the system is in a safe state
    isSafe(P, R, available, max, allocation);

    return 0;
}
