//#include<stdio.h>  
//#include<stdlib.h>  
//#include<windows.h>  
//
//#define MAX_SIZE 10001  
//struct Point {
//	int x, y;
//};
//
////判断z点与x、y点构成的直线的方位  
//double g1(struct Point x, struct Point y, struct Point z);
//
//void CalculateCH1(struct Point p[MAX_SIZE], int length, int mark[MAX_SIZE]);
//
//////暴力算法  
////int main()
////{
////	int i, n, j;
////	struct Point p[MAX_SIZE];
////	int mark[MAX_SIZE];
////
////	//double start,end;  
////	// CPU频率  
////	//LARGE_INTEGER li;
////	// 记录过程时间  
////	//LONGLONG start, end, fred;
////	// 获取CPU频率  
////	//QueryPerformanceFrequency(&li);
////	//fred = li.QuadPart;
////
////	//读取信息与写入的文件  
////	freopen("input.txt", "r", stdin);
////	freopen("outputbf1.txt", "w", stdout);
////	while (scanf("%d", &n) != EOF)
////	{
////		for (i = 0; i<n; i++)
////		{
////			scanf("%d %d", &p[i].x, &p[i].y);
////			mark[i] = 0;
////		}
////
////		//start = GetTickCount();  
////		// 获取开始时间  
////		//QueryPerformanceCounter(&li);
////		//start = li.QuadPart;
////		CalculateCH1(p, n, mark);
////		//end = GetTickCount();  
////		// 获取结束时间  
////		//QueryPerformanceCounter(&li);
////		//end = li.QuadPart;
////
////		printf("结果集:\n");
////		j = 0;
////		for (i = 0; i<n; i++)
////		{
////			if (!mark[i])
////			{
////				printf("%d,%d\t", p[i].x, p[i].y);
////				j++;
////				if (j % 5 == 0) printf("\n");
////			}
////		}
////		printf("\n");
////
////		//printf("经历时间为%dms\n\n", (int)11000 * (end - start) / fred);
////	}
////	return 0;
////}
//
//double g1(struct Point x, struct Point y, struct Point z)
//{
//	//前两个点组成的直线为ax + by = c 即 ax + by - c = 0;  
//	int a, b, c;
//	a = y.y - x.y;
//	b = x.x - y.x;
//	c = x.x * y.y - x.y * y.x;
//	return a * z.x + b * z.y - c;
//	//return ((z.y-x.y)*(z.x-y.x) - (z.y-y.y)*(z.x-x.x));  
//}
//
//void CalculateCH1(struct Point p[MAX_SIZE], int length, int mark[MAX_SIZE])
//{
//	int x, y, z, i;
//	double a, b, c;
//	//int num = length;  
//	for (x = 0; x<length; x++)
//	{
//		if (mark[x])
//			continue;
//		for (y = 0; y<length; y++)
//		{
//			if (y == x || mark[y])
//				continue;
//			for (z = 0; z<length; z++)
//			{
//				if (z == x || z == y || mark[z])
//					continue;
//				for (i = 0; i<length; i++)
//				{
//					if (i == x || i == y || i == z || mark[i])
//						continue;
//					a = g1(p[x], p[y], p[i])*g1(p[x], p[y], p[z]);
//					b = g1(p[x], p[z], p[i])*g1(p[x], p[z], p[y]);
//					c = g1(p[y], p[z], p[i])*g1(p[y], p[z], p[x]);
//					if (a >= 0 && b >= 0 && c >= 0)
//					{
//						mark[i] = 1;
//						//num--;  
//					}
//				}
//			}
//		}
//	}
//}