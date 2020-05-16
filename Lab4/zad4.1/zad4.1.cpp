
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAXSTRLENGTH 80
/* Стек для операторов*/
struct Stack_for_operators {

	char info;

	struct Stack_for_operators *next;

	//struct Stack_for_operators* begin;

} *stack1 = NULL;
/* Стек для операндов*/
struct Stack_for_numbers {

	int number;

	struct Stack_for_numbers* next;

	//struct Stack_for_numbers* begin;

} *stack2 = NULL;

typedef struct Stack_for_operators Stack1;
typedef struct Stack_for_numbers Stack2;

/* Моя strlen(const char *string)*/
int Mystrlen(const char* string)
{
	int i = 0;
	while (string[i] && string[i] != '\n')
	{
		++i;
	}
	return i;
}
/* Содержит операторы?*/
int Contains_operators(char ch)
{
	if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
	{
		return 1;/* Как true*/
	}
	return 0;/* Как false*/
	
}
/* Содержит десятичные цифры?*/
int Contains_numerals(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return 1;/* True*/
	}
	return 0;/* False*/
}
/* Приоритет операций*/
int Prior(char a) {

	switch (a) {

		case '*': case '/': return 2;

		case '-': case '+': return 1;

	}

	return 0;

}

/* Извлечь оператор и удалить элемент*/
Stack1* Delete1(Stack1* p, char *out) {

	// Устанавливаем указатель t на вершину p

	Stack1* t = p;

	*out = p->info;

	// Переставляем вершину p на следующий элемент

	p = p->next;

	free(t); // Удаляем бывшую вершину t

	return p; // Возвращаем указатель на новую вершину p!!!!

}
/* Добавляем элемент*/
Stack1* Add1(Stack1* p, char in) {

	// Захватываем память для элемента

	Stack1* t = malloc(sizeof(Stack1));

	if (!t)
	{
		printf_s("Memory allocation error");
		exit(-1);
	}

	t->info = in; // Формируем информационную часть

	t->next = p; // Формируем адресную часть

	return t;
}
/* Извлечь операнд и удалить элемент*/
Stack2* Delete2(Stack2* p, int* number) {

	// Устанавливаем указатель t на вершину p

	Stack2* t = p;

	*number = p->number;

	// Переставляем вершину p на следующий элемент

	p = p->next;

	free(t); // Удаляем бывшую вершину t

	return p; // Возвращаем новую вершину p

}
/* Добавляем элемент*/
Stack2* Add2(Stack2* p, int number) {

	// Захватываем память для элемента

	Stack2* t = (Stack2*)malloc(sizeof(Stack2));

	if (!t)
	{
		printf_s("Memory allocation error");
		exit(-1);
	}

	t->number = number; // Формируем информационную часть

	t->next = p; // Формируем адресную часть

	return t;
}

/* Показать стек операторов*/
void View1(Stack1* p) {

	Stack1* t = p;

	while (t != NULL) {

		// Вывод на экран информационной части, например

		printf_s("%c ", t->info);

		t = t->next;

	}

	printf_s("\n");

}
/* Показать стек операндов*/
void View2(Stack2* p) {

	Stack2* t = p;

	while (t != NULL) {

		// Вывод на экран информационной части, например

		printf_s("%d ", t->number);

		t = t->next;

	}

	printf_s("\n");

}
/* Возвращает кол-во элементов в стеке*/
int Number_of_operators(Stack1* p) {

	Stack1* t = p;

	int counter = 0;

	while (t != NULL) {

		counter++;

		t = t->next;

	}

	return counter;
}
/* Возвращает кол-во элементов в стеке*/
int Number_of_operands(Stack2* p) {

	Stack2* t = p;

	int counter = 0;

	while (t != NULL) {

		counter++;

		t = t->next;

	}

	return counter;
}
/* Удалить стек операторов*/
void Del_All_Stack1(Stack1** p) {

	Stack1* t;

	while (*p != NULL) {

		t = *p;

		*p = (*p)->next;

		free(t);

	}

}
/* Удалить стек операндов*/
void Del_All_Stack2(Stack2** p) {

	Stack2* t;

	while (*p != NULL) {

		t = *p;

		*p = (*p)->next;

		free(t);

	}

}

/* Преобразовать из строки число*/
int Myatoi(const char* s, int j) {
	
	int num = 0;

	for (size_t i = 0; i < j; i++)
	{
		num *= 10;

		num += s[i] - '0';


	}
	return num;
}
/* Добавляет символ к строке*/
char* AddChar(char* str, char ch)
{
	char* temp = malloc(sizeof(char)*(Mystrlen(str)+2));
	if (!temp)
	{
		printf_s("Memory allocation error");
		exit(-1);
	}
	size_t i;
	for (i = 0; i < Mystrlen(str); i++)
	{
		temp[i] = str[i];
	}
	temp[i] = ch;
	temp[i + 1] = '\0';
	free(str);
	str = temp;
	return str;
	
}
/* Вычисляет выражение*/
void Result(char ch)
{
	int res = 0;
	int num1, num2 = 0;
	stack2 = Delete2(stack2, &num1);
	stack2 = Delete2(stack2, &num2);
	switch (ch)
	{
		case '+': res = num1 + num2; break;
		case '-': res = num1 - num2; break;
		case '*': res = num1 * num2;  break;
		case '/': res = num1 / num2; break;
	default:
		printf_s("Error!");
		exit(1);
		break;
	}
	stack2 = Add2(stack2, res);
}

/* Извлекает операнды и операторы из строки*/
void Operator_number_delimiter(const char* str, int *counter_of_operands, int *counter_of_operators)
{
	char* current = malloc(MAXSTRLENGTH * sizeof(char));
	if (!current)
	{
		printf_s("Memory allocation error");
		exit(-1);
	}
	int size = 0;
	for (int i = 0, len = Mystrlen(str); i < len; i++) {
		if (i == len - 1)
		{
			current[size] = str[i];
			size++;
		}
		if (Contains_operators(str[i]) || i == len - 1)
		{
			if (Contains_numerals(str[i-1]) || i == len-1) 
			{
				current[size] = '\0';
				stack2 = Add2(stack2, Myatoi(current, size));
				(*counter_of_operands)++;

				size = 0;
				current[size] = '\0';
				
				if (stack1)
				{
					if (Prior(str[i]) <= Prior(stack1->info))
					{
						char ch;

						stack1 = Delete1(stack1, &ch);

						Result(ch);

						if (i != len - 1)
						{
							stack1 = Add1(stack1, str[i]);
							(*counter_of_operators)++;
						}
					}
					else
					{
						if (i != len - 1)
						{
							stack1 = Add1(stack1, str[i]);
							(*counter_of_operators)++;
						}
					}
					
				}
				else
				{
					if (i != len - 1)
					{
						stack1 = Add1(stack1, str[i]);
						(*counter_of_operators)++;
					}
				}
			}
			else
			{
				printf_s("Your expression is wrong\n");
				exit(-1);
			}

		}
		else
		{
			current[size] = str[i];
			size++;
		}

	}
	free(current);

	while (stack1 && stack2->next)
	{
		char ch;

		stack1 = Delete1(stack1, &ch);

		Result(ch);	
	}

}

int main(void)
{
	char* string = malloc(MAXSTRLENGTH * sizeof(char));

	if (!string)
	{
		printf_s("Memory allocation error");
		exit(-1);
	}

	int counter_of_operands = 0, counter_of_operators = 0;

	printf_s("Enter your expression with integer numbers\n");

	fgets(string, MAXSTRLENGTH * sizeof(char), stdin);

	for (size_t i = 0, len = Mystrlen(string); i < len; i++)
	{
		if (Contains_numerals(string[i]) || Contains_operators(string[i]))
		{
			
			if (i == len - 1 && Contains_numerals(string[len - 1]) && Contains_numerals(string[0]))
			{
				Operator_number_delimiter(string, &counter_of_operands, &counter_of_operators);
				if (counter_of_operands == counter_of_operators + 1)
				{
					printf_s("Answer:");
					View2(stack2);
					View1(stack1);
				}
				else
				{
					printf_s("Your expression is wrong\n");
					exit(-1);
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			printf_s("Your expression is wrong\n");
			exit(-1);
		}
	}

	Del_All_Stack1(&stack1);

	Del_All_Stack2(&stack2);

	free(string);

	_getch();

	return 0;
}


