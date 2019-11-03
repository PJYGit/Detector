/*
	This file includes all the implementation of the functions in "utilities.h".
	The discription of all the functions can be seen in the .h file.
*/
#include "utilities.h"

int is_finished(int* A, int m, int id)
{
	int i;

	for (i = 0; i < m; i++)
	{
		if (A[(id - 1) * m + i] != 0)
			return 0;
	}

	return 1;
}

int can_allocate(int* R, int* U, int m, int id)
{
	int i;

	for (i = 0; i < m; i++)
	{
		if (R[(id - 1) * m + i] > U[i])
			return 0;
	}
	return 1;
}

int one_can_run(int* f, int* R, int* U, int m, int n)
{
	int i;
	int found = 0;

	for (i = n; i > 0; i--)
	{
		if (f[i - 1] == 0 && can_allocate(R, U, m, i) == 1)
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
		return i;
	else
		return 0;
}

int is_deadlock(int* f, int n)
{
	int j;
	for (j = 0; j < n; j++)
	{
		if (f[j] == 0)
			return 1;
	}
	return 0;
}

void init_T(int* T, int* U, int m)
{
	int j;
	for (j = 0; j < m; j++)
		T[j] = U[j];
}

void print_deadlock(int* f, int n)
{
	int j;
	int count = 0;
	for (j = 0; j < n; j++)
	{
		if (f[j] == 0)
			count++;
	}

	int temp = 1;
	for (j = 0; j < n; j++)
	{
		if (f[j] == 0)
		{
			if (temp != count)
				printf("%d ", j + 1);
			else
				printf("%d", j + 1);

			temp++;
		}
	}
}

void add_proc(int* target, int id, int n)
{
	int j;
	for (j = 0; j < n; j++)
	{
		if (target[j] == 0)
		{
			target[j] = id;
			break;
		}
	}
}

void init_to_zero(int* target, int n)
{
	int j;
	for (j = 0; j < n; j++)
	{
		target[j] = 0;
	}
}
