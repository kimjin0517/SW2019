#define _CRT_SECURE_NO_WARNINGS
#include"ArrayStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	//variation
	char s1[1000], s[1000];
	Stack* pStack, * oper, *validity;
	char* ret ;
	int a[1000],b, c, d, len, i=0, temp = 0;
	char e;
	
	printf("Dyadic Operation Calculator\n\n");
	printf("Enter the a numerical expression (Not more than 1000 characters): ");
	gets(s);
	strcpy(s1, s);
	len = strlen(s);

	//create stack
	validity =CreateStack(len);
	pStack = CreateStack(len);
	oper = CreateStack(len);

	
	//validity check
	for (i = 0;i < len;i++) {
		if (s[i] == ' ') continue;
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (s[temp] == '+' || s[temp] == '-' || s[temp] == '*' || s[temp] == '/' || s[temp] == '(') {
				printf("Error: Expression error!! Program Down...\n");
				return 0;
			}
			else {
				temp = i;
				continue;
			}
		}
		if (s[i] == '0' || atoi(&s[i])!=0) {
			if (s[temp] == '+' || s[temp] == '-' || s[temp] == '*' || s[temp] == '/' || s[temp] == '(') {
				temp = i;
				continue;
			}
			else if (i == 0) {
				temp = i;
				continue;
			}
			else if (i-temp!=1 || s[temp]==')') {
				printf("Error: Expression error!! Program Down...\n");
				return 0;
			}
			else {
				temp = i;
				continue;
			}
			
		}
		
		if (s[i] == '(') {
			if (s[temp] == '+' || s[temp] == '-' || s[temp] == '*' || s[temp] == '/' || s[temp] == '(') {
				Push(validity, &s[i]);
				temp = i;
			}
			else {
				printf("Error: Expression error!! Program down...");
				return 0;
			}
			
		}
		if (s[i] == ')') {
			if (Pop(validity) == NULL){
				printf("Error: There's no pair of bracket!! Program Down...\n");
				return 0;
			}
		}

	}
	if (IsEmptyStack(validity)==0) {
		printf("Error: There's no pair of bracket!! Program Down...\n");
		return 0;
	}

	//calculate
	temp = 0;
	for ( i = 0;i < len;i++) {
		if (s[i] == ' ') continue;
		if (s[i] == '(') {
			Push(oper, &s[i]);
			continue;
		}
		if (s[i] == ')') {
			while (1) {
				e = *(char*)Pop(oper);
				if ( e== '+') {
					a[i+temp] = *(int*)Pop(pStack) + *(int*)Pop(pStack);
					Push(pStack, &a[i + temp]);
									}
				if (e == '-') {
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d - c;
					Push(pStack, &a[i + temp]);
				}
				if (e == '*') {
					a[i + temp] = *(int*)Pop(pStack) * *(int*)Pop(pStack);
					Push(pStack, &a[i + temp]);
				}
				if (e == '/') {
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d / c;
					Push(pStack, &a[i + temp]);
				}
				if (e == '(') break;
				temp++;
			}
			continue;
		}
		if (s[i] == '+') {
			if (IsEmptyStack(oper) || *(char*)oper->stack[(oper->top)] == '(') Push(oper, &s[i]);
			else if (*(char*)oper->stack[(oper->top)] == '*') {
				Pop(oper);
				a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
				Push(pStack, &a[i + temp]);
				
				if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '+') {
					a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
					Push(pStack, &a[i + temp]);
				}
				else if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '-') {
					Pop(oper);
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d - c;
					Push(pStack, &a[i + temp]);
					Push(oper, &s[i]);
				}
				else Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '/') {
				Pop(oper);
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d / c;
				Push(pStack,&a[i + temp]);
				
				if (!IsEmptyStack(oper)&&*(char*)oper->stack[(oper->top)] == '+') {
					a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
					Push(pStack, &a[i + temp]);
				}
				else if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '-') {
					Pop(oper);
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d - c;
					Push(pStack, &a[i + temp]);
					Push(oper, &s[i]);
				}
				else Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '+') {
				a[i + temp] = *(int*)Pop(pStack) + *(int*)Pop(pStack);
				Push(pStack, &a[i + temp]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '-') {
				Pop(oper);
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d - c;
				Push(pStack, &a[i + temp]);
				Push(oper,&s[i]);
			}
			continue;
		}
		if (s[i] == '-') {
			if (IsEmptyStack(oper) || *(char*)oper->stack[(oper->top)] == '(') Push(oper, &s[i]);
			else if (*(char*)oper->stack[(oper->top)] == '*') {
				Pop(oper);
				a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
				Push(pStack, &a[i + temp]);
				if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '+') {
					a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
					Push(pStack, &a[i + temp]);
				}
				else if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '-') {
					Pop(oper);
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d - c;
					Push(pStack, &a[i + temp]);
					Push(oper, &s[i]);
				}
				else Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '/') {
				Pop(oper);
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d / c;
				Push(pStack, &a[i + temp]);
				if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '+') {
					a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
					Push(pStack, &a[i + temp]);
				}
				else if (!IsEmptyStack(oper) && *(char*)oper->stack[(oper->top)] == '-') {
					Pop(oper);
					c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
					a[i + temp] = d - c;
					Push(pStack, &a[i + temp]);
					Push(oper, &s[i]);
				}
				else Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '+') {
				Pop(oper);
				a[i + temp] = *(int*)Pop(pStack) + *(int*)Pop(pStack);
				Push(pStack, &a[i + temp]);
				Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '-') {
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d - c;
				Push(pStack, &a[i + temp]);
			}
			continue;
		}
		if (s[i] == '*') {
			if (IsEmptyStack(oper)|| *(char*)oper->stack[(oper->top)] == '(') Push(oper, &s[i]);
			else if (*(char*)oper->stack[(oper->top)] == '*') {
				a[i + temp] = *(int*)Pop(pStack) * (*(int*)Pop(pStack));
				Push(pStack, &a[i + temp]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '/') {
				Pop(oper);
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d / c;
				Push(pStack, &a[i + temp]);
				Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '+' || *(char*)oper->stack[(oper->top)] == '-') {
				Push(oper, &s[i]);
			}
			continue;
		}
		if (s[i] == '/') {
			if (IsEmptyStack(oper) || *(char*)oper->stack[(oper->top)] == '(') Push(oper, &s[i]);
			else if (*(char*)oper->stack[(oper->top)] == '*') {
				Pop(oper);
				a[i + temp] = *(int*)Pop(pStack) * *(int*)Pop(pStack);
				Push(pStack, &a[i + temp]);
				Push(oper, &s[i]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '/') {
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d / c;
				Push(pStack, &a[i + temp]);
			}
			else if (*(char*)oper->stack[(oper->top)] == '+' || *(char*)oper->stack[(oper->top)] == '-') {
				Push(oper, &s[i]);
			}
			continue;
		}
		else {
			ret = strtok(&s[i], "+-()/*");
			a[i + temp] = atoi(ret);
			Push(pStack, &a[i + temp]);
			b = strlen(ret);
			s[i + b] = s1[i + b];
			i = i + b - 1;
		}
		continue;

	}
	
	
	while (oper->top != -1) {
		i += 1;
		e = *(char*)Pop(oper);
		if ( e == '+') {
			a[i + temp] = *(int*)Pop(pStack) + (*(int*)Pop(pStack));
				Push(pStack, &a[i + temp]);
		}
		else if (e == '-') {
			if (IsEmptyStack(oper)!=1 && *(char*)oper->stack[oper->top] == '-') {
				a[i + temp] = *(int*)Pop(pStack) + *(int*)Pop(pStack);
				Push(pStack, &a[i + temp]);
			}
			else {
				c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
				a[i + temp] = d - c;
				Push(pStack, &a[i + temp]);
			}
		}
		else if (e == '*') {
			a[i + temp] = *(int*)Pop(pStack) * *(int*)Pop(pStack);
			Push(pStack, &a[i + temp]);
		}
		else if (e == '/') {
			c = *(int*)Pop(pStack), d = *(int*)Pop(pStack);
			a[i + temp] = d / c;
			Push(pStack, &a[i + temp]);
		}
		
	}
	printf("Result: %d", *(int*)Pop(pStack));
	
	DestroyStack(oper);
	DestroyStack(pStack);
	DestroyStack(validity);
	
	return 0;
}