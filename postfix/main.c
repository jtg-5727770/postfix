#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element; 

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return 0;
	}
	else return s->data[(s->top)--];
}
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return 0;
	}
	else return s->data[(s->top)];
}

// 후위 표기 수식 계산 함수
int eval(char exp[])
{
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (isdigit(ch)) { // 입력이 피연산자이면
            value = ch - '0';
            push(&s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // 입력이 연산자이면
            if (s.top < 1) { // 스택에 피연산자가 두 개 이상 없으면 오류 출력
                printf("잘못된 입력입니다. 다시 확인해주세요.\n");
                return 0;
            }
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) { // 연산을 수행하고 스택에 저장
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        else { // 유효한 문자가 아니면 오류 출력
            printf("잘못된 입력입니다. 다시 확인해주세요.\n");
            return 0;
        }
    }
    if (s.top != 0) { // 스택에 피연산자가 한 개 이상 남아있으면 오류 출력
        printf("잘못된 입력입니다. 다시 확인해주세요.\n");
        return 0;
    }
    return pop(&s);
}

int main(void)
{
	char exp[MAX_STACK_SIZE];
	int result;
	printf("후위표기식: ");
	scanf_s("%s", exp, MAX_STACK_SIZE);
	result = eval(exp);
	printf("결과값: %d\n", result);
	system("pause");
	return 0;
}
