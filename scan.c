#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, pos, trc, dir, sum = 0;
    printf("No. of tracks (size): ");
    scanf("%d", &n);

    printf("Position of head: ");
    scanf("%d", &pos);

    printf("Enter no. of tracks to traverse: ");
    scanf("%d", &trc);

    int ar[trc];
    printf("Enter track requests: ");
    for (int i = 0; i < trc; i++)
        scanf("%d", &ar[i]);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &dir);

    qsort(ar, trc, sizeof(int), compare);

    int index = 0;
    for (int i = 0; i < trc; i++) {
        if (ar[i] > pos) {
            index = i;
            break;
        }
    }

    if (dir == 1) {
        for (int i = index; i < trc; i++) {
            sum += abs(ar[i] - pos);
            pos = ar[i];
        }
        sum += abs((n - 1) - pos);
        pos = n - 1;
        for (int i = index - 1; i >= 0; i--) {
            sum += abs(ar[i] - pos);
            pos = ar[i];
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            sum += abs(ar[i] - pos);
            pos = ar[i];
        }
        sum += abs(pos - 0);
        pos = 0;
        for (int i = index; i < trc; i++) {
            sum += abs(ar[i] - pos);
            pos = ar[i];
        }
    }

    printf("Total head movement is %d\n", sum);
    return 0;
}
