#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define ElemType char
#define MaxSize 100

typedef struct SqStack {
	ElemType data[MaxSize];
	int top;
}SqStack;

//��ʼ��ջs
void InitStack(SqStack*& s) {
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
	printf("(1)��ʼ��ջs\n");
}
//�ж�ջs�Ƿ�ǿ�
bool StackEmpty(SqStack* s) {
	if (s->top == -1) {
		return false;
	}
	else {
		return true;
	}
}
//���ν�ջԪ��a��b��c��d��e��
bool Push(SqStack*& s, ElemType e) {
	if (s->top == MaxSize - 1) {
		return false;
		exit(-1);
	}
	else {
		s->data[++(s->top)] = e;
		return true;
	}
	
}
//ȡ˳��ջ��ջ��Ԫ��
void GetTop(SqStack* s, ElemType& e) {
	if (s->top == -1) {
		exit(-1);
	}
	else {
		e = s->data[s->top];
		printf("%c\n",e );
	}
}
//�����ջ����
bool Pop(SqStack*& s,ElemType& e) {
	if (s->top == -1) {
		return false;
		exit(-1);
	}
	else {
		e = s->data[(s->top)--];
		printf("%c ", e);
		return true;
	}
}
//�ͷ�ջ
void DestroyStack(SqStack*& s) {
	s->top = -1;
	free(s);
	printf("�ͷ�ջ\n");
}