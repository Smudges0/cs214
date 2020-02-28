#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;

typedef struct Node
{
    char *val;
    struct Node *next;
} Node;

int main(int argc, char *argv[])
{
    int fd;
    char buf[100]; // Doesn't handle tokens larger than 100 characters?

    // open and read a file
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error Number % d\n", errno);
        exit(1);
    }
    read(fd, buf, 100);
    buf[100] = '\0'; // buf[99]? Buffer 100 might seg fault

    close(fd);
    fd = RemoveSpaces(buf);
    printf("%s\n", buf);

    //store string tokens in a linked list
    Node *head = NULL;
    Node *temp = NULL;
    Node *ptr = NULL;
    char *token = strtok(buf, ",");

    while (token != NULL)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->val = token;
        temp->next = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
        token = strtok(NULL, ",");
    }

    ptr = head;
    while (ptr != NULL)
    {
        printf("%s\n", ptr->val);
        ptr = ptr->next;
    }
    //int c = comparator(ptr, ptr->next);

    return 0;
}

int RemoveSpaces(char *str) // Only removes spaces?
{
    if (str == NULL)
    {
        return 0;
    }
    int n = 0;
    int i = 0;
    //for (i = 0; i < strlen(str); i++)
    while (str[i] != '\0')
    {
        if (!(str[i] == ' '))
        {
            str[n] = str[i];
            n++;
        }

        i++;
    }
    str[n] = '\0';
    return 1;
}

int comparator(Node *pa, Node *pb)
{
    int i;
    for (i = 0; pa->val[i] != '\0' && pb->val[i] != '\0'; i++)
    {
        if (pa->val[i] != pb->val[i])
        {
            break;
        }
    }
    printf("%c\n", pa->val[i]);
    printf("%c\n", pb->val[i]);
    printf("%d\n", pa->val[i] - pb->val[i]);
    return pa->val[i] - pb->val[i];
}

// int insertionSort(void* toSort, int (*comparator)(void*, void*)){
//     return 0;
// }

// int quickSort(void* toSort, int (*) comparator(void*, void*)){
//     return 0;
// }