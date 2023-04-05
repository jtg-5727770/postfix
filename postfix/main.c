#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element; 

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return 0;
	}
	else return s->data[(s->top)--];
}
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return 0;
	}
	else return s->data[(s->top)];
}

// ���� ǥ�� ���� ��� �Լ�
int eval(char exp[])
{
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (isdigit(ch)) { // �Է��� �ǿ������̸�
            value = ch - '0';
            push(&s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // �Է��� �������̸�
            if (s.top < 1) { // ���ÿ� �ǿ����ڰ� �� �� �̻� ������ ���� ���
                printf("�߸��� �Է��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
                return 0;
            }
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) { // ������ �����ϰ� ���ÿ� ����
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        else { // ��ȿ�� ���ڰ� �ƴϸ� ���� ���
            printf("�߸��� �Է��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
            return 0;
        }
    }
    if (s.top != 0) { // ���ÿ� �ǿ����ڰ� �� �� �̻� ���������� ���� ���
        printf("�߸��� �Է��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
        return 0;
    }
    return pop(&s);
}

int main(void)
{
	char exp[MAX_STACK_SIZE];
	int result;
	printf("����ǥ���: ");
	scanf_s("%s", exp, MAX_STACK_SIZE);
	result = eval(exp);
	printf("�����: %d\n", result);
	system("pause");
	return 0;
}
