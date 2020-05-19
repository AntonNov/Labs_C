#include <stdio.h>
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
		if (!(correct > 0 && (ch == '\n' || ch == ' ')))
		{
			printf_s("Incorrect input, try again:\n");
		}


	} while (!(correct > 0 && (ch == '\n' || ch == ' ')));

	*_i = i;
	return;
}
void EnterNumberOfTrees(int* _i)
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
		if (!(correct > 0 && i >= 0 && (ch == '\n' || ch == ' ')))
		{
			printf_s("Incorrect input, try again:\n");
		}


	} while (!(correct > 0 && i >= 0 && (ch == '\n' || ch == ' ')));

	*_i = i;
	return;
}
/* Индексация от 0 до number_of_trees-1*/
void EnterNumberOfTree(int* _i, int number_of_trees)
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
		if (!(correct > 0 && (i >= 0 && i < number_of_trees) && (ch == '\n' || ch == ' ')))
		{
			printf_s("Incorrect input, try again:\n");
		}


	} while (!(correct > 0 &&(i >= 0 && i < number_of_trees) && (ch == '\n' || ch == ' ')));

	*_i = i;
	return;
}


void EnterChar(char* _ch)
{
	char ch;
	do
	{
		scanf_s("%c", &ch);
		if (!(ch == 'A' || ch == 'D'))
		{
			printf_s("Incorrect input, try again:\n");
		}
		rewind(stdin);

	} while (!(ch == 'A' || ch == 'D'));

	*_ch = ch;

}
