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
    }
    for (int i=0;i<=63;i++){
        if (mask[i/8]>>(7-i%8)&1)
            cout<<i<<" ";
    }
}
void task_3a() {
    unsigned long long mask[156250];
    for (int i=0;i<156250;i++)
        mask[i]=0;               // инициализируем массив 0
    vector <int> arr;
    for (int i=1000000;i<9999999;i++) {
        arr.push_back(i);       // заполняем вектор семизначными числами
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(),arr.end(),g);        // перемешиваем их
    ofstream fout;
    fout.open("a.txt");
    for (int i=0;i<arr.size();i++) {
        fout<<arr[i]<<"\n";              // записываем числа в файл
    }
    fout.close();
    ifstream fin;
    fin.open("a.txt");      // открываем файл а
    int x;
    unsigned int start_time =  clock();  // начальное время
    for (int i = 0; i < 8000000; ++i) {
        fin>>x;
        mask[(x)/64]= mask [(x)/64] | ((unsigned long long)1<<63-x%64);     // устанавливаем в mask 1  в нужный разряд
    }
    fin.close();
    ofstream fout1;
    fout1.open("b.txt");
    for (int i=1000000;i<=9999999;i++){
        if (mask[i/64]>>(63-i%64)&(unsigned long long)1) {
            fout1<<int(i)<<"\n";                // вводим в файл номер разряда если в нем установлена 1
        }
    }
    cout<<"Память занимаемая массивом: "<<sizeof (mask)/1024.0/1024.0<<" Мб"<<endl;
    cout<<"Время работы: " <<(clock() - start_time) / CLOCKS_PER_SEC<<"c.";     // выводим время работы программы в секундах
}

int main() {
    task_1a();
    task_1b();
    task_1v();
    task_2a();
    task_2b();
    task_2v();
    task_3a();

}
