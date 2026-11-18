
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd1[2], fd2[2];
    pid_t pid;

    char filename[100];
    char buffer[500];

    pipe(fd1);
    pipe(fd2);

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }

    // Parent Process
    if(pid > 0)
    {
        close(fd1[0]);
        close(fd2[1]);

        printf("Enter file pathname: ");
        scanf("%99s", filename);

        write(fd1[1], filename, strlen(filename) + 1);

        close(fd1[1]);

        printf("\nFile Contents Received:\n");

        int n;

        while((n = read(fd2[0], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(fd2[0]);

        wait(NULL);
    }

    // Child Process
    else
    {
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], filename, sizeof(filename));

        close(fd1[0]);

        int file = open(filename, O_RDONLY);

        if(file < 0)
        {
            char msg[] = "Error: File not found!\n";
            write(fd2[1], msg, strlen(msg));
        }
        else
        {
            int n;

            while((n = read(file, buffer, sizeof(buffer))) > 0)
            {
                write(fd2[1], buffer, n);
            }

            close(file);
        }

        close(fd2[1]);
        exit(0);
    }

    return 0;
}


gcc pipe.c -o pipe
echo "Welcome to Operating System Lab." > sample.txt [sample text file]
./pipe
