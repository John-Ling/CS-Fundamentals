#ifndef Quicksort_H
#define Quicksort_H
#include <stdio.h>
#include <stdlib.h>

int quicksort(int arr[], const int n);
static int sort(int arr[], const int lowerIndex, const int upperIndex);
static int lomuto_partition(int arr[], const int lowerIndex, const int upperIndex);
static int hoare_partition(int arr[], const int lowerIndex, const int upperIndex);
static int first_item_pivot(const int n);
static int last_item_pivot(const int n);
static int middle_item_pivot(const int n);
static int random_pivot(const int n);
static int median_of_three(int arr[], const int n);


static int (*select_pivot)(const int) = &middle_item_pivot;
void swap(int* a, int* b);
#endif