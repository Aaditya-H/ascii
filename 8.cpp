
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define DISK_SIZE 200

int main()
{
    int a[MAX], n, head, i, j;
    int choice, total, pos, min, index;
    int temp, cur;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter disk requests:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\n1. SSTF");
    printf("\n2. SCAN");
    printf("\n3. C-LOOK");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    total = 0;
    cur = head;

    if(choice == 1)
    {
        int visited[MAX] = {0};

        printf("\nSSTF Order: ");

        for(i = 0; i < n; i++)
        {
            min = 9999;
            index = -1;

            for(j = 0; j < n; j++)
            {
                if(!visited[j] &&
                   abs(a[j] - cur) < min)
                {
                    min = abs(a[j] - cur);
                    index = j;
                }
            }

            visited[index] = 1;

            total += abs(a[index] - cur);
            cur = a[index];

            printf("%d ", cur);
        }
    }

    else if(choice == 2 || choice == 3)
    {
        // Sort requests in ascending order

        for(i = 0; i < n - 1; i++)
        {
            for(j = 0; j < n - i - 1; j++)
            {
                if(a[j] > a[j + 1])
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }

        // Find first request greater than or equal to head

        pos = 0;

        while(pos < n && a[pos] < head)
            pos++;

        printf("\nService Order: ");

        if(choice == 2)
        {
            // SCAN - Move towards higher cylinders

            for(i = pos; i < n; i++)
            {
                total += abs(a[i] - cur);
                cur = a[i];

                printf("%d ", cur);
            }

            // Move to the last cylinder

            total += abs((DISK_SIZE - 1) - cur);
            cur = DISK_SIZE - 1;

            // Reverse direction

            for(i = pos - 1; i >= 0; i--)
            {
                total += abs(a[i] - cur);
                cur = a[i];

                printf("%d ", cur);
            }
        }

        else
        {
            // C-LOOK - Move towards higher cylinders

            for(i = pos; i < n; i++)
            {
                total += abs(a[i] - cur);
                cur = a[i];

                printf("%d ", cur);
            }

            // Jump to the lowest pending request

            if(pos > 0)
            {
                total += abs(cur - a[0]);
                cur = a[0];

                printf("%d ", cur);

                for(i = 1; i < pos; i++)
                {
                    total += abs(a[i] - cur);
                    cur = a[i];

                    printf("%d ", cur);
                }
            }
        }
    }

    else
    {
        printf("Invalid Choice!\n");
        return 1;
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);

    return 0;
}


gcc disk.c -o disk
./disk