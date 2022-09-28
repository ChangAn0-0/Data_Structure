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
 //--------------------hash函数------------------
 int Hash(const char* key, int tablesize)
 {
	 unsigned int h = 0;
	 while (*key != '\0') {
		 h = (h << 5) + *key++;
	 }

	 return h % tablesize;
 }


 //-----------------平方探测法查找函数---------------------
 Position Find(HashTable H, ElementType key)
 {
	 Position CurrentPos, NewPos;
	 int CNum = 0;

	 NewPos = CurrentPos = Hash(key, H->TableSize);
	 while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != key) {
		 if (++CNum % 2) {
			 NewPos = CurrentPos + (CNum + 1) * (CNum + 1) / 4;
			 if (NewPos >= H->TableSize)
				 NewPos = NewPos % H->TableSize;
		 }
		 else {
			 NewPos = CurrentPos - CNum * CNum / 4;
			 while (NewPos < 0)
				 NewPos += H->TableSize;
		 }
	 }

	 return NewPos;
 }
 

 //--------------------平方探测法插入函数-------------------
 bool Insert(HashTable H, ElementType key)
 {
	 Position pos = Find(H, key);
	 if (H->Cells[pos].Info != Legitimate) {
		 H->Cells[pos].Info = Legitimate;
		 H->Cells[pos].Data = key;

		 return true;
	 }
	 else {
		 printf("error:The key value already exists\n");
		 return false;
	 }
 }



