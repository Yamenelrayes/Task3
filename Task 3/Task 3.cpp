#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdlib>
using namespace std::chrono;
using namespace std;

// This function adjusts the heap by finding the smallest child and swapping it to the parent position if necessary
int heapify(int arr[], int n, int i, int count = 0) {
    int minimum = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    // Here im comparing the left child with the current smallest to find the actual smallest.
    if (leftChild < n && arr[leftChild] < arr[minimum]) {
        minimum = leftChild;
        count++;
    }

    // Now im doing the same with the right child.
    if (rightChild < n && arr[rightChild] < arr[minimum]) {
        minimum = rightChild;
        count++;
    }

    // If the smallest isn't the current node, swap and continue heapifying.
    if (minimum != i) {
        swap(arr[i], arr[minimum]);
        heapify(arr, n, minimum, count);
    }

    return count;
}

// This function builds the heap from an unsorted array
int build_heap(int arr[], int n) {
    int count = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Im building the heap by calling heapify for each parent node, starting from the bottom
        count += heapify(arr, n, i);
    }
    return count;
}

// This function performs heap sort and counts the number of comparisons
int heap_sort(int arr[], int n) {
    int count = build_heap(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        // The largest element (at the root) is placed at the end of the array.
        swap(arr[0], arr[i]);
        // Reduce the heap size by one and reheapify.
        count += heapify(arr, i, 0);
    }

    return count;
}

// This function just wraps the heap_sort function
int heap_sort_count(int arr[], int n) {
    return heap_sort(arr, n);
}

// Here I implemented the bubble sort algorithm, which counts the comparisons.
int bubble_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return count;
}

// This function uses selection sort to sort the array and count the number of comparisons
int selection_sort_count(int arr[], int n) {
    int i, j, MinimumIndex, count = 0;

    for (i = 0; i < n - 1; i++) {
        MinimumIndex = i;
        for (j = i + 1; j < n; j++) {
            count++;
            if (arr[j] < arr[MinimumIndex])
                MinimumIndex = j;
        }
        if (MinimumIndex != i)
            swap(arr[MinimumIndex], arr[i]);
    }
    return count;
}

// This function implements insertion sort and counts the comparisons
int insertion_sort_count(int arr[], int n) {
    int count = 0, i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        // The following comparison determines whether to insert the element at this position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            count++;
        }
        arr[j + 1] = key;
    }

    return count;
}

// This function tests and records the number of comparisons made by each sorting algorithm on different array types
void number_of_comparisons() {
    ofstream file("number_of_comparisons.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    file << "n,Heap Sort,Bubble Sort,Insertion Sort,Selection Sort\n";
    cout << "   " << "n" << "       " << "Heap Sort" << "       " << "Bubble Sort" << "       " << "Insertion Sort" << "       " << "Selection Sort" << endl;

    // I'm testing on arrays of increasing size to see how the number of comparisons scales
    for (int n = 1; n <= 30; n++) {
        int* random_arr = new int[n];
        int* sorted_arr = new int[n];
        int* inverse_arr = new int[n];

        // Generating random, sorted, and inversely sorted arrays for each size
        for (int i = 0; i < n; i++) {
            random_arr[i] = rand() % 150 + 1;
            sorted_arr[i] = i + 1;
            inverse_arr[i] = n - i;
        }

        // Running each sort on each type of array and recording the number of comparisons
        int heap_random = heap_sort_count(random_arr, n);
        int bubble_random = bubble_sort_count(random_arr, n);
        int insertion_random = insertion_sort_count(random_arr, n);
        int selection_random = selection_sort_count(random_arr, n);

        int heap_sorted = heap_sort_count(sorted_arr, n);
        int bubble_sorted = bubble_sort_count(sorted_arr, n);
        int insertion_sorted = insertion_sort_count(sorted_arr, n);
        int selection_sorted = selection_sort_count(sorted_arr, n);

        int heap_inverse = heap_sort_count(inverse_arr, n);
        int bubble_inverse = bubble_sort_count(inverse_arr, n);
        int insertion_inverse = insertion_sort_count(inverse_arr, n);
        int selection_inverse = selection_sort_count(inverse_arr, n);

        // Printing and saving results to a CSV file for later analysis
        cout << "   " << n << "       " << heap_random << "       " << bubble_random << "       " << insertion_random << "       " << selection_random << endl << endl;
        cout << "   " << n << "       " << heap_sorted << "       " << bubble_sorted << "       " << insertion_sorted << "       " << selection_sorted << endl << endl;
        cout << "   " << n << "       " << heap_inverse << "       " << bubble_inverse << "       " << insertion_inverse << "       " << selection_inverse << endl << endl;
        file << n << "," << heap_random << "," << bubble_random << "," << insertion_random << "," << selection_random << "\n";
        file << n << "," << heap_sorted << "," << bubble_sorted << "," << insertion_sorted << "," << selection_sorted << "\n";
        file << n << "," << heap_inverse << "," << bubble_inverse << "," << insertion_inverse << "," << selection_inverse << "\n";

        // Cleaning up 
        delete[] random_arr;
        delete[] sorted_arr;
        delete[] inverse_arr;
    }
    file.close(); 
}

// Similar to number_of_comparisons this function measures the execution time of each sort
void execution_time() {
    ofstream file("execution_time.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }
    file << "n,Heap Sort,Bubble Sort,Insertion Sort,Selection Sort\n";
    cout << "   " << "n" << "       " << "Heap Sort" << "       " << "Bubble Sort" << "       " << "Insertion Sort" << "       " << "Selection Sort" << endl;

    for (int n = 1; n <= 30; n = n + 1) {
        int* random_arr = new int[n];
        int* sorted_arr = new int[n];
        int* inverse_arr = new int[n];

        for (int i = 0; i < n; i++) {
            random_arr[i] = rand() % 150 + 1;
            sorted_arr[i] = i + 1;
            inverse_arr[i] = n - i;
        }

        auto startHeap = chrono::high_resolution_clock::now();
        heap_sort_count(random_arr, n);
        auto endHeap = chrono::high_resolution_clock::now();
        double heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        auto startBubble = chrono::high_resolution_clock::now();
        bubble_sort_count(random_arr, n);
        auto endBubble = chrono::high_resolution_clock::now();
        double bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        auto startInsert = chrono::high_resolution_clock::now();
        insertion_sort_count(random_arr, n);
        auto endInsert = chrono::high_resolution_clock::now();
        double insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        auto startSelect = chrono::high_resolution_clock::now();
        selection_sort_count(random_arr, n);
        auto endSelect = chrono::high_resolution_clock::now();
        double selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        startHeap = chrono::high_resolution_clock::now();
        heap_sort_count(sorted_arr, n);
        endHeap = chrono::high_resolution_clock::now();
        heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        startBubble = chrono::high_resolution_clock::now();
        bubble_sort_count(sorted_arr, n);
        endBubble = chrono::high_resolution_clock::now();
        bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        startInsert = chrono::high_resolution_clock::now();
        insertion_sort_count(sorted_arr, n);
        endInsert = chrono::high_resolution_clock::now();
        insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        startSelect = chrono::high_resolution_clock::now();
        selection_sort_count(sorted_arr, n);
        endSelect = chrono::high_resolution_clock::now();
        selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        startHeap = chrono::high_resolution_clock::now();
        heap_sort_count(inverse_arr, n);
        endHeap = chrono::high_resolution_clock::now();
        heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        startBubble = chrono::high_resolution_clock::now();
        bubble_sort_count(inverse_arr, n);
        endBubble = chrono::high_resolution_clock::now();
        bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        startInsert = chrono::high_resolution_clock::now();
        insertion_sort_count(inverse_arr, n);
        endInsert = chrono::high_resolution_clock::now();
        insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        startSelect = chrono::high_resolution_clock::now();
        selection_sort_count(inverse_arr, n);
        endSelect = chrono::high_resolution_clock::now();
        selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        delete[] random_arr;
        delete[] sorted_arr;
        delete[] inverse_arr;
        file << n << "," << heap << "," << bubble << "," << insertion << "," << selection << "\n";

    }
    file.close();

}

int main() {
    cout << "Comparison Time:\n\n";
    number_of_comparisons();

    cout << "\n\n\nExecution time:\n\n";
    execution_time();

    cout << "\n Results have also been saved to the csv files";

    return 0;
}