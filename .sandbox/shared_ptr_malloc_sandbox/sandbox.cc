
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

int main(){
    int SIZE = 4;
    shared_ptr<void> data(malloc(sizeof(int) * SIZE), free);

    for (int i = 0; i < SIZE; ++i){
        cout << i << " ";
        ((int*) data.get())[i] = 10 * i + 1;
    }
    cout << endl;

    for (int i = 0; i < SIZE; ++i){
        cout << ((int*) data.get())[i] << endl;
    }
}
