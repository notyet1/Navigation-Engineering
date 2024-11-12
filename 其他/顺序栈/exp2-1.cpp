#include "sqstack.h"
int main() {
	
	SqStack* s;
	char e;

	InitStack(s);
	printf("(2)");
	if (StackEmpty(s))
		printf("栈为非空\n");
	else
		printf("栈为空\n");
	printf("(3)依次进栈元素a，b，c，d，e\n");
	Push(s, 'a');
	Push(s, 'b');
	Push(s, 'c');
	Push(s, 'd');
	Push(s, 'e');
	printf("(4)");
	if (StackEmpty(s))
		printf("栈为非空\n");
	else
		printf("栈为空\n");
	printf("(5)取栈顶元素：");
	GetTop(s, e);
	printf("(6)出栈序列：");
	while (StackEmpty(s)) {
		Pop(s,e);
	}
	if (!StackEmpty(s))
		printf("\n");
	printf("(7)");
	if (StackEmpty(s))
		printf("栈为非空\n");
	else
		printf("栈为空\n");
	printf("(8)");
	DestroyStack(s);
	return 0;
}