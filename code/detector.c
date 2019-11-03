/*
detector.c

Student Name : Jiayao Pang
Student ID # : 194174300

*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1000

/*
Any required standard libraries and your header files here
*/
#include "utilities.h"
#include <stdlib.h>

void detector(FILE *fd){
    /*
        Your code here.
        You may edit the following code
    */
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    
    int n, m;

	int i, j;
	int temp;
    //Processs first line
    fgets(line_buffer, MAX_LINE_LENGTH, fd);
    sscanf(line_buffer, "%d %d",&n, &m);

	// ask memory for arrays to store the data
	int* R = malloc(sizeof(int) * n * m);
	int* A = malloc(sizeof(int) * n * m);
	int* U = malloc(sizeof(int) * m);
	int* T = malloc(sizeof(int) * m);
	int* f = malloc(sizeof(int) * n);

	int* sequence = malloc(sizeof(int) * n);
	int* terminated = malloc(sizeof(int) * n);
	init_to_zero(sequence, n);
	init_to_zero(terminated, n);
 
    //Process remaining lines
    // init R
	for (i = 0; i < n; i++)
	{
		fgets(line_buffer, MAX_LINE_LENGTH, fd);
		for (j = 0; j < m; j++)
		{
			if (j == 0)
				token = strtok(line_buffer, " ");
			else
				token = strtok(NULL, " ");

			sscanf(token, "%d", &temp);
			R[i * m + j] = temp;
		}
	}
	// init A
	for (i = 0; i < n; i++)
	{
		fgets(line_buffer, MAX_LINE_LENGTH, fd);
		for (j = 0; j < m; j++)
		{
			if (j == 0)
				token = strtok(line_buffer, " ");
			else
				token = strtok(NULL, " ");

			sscanf(token, "%d", &temp);
			A[i * m + j] = temp;
		}
	}
	// init U & T
	fgets(line_buffer, MAX_LINE_LENGTH, fd);
	for (j = 0; j < m; j++)
	{
		if (j == 0)
			token = strtok(line_buffer, " ");
		else
			token = strtok(NULL, " ");

		sscanf(token, "%d", &temp);
		U[j] = temp;
		T[j] = temp;
	}
	// init f
	for (i = 0; i < n; i++)
		f[i] = is_finished(A, m, i + 1);

	// deadlock detection
	int proc = one_can_run(f, R, T, m, n);
	while (proc)
	{
		add_proc(sequence, proc, n);
		for (j = 0; j < m; j++)
		{
			T[j] += A[(proc - 1) * m + j];
		}
		f[proc - 1] = 1;
		proc = one_can_run(f, R, T, m, n);
	}

	// if not deadlock
	if (!is_deadlock(f, n))
	{
		// print the sequence
		for (j = 0; j < n; j++)
		{
			if (j == n - 1)
				printf("%d", sequence[j]);
			else
				printf("%d ", sequence[j]);
		}
		printf("\n");
	}
	// if deadlock -> deadlock correction
	else
	{
		// print the processors involved in the deadlock
		print_deadlock(f, n);

		// try to terminate one or more processors
		init_T(T, U, m);
		for (i = n; i > 0; i--)
		{
			// processor with the largest number in the deadlock
			if (f[i - 1] == 0)
			{
				// terminated it
				for (j = 0; j < m; j++)
				{
					T[j] += A[(i - 1) * m + j];
				}
				f[i - 1] = 1;
				add_proc(terminated, i, n);

				// deadlock detection again
				proc = one_can_run(f, R, T, m, n);
				while (proc)
				{
					add_proc(sequence, proc, n);
					for (j = 0; j < m; j++)
					{
						T[j] += A[(proc - 1) * m + j];
					}
					f[proc - 1] = 1;
					proc = one_can_run(f, R, T, m, n);
				}
				// if deadblock corrected
				if (!is_deadlock(f, n))
				{
					// print the terminated processors
					printf("\n");
					for (j = 0; j < n; j++)
					{
						if (terminated[j])
						{
							if (j == 0)
								printf("%d", terminated[j]);
							else
								printf(" %d", terminated[j]);
						}
					}
					// print the sequence
					printf("\n");
					for (j = 0; j < n; j++)
					{
						if (sequence[j])
						{
							if (j == 0)
								printf("%d", sequence[j]);
							else
								printf(" %d", sequence[j]);
						}
					}
					printf("\n");

					break;
				}
			}
		}
	}
	
}