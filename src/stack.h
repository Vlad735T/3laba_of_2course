#pragma once 

#include "/home/kln735/4test_lab/src/array.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

template <typename T>
class Stack {

private:
    class Node {
        public:
        T person;
        Node* next;

        Node(T person) : person(person), next(nullptr) {}
    };

    Node* head;
    int SIZE;  // Добавляем переменную для размера стека

public:
    Stack() : head(nullptr), SIZE(0) {}

    ~Stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool is_empty() const {
        return head == nullptr;
    }

    void push(const T& name) {
        Node* new_node = new Node(name);
        new_node->next = head;
        head = new_node;
        ++SIZE;  // Увеличиваем размер стека
    }

    void pop() {
        if (is_empty()) {
            throw runtime_error("Stack is empty");
        }
        else {
            Node* new_head = head->next;
            delete head;
            head = new_head;
            --SIZE;  // Уменьшаем размер стека
        }
    }

    T top() const {
        if (is_empty()) {
            throw runtime_error("Stack is empty");
        }
        return head->person;
    }

    int size() const {
        return SIZE;  // Возвращаем текущий размер стека
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->person << " ";
            current = current->next;
        }
        cout << "\n";
    }




        void serialization(const string& filename){
        ofstream file(filename, ios::binary);
        if(!file.is_open()){
            cerr << "Ошибка открытия файла для записи.\n";
            return;
        }

        int size = this -> SIZE;
        file.write(reinterpret_cast<char*>(&size), sizeof(size));

        Node* temp = head;
        for(int i = 0; i < SIZE; i++){
            size_t length_word = temp -> person.size();
            file.write(reinterpret_cast<char*>(&length_word), sizeof(length_word));
            file.write(temp -> person.c_str(), length_word);
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
            push(buffer);
            
        }
        cout << "Deserialization was successful done!!!\n";
        file.close();
    }
};


    // void save_to_file(const string& filename, const string& name_structure) const {
    //     ifstream read_file(filename);
    //     vector<string> lines;
    //     string line;
    //     bool structure_found = false;

    //     if (read_file.is_open()) {
    //         while (getline(read_file, line)) {
    //             lines.push_back(line);
    //         }
    //         read_file.close();
    //     } else {
    //         cerr << "Error opening the file for reading.\n";
    //         return;
    //     }

    //     ofstream write_file(filename);
    //     if (!write_file.is_open()) {
    //         cerr << "Error opening the file for writing.\n";
    //         return;
    //     }

    //     for (const auto& existing_line : lines) {
    //         if (existing_line.find(name_structure + " : ") == 0) {
    //             structure_found = true;
    //             write_file << name_structure << " : ";

    //             Node* current = head;
    //             bool first = true;
    //             while (current != nullptr) {
    //                 if (!first) write_file << ", ";
    //                 write_file << current->data;
    //                 current = current->next;
    //                 first = false;
    //             }
    //             write_file << "\n";
    //         } else {
    //             write_file << existing_line << "\n";
    //         }
    //     }

    //     if (!structure_found) {
    //         write_file << name_structure << " : ";
    //         Node* current = head;
    //         bool first = true;

    //         while (current != nullptr) {
    //             if (!first) write_file << ", ";
    //             write_file << current->data;
    //             current = current->next;
    //             first = false;
    //         }
    //         write_file << "\n";
    //     }

    //     write_file.close();
    // }

    // void load_from_file(const string& filename, const string& name_structure) {
    //     ifstream file(filename);

    //     if (!file.is_open()) {
    //         cerr << "Error opening the file for reading.\n";
    //         return;
    //     }

    //     string line;
    //     bool structure_found = false;

    //     while (getline(file, line)) {
    //         if (line.find(name_structure + " : ") == 0) {
    //             structure_found = true;
    //             int pos = line.find(':');
    //             string values = line.substr(pos + 1);
    //             stringstream ss(values);
    //             string value;

    //             Stack<T> temp_stack;
    //             while (getline(ss, value, ',')) {
    //                 value.erase(0, value.find_first_not_of(" "));
    //                 value.erase(value.find_last_not_of(" ") + 1);

    //                 stringstream converter(value);
    //                 T converted_value;
    //                 converter >> converted_value;

    //                 temp_stack.push(converted_value);
    //             }

    //             while (!temp_stack.is_empty()) {
    //                 push(temp_stack.top());
    //                 temp_stack.pop();
    //             }
    //             break;
    //         }
    //     }

    //     file.close();
    // }

