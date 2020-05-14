
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//#include "Header.h"
struct Stack_for_operators {

	char info;

	struct Stack_for_operators* next;

} *stack1 = NULL;

struct Stack_for_numbers {

	int number;

	struct Stack_for_numbers* next;

} *stack2 = NULL;

typedef struct Stack_for_operators Stack1;
typedef struct Stack_for_numbers Stack2;

/*int MyStrlen(const char* string)
{
	int i = 0;
	while (string[i] && string[i] != '\n')
	{
		++i;
	}
	return i;
}*/
int Prior(char a) {

	switch (a) {

	case '*': case '/': return 2;

	case '-': case '+': return 1;

	}

	return 0;

}

Stack1* Delete1(Stack1* p, char* out) {

	// Устанавливаем указатель t на вершину p

	Stack1* t = p;

	*out = p->info;

	// Переставляем вершину p на следующий элемент

	p = p->next;

	free(t); // Удаляем бывшую вершину t

	return p; // Возвращаем указатель на новую вершину p!!!!

}
Stack1* Add1(Stack1* p, char in) {

	// Захватываем память для элемента

	Stack1* t = malloc(sizeof(Stack1));

	t->info = in; // Формируем информационную часть

	t->next = p; // Формируем адресную часть

	return t;
}

Stack2* Delete2(Stack2* p, int* number) {

	// Устанавливаем указатель t на вершину p

	Stack2* t = p;

	*number = p->number;

	// Переставляем вершину p на следующий элемент

	p = p->next;

	free(t); // Удаляем бывшую вершину t

	return p; // Возвращаем новую вершину p

}
Stack2* Add2(Stack2* p, int number) {

	// Захватываем память для элемента

	Stack2* t = (Stack2*)malloc(sizeof(Stack2));

	t->number = number; // Формируем информационную часть

	t->next = p; // Формируем адресную часть

	return t;
}

int OperatorDelimeter(const char* str)
{
	char extrastr[] = "+-*";

	int counter = 0;

	for (int i = 0, len1 = strlen(str); i < len1; i++) {

		for(int j = 0, len2 = strlen(extrastr); j < len2; j++)
		{

			if (extrastr[i]==str[j])
			{
				stack1 = Add1(stack1, extrastr[i]);

				counter++;
			}
			
		}

	}

	return counter;
}

void View1(Stack1* p) {

	Stack1* t = p;

	while (t != NULL) {

		// Вывод на экран информационной части, например

		printf_s("%c", t->info);

		t = t->next;

	}

}
void View2(Stack2* p) {

	Stack2* t = p;

	while (t != NULL) {

		// Вывод на экран информационной части, например

		printf_s("%d", t->number);

		t = t->next;

	}

}

void Del_All_Stack1(Stack1** p) {

	Stack1* t;

	while (*p != NULL) {

		t = *p;

		*p = (*p)->next;

		free(t);

	}

}
void Del_All_Stack2(Stack2** p) {

	Stack2* t;

	while (*p != NULL) {

		t = *p;

		*p = (*p)->next;

		free(t);

	}

}

int main(void)
{
	char* string = malloc(100 * sizeof(char));

	fgets(string, 100 * sizeof(char), stdin);

	OperatorDelimeter(string);

	View1(stack1);

	printf("hui");

	Del_All_Stack1(&stack1);

	Del_All_Stack2(&stack2);



	_getch();

	return 0;
}


/*int NumberDelimiter(const char* str)
{

	char* extrastr = (char*)malloc(5 * sizeof(char));

	extrastr = "+//-*";

	size_t j = 0;

	for (size_t i = 0; i < MyStrlen(extrastr); i++)
	{

		while (str[j] != extrastr[i] && j<MyStrlen(str))
		{
			j++;
		}


		if (str[j] == extrastr[i])
		{
			break;
		}
		else
		{
			j = 0;
		}
	}

	char* temp = (char*)malloc(100 * sizeof(char));

	for (size_t i = 0; i < j; i++)
	{
		temp[i] = str[i];
	}

	temp[j] = '\0';

	int num = 0;

	for (size_t i = 0; i < j; i++)
	{
		num *= 10;

		num += temp[i] - '0';


	}

	char* str2 = (char*)malloc(100 * sizeof(char));

	for (size_t i = 0; i <= MyStrlen(str); i++)
	{
		str2[i] = str[i];
	}

	for (int i = j; i< MyStrlen(str); i++)
	{
		str[i] = str2[j];
	}

	str[MyStrlen(str)] = '\0';

	free(str2);

	free(temp);

	return num;
} */

int[] ParseToNumbers(char s) {
	int result[1000]{};
	char current[100]{};
	int cnt = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] != '+' && s[i] != '-' && s[i] != '' && s[i] != '/') {
			strcat(current, s[i]);
		}
		else {
			result[cnt] = atoi(current);
			cnt++;
			result = "\0";
		}
	}
	return result;
}
