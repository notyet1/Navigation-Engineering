#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define ElemType char
#define MaxSize 100

typedef struct SqStack {
	ElemType data[MaxSize];
	int top;
}SqStack;

//初始化栈s
void InitStack(SqStack*& s) {
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
	printf("(1)初始化栈s\n");
}
//判断栈s是否非空
bool StackEmpty(SqStack* s) {
	if (s->top == -1) {
		return false;
	}
	else {
		return true;
	}
}
//依次进栈元素a、b、c、d、e。
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
//取顺序栈的栈顶元素
void GetTop(SqStack* s, ElemType& e) {
	if (s->top == -1) {
		exit(-1);
	}
	else {
		e = s->data[s->top];
		printf("%c\n",e );
	}
}
//输出出栈序列
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
//释放栈
void DestroyStack(SqStack*& s) {
	s->top = -1;
	free(s);
	printf("释放栈\n");
}