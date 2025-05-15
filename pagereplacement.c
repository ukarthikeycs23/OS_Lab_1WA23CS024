#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int search(int key, int frame[], int size) {
    for (int i = 0; i < size; i++)
        if (frame[i] == key)
            return i;
    return -1;
}

void FIFO(int pages[], int n, int frames) {
    int frame[MAX], front = 0, count = 0, hits = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, frames) == -1) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            count++;
        } else {
            hits++;
        }
    }
    printf("FIFO Page Faults: %d, Page Hits: %d\n", count, hits);
}

void LRU(int pages[], int n, int frames) {
    int frame[MAX], count = 0, hits = 0;
    int recent[MAX];

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int pos = search(pages[i], frame, frames);
        if (pos != -1) {
            hits++;
            recent[pos] = i;
        } else {
            int lru = 0;
            for (int j = 1; j < frames; j++)
                if (recent[j] < recent[lru])
                    lru = j;
            frame[lru] = pages[i];
            recent[lru] = i;
            count++;
        }
    }
    printf("LRU Page Faults: %d, Page Hits: %d\n", count, hits);
}

int predict(int pages[], int n, int frame[], int frames, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void Optimal(int pages[], int n, int frames) {
    int frame[MAX], count = 0, hits = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, frames) != -1) {
            hits++;
            continue;
        }

        int j;
        for (j = 0; j < frames; j++) {
            if (frame[j] == -1) {
                frame[j] = pages[i];
                break;
            }
        }

        if (j == frames) {
            int idx = predict(pages, n, frame, frames, i + 1);
            frame[idx] = pages[i];
        }
        count++;
    }
    printf("Optimal Page Faults: %d, Page Hits: %d\n", count, hits);
}

int main() {
    int n, pages[MAX], frames;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    printf("Enter the page strings:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the no of page frames:\n");
    scanf("%d", &frames);

    FIFO(pages, n, frames);
    Optimal(pages, n, frames);
    LRU(pages, n, frames);

    return 0;
}
