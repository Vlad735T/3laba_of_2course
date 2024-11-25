#pragma once 
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "/home/kln735/4test_lab/src/array.h"

template <typename T>
class QUEUE {

private:
    class Node {
    public:
        T person;
        Node* next;

        Node(T person) : person(person), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    QUEUE() : head(nullptr), tail(nullptr) {}

    ~QUEUE() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    bool is_empty() const {
        return head == nullptr;
    }

    int size(){
        if (is_empty()){
            throw runtime_error("Empty!");
        }
        Node* current = head;
        int count = 0;
        while(current){
            count++;
            current = current->next;
        }
        return count;
    }  

    void push(const T& name) {
        Node* new_node = new Node(name);

        if (is_empty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void pop() {
        if (is_empty()) {
            throw runtime_error("QUEUE is empty");
        }

        Node* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    T front() const {
        if (is_empty()) {
            throw runtime_error("QUEUE is empty");
        }
        return head->person;
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

        int SIZE = this -> size();
        file.write(reinterpret_cast<char*>(&SIZE), sizeof(SIZE));

        Node* temp = head;
        for(int i = 0; i < SIZE; i++,  temp = temp -> next){
            size_t length_word = temp -> person.size();
            file.write(reinterpret_cast<char*>(&length_word), sizeof(length_word));
            file.write(temp -> person.c_str(), length_word);
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
    
    // void save_to_file(const string& filename, const string& name_structure) const {
    //     ifstream read_file(filename);
    //     Myvector<string> lines;  
    //     string line;
    //     bool structure_found = false;

    //     if (read_file.is_open()) {
    //         while (getline(read_file, line)) {
    //             lines.MPUSH(line);  
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

    //     for (auto& existing_line : lines) {
    //         if (existing_line.find(name_structure + " : ") == 0) {
    //             structure_found = true;
    //             write_file << name_structure << " : ";
    //             Node* current = head;  
    //             bool first = true;
    //             while (current != nullptr) {
    //                 if (!first) write_file << ", ";
    //                 write_file << current->person;
    //                 first = false;
    //                 current = current->next;
    //             }
    //             write_file << endl;
    //         } else {
    //             write_file << existing_line << endl;
    //         }
    //     }

    //     if (!structure_found) {
    //         write_file << name_structure << " : ";
    //         Node* current = head;
    //         bool first = true;
    //         if (current == nullptr) {
    //             cerr << "Error: the queue is empty, I can't add " << name_structure << " : \n";
    //         } else {
    //             while (current != nullptr) {
    //                 if (!first) write_file << ", ";
    //                 write_file << current->person;
    //                 first = false;
    //                 current = current->next;
    //             }
    //             write_file << endl;
    //         }
    //     }

    //     write_file.close();
    // }

    // void load_from_file(const string& filename, const string& name_structure) {
    //     ifstream file(filename);
        
    //     if (file.is_open()) {
    //         string line;
    //         bool structure_found = false;

    //         while (getline(file, line)) {
    //             if (line.find(name_structure + " : ") != string::npos) {
    //                 structure_found = true;
    //                 size_t pos = line.find(':');
    //                 string values = line.substr(pos + 1); 
    //                 stringstream ss(values);
    //                 string value;

    //                 while (getline(ss, value, ',')) {
    //                     push(value);
    //                 }
    //                 break; 
    //             }
    //         }

    //         file.close();
    //     } else {
    //         cerr << "Error opening the file for reading.\n";
    //     }
    // }

};
