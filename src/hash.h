#pragma once

#include "/home/kln735/4test_lab/src/array.h"
#include <cstdint>

template <typename K, typename V>
class Hashtable {
private:

    class Node {
    public:
        K key;
        V value;
        Node* next;

        Node(const K& key, const V& value) : key(key), value(value), next(nullptr) {}
    };

    Node** table; // An array of pointers to the beginning of the chains
    int size;

    int hashfunction(const K& key) const {
        uint32_t hash = 5381;

        if constexpr (is_same<K, string>::value) {
            // Для строк — итерируемся по символам
            for (auto& c : key) {
                hash = ((hash << 5) + hash) + c; // hash * 33 + c
            }
        } else if constexpr (is_integral<K>::value) {
            // Для целых чисел — преобразуем в строку (необязательно, можно оптимизировать)
            hash = ((hash << 5) + hash) + key;
        } 

        return hash % size;
    }

public:


    Hashtable(int size) : size(size) {
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~Hashtable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }

    void add(const K& key, const V& value) {
        int index = hashfunction(key);
        Node* current = table[index];

        // Проверяем существующий ключ
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ существует
                return;
            }
            current = current->next;
        }

        // Если ключ не найден, добавляем новый узел
        Node* new_node = new Node(key, value);
        new_node->next = table[index];
        table[index] = new_node;
    }

    V get(const K& key) const {
        int index = hashfunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        throw runtime_error("The key was not found");
    }

    void remove(const K& key) {
        int index = hashfunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) { 
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next; // Если первый в цепочке
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        throw runtime_error("The key was not found");
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            Node* current = table[i];
            if (current != nullptr) {
                while (current != nullptr) {
                    cout << "[" << current->key << ": " << current->value << "]";
                    current = current->next;
                    if (current != nullptr) {
                        cout << " -> ";
                    }
                }
            }
            cout << "\n";
        }
    }



    // void load_from_file(const string& filename, const string& name_structure) {
    //     ifstream file(filename);
        
    //     if (!file.is_open()) {
    //         cerr << "Error opening the file for reading.\n";
    //         return;
    //     }

    //     string line;
    //     bool structure_found = false;

    //     while (getline(file, line)) {
    //         // Проверяем, является ли строка началом структуры хеш-таблицы
    //         if (line.find(name_structure + " : ") != string::npos) {
    //             structure_found = true; // Нашли хеш-таблицу с указанным именем
    //             size_t pos = line.find(':');
    //             string values = line.substr(pos + 1); 
    //             stringstream ss(values);
    //             string pair;

    //             // Парсим ключ-значение, разделенные запятыми
    //             while (getline(ss, pair, ',')) {
    //                 size_t start = pair.find('[');
    //                 size_t middle = pair.find(':');
    //                 size_t end = pair.find(']');

    //                 if (start != string::npos && middle != string::npos && end != string::npos) {
    //                     string key = pair.substr(start + 1, middle - start - 1);  // Получаем ключ
    //                     string value = pair.substr(middle + 2, end - middle - 2); // Получаем значение

    //                     // Добавляем пару ключ-значение в хеш-таблицу
    //                     add(key, value);
    //                 }
    //             }
    //             break;
    //         }
    //     }

    //     file.close();

    // }

    // void save_to_file(const string& filename, const string& name_structure) const {
    //     // Читаем существующие данные из файла
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
    //         cerr << "Ошибка открытия файла для записи.\n";
    //         return;
    //     }

    //     // Проверяем наличие структуры с именем name_structure
    //     for (auto& existing_line : lines) {
    //         if (existing_line.find(name_structure + " : ") == 0) {
    //             structure_found = true;

    //             // Заменяем строку структуры новыми значениями
    //             write_file << name_structure << " : ";
                
    //             // Проходим по всем элементам хеш-таблицы
    //             bool first_entry = true;
    //             for (int i = 0; i < size; ++i) {
    //                 Node* current = table[i];
    //                 while (current != nullptr) {
    //                     if (!first_entry) {
    //                         write_file << ", "; // Добавляем разделитель
    //                     }
    //                     write_file << "[" << current->key << ": " << current->value << "]";
    //                     first_entry = false;
    //                     current = current->next;
    //                 }
    //             }
    //             write_file << endl;
    //         } else {
    //             write_file << existing_line << endl; // Сохраняем остальные строки
    //         }
    //     }

    //     // Если структура не найдена, добавляем её в конец файла
    //     if (!structure_found) {
    //         write_file << name_structure << " : ";
    //         bool first_entry = true;
    //         for (int i = 0; i < size; ++i) {
    //             Node* current = table[i];
    //             while (current != nullptr) {
    //                 if (!first_entry) {
    //                     write_file << ", "; // Добавляем разделитель
    //                 }
    //                 write_file << "[" << current->key << ": " << current->value << "]";
    //                 first_entry = false;
    //                 current = current->next;
    //             }
    //         }
    //         write_file << endl;
    //     }

    //     write_file.close();
    // }

};

