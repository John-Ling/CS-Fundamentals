int naive_quicksort(int arr[], int n);
int partition(int arr[], int n);
static int first_item_pivot(int arr[], const int n);
static int last_item_pivot(int arr[], const int n);
static int middle_item_pivot(int arr[], const int n);
static int random_pivot(int arr[], const int n);
static int median_of_three(int arr[], const int n);


static int (*select_pivot)(int[], int) = &median_of_three;