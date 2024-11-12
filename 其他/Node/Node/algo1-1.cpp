#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define ElemType char

typedef struct LinkList {
	char data;
	struct LinkList* next;
}LinkList;


//��ʼ��
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

//β����
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
//�ڵ�i��λ���ϲ���

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
//�������

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

//�������
extern void ListLength(LinkList* L) {
	LinkList* p = L;
	int i = 0;
	while (p) {
		i++;
		p = p->next;
	}
	printf("������h����=%d\n", i);
}

//�ж��Ƿ�Ϊ��
extern bool ListEmpty(LinkList* L) {
	return L == NULL;
}

//ɾ��ָ������
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
//�����i��Ԫ��

extern bool GetElem(LinkList* L, int i, ElemType& e) {
	LinkList* p = L;
	int j = 0;
	while ((p) && (j < i - 1)) {
		j++;
		p = p->next;
	}
	printf("������h�ĵ�%d��Ԫ��=%c\n", i, p->data);
	return true;
}

//���Ԫ��a��λ��

extern int LocateElem(LinkList* L, ElemType e) {
	LinkList* p = L;
	int i = 0;
	while ((p) && (p->data != e)) {
		p = p->next;
		i++;
	}
	i++;
	printf("Ԫ��%c��λ��=%d\n", e, i);
	return i;
}
//��������
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
	printf("(1)��ʼ��������h\n");
	InitList(&L);
	printf("(2)���β���β�巨����a��b��c��d��eԪ��\n");
	Create_R(&L, e = 'a');
	Create_R(&L, e = 'b');
	Create_R(&L, e = 'c');
	Create_R(&L, e = 'd');
	Create_R(&L, e = 'e');
	printf("(3)���������h��");
	DispList(L);
	
	printf("(4)");
	ListLength(L);
	printf("(5)������hΪ");
	if (!ListEmpty(L)) {
		printf("�ǿ�\n");
	}
	printf("(6)");
	GetElem(L, 3, e);
	printf("(7)");
	LocateElem(L, 'a');
	printf("(8)�ڵ�4��Ԫ��λ���ϲ���fԪ��\n");
	ListInsert(&L, 4, e = 'f');
	printf("(9)���������h��");
	DispList(L);
	printf("(10)ɾ��h�ĵ�3��Ԫ��\n");
	ListDelete(&L, 3, e);
	printf("(11)���������h��");
	DispList(L);
	printf("(12�ͷŵ�����h\n");
	DestoryList(&L);
	return 0;
}

