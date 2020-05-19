#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueItemInfo
{
	int number_of_tree;
	char action;
	int number; /*info*/
}  QueueItemInfo;

typedef struct QueueItem {
	struct QueueItem* prev;
	struct QueueItem* next;
	QueueItemInfo info;
} QueueItem;

typedef struct Queue {
	struct QueueItem* start;
	struct QueueItem* end;
} Queue;

/* Инициализация*/
void InitializationQueue(Queue* queue)
{
	queue->start = NULL;
	queue->end = NULL;

}

//добавление в конец списка
void QueueAdd(Queue* queue, int numb, char action, int number_of_tree) {
	QueueItem* temp = (QueueItem*)malloc(sizeof(QueueItem));

	temp->info.number = numb;
	temp->info.action = action;
	temp->info.number_of_tree = number_of_tree;
	temp->next = NULL;
	temp->prev = queue->end;
	
	if (!queue->start) {
		queue->start = temp;
	}
	else {
		queue->end->next = temp;
	}

	queue->end = temp;
}

//удаление элемента
QueueItem* OutQueue(QueueItem* p, int* number, char *action, int *number_of_tree) {

	QueueItem*t = p;

	*number = p->info.number;

	*action = p->info.action;

	*number_of_tree = p->info.number_of_tree;

	p = p->next; 

	free(t); 

	return p; 

}

//печать
void PrintQueue(Queue* queue) {
	QueueItem* li = queue->start;
	while (li) {
		printf_s("%d %d %c\n", li->info.number_of_tree, li->info.number, li->info.action);
		li = li->next;
	}
}

void Clear(Queue* list) {
	QueueItem* li = list->start, *temp;
	while (li) {
		temp = li;
		li = li->next;
		free(temp);
	}

	list->start = NULL;
	list->end = NULL;
}

void CopyQueue(Queue* queueFrom, Queue* queueTo) {
	Clear(queueTo);
	QueueItem* li = queueFrom->start;
	while (li) {
		QueueAdd(queueTo, li->info.number, li->info.action, li->info.number_of_tree);
		li = li->next;
	}
	Clear(queueFrom);
}
