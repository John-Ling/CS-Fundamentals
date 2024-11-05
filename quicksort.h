int quicksort(int arr[], const int n, int lower, int upper);
int naive_quicksort(int arr[], int n);
static int lomuto_partition(int arr[], int lower, int upper);
static int partition(int arr[], const int n, int lower, int upper);
static int first_item_pivot(const int n);
static int last_item_pivot(const int n);
static int middle_item_pivot(const int n);
static int random_pivot(const int n);
static int median_of_three(int arr[], const int n);


static int (*select_pivot)(const int) = &middle_item_pivot;