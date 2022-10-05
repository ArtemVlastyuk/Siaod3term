#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
using namespace std;
class polic{
private:
    int num;     //Номер полиса(ключ)
    string company;     // Компания
    string surname;     //Фамилия владельца
    bool del=0;//хранит информацию о том удаленна ли ячейна
public:
    bool isDel() const {         //возвращает информацию о том удаленна ли ячейка
        return del;
    }

    void setDel(bool del) {
        polic::del = del;
    }

    int getNum() const {      //возвращаем номер полиса
        return num;
    }
    void setNum(int num) {       // устанавливает номер полиса
        polic::num = num;
    }

    polic(int num, string company, string surname) : num(num), company(std::move(company)), surname(std::move(surname)) {}
    void print(){   //вывод записи
        cout<<this->num<<"\t\t"<<this->company<<"\t\t"<<this->surname<<"\t\t"<<endl;}
};
class hesh{       //Хранит хэш таблицу
private:
    polic **arr;       //Массив указателей на объекты класса polic
    int size;          // размер таблицы
    int cur_size;    // количество записей в таблице
public:
    hesh(int s){
        this->size=s;
        this->cur_size=0;
        arr=new polic * [size];

    }
    int hash_funct(int key){ return key % size;};     //хэш функция
    bool del(int key){                        // Удаление записи из таблицы
        int ind= hash_funct(key);    //находим хэш
        for (int i=ind;i<size;i++){   //В цикле ищем данную запись
            if (arr[i]== nullptr)
                return false;    // если мы дошли до пустой ячейки значит что по логике дальше наша запись содержаться не может, поэтому возвращаем false
            if(arr[i]->getNum()==key){    //помечаем данную запись как удалённую
                arr[i]->setDel(true);  //перердаем информацию о том что мы удалили данную ячейку
                cur_size--;       // уменьшаем количество записей в таблице
                return true;      // возвращем true - значит операция выполнена успешна
            }
        }
        return false;       // если мы дошли до конца и не нашли запись значит удаление не было произведено
    };
    void print(){      // Вывод таблицы

        cout<<"Номер\t\tКомпания\t\tФамилия\n";
        for (int i=0;i<15;i++)
            cout<<"---";
        for(int i=0;i<size;i++){
            if (arr[i]!= nullptr and arr[i]->isDel()!=1){    // Если ячейка не пустая и не удалена выводим информацию о ней
                cout<<endl;
                arr[i]->print();
                for (int i1=0;i1<15;i1++)
                    cout<<"---";}
        }
        cout<<"\n";
    };
    polic* search(int key){
        int ind= hash_funct(key);
        for (int i=ind;i<size;i++){
            if (arr[i]== nullptr)      // если мы дошли до пустой ячейки значит что по логике дальше
                // наша запись содержаться не может, поэтому возвращаем нулевой указатель
                return nullptr;
            if(arr[i]->getNum()==key){
                return arr[i];      //Возвращаем указатель на найденную ячейку
            }


        }
        return nullptr;    // Если дошли до конца и не ничего не нашли значит такой записи нет возвращаем нулевой указатель
    };     // Поиск по ключу
    void add(polic* a){            // Вставка записи в таблицу

        int ind = hash_funct(a->getNum());

        int i;
        for (i = ind; i < size; i++) {
            if (arr[i] == nullptr or arr[i]->isDel()==1) {    // Если ячейка пуская пустая или удаленна
                // то выходим из цикла и в данную ячейку добавляем нужную запись
                break;
            }
        }
        if (i!=ind){
            cout << "---------Возникновение колизии--------\n";
        }
        if(i==size){
            cout<<"----------Выполнение рэшеширования из-за невозможности добавления записи----------\n ";
            rehash();
            add(a);
        }      // если мы дошли до конца таблицы и не нашли пустой ячейки
        // то производим рехеширование чтобы мы смогли добавить данную запись в ячейку
        else {

            arr[i] = a;   // Добавляем в ячейку нужную запись
            cur_size++;   // увеличиваем количество заполненных ячеек
            if((float)(cur_size)/(float)(size)>0.75) {
                cout<<"----------Выполнение рехэшировния из-за большого количества  записей----------\n ";
                rehash(); // Если заполнение таблицы больше
            }
            // чем 0.75 то производим рехеширование и увеличиваем размер таблицы в два раза
        }

    };
    void rehash(){    // рехэширование
        auto old_table=this->arr;   // запоминаем старую хэщ таблицу
        int old_size=size;  // запоминаем размер cтарой таблицы
        this->size*=2;  // увеличиваем размер новой таблицы в 2 раза
        cur_size=0;   // количество заполненных ячеек 0

        arr=new polic * [size];   //Объявляем массив указателей размером size
        for(int i=0;i<old_size;i++){

            if (old_table[i]){
                add(old_table[i]);    // добавляем старые записи в новую таблицу
            }

        }
        delete old_table;
        cout<<"\n-----------Выполнено рехэширование--------------\n";
    };

};

int main() {
    int num_command;
    hesh a(10);
    //polic b(11,"b","a");
    string alf[]={"ВТБ1","ВТБ2","ВТБ3","ВТБ4","ВТБ5","ВТБ6","ВТБ7"};
    string surname_arr[]={"Ivanov","Smirnov","Sobolev","Petrov","Sviridov","Popov","Sviridov"};

    for (int i=0;i<7;i++){
        int r=rand()%89+10;
        string rs=alf[rand()%6];
        string rss=surname_arr[rand()%6];
//        cout<<r<<"  "<<rs<<"  "<<rss<<endl;
        a.add(new polic(r,rs,rss));
    }  // рандомно заполняем таблицу
    a.print();
    while (true){
        cout << "Выберите команду которую хотите выполнить:\n1.Добавить полис"
                "\n2.Удаление полиса"
                "\n3.Поиск по номеру полиса\n"
                "4.Вывод таблицы\n"
                "0.Завершить программу\n";
    cin >> num_command;
    if(num_command==1){
        int num;
        string company,surname;
        cout<<"Введите номер полиса: ";
        cin>>num;
        cout<<"Введите компанию: ";
        cin>>company;
        cout<<"Введите фамилию: ";
        cin>>surname;
        a.add(new polic(num,company,surname));
    }
    else if(num_command==2){
        cout<<"Введите номер полиса:\n";
        int key;
        cin>>key;
        if(a.del(key))
            cout<<"Удаление выполнено\n";
        else
            cout<<"Номер не найден\n";
    }
    else if(num_command==3){
        cout<<"Введите номер полиса:\n";
        int key;
        cin>>key;
        auto found_obj=a.search(key);
        if (found_obj) {
            found_obj->print();
        }
        else
            cout<<"Объект не найден\n";
    }
    else if(num_command==4){
        a.print();
    }
    else if(num_command==0){ break;}
    else
        cout<<"Повторите ввод\n\n";

    }

}
