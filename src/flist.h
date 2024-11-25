#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class ForwardList {
private:
    class Node {
    public:
        T data;  // изменяем тип на шаблонный параметр
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    ForwardList() : head(nullptr), tail(nullptr) {}

    ~ForwardList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
    }

    bool is_empty() const {
        return head == nullptr;
    }

    int size(){
        Node* temp = head;
        int razmer = 0;
        while(temp != nullptr){
            razmer++;
            temp = temp -> next;
        }
        return razmer;
    }
    void addtail(T value) {
        Node* newNode = new Node(value);
        if (is_empty()) {
            head = newNode;
            tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    void addhead(T value) {
        Node* newNode = new Node(value);
        if (is_empty()) {
            head = newNode;
            tail = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    string get(size_t index) const {
        if (index < 0) {
            throw out_of_range("Index must be non-negative");
        }

        Node* current = head;
        size_t current_index = 0;

        while (current != nullptr) {
            if (current_index == index) {
                return current->data;
            }
            current = current->next;
            current_index++;
        }

        throw out_of_range("Index out of bounds");
    }
    bool search(T value) {
        if (is_empty()) {
            throw runtime_error("ForwardList is empty");
        }

        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                //cout << "Value \"" << value << "\" found in the list." << endl;
                return true;
            }
            current = current->next;
        }

        //cout << "Value \"" << value << "\" not found in the list." << endl;
        return false;
    }

    void delhead() {
        if (is_empty()) {
            throw runtime_error("ForwardList is empty");
        }
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node* node = head;
        head = node->next;
        delete node;
    }

    void deltail() {
        if (is_empty()) {
            throw runtime_error("ForwardList is empty");
        }
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node* node = head;
        while (node->next != tail) {
            node = node->next;
        }
        delete tail;
        tail = node;
        tail->next = nullptr;
    }

    void remove(T value) {
        if (is_empty()) {
            throw runtime_error("ForwardList is empty");
        }
        // Если удаляем голову
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            return;
        }
        // Поиск узла с данным значением
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            //cout << "Value \"" << value << "\" not found in the list." << endl;
            return;
        }

        if (current == tail) {
            tail = prev;
        }

        if (prev != nullptr) {
            prev->next = current->next;
        }
        delete current;
    }


    void print() const {
        if (is_empty()) {
            cout << "List is empty" << endl;
            return;
        }
        Node* current = head;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }

    void serialization(const string& filename){

        ofstream file(filename, ios::binary);
        if(!file.is_open()){
            cerr << "Error opening file!!!" << "\n";
            return;
        }

        int sizes = this -> size();

        file.write(reinterpret_cast<char*>(&sizes), sizeof(sizes));

        Node* temp = head;

        for(int i = 0; i < sizes; i++){
            size_t count_of_letters = temp -> data.size();

            file.write(reinterpret_cast<char*>(&count_of_letters), sizeof(count_of_letters));
            file.write(temp -> data.c_str(), count_of_letters);
            temp = temp -> next;
        }
        file.close();
    }

    void deserialization(const string& filename){

        ifstream file(filename, ios::binary);

        if(!file.is_open()){
            cerr << "Error opening file!!!" << "\n";
            return;
        }

        int size; 
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        for(int i = 0; i < size; i++){
            size_t length_word;
            file.read(reinterpret_cast<char*>(&length_word), sizeof(length_word));

            char* letter = new char [length_word + 1];
            file.read(letter, length_word);
            letter[length_word] = '\0';
            addtail(string(letter));
            delete [] letter;
        }
        cout << "Deserialization was successful done!!!\n";
        file.close();
    }
    
    // void load_from_file(const string& filename, const string& name_structure) {
    //     ifstream file(filename);
        
    //     if (!file.is_open()) {
    //         cerr << "Ошибка открытия файла для чтения.\n";
    //         return;
    //     }

    //     string line;
    //     bool structure_found = false;

    //     while (!is_empty()) {
    //         delhead();
    //     }

    //     while (getline(file, line)) {
    //         // Проверяем, является ли строка началом новой структуры
    //         if (line.find(name_structure + " : ") != string::npos) {
    //             structure_found = true; // Найдена структура с указанным именем
    //             size_t pos = line.find(':');
    //             string values = line.substr(pos + 1); 
    //             stringstream ss(values);
    //             T value;

    //             // Парсим значения, разделенные запятыми, и добавляем их в список
    //             while (getline(ss, value, ',')) {
    //                 value.erase(0, value.find_first_not_of(" \t"));  // Удаляем пробелы перед значениями
    //                 addtail(value);  
    //             }
    //             break;  
    //         }
    //     }

    //     file.close();
    // }

    // void save_to_file(const string& filename, const string& name_structure) const {
    //     ifstream read_file(filename);
    //     ForwardList<T> lines;
    //     string line;
    //     bool structure_found = false;

    //     // Читаем файл построчно и сохраняем все строки во временный список
    //     if (read_file.is_open()) {
    //         while (getline(read_file, line)) {
    //             lines.addtail(line);
    //         }
    //         read_file.close();
    //     } else {
    //         cerr << "Ошибка открытия файла для чтения.\n";
    //         return;
    //     }

    //     // Открываем файл для записи (перезапись)
    //     ofstream write_file(filename);
    //     if (!write_file.is_open()) {
    //         cerr << "Ошибка открытия файла для записи.\n";
    //         return;
    //     }

    //     Node* current = lines.head;

    //     while (current != nullptr) {
    //         string& existing_line = current->data;
    //         if (existing_line.find(name_structure + " : ") == 0) {
    //             structure_found = true;

    //             // Заменяем строку структуры новыми значениями из списка
    //             write_file << name_structure << " : ";
    //             Node* data_node = head;
    //             bool first = true;
    //             while (data_node != nullptr) {
    //                 if (!first) {
    //                     write_file << ", ";
    //                 }
    //                 write_file << data_node->data;
    //                 first = false;
    //                 data_node = data_node->next;
    //             }
    //             write_file << endl;
    //         } else {
    //             // Записываем все остальные строки как есть
    //             write_file << existing_line << endl;
    //         }
    //         current = current->next;
    //     }

    //     // Если структура не найдена, добавляем её в конец файла
    //     if (!structure_found) {
    //         write_file << name_structure << " : ";
    //         Node* data_node = head;
    //         bool first = true;
    //         while (data_node != nullptr) {
    //             if (!first) {
    //                 write_file << ", ";
    //             }
    //             write_file << data_node->data;
    //             first = false;
    //             data_node = data_node->next;
    //         }
    //         write_file << endl;
    //     }

    //     write_file.close();
    // }

};

