
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int a[], int n)
{
    int i, j, temp;

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
}

int main()
{
    int a[50], n, i;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }

    if(pid == 0)
    {
        printf("\nChild Process Sorting:\n");

        sort(a, n);

        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\nChild Process ID: %d\n", getpid());
    }
    else
    {
        printf("\nParent Process Sorting:\n");

        sort(a, n);

        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\nParent Process ID: %d\n", getpid());

        wait(NULL);

        printf("\nChild Process Completed.\n");
    }

    return 0;
}


gcc process.c -o process
./process


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int choice;
    pid_t pid;

    printf("1. Zombie Process\n");
    printf("2. Orphan Process\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }

    if(choice == 1)
    {
        if(pid == 0)
        {
            printf("Child Process Exiting.\n");
            exit(0);
        }
        else
        {
            printf("Parent Sleeping. Child becomes Zombie.\n");
            sleep(10);

            system("ps -o pid,ppid,state,cmd");

            wait(NULL);
            printf("Zombie Process Removed.\n");
        }
    }
    else if(choice == 2)
    {
        if(pid == 0)
        {
            sleep(5);
            printf("Child PID: %d\n", getpid());
            printf("New Parent PID: %d\n", getppid());
        }
        else
        {
            printf("Parent Exiting.\n");
            exit(0);
        }
    }

    return 0;
}


gcc states.c -o states
./states