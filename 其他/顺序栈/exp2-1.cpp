#include "sqstack.h"
int main() {
	
	SqStack* s;
	char e;

	InitStack(s);
	printf("(2)");
	if (StackEmpty(s))
		printf("ջΪ�ǿ�\n");
	else
		printf("ջΪ��\n");
	printf("(3)���ν�ջԪ��a��b��c��d��e\n");
	Push(s, 'a');
	Push(s, 'b');
	Push(s, 'c');
	Push(s, 'd');
	Push(s, 'e');
	printf("(4)");
	if (StackEmpty(s))
		printf("ջΪ�ǿ�\n");
	else
		printf("ջΪ��\n");
	printf("(5)ȡջ��Ԫ�أ�");
	GetTop(s, e);
	printf("(6)��ջ���У�");
	while (StackEmpty(s)) {
		Pop(s,e);
	}
	if (!StackEmpty(s))
		printf("\n");
	printf("(7)");
	if (StackEmpty(s))
		printf("ջΪ�ǿ�\n");
	else
		printf("ջΪ��\n");
	printf("(8)");
	DestroyStack(s);
	return 0;
}