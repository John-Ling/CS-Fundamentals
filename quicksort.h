int quicksort(int arr[], const int n);
static int sort(int arr[], const int lowerIndex, const int upperIndex);
static int lomuto_partition(int arr[], const int lowerIndex, const int upperIndex);
static int first_item_pivot(const int n);
static int last_item_pivot(const int n);
static int middle_item_pivot(const int n);
static int random_pivot(const int n);
static int median_of_three(int arr[], const int n);


static int (*select_pivot)(const int) = &middle_item_pivot;