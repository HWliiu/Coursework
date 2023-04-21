#include <malloc.h>
#include <stdio.h>
#include <string.h>
typedef struct table
{
  int address; /*存储分区起始地址*/
  int length;  /*存储分区长度*/
  struct table *next;
} node;
int success = 0; /*分配成功与否的标志*/
int count = 1;
node *work;

node *init() /*创建空闲分区表*/
{
  node *head;
  node *p1, *p2;
  printf("address|length\n");
  head = (node *)malloc(sizeof(node));
  p1 = (node *)malloc(sizeof(node));
  p2 = head;
  scanf("%d %d", &p1->address, &p1->length);
  fflush(stdin);
  while (p1->length != 0) // 结束标志
  {
    p2->next = p1;
    p2 = p1;
    p1 = (node *)malloc(sizeof(node));
    scanf("%d %d", &p1->address, &p1->length);
    fflush(stdin);
  }
  p2->next = NULL;
  return (head);
}

node *firstFit(node *head, node *work)
{
  node *q, *p;
  q = head->next;
  while (q) /*完成分配过程*/
  {
    p = q;
    if (q->length >= work->length)
    {
      work->address = q->address;
      success = 1;
      if (q->length > work->length) /*剩余部分仍修改为空闲分区*/
      {
        q->address = q->address + work->length;
        q->length = q->length - work->length;
      }
      else /*无剩余部分则删除该节点*/
        if (q == head)
          head = q->next;
        else
          p->next = q->next;
      break;
    }
    else
      q = q->next;
  }
  return (head);
}

node *found(node *head, int x)
{
  node *p, *q;
  q = p = head->next;
  while (p && p->length < x) /*寻找能容纳x的位置*/
    p = p->next;
  if (!p)
    return (p);
  else
  {
    q = p;
    p = p->next;
  }         /*q记录能容纳x的位置的空闲分区*/
  while (p) /*寻找能容纳x的最小分区*/
  {
    if (q->length > p->length && p->length >= x)
      q = p;
    p = p->next;
  }
  return (q);
}

node *bestFit(node *head, node *work)
{
  node *q, *p, *pre;
  pre = head;
  p = found(head, work->length);
  if (p) /*完成分配过程*/
  {
    q = p;
    success = 1;
    work->address = q->address;
    if (q->length > work->length) /*剩余部分仍修改为空闲分区*/
    {
      q->address = q->address + work->length;
      q->length = q->length - work->length;
    }
    else /*无剩余部分则删除该节点*/
    {
      while (pre->next != q)
        pre = pre->next; /*删除q节点*/
      pre->next = q->next;
    }
  }
  return (head);
}

void distribution(node *q)
{
  int a, x;
  node *work;
  printf("请选择分配算法：(0-firstFit 1-bestFit)\n"); /*输入要分配的工作情况*/
  fflush(stdin);
  scanf("%d", &x);

  while (1)
  {
    if (x != 0 && x != 1)
    {
      printf("\n输入有误！请重新输入:");
      fflush(stdin);
      scanf("%d", &x);
    }
    else
      break;
  }

  printf("\nIt's length is:"); /*输入要分配的工作情况*/
  scanf("%d", &a);
  work = (node *)malloc(sizeof(node));
  work->length = a;
  work->next = NULL;

  if (x == 0)
    q = firstFit(q, work);
  else if (x == 1)
    q = bestFit(q, work);
  if (success)
  {
    printf("distributing is successful!\n");
    printf("\nfree table is :\n");
    print(q);
  }
  else
  {
    printf("distributing is not successful!\n");
    return;
  }
  while (work->length != 0)
  {
    free(work);
    success = 0;
    count = 1;
    printf("\nIt's length is:"); /*输入要分配的工作情况*/
    scanf("%d", &a);
    work = (node *)malloc(sizeof(node));
    work->length = a;
    work->next = NULL;
    q = firstFit(q, work);
    if (success)
    {
      printf("distributing is successful!\n");
      printf("\nfree table is :\n");
      print(q);
    }
    else
    {
      printf("\ndistributing is not successful!\n");
      return;
    }
  }
}

void print(node *head) /*输出链表*/
{
  node *p;
  p = head->next;
  if (head->next != NULL)
    while (p != NULL)
    {
      printf("%d  startAddr:%d   size:%d\n", count, p->address, p->length);
      p = p->next;
      count++;
    }
}
/*空闲分区表：起始地址 大小
100 32
150 10
200 5
220 218
530 96
600 0

作业序列：
96 20 200*/
void main()
{
  node *q;
  printf("the free table is:\n");
  q = init(); /*输入未分配情况表*/
  distribution(q);
  return 0;
}
