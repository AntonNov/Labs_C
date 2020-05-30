#pragma once

typedef struct Account
{
	char name[20];
	long long passwordHash;

}Account;
Account loginAcc;