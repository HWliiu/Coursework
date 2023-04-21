#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define N 99

typedef struct kk
{
    int data;
    bool finish;
    struct kk *next;
} work;

work *init()
{
    int x;
    work *head;
    head = (work *)malloc(sizeof(work));
    work *q, *tail;
    tail = head;
    q = (work *)malloc(sizeof(work));
    printf("请输入请求队列，以-1结束:\n");
    while (scanf("%d", &x) && x != -1)
    {
        q->data = x;
        q->finish = false;
        tail->next = q;
        tail = q;
        q = (work *)malloc(sizeof(work));
    }
    tail->next = NULL;
    return head;
}
void initstate(work *head)
{
    work *q;
    q = head->next;
    while (q)
    {
        q->finish = false;
        q = q->next;
    }
}
bool notfinish(work *head)
{ // 判断队列中是否有未完成的进程
    work *q = head->next;
    while (q)
    {
        if (!q->finish)
            return true;
        q = q->next;
    }
    return false;
}
void sstf(work *head, int position)
{
    int movelength = 0;
    work *q = head->next;
    work *latestwork;
    int mindistance;
    printf("\nSSTF算法移动顺序：\n");
    while (notfinish(head))
    {
        mindistance = 999;
        while (q)
        {
            if (mindistance > fabs(q->data - position) && !q->finish)
            {
                latestwork = q;
                mindistance = fabs(q->data - position);
            }
            q = q->next;
        }
        printf("%d\t", latestwork->data);
        movelength = movelength + fabs(position - latestwork->data);
        position = latestwork->data;
        latestwork->finish = true;

        q = head->next;
    }
    printf("\n   总移动长度:%d\n\n\n", movelength);
}
void scan(work *head, int position, int derection)
{
    int movelength = 0;
    work *q = head->next;
    work *latestwork;
    int mindistance;
    int max = 0, min = 999;
    printf("\nSCANF算法移动顺序：\n");
    while (notfinish(head))
    {
        mindistance = 999;
        while (q)
        {
            if (max < q->data)
                max = q->data;
            if (min > q->data)
                min = q->data;
            if (derection == 1)
            {
                if (mindistance > q->data - position && !q->finish && q->data - position >= 0)
                {
                    latestwork = q;
                    mindistance = q->data - position;
                }
                q = q->next;
            }
            else if (derection == 0)
            {
                if (mindistance > position - q->data && !q->finish && q->data - position < 0)
                {
                    latestwork = q;
                    mindistance = position - q->data;
                }
                q = q->next;
            }
        }

        printf("%d\t", latestwork->data);
        movelength = movelength + fabs(position - latestwork->data);
        position = latestwork->data;
        if (position == max)
            derection = 0;
        if (position == min)
            derection = 1;
        latestwork->finish = true;

        q = head->next;
    }
    printf("\n   总移动长度:%d\n\n", movelength);
}
void print(work *head)
{
    work *q;
    q = head->next;
    while (q)
    {
        printf("%d\t", q->data);
        q = q->next;
    }
}
int main()
{
    work *head;
    int position;
    int derection;
    head = init();
    printf("\n请输入开始位置(0到200之间)：\n");
    scanf("%d", &position);
    fflush(stdin);
    // print(head);
    sstf(head, position);
    initstate(head);
    printf("请输入初始移动方向(1为正向，0为方向)\n");
    scanf("%d", &derection);
    scan(head, position, derection);
    initstate(head);
    printf("请输入初始移动方向(1为正向，0为方向)\n");
    scanf("%d", &derection);
    scan(head, position, derection);
}
// 86 147 91 177 94 150 102 175 130 -1
