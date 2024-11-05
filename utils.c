void swap(int* a, int* b)
{
    int c = *b;
    *b = *a;
    *a = c;
    return;
}