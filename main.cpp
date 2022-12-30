#include <iostream>
#include <cstring>
#include <filesystem>
#include <utility>
#include <vector>
#include <thread>
#include <Windows.h>

using namespace std;



int countThreads = 0;






int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string path = "C:\\";

    if (argc < 2) {
        cout << "Недостаточно аргументов" << endl;
        return 0;
    }

    std::string filename = argv[1];

    for (int i = 1; i < argc - 1; i++) {
        if(strcmp(argv[i + 1], "") == 0){
            cout << "Аргумент не может быть пустым" << endl;
            return 0;
        }
        if (strcmp(argv[i], "--path") == 0) {
            path = argv[i + 1];
        } else if (strcmp(argv[i], "--num_threads") == 0) {
            countThreads = stoi(argv[i + 1]);
        }
    }



    return 0;
}
