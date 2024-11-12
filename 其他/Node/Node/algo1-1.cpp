#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define ElemType char

typedef struct LinkList {
	char data;
	struct LinkList* next;
}LinkList;


//初始化
extern void InitList(LinkList** L) {
	*L = NULL;
}

LinkList* BuyList(ElemType& e) {
	LinkList* p = (LinkList*)malloc(sizeof(LinkList));
	if (p == NULL) {
		printf("malloc error!");
		exit(-1);
	}
	p->data = e;
	p->next = NULL;
	return p;
}

//尾插入
void Create_R(LinkList** L, ElemType& e) {
	LinkList* p = BuyList(e);
	LinkList* R = *L;
	if (R == NULL) {
		*L = p;
	}
	else {
		while (R->next) {
			R = R->next;
		}
		R->next = p;
	}
}
//在第i个位置上插入

extern bool ListInsert(LinkList** L, int i, ElemType& e) {
	if (i < 1)
		return false;
	int j = 0;
	LinkList* p = *L;
	LinkList* s = BuyList(e);
	if (i == 1) {
		s->next = p;
		*L = s;
		return true;
	}
	while ((p) && (j < i - 1)) {
		p = p->next;
		j++;
	}
	if (p && j == i - 1) {
		s->next = p->next;
		p->next = s;
	}
	return true;
}
//输出链表

extern bool DispList(LinkList* L) {
	LinkList* p = L;
	while (p) {
		printf("%c ", p->data);
		p = p->next;
	}
	if (p == NULL) {
		printf("\n");
	}
	return true;
}

//输出长度
extern void ListLength(LinkList* L) {
	LinkList* p = L;
	int i = 0;
	while (p) {
		i++;
		p = p->next;
	}
	printf("单链表h长度=%d\n", i);
}

//判断是否为空
extern bool ListEmpty(LinkList* L) {
	return L == NULL;
}

//删除指定链表
extern bool ListDelete(LinkList** L, int i, ElemType& e) {
	LinkList* p = *L;
	int j = 0;
	LinkList* q = NULL;
	if (i == 1) {
		if (p) {
			*L = p->next;
			e = p->data;
			free(p);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		while (p && j < i - 2) {
			p = p->next;
			j++;
		}
		if ((p) && (p->next) && (j == i - 2)) {
			q = p->next;
			p->next = q->next;
			e = q->data;
			free(q);
			return true;
		}
		else
			return false;
	}
}
//输出第i个元素

extern bool GetElem(LinkList* L, int i, ElemType& e) {
	LinkList* p = L;
	int j = 0;
	while ((p) && (j < i - 1)) {
		j++;
		p = p->next;
	}
	printf("单链表h的第%d个元素=%c\n", i, p->data);
	return true;
}

//输出元素a的位置

extern int LocateElem(LinkList* L, ElemType e) {
	LinkList* p = L;
	int i = 0;
	while ((p) && (p->data != e)) {
		p = p->next;
		i++;
	}
	i++;
	printf("元素%c的位置=%d\n", e, i);
	return i;
}
//销毁链表
extern void DestoryList(LinkList** L) {
	LinkList* p = *L;
	if (*L) {
		while (p) {
			LinkList* q = p->next;
			free(p);
			p = q;
		}
		*L = NULL;

	}

	else
		printf("Error!\n");

}

int main(int argc, char* argv[]) {
	ElemType e; 
	LinkList* L = NULL;
	printf("(1)初始化单链表h\n");
	InitList(&L);
	printf("(2)依次采用尾插法插入a，b，c，d，e元素\n");
	Create_R(&L, e = 'a');
	Create_R(&L, e = 'b');
	Create_R(&L, e = 'c');
	Create_R(&L, e = 'd');
	Create_R(&L, e = 'e');
	printf("(3)输出单链表h：");
	DispList(L);
	
	printf("(4)");
	ListLength(L);
	printf("(5)单链表h为");
	if (!ListEmpty(L)) {
		printf("非空\n");
	}
	printf("(6)");
	GetElem(L, 3, e);
	printf("(7)");
	LocateElem(L, 'a');
	printf("(8)在第4个元素位置上插入f元素\n");
	ListInsert(&L, 4, e = 'f');
	printf("(9)输出单链表h：");
	DispList(L);
	printf("(10)删除h的第3个元素\n");
	ListDelete(&L, 3, e);
	printf("(11)输出单链表h：");
	DispList(L);
	printf("(12释放单链表h\n");
	DestoryList(&L);
	return 0;
}

