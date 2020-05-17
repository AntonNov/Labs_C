#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Структура, описывающая элемент двунаправленного списка */ 
typedef struct item 
{   
	int digit;   
	struct item *next;   
	struct item *prev;
} Item; 
/* Структура, описывающая многоразрядное число */ 
typedef struct mnumber 
{   Item *head;
	Item *tail;   
	int n; 
} MNumber;
/* Добавляем элемент в конец*/
void AddDigit(MNumber* number, int digit) {
	Item* p = (Item*)malloc(sizeof(Item));
	p->digit = digit;
	p->next = p->prev = NULL;
	if (number->head == NULL)
		number->head = number->tail = p;
	else {
		number->tail->next = p;
		p->prev = number->tail;
		number->tail = p;
	}
	number->n++;
}
MNumber CreateMNumber(const char *string)
{
	int i = strlen(string)-1;
	MNumber number = { NULL, NULL, 0};
	while (i>=0)
	{
		AddDigit(&number, (string[i] - '0'));
		i--;
	}
	return number;

}

/* Возвращает сумму двух многоразрядных чисел */ 
MNumber SumMNumber(MNumber *n1, MNumber *n2) 
{
	MNumber sum = CreateMNumber("");   
	Item* p1 = n1->head, * p2 = n2->head;   
	int digit, pos = 0, s1, s2;

	while (p1 || p2) { 
		if (p1) 
		{ 
			s1 = p1->digit; 
			p1 = p1->next;
		} 
		else
		{
			s1 = 0;
		}
		if (p2) 
		{ 
			s2 = p2->digit; 
			p2 = p2->next;
		} 
		else
		{
			s2 = 0;
		}
		digit = (s1 + s2 + pos) % 10;     
		pos = (s1 + s2 + pos) / 10;     
		AddDigit(&sum, digit); 
	}   
	if (pos)
	{
		AddDigit(&sum, pos);
	}
	return sum;
}
/* Возвращает произведение многоразрядного числа на число */
MNumber Mult_number_Mnumber(MNumber n1, int number) {
	MNumber mult = CreateMNumber("");
	Item* p1 = n1.head;
	int digit, pos = 0, s1;

	while (p1) {
		if (p1)
		{
			s1 = p1->digit;
			p1 = p1->next;
		}
		digit = (s1*number + pos) % 10;
		pos = (s1*number+ pos) / 10;
		AddDigit(&mult, digit);
	}
	if (pos)
	{
		AddDigit(&mult, pos);
	}
	return mult;
}
/* Умножает число на 10*/
void Multiplyby10(MNumber *num2)
{
	Item* p = (Item*)malloc(sizeof(Item));
	p->prev = NULL;
	p->digit = 0;
	num2->head->prev = p;
	p->next = num2->head;
	num2->head = p;
	num2->n++;
	
}
void Clear(MNumber *number);

void CopyList(MNumber* listFrom, MNumber* listTo) {
	Item* li = listFrom->head;
	Clear(listTo);
	while (li) {
		AddDigit(listTo, li->digit);
		li = li->next;
	}
}
void PrintMNumber(MNumber number);
/* Умножает многоразрядное число на многоразрядное*/
MNumber MultMnumber(MNumber n1, MNumber n2)
{
	MNumber num1 = CreateMNumber("");
	MNumber num2 = CreateMNumber("");
	MNumber temp = CreateMNumber("");
	MNumber sum = CreateMNumber("");

	Item* p2 = n2.head;

	size_t counter = 0;
	while (p2)
	{
		CopyList(&Mult_number_Mnumber(n1, p2->digit), &num1);

		p2 = p2->next;
	
		if (p2)
		{
			CopyList(&Mult_number_Mnumber(n1, p2->digit), &num2);

			Multiplyby10(&num2);
			
			p2 = p2->next;

		}
		else
		{
			for (size_t i = 0; i < counter; i++)
			{
				Multiplyby10(&num1);
			}
			CopyList(&SumMNumber(&num1, &sum), &sum);
			
			return sum;
		}
		CopyList(&SumMNumber(&num1, &num2), &temp);
		
		for (size_t i = 0; i < counter; i++)
		{
			Multiplyby10(&temp);
		}
		CopyList(&SumMNumber(&temp, &sum), &sum);
		counter += 2;
		CopyList(&CreateMNumber(""), &num1);
		CopyList(&CreateMNumber(""), &num2);
	}
	return sum;
}

/* Выводит многоразрядное число на экран */ 
void PrintMNumber(MNumber number) {
	Item* p = number.tail;
	printf("Factorial: ");    
	while (p) 
	{ 
		printf("%d", p->digit);      
		p = p->prev; 
	}
	printf_s("\n");
}
void Clear(MNumber* list) {
	Item* li = list->head, *temp;
	while (li) {
		temp = li;
		li = li->next;
		free(temp);
	}

	list->head = NULL;
	list->tail = NULL;
}
void EnterInt(int* _i)
{
	char ch;
	int i;
	int correct;
	do
	{
		correct = scanf_s("%9d%c", &i, &ch, 1);
		if (ch != '\n')
		{
			scanf_s("%*[^\n]"); /* Clearing the buffer */
		}
		if (!(correct > 0  && i>=0 /*&& i> 100*/ && (ch == '\n' || ch == ' ')))
		{
			printf_s("Incorrect input, try again:\n");
		}


	} while (!(correct > 0  && i>=0/*&& i > 100*/ && (ch == '\n' || ch == ' ')));

	*_i = i;
	return;
}
int main(void)
{	
	printf_s("Factorial (n>100):\n");
	printf_s("Enter\n");
	int n;
	EnterInt(&n);
	int counter = 2;
	MNumber a = CreateMNumber("");
	MNumber b = CreateMNumber("1");
	char buffer[1000];
	while (counter <= n)
	{
		_itoa_s(counter, buffer, 10);
		CopyList(&CreateMNumber(buffer), &a);
		CopyList(&MultMnumber(a, b), &b);
		counter++;
	}
	PrintMNumber(b);
	Clear(&a);
	Clear(&b);
	return 0;
}
