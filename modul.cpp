#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include "modul.h"
using namespace std;

void Menu() {
      NumericRing ring;
    string filename;
    while (true) {
        system("cls");
        cout<<"Введите имя файла (0 - выход): ";
        cin>>filename;
        if (filename=="0") {
            cout<<"\nДо свидания!\n";
            break;
        }
        int loadResult=ring.load(filename);
        if (loadResult==0) {
            cout<<"\nПоиск решения...\n";
            string result;
            if (ring.find(result)) {
                cout<<"\nНайдено решение: "<<result<<"\n";
                ofstream out("output.txt");
                if (out.is_open()) {
                    out<<result<<"\n";
                    out.close();
                    cout<<"Результат сохранён в output.txt\n";
                }
                else {
                    cout<<"Не удалось создать файл output.txt\n";
                }
            }
            else {
                cout<<"\nРешение не найдено\n";
                ofstream out("output.txt");
                if (out.is_open()) {
                    out<<"No\n";
                    out.close();
                }
            }
        }
        else {
            cout<<"\nОшибка загрузки файла!\n\n";
            switch(loadResult) {
                case 1:
                    cout<<"Причина: файл \""<<filename<<"\" не найден или не может быть открыт\n";
                    break;
                case 2:
                    cout<<"Причина: файл пуст или содержит только пробелы\n";
                    break;
                case 3:
                    cout<<"Причина: файл содержит нецифровые символы (буквы, знаки и т.д.)\n";
                    break;
                case 4:
                    cout<<"Причина: длина строки превышает 1000 символов\n";
                    break;
                default:
                    cout<<"Причина: неизвестная ошибка\n";
                    break;
            }
        }
        cout<<"\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        cout<<endl;
    }
}
