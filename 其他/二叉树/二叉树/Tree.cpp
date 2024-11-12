#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define ElemType int
typedef struct TreeNode* BinTree;
typedef struct TreeNode {
	ElemType data;
	BinTree L,R;
}Node;

//先序遍历PreOrdertraverse
void Preorder(BinTree T){
	if (T) {
		printf("%d", T->data);
		Preorder(T->L);
		Preorder(T->R);
	}
}
//中序遍历
void Inorder(BinTree T) {
	if (T) {
		Inorder(T->L);
		printf("%d", T->data);
		Inorder(T->R);
	}
}
//后序遍历
void Postorder(BinTree T) {
	if (T) {
		Postorder(T->L);
		Postorder(T->R);
		printf("%d", T->data);
	}
}
//二分查找
BinTree Find(ElemType x, BinTree T){
	if (!T)
		return NULL;
	if (x < T->data)
		return Find(x, T->L);
	else if (x > T->data)
		return Find(x, T->R);
	else
		return T;
}
//最大值（递归）
BinTree FindMax(BinTree T) {
	if (!T)
		return NULL;
	if (!T->R)
		return T;
	else
		return FindMax(T);
}
//最小值(迭代)
BinTree FindMin(BinTree T) {
	if (!T)
		return NULL;
	while (T->L)
		T = T->L;
	return T;
}
//插入
BinTree Insert(BinTree T, ElemType x) {
	if (!T) {
		T = (BinTree)malloc(sizeof(Node));
		T->data = x;
		T->L = T->R = NULL;
	}
	else
		if (x > T->data) {
			T->R =Insert(T->R, x);
		}
		if (x < T->data) {
			T->L= Insert(T->L, x);
		}
	return T;
}
//删除
BinTree Delete( ElemType x ,BinTree T) {
	BinTree Tmp;
	if (!T) {
		printf("ERROR\n");
		return NULL;
	}
	if (x > T->data)
		T->R = Delete(x, T->R);
	else if(x<T->data)
		T->L= Delete(x, T->L);
	else {
		if (T->L && T->R) {
			Tmp = FindMin(T->R);
			T->data = Tmp->data;
			T->R = Delete(T->data, T->R);
		}
		else
			Tmp = T;
			if (!T->L)
				T = T->R;
			else if (!T->R)
				T = T->L;
		free(Tmp);
	}
}