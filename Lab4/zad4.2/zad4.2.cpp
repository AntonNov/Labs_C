#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define FILENAME "MyFile.txt"
#define MAXSTRLEN 80

void ToLower(char* c)
{
	if (*c >= 'A' && *c <= 'Z')
	{
		*c += 32;
	}

}
size_t Mystrlen(const char* string)
{
	size_t i = 0;
	while (string[i] && string[i]!='\n')
	{
		i++;
	}
	return i;
}
void InsertSort(char * string) {
	
	for (int i = 1, len = Mystrlen(string); i < len; i++) {
		char x = string[i]; 
		int j = i - 1;
		while (x < string[j]) { 
			string[j + 1] = string[j];
			j--;
			if (j < 0) break; 
		}
		string[j + 1] = x; 
	}
}
char  **CreateArray(char **pointer, size_t counter_of_strings)
{
	pointer = (char**)malloc(counter_of_strings * sizeof(char*));

	if (!pointer)
	{
		printf_s("Memory allocation error");

		exit(1);
	}

	for (size_t i = 0; i < counter_of_strings; i++)
	{
		pointer[i] = (char*)malloc(sizeof(char) * MAXSTRLEN);
	}
	return pointer;
}
void DeleteArray(char **pointer, size_t counter_of_strings)
{
	for (size_t i = 0; i < counter_of_strings; i++)
	{
		free(pointer[i]);
	}
	free(pointer);
}
void Mystrcpy(char *destination, const char *source)
{
	size_t k = 0;
	for (size_t len = Mystrlen(source); k < len; k++)
	{
		destination[k] = source[k];
		ToLower(&destination[k]);
	}
	destination[k] = '\n';
	destination[k+1] = '\0';
	
}

int Equals(const char* string1, const char * string2)
{
	if (Mystrlen(string1) == Mystrlen(string2))
	{
		for (size_t i = 0, len = Mystrlen(string1); i < len; i++)
		{
			if (i = len - 1 && string1[i] == string2[i])
			{
				return 1;/*True*/
			}
			if (string1[i] == string2[i])
			{
				continue;
			}
			return 0;/*False*/
		}
	}
	return 0; /*False*/
}
int main(void)
{
	
	FILE* f;
	if ((f = fopen(FILENAME, "rt")) == NULL)
	{
		printf_s("Cannot open file.");
		exit(1);
	}
	else {
		if (fgetc(f) == EOF)
		{/* Если файл пустой*/
			printf_s("File is empty");
			exit(1);
			
		}
		rewind(f);
		char string[MAXSTRLEN];
		size_t counter_of_strings = 0;
		while (!feof(f))
		{
			fgets(string, MAXSTRLEN-1 , f);
			counter_of_strings++;	
		}

		rewind(f);

		char** dictionary = NULL; 
		char** dictionary_copy = NULL;
	
		dictionary = CreateArray(dictionary, counter_of_strings);

		dictionary_copy = CreateArray(dictionary_copy, counter_of_strings);

		for (size_t i = 0; i < counter_of_strings; i++)
		{
			fgets(dictionary[i], MAXSTRLEN - 1, f);

			Mystrcpy(dictionary_copy[i], dictionary[i]);
		}
		for (size_t i = 0; i < counter_of_strings; i++)
		{
			InsertSort(dictionary_copy[i]);
		}
		int* array = (int*)malloc(sizeof(int) * counter_of_strings);

		if (!array)
		{
			printf_s("Memory allocation error");

			exit(1);
		}
		
		*array = 0;

		for (size_t i = 0; i < counter_of_strings-1; i++)
		{
			for (size_t j = i+1; j < counter_of_strings; j++)
			{
				if (Equals(dictionary_copy[i], dictionary_copy[j]))
				{
					array[i]++;
					array[j]++;
				}
			}
		}
		printf_s("Group of words:\n");

		for (size_t i = 0; i < counter_of_strings; i++)
		{
			if (array[i])
			{
				printf_s("%s", dictionary[i]);

			}
		}
		
		DeleteArray(dictionary, counter_of_strings);
		DeleteArray(dictionary_copy, counter_of_strings);
		free(array);
		fclose(f);
	}
}
