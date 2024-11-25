#pragma once 
#include "library.h"
#include <stdexcept>

template <typename T>  // Шаблонный класс LinkedList
class LinkedList {
private:
    class Node {
    public:
        T data;  // Шаблонный тип данных
        Node* next;
        Node* prev;

        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

    // Счетчик элементов списка
    size_t list_size;

public:
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = tail = nullptr;
        list_size = 0;
    }

    // Проверка на пустоту списка
    bool is_empty() const {
        return list_size == 0;
    }

    // Получение размера списка
    size_t size() const {
        return list_size;
    }

    void addhead(T value) {
        Node* newnode = new Node(value);
        if (head == nullptr) {
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        ++list_size;  // Увеличиваем счетчик
    }

    void addtail(T value) {
        Node* newnode = new Node(value);
        if (head == nullptr) {
            head = newnode;
            tail = newnode;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        ++list_size;  // Увеличиваем счетчик
    }

    void delhead() {
        if (is_empty()) {
            throw runtime_error("LinkedList is empty");
        }
        Node* next_node = head->next;
        if (next_node != nullptr) {
            next_node->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete head;
        head = next_node;
        --list_size;  // Уменьшаем счетчик
    }

    void deltail() {
        if (is_empty()) {
            throw runtime_error("LinkedList is empty");
        }
        Node* prev_node = tail->prev;
        if (prev_node != nullptr) {
            prev_node->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete tail;
        tail = prev_node;
        --list_size;  // Уменьшаем счетчик
    }

    void remove(T value) {
        if (is_empty()) {
            throw runtime_error("LinkedList is empty");
        }
        Node* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->data == value) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    } else {
                        tail = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                --list_size;  // Уменьшаем счетчик
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            //cout << "Element not found in LinkedList!" << "\n";
        }
    }

    void search(T value) {
        if (is_empty()) {
            throw runtime_error("LinkedList is empty");
        }

        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                //cout << "Element found in LinkedList!" << "\n";
                return;
            }
            current = current->next;
        }
        throw runtime_error("Element not found in LinkedList!");
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }

    // Шаблонный метод get: возвращает элемент по индексу
    T get(int index) const {
        if (is_empty()) {
            throw runtime_error("LinkedList is empty");
        }

        if (index < 0 || static_cast<size_t>(index) >= list_size) {
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        int count = 0;

        // Пробегаем по списку до нужного индекса
        while (current != nullptr) {
            if (count == index) {
                return current->data;
            }
            current = current->next;
            count++;
        }

        // Если индекс выходит за пределы списка
        throw out_of_range("Index out of range");
    }

    void serialization(const string& filename){
        ofstream file(filename, ios::binary);
        if(!file.is_open()){
            cerr << "Ошибка открытия файла для записи.\n";
            return;
        }

        int size = this -> list_size;
        file.write(reinterpret_cast<char*>(&size), sizeof(size));

        Node* temp = head;
        for(int i = 0; i < list_size; i++){
            size_t length_word = temp -> data.size();
            file.write(reinterpret_cast<char*>(&length_word), sizeof(length_word));
            file.write(temp -> data.c_str(), length_word);
            temp = temp -> next;
        }
        file.close();
    }


    void deserialization(const string& filename){
        ifstream file(filename, ios::binary);

        if(!file.is_open()){
            cerr << "Ошибка открытия файла для чтения.\n";
            return;
        }

        int size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        for(int i = 0; i < size; i++){
            size_t length_word;
            file.read(reinterpret_cast<char*>(&length_word), sizeof(length_word));

            string buffer(length_word, '\0');
            file.read(&buffer[0], length_word);
            addtail(buffer);
            
        }
        cout << "Deserialization was successful done!!!\n";
        file.close();
    }

};


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
    //             string value;

    //             // Парсим значения, разделенные запятыми, и добавляем их в список
    //             while (getline(ss, value, ',')) {
    //                 value.erase(0, value.find_first_not_of(" \t"));  
    //                 addtail(value);  
    //             }
    //             break;  
    //         }
    //     }

    //     file.close();
    // }

    // void save_to_file(const string& filename, const string& name_structure) const {
    //     ifstream read_file(filename);
    //     LinkedList lines;  
    //     string line;
    //     bool structure_found = false;

    //     if (read_file.is_open()) {
    //         while (getline(read_file, line)) {
    //             lines.addtail(line);
    //         }
    //         read_file.close();
    //     } else {
    //         cerr << "Ошибка открытия файла для чтения.\n";
    //         return;
    //     }

    //     ofstream write_file(filename);
    //     if (!write_file.is_open()) {
    //         cerr << "Ошибка открытия файла для записи.\n";
    //         return;
    //     }

    //     Node* current = lines.head;

    //     while (current != nullptr) {
    //         string& existing_line = current->person;  // Получаем строку из временного списка
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
    //                 write_file << data_node->person;  // Записываем элемент
    //                 first = false;
    //                 data_node = data_node->next; 
    //             }
    //             write_file << endl; 
    //         } else {
    //             // Записываем все остальные строки как есть
    //             write_file << existing_line << endl;
    //         }
    //         current = current->next;  // Переходим к следующему элементу во временном списке
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
    //             write_file << data_node->person; 
    //             first = false;
    //             data_node = data_node->next;  // Переходим к следующему элементу
    //         }
    //         write_file << endl; 
    //     }

    //     write_file.close();  
    // }
