
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define N 10
typedef struct kk
{
    char pname[N];
    int runtime;
    int arrivetime;
    char state;
    int cyclingtime; // 周转时间
    struct kk *next;
} pcb;

pcb *init()
{ // 创建进程队列
    pcb *head;
    head = (pcb *)malloc(sizeof(pcb));
    pcb *q, *tail;
    char x[N];
    int y, z;
    tail = head;
    q = (pcb *)malloc(sizeof(pcb));
    printf("create new progress table(endby pname echo '0'):\n");
    printf("pname|arrivetime|runtime\n");
    while (scanf("%s", x) && x[0] != '0')
    { // 当进程名为 0 时结束
        scanf("%d %d", &y, &z);
        fflush(stdin);
        strcpy(q->pname, x);
        q->arrivetime = y;
        q->runtime = z;
        q->state = 'r';
        q->cyclingtime = 0;
        tail->next = q;
        tail = q;
        q = (pcb *)malloc(sizeof(pcb));
    }
    tail->next = NULL;
    return head;
}
bool notfinish(pcb *head)
{ // 判断队列中是否有未完成的进程
    pcb *q = head->next;
    while (q)
    {
        if (q->state == 'r')
            return true;
        q = q->next;
    }
    return false;
}
void fcfs(pcb *head)
{
    pcb *minpcb;            // 用于指向特定条件的节点
    pcb *temp;              // 用于指向初始为minpcb分配的内存块，以便删除该内存块
    int time = 0;           // 用于记录当前的运行时间
    int count = 1;          // 计数器
    float totalcyltime = 0; // 记录总周转时间
    pcb *q = head->next;
    printf("FCFS算法:\n\n");
    while (notfinish(head))
    {
        minpcb = (pcb *)malloc(sizeof(pcb));
        temp = minpcb;
        minpcb->arrivetime = 999;
        while (q)
        { // 找到最小到达时间且未完成的节点
            if ((minpcb->arrivetime > q->arrivetime) && q->state == 'r')
            {
                minpcb = q;
                free(temp);
            }
            q = q->next;
        }

        minpcb->state = 'c';
        time = time + minpcb->runtime;
        minpcb->cyclingtime = time - minpcb->arrivetime;
        totalcyltime = totalcyltime + minpcb->cyclingtime;
        printf("第%d个完成的进程为%s\t周转时间为%d\n", count, minpcb->pname, minpcb->cyclingtime);
        count++;
        q = head->next;
    }
    printf("\n  FCFS算法的平均周转时间为%.2lf\n", totalcyltime / (count - 1));
    printf("\n");
}
void spf(pcb *head)
{
    pcb *minpcb;
    pcb *temp;
    int time = 0;
    int count = 1;
    float totalcyltime = 0;
    pcb *q = head->next;
    printf("SPF算法:\n\n");
    while (notfinish(head))
    {
        minpcb = (pcb *)malloc(sizeof(pcb));
        temp = minpcb;
        minpcb->runtime = 999;
        while (q)
        {
            if ((minpcb->runtime > q->runtime) && q->state == 'r')
            {
                minpcb = q;
                free(temp);
            }
            q = q->next;
        }
        q = head->next;
        if (minpcb->arrivetime <= time)
        {
            minpcb->state = 'c';
            time = time + minpcb->runtime;
            minpcb->cyclingtime = time - minpcb->arrivetime;
            totalcyltime = totalcyltime + minpcb->cyclingtime;
            printf("第%d个完成的进程为%s\t周转时间为%d\n", count, minpcb->pname, minpcb->cyclingtime);
        }
        else
        {
            minpcb = (pcb *)malloc(sizeof(pcb));
            temp = minpcb;
            minpcb->arrivetime = 999;
            while (q)
            {
                if ((minpcb->arrivetime > q->arrivetime) && q->state == 'r')
                {
                    minpcb = q;
                    free(temp);
                }
                q = q->next;
            }
            minpcb->state = 'c';
            time = time + minpcb->runtime;
            minpcb->cyclingtime = time - minpcb->arrivetime;
            totalcyltime = totalcyltime + minpcb->cyclingtime;
            printf("第%d个完成的进程为%s\t周转时间为%d\n", count, minpcb->pname, minpcb->cyclingtime);
        }
        count++;
        q = head->next;
    }
    printf("\n   SPF算法的平均周转时间为%.2lf\n", totalcyltime / (count - 1));
    printf("\n");
}
void rr(pcb *head, int timeslice)
{
    pcb *minpcb;
    pcb *queuehead, *queuetail, *p;
    queuehead = (pcb *)malloc(sizeof(pcb)); // 用于创建运行队列
    queuetail = queuehead;
    pcb *temp;
    int time = 0;
    int count = 1;
    float totalcyltime = 0;
    pcb *q = head->next;
    printf("RR算法:\n\n");
    while (notfinish(head))
    { // 创建一个时间轮转队列//此处错误，时间轮转队应动态创建，暂无时间修改
        minpcb = (pcb *)malloc(sizeof(pcb));
        temp = minpcb;
        minpcb->arrivetime = 999;
        while (q)
        {
            if ((minpcb->arrivetime > q->arrivetime) && q->state == 'r')
            {
                minpcb = q;
                free(temp);
            }
            q = q->next;
        }
        p = (pcb *)malloc(sizeof(pcb));
        *p = *minpcb;
        minpcb->state = 'c';
        queuetail->next = p;
        queuetail = p;
        q = head->next;
    }
    queuetail->next = NULL;
    pcb *pre; // 删除节点时会用到
    while (queuehead->next)
    {
        p = queuehead->next;
        pre = queuehead;
        while (p)
        {
            if (p->runtime > timeslice)
            {
                p->runtime = p->runtime - timeslice;
                time = time + timeslice; // printf("time1:%d\n",time);//测试代码
                p = p->next;
                pre = pre->next;
            }
            else
            { // 运行时间小于时间片时说明该进程已运行完
                time = time + p->runtime;
                // printf("time2:%d\n",time);//测试代码
                p->cyclingtime = time - p->arrivetime;
                totalcyltime = totalcyltime + p->cyclingtime;
                printf("第%d个进程为%s\t周转时间为%d\n", count, p->pname, p->cyclingtime);
                count++;
                pre->next = p->next;
                free(p);
                p = pre->next;
            }
        }
    }
    printf("\n   RR算法的平均周转时间为%.2lf\n", totalcyltime / (count - 1));
    printf("\n");
}
void initstate(pcb *head)
{
    pcb *q;
    q = head->next;
    while (q)
    {
        q->state = 'r';
        q = q->next;
    }
}
void print(pcb *head)
{
    pcb *q;
    q = head->next;
    while (q)
    {
        printf("进程名:%-10s到达时间:%-5d运行时间:%-5d\n", q->pname, q->arrivetime, q->runtime);
        q = q->next;
    }
}
/*a 0 4
b 1 3
c 2 5
d 3 2
e 4 4
0*/
int main()
{
    int timeslice;
    pcb *head;
    head = init();
    fcfs(head);
    initstate(head); // 重置列表的状态
    spf(head);
    initstate(head);
    printf("\n请输入时间片大小：");
    scanf("%d", &timeslice);
    fflush(stdin);
    rr(head, timeslice);
    return 0;
}
