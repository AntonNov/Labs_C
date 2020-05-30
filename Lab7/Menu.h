#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Colors.h"

int CommentsMenu()
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + 3) % 3;

		if (key == 0)
		{
			SetRed();
			puts(">Edit");
			SetWhite();
		}
		else
		{
			puts("Edit");
		}
		if (key == 1)
		{
			SetRed();
			puts(">Delete");
			SetWhite();
		}
		else
		{
			puts("Delete");
		}
		if (key == 2)
		{
			SetRed();
			puts(">Back");
			SetWhite();
		}
		else
		{
			puts("Back");
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

int LoginMenu()
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + 2) % 2;

		if (key == 0)
		{
			SetRed();
			puts(">Login");
			SetWhite();
		}
		else
		{
			puts("Login");
		}
		if (key == 1)
		{
			SetRed();
			puts(">Register");
			SetWhite();
		}
		else
		{
			puts("Register");
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

int SearchMenu()
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + 2) % 2;

		if (key == 0)
		{
			SetRed();
			puts(">Search topic");
			SetWhite();
		}
		else
		{
			puts("Search topic");
		}
		if (key == 1)
		{
			SetRed();
			puts(">Open topic");
			SetWhite();
		}
		else
		{
			puts("Open topic");
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

int PageMenu()
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + 4) % 4;

		if (key == 0)
		{
			SetRed();
			puts(">Article");
			SetWhite();
		}
		else
		{
			puts("Article");
		}
		if (key == 1)
		{
			SetRed();
			puts(">Code");
			SetWhite();
		}
		else
		{
			puts("Code");
		}
		if (key == 2)
		{
			SetRed();
			puts(">Comments");
			SetWhite();
		}
		else
		{
			puts("Comments");
		}
		if (key == 3)
		{
			SetRed();
			puts(">Back");
			SetWhite();
		}
		else
		{
			puts("Back");
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