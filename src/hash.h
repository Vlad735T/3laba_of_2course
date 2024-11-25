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

    void serialization(const string& filename) { 
            ofstream file(filename, ios::binary);
            if (!file.is_open()) {
                cerr << "Error opening file for writing: " << filename << "\n";
                return;
            }

            int SIZE = this->size;
            file.write(reinterpret_cast<char*>(&SIZE), sizeof(SIZE));
            if (!file) {
                cerr << "Error writing size to file.\n";
                return;
            }

            // Проходим по таблице и записываем данные
            for (int i = 0; i < SIZE; i++) {
                Node* current = table[i];
                while (current != nullptr) {
                    int key_length = current->key.size();
                    file.write(reinterpret_cast<char*>(&key_length), sizeof(key_length));
                    if (!file) {
                        cerr << "Error writing key length to file.\n";
                        return;
                    }
                    file.write(current->key.c_str(), key_length);
                    if (!file) {
                        cerr << "Error writing key to file.\n";
                        return;
                    }

                    int value_length = current->value.size();
                    file.write(reinterpret_cast<char*>(&value_length), sizeof(value_length));
                    if (!file) {
                        cerr << "Error writing value length to file.\n";
                        return;
                    }
                    file.write(current->value.c_str(), value_length);
                    if (!file) {
                        cerr << "Error writing value to file.\n";
                        return;
                    }

                    // cout << "Serialized key-value pair: [" << current->key << ": " << current->value << "]" << endl;

                    current = current->next;
                }
            }

            file.close();
            if (!file) {
                cerr << "Error closing file after writing.\n";
            } else {
                cout << "Serialization successful!" << "\n";
            }
    }


    void deserialization(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        // Очистка таблицы перед загрузкой
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }

        // Читаем новый размер
        int size_new;
        file.read(reinterpret_cast<char*>(&size_new), sizeof(size_new));
        if (!file) {
            cerr << "Error reading size from file.\n";
            return;
        }

        // Если размер изменился, пересоздаем таблицу
        if (size_new != size) {
            delete[] table;
            size = size_new;
            table = new Node*[size];
            for (int i = 0; i < size; ++i) {
                table[i] = nullptr;
            }
        }

        // Чтение ключей и значений из файла
        while (file.peek() != EOF) {
            int keyLength;
            file.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
            if (!file) {
                cerr << "Error reading key length from file.\n";
                return;
            }

            string key(keyLength, '\0');
            file.read(&key[0], keyLength);
            if (!file) {
                cerr << "Error reading key from file.\n";
                return;
            }

            int valueLength;
            file.read(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));
            if (!file) {
                cerr << "Error reading value length from file.\n";
                return;
            }

            string value(valueLength, '\0');
            file.read(&value[0], valueLength);
            if (!file) {
                cerr << "Error reading value from file.\n";
                return;
            }

            add(key, value);
        }

        file.close();
        if (!file) {
            cerr << "Error closing file after reading.\n";
        } else {
            cout << "Deserialization successful!" << "\n";
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

