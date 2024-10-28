#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// implementation of bogosort greatest algorithm yes yes for learning purposes

int is_sorted(int arr[], int n);

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("run ./bogosort N\n");
		return EXIT_FAILURE;
	}
	const int N = atoi(argv[1]);

	printf("LET'S GO GAMBLING\n");
	srand(time(NULL));
	int arr[N];

	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % 1000;
	}

	unsigned long long iterations = 0;
	while (1)
	{
		// shuffle
        iterations++;
        if (is_sorted(arr, N))
        {
            break;
        }
        
		for (int i = 0; i < N-1; i++)
		{
			int j = rand() % (N - i) + i;
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		for (int i = 0; i < N; i++)
		{
			printf("%3d ", arr[i]);
        }
        printf("AWW DANG IT\n");
		
	}
	printf("LETS GO!!!!!\n");
    printf("Completed in %llu iterations\n", iterations);
	return EXIT_SUCCESS;
}

int is_sorted(int arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}