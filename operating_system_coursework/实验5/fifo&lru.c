#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct kk
{
    int work;
    int weight; // 用于记录该进程的置换权重，值越大越容易被置换
    struct kk *next;
} MemBlock;
MemBlock *init(int MemSize)
{
    int i = 0;
    MemBlock *head, *tail, *q;
    head = (MemBlock *)malloc(sizeof(MemBlock));
    tail = head;
    while (i < MemSize)
    {
        q = (MemBlock *)malloc(sizeof(MemBlock));
        q->work = -1;
        q->weight = MemSize - 1;
        tail->next = q;
        tail = q;
        i++;
    }
    tail->next = NULL;
    return head;
}
void print(MemBlock *head, int MemSize, bool noChange)
{
    MemBlock *q;
    q = head->next;
    while (q)
    {
        if (q->work == -1)
        {
            printf("null\t");
        }
        else
        {
            printf("%d\t", q->work);
        }
        q = q->next;
    }
    if (noChange)
    {
        printf(" ");
    }
    else
    {
        printf("是");
    }
    // printf("\n");
}
void pageChange(MemBlock *head, int MemSize, bool lru)
{
    int x;
    int i = 0;
    int count = 0;
    bool noChange; // 记录是否发生置换
    int changeCount = 0;
    MemBlock *q, *p;
    printf("请输入作业序列，以-1结束！\n");
    scanf("%d", &x);
    for (i = 0; i < MemSize; i++)
    {
        printf("块%d\t", i + 1);
    }
    printf("缺页");
    printf("\n");
    while (x != -1)
    {
        noChange = false;
        q = p = head->next;
        while (p)
        {
            if (p->work == x)
            {
                noChange = true;
                if (lru)
                {
                    q = head->next;
                    while (q)
                    {
                        if (q->weight < p->weight)
                            q->weight++;
                        q = q->next;
                    }
                    p->weight = 0;
                }
                break;
            }
            else
            {
                p = p->next;
            }
        }
        if (!noChange)
        {
            while (q)
            {
                if (q->work == -1)
                {
                    q->work = x;
                    q->weight = 0;
                    break;
                }
                else if (q->weight == MemSize - 1)
                {
                    q->work = x;
                    q->weight = 0;
                    p = q->next;
                    while (p)
                    {
                        p->weight++;
                        p = p->next;
                    }
                    break;
                }
                else if (q->work != x)
                {
                    q->weight++;
                    q = q->next;
                }
            }
            changeCount++;
        }
        count++;
        print(head, MemSize, noChange);
        printf("\n");
        scanf("%d", &x);
    }
    printf("缺页次数：%d\t", changeCount);
    printf("缺页率：%d/%d", changeCount, count);
}

// eg: 1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6 -1
int main()
{
    MemBlock *head;
    int MemSize;
    int x;
    bool lru = false; // 记录是否为lru算法
    printf("请输入内存块大小：");
    scanf("%d", &MemSize);
    printf("请选择算法.(输入0为FIFO,输入其他数字为LRU)\n");
    scanf("%d", &x);
    if (x != 0)
    {
        lru = true;
    }
    head = init(MemSize);
    pageChange(head, MemSize, lru);
    return 0;
}
