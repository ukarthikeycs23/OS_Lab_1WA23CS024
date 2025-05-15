#include <stdio.h>

#define MAX 100

void worstFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    int originalBlock[MAX];
    
    // Copy original block sizes for output
    for (int i = 0; i < m; i++)
        originalBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                if (wstIdx == -1 || blockSize[j] > blockSize[wstIdx])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= fileSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, fileSize[i], allocation[i] + 1, originalBlock[allocation[i]]);
        else
            printf("%d\t\t%d\t\tNot Allocated\t-\n", i + 1, fileSize[i]);
    }
}

void bestFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    int originalBlock[MAX];

    for (int i = 0; i < m; i++)
        originalBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= fileSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, fileSize[i], allocation[i] + 1, originalBlock[allocation[i]]);
        else
            printf("%d\t\t%d\t\tNot Allocated\t-\n", i + 1, fileSize[i]);
    }
}

void firstFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    int originalBlock[MAX];

    for (int i = 0; i < m; i++)
        originalBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                allocation[i] = j;
                blockSize[j] -= fileSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, fileSize[i], allocation[i] + 1, originalBlock[allocation[i]]);
        else
            printf("%d\t\t%d\t\tNot Allocated\t-\n", i + 1, fileSize[i]);
    }
}

int main() {
    int m, n;
    int blockSize[MAX], fileSize[MAX];
    int blockSizeCopy[MAX];

    printf("Enter number of blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of files: ");
    scanf("%d", &n);
    printf("Enter size of each file:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &fileSize[i]);

    for (int i = 0; i < m; i++)
        blockSizeCopy[i] = blockSize[i];
    worstFit(blockSizeCopy, m, fileSize, n);

    for (int i = 0; i < m; i++)
        blockSizeCopy[i] = blockSize[i];
    bestFit(blockSizeCopy, m, fileSize, n);

    for (int i = 0; i < m; i++)
        blockSizeCopy[i] = blockSize[i];
    firstFit(blockSizeCopy, m, fileSize, n);

    return 0;
}
