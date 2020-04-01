#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t MyStrlen(char* str)
{
	size_t i = 0;

	while (str[i])
	{
		i++;
	}

	return i;
}

int NumberDelimiter(char* str)
{

	char* extrastr = (char*)malloc(5 * sizeof(char));

	extrastr = "+-*/\0";

	size_t j = 0;

	for (size_t i = 0; i < MyStrlen(extrastr); i++)
	{

		while (str[j] != extrastr[i] && j<MyStrlen(str))
		{
			j++;
		}


		if (str[j] == extrastr[i])
		{
			break;
		}
		else
		{
			j = 0;
		}
	}

	char* temp = (char*)malloc(100 * sizeof(char));

	for (size_t i = 0; i < j; i++)
	{
		temp[i] = str[i];
	}

	temp[j] = '\0';

	int num = 0;

	for (size_t i = 0; i < j; i++)
	{
		num *= 10;

		num += temp[i] - '0';


	}

	char* str2 = (char*)malloc(100 * sizeof(char));
	
	for (size_t i = 0; i < MyStrlen(str); i++)
	{
		str2[i] = str[i];
	}

	str2[MyStrlen(str)] = '\0';

	for (int i = 0; j< MyStrlen(str); j++, i++)
	{
		str[i] = str2[j];
	}

	str[MyStrlen(str)] = '\0';

	free(str2);

	free(temp);

	return num;


}

int main(void)
{
	char* str = (char*)malloc(100* sizeof(char));

	const int numbers_size, signs_size;

	//char sign[5] = { '+','-','*','/','\0' };

	//gets(str);

	////puts(str);

	//for (size_t i = 0, len = strlen(str); i < len; i++)
	//{

	//	int a, b;

	//	if (str[i] == '/' || str[i] == '*')
	//	{
	//		a = str[i - 1] - '0';

	//		b = str[i + 1] - '0';

	//		size_t k;

	//		for (k = 0; k < 5; k++)
	//		{
	//			size_t j;

	//			for (j = i - 1; j > 1; j--)
	//			{

	//				if (str[j] = !sign[k])
	//				{
	//					break;
	//				}

	//				a += 10*(str[j - 1] - '0');

	//			}
	//			
	//		}

	//		k = 0;
	//
	//		for (k = 0; k < 5; k++)
	//		{
	//			size_t j;

	//			for (j = i + 1; ; j++)
	//			{
	//				b *= 10;
	//				b += str[j + 1] - '0';

	//				if (str[j] = !sign[k])
	//				{
	//					break;
	//				}

	//			}
	//		}

	//		if (str[i] == '/')
	//		{

	//			str[i - 1] = (a / b) + '0';

	//		}
	//		else
	//		{
	//			str[i - 1] = (a * b) + '0';
	//		}
	//		for (int m = i; m < len; m++)
	//		{
	//			str[m] = str[m + 2];
	//		}

	//		i = 0;
	//	}

	//}

	//puts(str);

	//delete[] str;

	gets(str);

	printf_s("%d", NumberDelimiter(str));

	//puts(str);

	free(str);

	return 0;
}

