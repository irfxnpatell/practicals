#include<bits/stdc++.h>
using namespace std;

class MaxHeap{
    int *heap;
    int size;
    int capacity;

    void heapify(int idx){
        int largest = idx;
        int left = 2*idx + 1;
        int right = 2*idx + 2;

        if(left < size && heap[left] > heap[largest]){
            largest = left;
        }
        if(right < size && heap[right] > heap[largest]){
            largest = right;
        }

        if(largest != idx){
            swap(heap[largest], heap[idx]);
            heapify(largest);
        }
    }

public: 
    MaxHeap(int cap){
        this->capacity = cap;
        size = 0;
        heap = new int[capacity];
    }

    ~MaxHeap(){
        delete[] heap;
    }

    void insert(int val){
        if(size == capacity){
            cout<<"Heap is full"<<endl;
            return;
        }
        heap[size] = val;
        int currIdx = size-1;
        while(currIdx != 0){
            int parent = currIdx / 2;
            if(heap[parent] > heap[currIdx]){
                swap(heap[currIdx], heap[parent]);
                currIdx = parent;
            }
        }
        size++;
    }

    void buildHeap(int arr[], int n){
        if(n > capacity){
            return;
        }
        size = n;
        for(int i=0;i<size;i++){
            heap[i] = arr[i];
        }
        for(int i=(size/2)-1;i>=0;i--){
            heapify(i);
        }
    }

    int removeMax(){
        if(size == 0){
            return -1;
        }

        int root = heap[0];
        heap[0] = heap[size-1];
        size--;
        heapify(0);
        return root;
    }
};

void heapSort(int arr[], int n){
    MaxHeap h(n);
    h.buildHeap(arr, n);

    for(int i=n-1;i>=0;i--){
        arr[i] = h.removeMax();
    }
}

int main(){

    int arr[5] = {1, 2, 5, 8, 4};
    heapSort(arr, 5);
    for(int i : arr){
        cout<<arr[i]<<" ";
    }
    
    return 0;
}