#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define M 3
#define N 5
int Resource[M];
int Max[N][M];
int Allocation[N][M];
int Need[N][M];
int Available[M];
int Work[M];
bool Finish[N];
int List[N]; // 存放安全序列的下标序列

void init()
{ // 创建初始状态：先输入Resource、Max和Allocation，再计算出Need、Available。
	int i, j;
	printf("请输入M种资源的总数量(Resource):\n");
	for (i = 0; i < M; i++)
		scanf("%d", &Resource[i]);

	printf("请输入N个进程分别对M种资源的最大需求量(Max):\n");
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			scanf("%d", &Max[i][j]);

	printf("请输入N个进程获得M种资源的数量(Allocation):\n");
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			scanf("%d", &Allocation[i][j]);

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];

	for (j = 0; j < M; j++)
	{
		Available[j] = Resource[j];
		for (i = 0; i < N; i++)
			Available[j] = Available[j] - Allocation[i][j];
	}
}
bool isSafe()
{
	int i, j, k = 0, index = -1;
	for (i = 0; i < N; i++) // 初始化Finish数组
		Finish[i] = false;
	for (j = 0; j < M; j++) // 初始化Work数组
		Work[j] = Available[j];
	for (i = 0; i < N; i++)
	{
		index = whichFinish(); // 调用isfinish函数并保存返回值
		if (index == -1)
			break;
		else
		{
			for (j = 0; j < M; j++)
				Work[j] = Work[j] + Allocation[index][j]; // 修改work数组
			List[k] = index;							  // 修改List数组
			k++;
		}
	}

	for (i = 0; i < N; i++) // 判断系统是否处在安全状态
		if (!Finish[i])
			return false;

	return true;
}
void reqResource(int i, int request[M])
{
	bool flag;
	int j;

	flag = true;
	for (j = 0; j < M; j++) // Step1: 判断条件Request[j]≤Need[i][j]
	{
		if (request[j] > Need[i][j])
		{
			flag = false;
			break;
		}
	}

	if (!flag)
	{
		printf("\n第%d个进程需要的资源数超过它的Max.\n", i);
		return;
	}

	flag = true;
	for (j = 0; j < M; j++) // Step2: 判断条件Request[j]≤Available[j]
	{
		if (request[j] > Available[j]) // request与available进行比较
		{
			flag = false;
			break;
		}
	}
	if (flag == false)
	{
		printf("\n资源不足，第%d个进程堵塞。\n", i);
		return;
	}

	for (j = 0; j < M; j++) // Step3: 预先分配
	{
		Need[i][j] = Need[i][j] - request[j]; // 修改need、available和allocation数组
		Allocation[i][j] = Allocation[i][j] + request[j];
		Available[j] = Available[j] - request[j];
	}

	flag = isSafe(); // Step4:检测是否为安全状态
	if (flag == false)
	{
		printf("\n不存在安全序列，不是安全状态。\n");
		for (j = 0; j < M; j++) // 撤销预分配
		{
			Need[i][j] = Need[i][j] + request[j];
			Allocation[i][j] = Allocation[i][j] - request[j];
			Available[j] = Available[j] + request[j]; // 修改need、available和allocation数组
		}
	}
	else
	{
		printf("\n是安全状态，分配成功！\n");
		printList();
	}
}
void printList()
{
	int j, k, w;
	printf("\n安全序列表:\n");
	printf("   Process   |   Work     |    Need    | Allocation | Work+Alloc |   Finish\n");
	for (j = 0; j < M; j++)
		Work[j] = Available[j];
	for (k = 0; k < N; k++)
	{
		printf("   P%-9d|", List[k]);
		for (j = 0; j < M; j++)
			printf("  %-2d", Work[j]);
		printf("|");
		w = List[k]; // 记录安全序列下标
		for (j = 0; j < M; j++)
			printf("  %-2d", Need[w][j]);
		printf("|");
		for (j = 0; j < M; j++)
			printf("  %-2d", Allocation[w][j]);
		printf("|");
		for (j = 0; j < M; j++)
		{
			Work[j] = Work[j] + Allocation[w][j];
			printf("  %-2d", Work[j]);
		}
		printf("|    true\n");
	}
	printf("\n");
}
int whichFinish()
{ // 返回同时满足两个条件{①Finish[i]=false; ②Need[i][j]≤Work[j]}的进程下标i(修改Finish[i]=true)，否则返回-1。
	int i, j;
	bool flag;
	for (i = 0; i < N; i++)
	{
		if (Finish[i] == false)
		{
			flag = true;
			for (j = 0; j < M; j++)
				if (Need[i][j] > Work[j])
				{
					flag = false;
					break;
				}

			if (flag)
			{
				Finish[i] = true;
				return i;
			}
		}
	}
	return -1;
}
void printState()
{
	int i, j;
	printf("\n状态表：\n");
	printf("  Process  |     Max      |  Allocation  |     Need     |     Available  \n");
	for (i = 0; i < N; i++)
	{
		printf("   P%-7d|  ", i);
		for (j = 0; j < M; j++)
		{
			printf("%-4d", Max[i][j]);
		}
		printf("|  ");
		for (j = 0; j < M; j++)
		{
			printf("%-4d", Allocation[i][j]);
		}
		printf("|  ");
		for (j = 0; j < M; j++)
		{
			printf("%-4d", Need[i][j]);
		}
		printf("|  ");
		if (i == 0)
		{
			for (j = 0; j < M; j++)
			{
				printf("%4d", Available[j]);
			}
			printf("\n");
		}
		else
			printf("      \t \n");
	}
	printf("\n");
}
// 输入数据:
//  Resource 10 5 7
//  Max 7 5 3 3 2 2 9 0 2 2 2 2 4 3 3
//  Allocation 0 1 0 2 0 0 3 0 2 2 1 1 0 0 2
int main()
{
	int reqId = -1, j, req[M];
	init();
	printState();
	if (!isSafe())
		printf("Initial state is unsafe!\n");
	else
	{
		printf("Initial state is safe!\n");
		printList();
		printf("Input the id of request process:");
		scanf("%d", &reqId);
		while (reqId >= 0 && reqId < N || reqId != -1)
		{
			printf("Input request resources:");
			for (j = 0; j < M; j++)
			{
				scanf("%d", &req[j]);
			}
			reqResource(reqId, req);
			printState();
			printf("Input the id of request process:");
			scanf("%d", &reqId);
		}
	}

	return 0;
}
