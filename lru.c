#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, n;
    int pages[50], frame[10], time[10];
    int count = 0, faults = 0, flag1, flag2, pos;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrame Status\n");

    for (int i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (!flag1) {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    count++;
                    faults++;
                    frame[j] = pages[i];
                    time[j] = count;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (!flag2) {
            pos = findLRU(time, frames);
            count++;
            faults++;
            frame[pos] = pages[i];
            time[pos] = count;
        }

        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
