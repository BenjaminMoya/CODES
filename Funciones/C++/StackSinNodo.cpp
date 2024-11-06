#include <iostream>
using namespace std;

//Recreando una cola de stack mediante objetos

class Stack{

    public:

        int *data;
        int size;
        int top;

    Stack(int i){

        data = new int[i];//New crea memoria para objetos de tamaño i (Reemplaza el MALLOC)
        size = i;
        top = -1;
    }
    ~Stack(){//Todo destructor que libera memoria del sistema debe tener en un comienzo una ~

        delete[] data;//Reemplaza la funcion free
    }
    bool isEmpty(){
        return (top==-1);
    }
    void push(int i){
        if(top==size-1){
            int *data_tmp= new int[size*2];
            for(int n=0;n<size;n++){

                data_tmp[n]=data[n];
            }
            delete[] data;
            data=data_tmp;
            size*=2;
        }
        ++top;
        data[top]=i;
    }

    int pop(){

        if(isEmpty()){
            cout << "Stack Overflow" << endl;
            return -1;
        }
        return data[top--];
    }
};

int main(){

    Stack *s = new Stack(100);
    cout << "Vacio? " << s->isEmpty() << endl;
    for (int i=0; i<100; i++){

        s->push(i);
        cout << "Push" << i << "Cantidad: " << s->top+1 << endl;

    }
    for (int i=0; i<100; i++){

        int x=s->pop();
        cout << "pop"<< x << "Cantidad: " << s->top+1 << endl;
    }
}