#define _CRT_SECURE_NO_WARNINGS
#include "List.h"

int PrintList(List* list)
{
	int key = 0;
	int code;
	int flag1 = 0, flag2 = 0;

	do
	{
		Node* current = list->head;
		system("cls");
		key = (key + list->size + 1) % (list->size + 1);

		int i = 0;
		while (current != NULL)
		{
			if (key == i)
			{
				if (strcmp(current->data.name, loginAcc.name) == 0)
				{
					flag1 = 1;
				}
				else
				{
					flag1 = 0;
				}
				SetRed();
				printf(">%d\n", current->data.ID);
				printf(" %s\n", current->data.name);
				printf(" %s\n", current->data.text);
				SetWhite();
			}
			else if (strcmp(current->data.name, loginAcc.name) == 0)
			{
				SetGreen();
				printf("%d\n", current->data.ID);
				printf("%s\n", current->data.name);
				printf("%s\n", current->data.text);
				SetWhite();
			}
			else
			{
				printf("%d\n", current->data.ID);
				printf("%s\n", current->data.name);
				printf("%s\n", current->data.text);
			}
			printf("\n");
			current = current->pNext;
			i++;
		}
		if (key == list->size)
		{
			flag2 = 1;
			SetRed();
			puts(">Add");
			SetWhite();
		}
		else
		{
			flag2 = 0;
			puts("Add");
		}

		code = getch();
		if (code == 80)
		{
			key++;
		}
		else if (code == 72)
		{
			key--;
		}

		if (code == 27)
		{
			system("cls");
			return -1;
		}
	} while (code != 13 || (!flag1 && !flag2));

	system("cls");

	return key;
}

Comment* Get(List* list, int num)
{
	Node* current = list->head;
	for (int i = 0; i < num; i++)
	{
		if (current == NULL)
		{
			return NULL;
		}
		current = current->pNext;
	}

	return &(current->data);
}

void PrintCommentsByName(List* list, char name)
{
	Node* current = list->head;

	while (current != NULL)
	{
		if (strcmp(name, current->data.name) == 0)
		{
			printf("%s", current->data.text);
		}
		current = current->pNext;
	}
	printf("\n");
}

void PushBack(List* list, Comment data)
{
	if (list->head == NULL && list->tail == NULL)
	{
		Node* newNode = (Node*)calloc(1, sizeof(Node));
		newNode->pNext = NULL;
		newNode->pPrev = NULL;
		newNode->data = data;


		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		Node* newNode = (Node*)calloc(1, sizeof(Node));
		newNode->pNext = NULL;
		newNode->pPrev = list->tail;
		newNode->data = data;

		list->tail->pNext = newNode;
		list->tail = newNode;
	}

	list->size++;
}

void PushFront(List* list, Comment data)
{
	if (list->head == NULL && list->tail == NULL)
	{
		Node* newNode = (Node*)calloc(1, sizeof(Node));
		newNode->pNext = NULL;
		newNode->pPrev = NULL;
		newNode->data = data;


		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		Node* newNode = (Node*)calloc(1, sizeof(Node));
		newNode->pNext = list->head;
		newNode->pPrev = NULL;
		newNode->data = data;

		list->head->pPrev = newNode;
		list->head = newNode;
	}

	list->size++;
}

void Insert(List* list, int index, Comment data)
{
	if (index == 0)
	{
		PushFront(list, data);
		return;
	}

	if (index == list->size)
	{
		PushBack(list, data);
		return;
	}

	Node* current;

	if (index < list->size / 2)
	{
		int counter = 0;
		current = list->head;

		while (counter < index)
		{
			current = current->pNext;
			counter++;
		}
	}
	else
	{
		int counter = list->size - 1;
		current = list->tail;

		while (counter > index)
		{
			current = current->pPrev;
			counter--;
		}
	}

	Node* newNode = (Node*)calloc(1, sizeof(Node));

	newNode->pPrev = current->pPrev;
	newNode->pNext = current;

	current->pPrev->pNext = newNode;
	current->pPrev = newNode;

	newNode->data = data;

	list->size++;

}

void PopFront(List* list)
{
	if (list->size == 0) return;

	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return;
	}

	Node* toDelete = list->head;
	list->head = list->head->pNext;

	list->head->pPrev = NULL;

	free(toDelete);

	list->size--;
}

void PopBack(List* list)
{
	if (list->size == 0) return;

	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return;
	}

	Node* toDelete = list->tail;
	list->tail = list->tail->pPrev;

	list->tail->pNext = NULL;

	free(toDelete);

	list->size--;
}

void Delete(List* list, int index)
{
	if (index == 0)
	{
		PopFront(list);
		return;
	}

	if (index == list->size - 1)
	{
		PopBack(list);
		return;
	}

	Node* current;

	if (index < list->size / 2)
	{
		int counter = 0;
		current = list->head;

		while (counter < index)
		{
			current = current->pNext;
			counter++;
		}
	}
	else
	{
		int counter = list->size - 1;
		current = list->tail;

		while (counter > index)
		{
			current = current->pPrev;
			counter--;
		}
	}

	Node* toDelete = current;

	current->pPrev->pNext = current->pNext;
	current->pNext->pPrev = current->pPrev;

	free(toDelete);

	list->size--;

}

void DeleteAll(List* list)
{
	while (list->size > 0)
	{
		PopFront(list);
	}
}

Comment* Find(List* list, int ID)
{
	Node* current = list->head;

	while (current != NULL)
	{
		if (current->data.ID == ID)
		{
			return &(current->data);
		}
		current = current->pNext;
	}
	return NULL;
}


void WriteToFile(List* list, FILE* file, int first)
{
	Node* current = list->head;

	while (current != NULL)
	{
		if (first == 1)
		{
			fprintf(file, "%d\n", current->data.ID);
			first = 0;
		}
		else
		{
			fprintf(file, "\n%d\n", current->data.ID);
		}
		fprintf(file, "%s\n", current->data.name);
		fprintf(file, "%s", current->data.text);

		current = current->pNext;
	}
}

//void WriteToFile(List* list, FILE* file)
//{
//	Node* current = list->head;
//
//	while (current != NULL)
//	{
//		fprintf(file, "%d\n", current->data.ID);
//		fprintf(file, "%s\n", current->data.name);
//		fprintf(file, "%s", current->data.text);
//
//		current = current->pNext;
//	}
//}

void ReadFromFile(List* list, FILE* file)
{
	char buff[100];

	while (!feof(file))
	{
		Comment comm;

		fscanf(file, "%d", &comm.ID);
		fscanf(file, "%s", comm.name);
		fscanf(file, "%s", comm.text);

		fgetc(file);

		PushBack(list, comm);
	}
}