#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include "Comment.h"
#include "Account.h"


typedef struct Node
{
	Comment data;
	struct Node* pNext;
	struct Node* pPrev;
} Node;

typedef struct List
{
	Node* head;
	Node* tail;
	int size;
} List;

void PushBack(List*, Comment);
void PushFront(List*, Comment);
void Insert(List*, int, Comment);

void PopFront(List*);
void PopBack(List*);
void Delete(List*);
void Delete(List*, int);

int PrintList(List*);
void PrintCommentsByName(List*, char[]);
void DeleteAll(List*);

void Sort(List*);
Comment* Get(List*, int);
Comment* Find(List*, int);
int FindIndex(List*, int);

void WriteToFile(List*, FILE*);
void WriteToFile(List*, FILE*, int);
void ReadFromFile(List*, FILE*);
