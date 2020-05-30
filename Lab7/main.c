#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include "List.h"
#include "Comment.h"
#include "Account.h"
#include "Path.h"
#include "Menu.h"
#include "Page.h"

#define PRIME_SIZE 31



struct HashTable
{
	Page* table[PRIME_SIZE];
}hashTable;

int countAccount = 0;

int PrintFromFile(char name[])
{
	FILE* file;
	if ((file = fopen(name, "r")) == NULL)
	{
		return 1;
	}
	char buffer[128];
	fgets(buffer, 127, file);
	printf("%s", buffer);
	fclose(file);
	return 0;
}

int LoadAccountsFromFile(char path[], Account** accounts)
{
	FILE* file;
	if ((file = fopen(path, "r+")) == NULL)
	{
		return 1;
	}

	int countLines = 0;
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
		{
			countLines++;
		}
	}

	countAccount = countLines / 2;
	rewind(file);

	if ((*accounts = (Account*)malloc(sizeof(Account) * (countAccount + 1))) == NULL)
	{
		return 1;
	}

	for (int i = 0; i < countAccount; i++)
	{
		fscanf(file, "%s", (*accounts)[i].name);

		char buf[31];
		fgets(buf, 30, file);
		fgets(buf, 30, file);
		(*accounts)[i].passwordHash = atol(buf);
	}

	fclose(file);
	return 0;
}

long long Hash(char str[])
{
	const int p = 31;
	long long hash = 0, p_pow = 1;

	int i = 0;
	while (str[i] != 0)
	{
		hash += (str[i] - '0' + 1) * p_pow;
		p_pow *= p;
		i++;
	}

	return hash;
}

int Login(char name[20], char password[30], Account* accounts)
{
	const int p = 31;
	long long hash = 0, p_pow = 1;
	for (int j = 0; j < countAccount; j++)
	{
		if (strcmp(name, accounts[j].name) == 0)
		{
			long long hash = Hash(password);

			if (hash == accounts[j].passwordHash)
			{
				loginAcc = accounts[j];
				return 1;
			}
		}
	}
	return 0;
}

int Register(char path[], char name[20], char password[30], Account** accounts)
{
	FILE* file;
	if ((file = fopen(path, "a+")) == NULL)
	{
		return 1;
	}

	int i = 0;
	while (name[i] != 0)
	{
		(*accounts)[countAccount].name[i] = name[i];
		i++;
	}
	(*accounts)[countAccount].name[i] = 0;
	
	long long hash = Hash(password);
	(*accounts)[countAccount].passwordHash = hash;

	countAccount++;
	fprintf(file, "%s\n", name);
	fprintf(file, "%lld\n", hash);

	fclose(file);
	return 0;
}

void Authorization(char path[], Account** acc)
{
	char login[20], password[30];
	int isLogin = 0;

	while (!isLogin)
	{
		int key = LoginMenu();
		puts("Login:");
		gets(login);
		puts("Password:");
		gets(password);

		switch (key)
		{
		case 0:
			if (isLogin = Login(login, password, *acc))
			{
				puts("login done");
			}
			else
			{
				puts("wrong login or password");
				Sleep(1000);
			}
			break;
		case 1:
			Register(path, login, password, acc);
			key = 0;
			system("cls");
			puts("registered");
			break;
		default:
			break;
		}
	}
}

#define FilePrint FILE* file;\
if ((file = fopen(path, "r+")) == NULL)\
{\
	return 1;\
}\
char buf[100];\
while (fgets(buf, 100, file) != NULL)\
{\
	printf("%s", buf);\
}\
fclose(file);

int PrintArticlesFromFile(char startPath[], int ID)
{
	char id[10] = "";
	_itoa(ID, id, 10);
	char path[100] = "";
	strcat(path, startPath);
	strcat(path, id);
	strcat(path, ".txt");
	FilePrint
		return 0;
}

int PrintCodeFromFile(char startPath[], int ID)
{
	char id[10] = "";
	_itoa(ID, id, 10);
	char path[100] = "";
	strcat(path, startPath);
	strcat(path, id);
	strcat(path, "_Code.txt");
	FilePrint
		return 0;
}

int countPage = 0;
int LoadIDFromFile(char path[], int** ID)
{
	FILE* file;
	if ((file = fopen(path, "r+")) == NULL)
	{
		return 1;
	}

	int countLines = 0;
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
		{
			countLines++;
		}
	}
	countLines++;
	countPage = countLines / 2;

	rewind(file);

	if ((*ID = (int*)malloc(sizeof(int) * (countPage))) == NULL)
	{
		return 1;
	}

	for (int i = 0; i < countPage; i++)
	{
		char buf[31];
		fgets(buf, 10, file);
		(*ID)[i] = atol(buf);
		fgets(buf, 30, file);
	}

	fclose(file);
	return 0;
}

int LoadThemesFromFile(char path[], Page** page)
{
	FILE* file;
	if ((file = fopen(path, "r+")) == NULL)
	{
		return 1;
	}

	int countLines = 0;
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
		{
			countLines++;
		}
	}
	countLines++;
	countPage = countLines / 2;

	rewind(file);


	for (int i = 0; i < countPage; i++)
	{
		fscanf(file, "%s");
		fscanf(file, "%s", (*page)[i].name);
	}

	fclose(file);
	return 0;
}

int LoadCommentsFromFile(char path[], int ID, List* list)
{
	FILE* file;
	if ((file = fopen(path, "r+")) == NULL)
	{
		return 1;
	}

	int countLines = 0;
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
		{
			countLines++;
		}
	}
	countLines++;
	int countComments = countLines / 3;
	rewind(file);

	for (int i = 0; i < countComments; i++)
	{
		char buf_ch[31] = "";
		Comment buf;
		fgets(buf_ch, 10, file);
		buf.ID = atol(buf_ch);

		if (buf.ID == ID)
		{
			fscanf(file, "%s", buf.name);
			fgets(buf_ch, 10, file);
			fgets(buf.text, "%s", file);
			

			if (i != countComments - 1)
			{
				buf.text[strlen(buf.text) - 1] = 0;
			}

			PushBack(list, buf);
		}
		else
		{
			fgets(buf_ch, 30, file);
			fgets(buf_ch, 30, file);
		}
	}

	fclose(file);
	return 0;
}

void AddToHashTable(Page* page)
{
	int i = page->ID % PRIME_SIZE;
	while (hashTable.table[i] != NULL)
	{
		i = (i + 1) % PRIME_SIZE;
	}
	hashTable.table[i] = page;
}

int FindInHashTable(int key)
{
	int i = key % PRIME_SIZE;
	while (hashTable.table[i]->ID != key)
	{
		i = (i + 1) % PRIME_SIZE;
	}
	return i;
}

void ListInit(List** list)
{
	if ((*list = (List*)malloc(sizeof(List) * countPage)) == NULL) return 1;
	for (int i = 0; i < countPage; i++)
	{
		(*list)[i].head = NULL;
		(*list)[i].tail = NULL;
		(*list)[i].size = 0;
	}

}

int IDMenu(int* ID, int count)
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + count) % (count);

		for (int i = 0; i < count; i++)
		{
			if (key == i)
			{
				SetRed();
				printf(">%d\n", ID[i]);
				SetWhite();
			}
			else
			{
				printf("%d\n", ID[i]);
			}
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
	} while (code != 13);

	system("cls");

	return key;
}

int AddCommentToFile(Comment comm)
{
	FILE* file;
	if ((file = fopen(path4, "a+")) == NULL)
	{
		return 1;
	}

	fprintf(file, "\n%d\n", comm.ID);
	fprintf(file, "%s\n", comm.name);
	fprintf(file, "%s", comm.text);

	fclose(file);

	return 0;
}

int DeleteCommentFromeFile(int numComment, int tableIter)
{
	FILE* file = fopen(path4, "r");

	if (!file) return 1;

	int countLines = 0;
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
		{
			countLines++;
		}
	}
	countLines++;
	rewind(file);

	char id[10];
	_itoa(hashTable.table[tableIter]->ID, id, 10);

	char** buf = (char**)malloc(countLines * sizeof(char*));
	for (int i = 0; i < countLines; i++) {
		buf[i] = (char*)malloc(32 * sizeof(char));
	}

	for (int i = 0; i < countLines; i++)
	{
		fscanf(file, "%s", buf[i]);
	}

	fclose(file);

	file = fopen(path4, "w");

	int count = 0;
	for (int i = 0; i < countLines; i++)
	{
		if (!strcmp(buf[i], id))
		{
			if (count == numComment)
			{
				count = i;
			}
			count++;
		}
	}

	int first = 0;
	for (int i = 0; i < countLines; i++)
	{
		if (count == i + 1)
		{
			i += 3;
		}

		if (i < countLines)
		{
			if (first == 0)
			{
				fprintf(file, "%s", buf[i]);
			}
			else
			{
				fprintf(file, "\n%s", buf[i]);
			}
		}

		first++;
	}

	fclose(file);
	for (int i = 0; i < countLines; i++) {
		free(buf[i]);
	}
	free(buf);

	return 0;
}

int WriteCommentsToFile(List* listComm)
{
	char buf[32];

	FILE* file = fopen(path4, "w");

	if (!file) return 1;

	int first = 1;
	for (int i = 0; i < PRIME_SIZE; i++)
	{
		if (hashTable.table[i] != NULL && hashTable.table[i]->Comments->head != NULL)
		{
			WriteToFile(hashTable.table[i]->Comments, file, first);
			first++;
		}
	}

	fclose(file);

	return 0;
}




void PageLogic(int key, int tableIter, List* listComm)  //действия со статьей
{
	int numComment, n;
	Comment comm;
	Comment* selectComm;

	switch (key)
	{
	case 0:
		PrintArticlesFromFile(path3, hashTable.table[tableIter]->ID);
		getch();
		break;
	case 1:
		PrintCodeFromFile(path3, hashTable.table[tableIter]->ID);
		getch();
		break;
	case 2:
		numComment = PrintList(hashTable.table[tableIter]->Comments);

		if (numComment == -1) //esc
		{
			break;
		}

		if (numComment == hashTable.table[tableIter]->Comments->size) //Add comment
		{
			comm.ID = hashTable.table[tableIter]->ID;
			strcpy(comm.name, loginAcc.name);
			scanf("%s", comm.text);
			if (AddCommentToFile(comm)) exit(1);
			PushBack(hashTable.table[tableIter]->Comments, comm);
		}
		else //действие с выбранным комментом
		{
			selectComm = Get(hashTable.table[tableIter]->Comments, numComment);

			if ((n = CommentsMenu()) == 2) //Back
			{
				break;
			}

			switch (n)
			{
			case 0://edit
				scanf("%s", selectComm->text);
				if (WriteCommentsToFile(listComm)) exit(1);
				break;
			case 1://del
				Delete(hashTable.table[tableIter]->Comments, numComment);
				if (DeleteCommentFromeFile(numComment, tableIter)) exit(1);
				break;
			}

		}
		break;

	default:
		break;
	}
}

void SearchPage(Page* page, List* listComm) //поиск нужной статьи
{
	int* ID = (int*)malloc(sizeof(int) * countPage);
	int numID;
	char name[32];
	int id;
	int flag = 0;
	int ifContinue = 1;

	while (ifContinue)
	{
		int key = SearchMenu();
		flag = 0;
		ifContinue = 0;
		switch (key)
		{
		case 0: //поиск по названию
			flag = 1;
			printf(":");
			gets(name);
			int count = 0;
			for (int i = 0; i < countPage; i++)
			{
				if (strcmp(name, page[i].name) == 0)
				{
					ID[count] = page[i].ID;
					count++;
				}
			}
			if (count == 0)
			{
				printf("Not found");
				Sleep(1000);
				ifContinue = 1;
				break;
			}
			else//если нашло
			{
				numID = IDMenu(ID, count);
			}
		case 1: //логика ствтьи (страница сайта)
			if (flag)//если продолжение case 0
			{
				id = ID[numID];
			}
			else
			{
				for (int i = 0; i < countPage; i++)
				{
					ID[i] = page[i].ID;
				}
				numID = IDMenu(ID, countPage);
				id = ID[numID];
			}

			int tableIter = FindInHashTable(id);

			while (1)
			{
				if ((key = PageMenu()) == 3) //Back
				{
					ifContinue = 1;
					break;
				}
				else
				{
					system("cls");
					PageLogic(key, tableIter, listComm);
				}
			}
			break;
		default:
			break;
		}
	}
}

int main()
{
	system("chcp 1251");

	List* listComm;
	Page* page;
	Account* acc;
	int* ID = NULL;

	for (int i = 0; i < PRIME_SIZE; i++)
	{
		hashTable.table[i] = NULL;
	}

	if (LoadAccountsFromFile(path1, &acc))	return 1;

	if (LoadIDFromFile(path2, &ID))	return 1;

	if ((page = (Page*)malloc(sizeof(Page) * countPage)) == NULL) return 1;

	if (LoadThemesFromFile(path2, &page))	return 1;

	ListInit(&listComm);

	for (int i = 0; i < countPage; i++)
	{
		if (LoadCommentsFromFile(path4, ID[i], &listComm[i])) return 1;
		page[i].ID = ID[i];
		page[i].Comments = &listComm[i];
		AddToHashTable(&page[i]);
	}

	Authorization(path1, &acc);

	SearchPage(page, listComm);

	DeleteAll(listComm);
	free(acc);
	free(ID);
	free(page);

	getch();
}

