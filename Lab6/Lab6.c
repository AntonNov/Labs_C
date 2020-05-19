#include "Tree.h"
#include "Queue.h"
#include "Functions.h"
#include <conio.h>

TreeList* treelist = NULL;
Queue* queue = NULL;

void ClearTreeList(TreeList* treelist);

TreeItem* Find_Treeitem(TreeItem *root, int number_of_tree)
{
	TreeItem* start = root;
	while (number_of_tree)
	{
		start = start->next;
		number_of_tree--;
	}
	return start;
}

void PrintTreeList(TreeList* treelist)
{
	printf_s("Trees:\n");
	TreeItem* start = treelist->start;
	while (start)
	{
		PrintTree(start, 0);
		printf("\n");
		start = start->next;
	}
}
int main(void)
{
	char ch, action;

	int element, number_of_tree, number_of_trees;

	treelist = (TreeList*)malloc(sizeof(TreeList));
	queue = (Queue*)malloc(sizeof(Queue));

	InitializationQueue(queue);
	InitializationTrees(treelist);
	/*start, end - NULL*/

	TreeItem** pointer1 = &(treelist->start);
	TreeItem** pointer2 = &(treelist->start);

	printf_s("Enter number of trees:\n");
	EnterNumberOfTrees(&number_of_trees);

	treelist->count = number_of_trees;

	for (size_t i = 0; i < (size_t)number_of_trees;	i++)
	{
		do
		{
			printf_s("Enter element of %u tree:\n", i);
			int num;
			EnterInt(&num);
			if (i % 2) {
				*pointer1 = Tree_Add_not_rec(*pointer1, num); 
				treelist->start->prev = NULL;
				treelist->end = *pointer1;
			}
			else
			{
				*pointer2 = Tree_Add_not_rec(*pointer2, num);
				treelist->start->prev = NULL;
				treelist->end = *pointer2;
			}
			printf_s("Enter space to continue input of elements of tree\n");
		} while (ch = _getch() == ' ');

		if (i % 2)
		{
			pointer2 = &((*pointer1)->next);
		}
		else
		{
		
			pointer1 = &((*pointer2)->next);
		}
	}

	PrintTreeList(treelist);

	size_t counter = 0;
	do
	{
		printf_s("%u element of queue:\n", counter);

		printf_s("Enter number of tree:\n");
		EnterNumberOfTree(&number_of_tree, number_of_trees);

		printf_s("Enter element in queue:\n");
		EnterInt(&element);

		printf_s("Enter action of element in queue:\n");
		EnterChar(&action);

		QueueAdd(queue, element, action, number_of_tree);

		printf_s("Enter '!' to continue input\n");
		
		counter++;

	} while (ch = _getch() == '!');

	PrintQueue(queue);
	
	int number_new = 0, number_of_tree_new = 0;
	char action_new;
	QueueItem* queue_start = queue->start;
	for (size_t i = 0; queue_start; i++)
	{
		queue_start = OutQueue(queue_start, &number_new, &action_new, &number_of_tree_new);
		TreeItem* temp = Find_Treeitem(treelist->start, number_of_tree_new);
		if (action_new == 'A')
		{
			temp = Tree_Add_not_rec(temp, number_new);
		}
		else if (action_new == 'D')
		{
			Delete_Node_BinaryTree(&temp, number_new);
			TreeItem** pointer1_2 = &(treelist->start);
			TreeItem** pointer2_2 = &(treelist->start);
			TreeItem* next = NULL, *prev = NULL, *end = NULL;
			size_t i = 0;
			for (i; number_of_tree; i++)
			{
				if (i % 2)
					pointer2_2 = &((*pointer1_2)->next);
	
				else
					pointer1_2 = &((*pointer2_2)->next);
				number_of_tree--;
			}
			if (i % 2)
			{
				next = (*pointer2_2)->next;
				*pointer2_2 = temp;
				(*pointer2_2)->next = next;
			
			}
			else
			{
				next = (*pointer1_2)->next;
				*pointer1_2 = temp;
				(*pointer1_2)->next = next;
			}

		}
	}
	
	PrintTreeList(treelist);
	free(queue);
	ClearTreeList(treelist);
	printf("The end");
	return 0;
}
void ClearTreeList(TreeList* treelist)
{
	TreeItem* start_new;
	for (int j = 0; j < treelist->count; j++)
	{
		start_new = treelist->start;
		for (int i = 0; i < treelist->count; i++)
		{
			start_new = start_new->next;
		}
		Tree_clear(start_new);
		treelist->count--;
	}
	free(treelist);
}
