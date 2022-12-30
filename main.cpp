#include <iostream>
#include <cstring>
#include <filesystem>
#include <utility>
#include <vector>
#include <thread>
#include <Windows.h>

using namespace std;
struct Node{
public:
    vector<string>* files;
    vector<Node*>* directories;
    string name;
    string fullPath;

    explicit Node(string name, string full_path) : name(std::move(name)), fullPath(std::move(full_path)) {
        files = new vector<string>();
        directories = new vector<Node*>();
    }

    void parse(){
        parse(name, 0);
    }


private:
    void parse(const string& path, int nesting){
        for(const auto& file : filesystem::directory_iterator(path))
        {
            for(int i = 0; i < nesting; i++) cout << "\t";
            cout << file.path().filename() << endl;
            if(filesystem::is_directory(file)) {
                Node* node = new Node(file.path().filename().string(), file.path().string());
                directories->push_back(node);
                node->parse(file.path().string(), nesting + 1);
            }
            else
                files->push_back(file.path().filename().string());
        }
    }


};



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

    Node* first = new Node(path, path);
    first->parse();


    return 0;
}
