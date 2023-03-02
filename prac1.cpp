#include <iostream>
#include <bitset>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
using namespace std;

void task_1a(){
    unsigned char x=255;         //8-разрядное двоичное число 11111111
    unsigned char maska=1;       //1=00000001 – 8-разрядная маска
    x=x&(~(maska<<4));           //Результат x=239
    cout<<"Результат: "<<int(x)<<endl<<"Результат: "<<bitset<8>(x);          // Вывод результата
}
void task_1b(){
    unsigned char x=12;     //8-разрядное двоичное число 11111111
    unsigned char maska=1;    //1=00000001 – 8-разрядная маска
    x=x|((maska<<6));    //Результат x=64 (01000000)
    cout<<"Результат: "<<int(x)<<endl<<"Результат: "<<bitset<8>(x);          // Вывод результата

}
void task_1v(){
    unsigned int x=55;
    const int n =sizeof(int)*8; // =32 - количество рязрядов в числе типа int
    unsigned maska=(1<<n-1); // уставливаем 1 в старший разряд
    cout<<"начальный вид маски: "<<bitset<n>(maska)<<endl;
    cout<<"Результат: ";
    for(int i=1; i<=n;i++){
        cout<<((x&maska)>>(n-i));   // если в текущем разряде числа 1 то выводим 1, если 0, то выводим 0
        maska=maska>>1;        // сдвигаем маску на 1 бит влево
    }
    cout<<endl;
}
void task_2a(){
    int n;
    cin>>n;   // вводим количество элементов
    unsigned char mask=0;
    int x;
    for (int i=0;i<n;i++) {
        cin>>x;      // вводим число
        mask = mask | (1<<7-x);   // устанавливаем в mask 1  в нужный разряд
    }
    cout<<"Отсортированный массив: ";
    for (int i=0;i<8;i++){
        if (mask>>(7-i)&1)
            cout<<i<<" ";   // выводим номер разряда если в нем установлена 1
    }
}
void task_2b(){
    int n;
    cin>>n;
    int x;
    unsigned long long mask=0;
    for (int i=0;i<n;i++) {
        cin>>x;
        mask = mask | ((unsigned long long)1<<63-x);
    }
    cout<<"Отсортированный массив: ";
    for (int i=0;i<=63;i++){

        if (mask>>(63-i)&(unsigned long long)1)
            cout<<i<<" ";

    }
}
void task_2v(){
    int n;
    cin>>n;
    int x;
    unsigned char mask[8]={0,0,0,0,0,0,0,0};
    for (int i=0;i<n;i++) {
        cin>>x;
        mask[(x)/8]= mask [(x)/8]| (1<<7-x%8);
