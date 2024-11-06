#include <iostream>
#include "Heap.h"

Heap::Heap(int capacity) {

    this->capacity = capacity;
    this->size = 0;
    this->arr = new int[capacity];

}

Heap::~Heap() { 

    delete [] arr;
    
}

// Aqui se define si vamos a mantener el heap como min heap o max heap en este caso esta realizando un min heap 

void Heap::push(int val) {

    if (size==capacity) {

        cout << "Heap is full capacity" << endl;
        int *arr_tmp = new int[capacity*2];

        for(int i=0; i<capacity; i++) {

            arr_tmp[i] = arr[i];

        }

        delete [] arr;
        arr = arr_tmp;
        capacity *= 2;

    }

    arr[size] = val;
    size++;
    int i = size-1;

    while(i != 0 && arr[i] < arr[(i-1)/2]) { 

        int temp = arr[i]; 
        arr[i] = arr[(i-1)/2];
        arr[(i-1)/2] = temp;
        i = (i-1)/2;

    }

}

int Heap::pop() {

    if (size == 0) {

        return -1;

    }

    int val = arr[0]; // Retornamos la raiz
    arr[0] = arr[size-1]; // Ponemos el ultimo elemento en la raiz
    size--; // Disminuimos el tamaño
    int i = 0;

    while(2*i+1 < size) {

        int left = 2*i+1;
        int right = 2*i+2;
        int min = left;

        if (right < size && arr[right] < arr[left]) {

            min = right;

        }

        if (arr[i] < arr[min]) {

            break; // Ya esta ordenado

        }

        int temp = arr[i]; // Si no cuple orden entonces hacemos el swap
        arr[i] = arr[min];
        arr[min] = temp;
        i = min;
        
    }

    return val;
}