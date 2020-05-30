#pragma once

typedef struct Page
{
	int ID;
	char name[32];
	List* Comments;
}Page;
