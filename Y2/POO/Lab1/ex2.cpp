#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Sorter
{
public:

    void interschimbare(int arr[], int n)
    {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[i] <= arr[j])
                    swap(arr[i], arr[j]);
    }

    void bubbleSort(int arr[], int n){
        int swapped;
        for(int i=0;i<n-1;i++)
        {
            swapped = 0;
            for(int j=0;j<n-1;j++)
                if(arr[j] < arr[j+1])
                {
                    swap(arr[j],arr[j+1]);
                    swapped = 1;
                }
            if(!swapped)
                break;        
        }         
    }

    void insertionSort(int arr[], int n)
    {
        int temp;
        for(int i=1;i<n;i++)
            for(int j=0;j<i;j++)
                if(arr[i] > arr[j])
                    {
                        temp = arr[i];
                        for(int k = i; k > j; k--)
                            arr[k]=arr[k-1];
                        arr[j]=temp;
                    }
    }

    void merge(int arr[], int left,int middle, int right)
    {
        int leftLength = middle - left + 1;
        int rightLength = right - middle;
        int *leftArray= (int*)malloc(sizeof(int)*(size_t)leftLength);
        int *rightArray=(int*)malloc(sizeof(int)*(size_t)rightLength);

        for(int i=0;i<leftLength;i++)
            leftArray[i]=arr[left+i];

        for(int i=0;i<rightLength;i++)
            rightArray[i]=arr[middle+i+1];
            
        int i = 0, j = 0;

        while( i <  leftLength && j < rightLength)
        {
            if(leftArray[i] > rightArray[j]){
                arr[left++]= leftArray[i++];
            }
            else {
                arr[left++] = rightArray[j++];
            }
        }

        while (i < leftLength){
            arr[left++]=leftArray[i++];
        }

        while (j< rightLength){
            arr[left++]=rightArray[j++];
        }

        free(leftArray);
        free(rightArray);
    }
    void mergeSort(int arr[], int left, int right)
    {
        if(left < right)
        {
            int middle = (left+right)/2;
            mergeSort(arr,left,middle);
            mergeSort(arr,middle+1,right);
            merge(arr,left,middle,right);
        }
    }

    int partition(int arr[], int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (arr[j] > pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quickSort(int arr[], int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(arr, low, high);
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }

    void printArray(int arr[], int n)
    {
        int i;
        for (i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    int arr[5] = {40, 8, 11, 2, 99};
    int n = 5;
    Sorter sorting;
    sorting.bubbleSort(arr, n);
    sorting.printArray(arr, n);

    return 0;
}
