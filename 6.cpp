
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main(int argc, char *argv[])
{
    int fd;
    char str[500], result[5000];

    if(argc != 2)
    {
        printf("Usage: ./fifo sender OR ./fifo receiver\n");
        return 1;
    }

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // First Process
    if(strcmp(argv[1], "sender") == 0)
    {
        fd = open(FIFO1, O_WRONLY);

        printf("Enter sentences (END to stop):\n");

        while(1)
        {
            fgets(str, sizeof(str), stdin);

            if(strcmp(str, "END\n") == 0)
                break;

            write(fd, str, strlen(str));
        }

        close(fd);

        // Receive result
        fd = open(FIFO2, O_RDONLY);

        int n = read(fd, result, sizeof(result) - 1);
        result[n] = '\0';

        printf("\nResult received from second process:\n");
        printf("%s", result);

        close(fd);
    }

    // Second Process
    else if(strcmp(argv[1], "receiver") == 0)
    {
        int chars = 0, words = 0, lines = 0;
        int inword = 0, n, i;
        char ch;

        fd = open(FIFO1, O_RDONLY);

        while((n = read(fd, str, sizeof(str))) > 0)
        {
            for(i = 0; i < n; i++)
            {
                ch = str[i];
                chars++;

                if(ch == '\n')
                    lines++;

                if(isspace((unsigned char)ch))
                    inword = 0;
                else if(inword == 0)
                {
                    words++;
                    inword = 1;
                }
            }
        }

        close(fd);

        FILE *fp = fopen("result.txt", "w");

        fprintf(fp, "Number of Characters: %d\n", chars);
        fprintf(fp, "Number of Words: %d\n", words);
        fprintf(fp, "Number of Lines: %d\n", lines);

        fclose(fp);

        fp = fopen("result.txt", "r");

        n = fread(result, 1, sizeof(result) - 1, fp);
        result[n] = '\0';

        fclose(fp);

        // Send result through second FIFO
        fd = open(FIFO2, O_WRONLY);

        write(fd, result, strlen(result));

        close(fd);

        printf("Result saved in result.txt\n");
    }

    else
    {
        printf("Invalid argument!\n");
    }

    return 0;
}


gcc fifo.c -o fifo
./fifo receiver (terminal 1)
./fifo sender (terminal 2)