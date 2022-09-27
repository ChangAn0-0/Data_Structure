#include <stdio.h>
#include <math.h>

//--------------------类型声明------------------------------------
#define MAXTABLESIZE 100000
typedef int ElementType;
typedef int Index;
typedef Index Position;

 typedef enum{Legitimate,Empty,Deleted}EntryType;
 typedef enum{false,true}bool;

 typedef struct HashEntry Cell;
 struct HashEntry {
	 ElementType Data;
	 EntryType Info;
 };

 typedef struct TblNode* HashTable;
 struct TblNode {
	 int TableSize;
	 Cell* Cells;
 };

 //-----------------------------初始化函数---------------------
 //函数NextPrime，返回大于N的素数。
 int NextPrime(int N)
 {
	 int i, p = (N % 2) ? N + 2 : N + 1;

	 while (p <= MAXTABLESIZE) {
		 for (i = (int)sqrt(p); i > 2; i--)
			 if (!(p % i))break;
		 if (i == 2)break;
		 else p += 2;
	 }
	 return p;
 }

 //创建散列表并初始化
 HashTable CreateTable(int TableSize)
 {
	 HashTable H;
	 int i;
	 H = (HashTable)malloc(sizeof(struct TblNode));
	 H->TableSize = NextPrime(TableSize);
	 H->Cells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	 for (i = 0; i < H->TableSize; i++)
		 H->Cells[i].Info = Empty;

	 return H;
 }
//------------------初始化完成--------------------
//--------------------平方探测法插入函数-------------------
 bool Insert(HashTable H, ElementType key)
 {

 }

