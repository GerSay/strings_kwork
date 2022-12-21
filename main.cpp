#include <iostream>
#include <fstream>
#include "include/include.h"

#define MAX_SIZE_STRING 10

// создание отступов согласно условию задачи
void create_paragraph(const uint32_t count_left_paragraph, const uint32_t count_up_paragraph, std::ofstream &file) {
    for (uint32_t i = 0; i <= count_up_paragraph; i++)
        file << '\n';
    for (uint32_t i = 0; i < count_left_paragraph; i++)
        file << ' ';
}

int main() {
    uint32_t count_left_paragraph, count_right_paragraph, count_up_paragraph;   // переменные для хранения отступов
    String input_file, output_file;         // переменные, для хранения адресов файлов ввода и вывода
    // считывание переменных условия
    std::cin >> count_left_paragraph >> count_right_paragraph >> count_up_paragraph >> input_file >> output_file;

    std::ifstream fin;                      // переменная потока ввода
    std::ofstream fout;                     // переменная потока вывода
    fin.open(input_file.c_str(), std::ios_base::in);                            // открываем файл с модом: чтение
    fout.open(output_file.c_str(), std::ios_base::out | std::ios_base::trunc);  // открываем файл с модом: перезапись

    // проверка на то, что файлы открылись
    if (!fin.is_open())                     // если не открылись -> выводим в поток ошибок сообщение и завершаем работу
        return std::cerr << "Error: the file " << input_file << " cannot be opened" << std::endl, 0;
    if (!fout.is_open())
        return std::cerr << "Error: the file " << output_file << " cannot be opened" << std::endl, 0;


    uint32_t count_symbol_in_string = 0;    // переменная количества символов в строке
    String word;                            // строка для считывания по словам
    char c;                                 // символ для чтения
    while (fin.get(c)) {                    // считываем посимвольно из файла
        if (c == ' ' || c == '\n') {        // если считываемый символ - пробел или символ новой строки
            char c1;                        // создаем новую переменную, считываем из файла символ в новую переменную
            fin.get(c1);

            if (c1 == ' ' && c == ' ') {    // если оба символа - пробелы -> создаем абзац
                create_paragraph(count_left_paragraph, count_up_paragraph - (count_symbol_in_string == 0), fout);
                for (uint32_t i = 0; i < MAX_SIZE_STRING - 2; i++)
                    fin.get(c);             // считываем все оставшиеся пробелы в строке
                count_symbol_in_string = count_left_paragraph + count_right_paragraph;
            }                               // так как наша строка была нулевой, етперь ее размер будет равен количеству
            // пробелов слева, чтобы сделать отступ справа, мы добавим количество
            // правых пробелов в строку, чтобы, когда мы введем допустимое количество
            // символов - нас перекинуло на новую строку
            if (!word.isEmpty()) {          // если мы считали слово:
                if (count_symbol_in_string + word.size() > MAX_SIZE_STRING)     // если слово переполнит строку
                    fout << '\n', count_symbol_in_string = 0;                   // создаем новую строку, обнуляем размер
                fout << word, count_symbol_in_string += word.size(), word.clear();
                // записываем слово в файл, количество символов в строке увеличиваем на
                // размер слова, очищаем память из-под слова
                if (count_symbol_in_string < MAX_SIZE_STRING)       // если количество символов меньше максимального
                    fout << ' ', count_symbol_in_string++;          // добавляем пробел и увеличиваем количество
                else                                                // символов на 1
                    fout << '\n', count_symbol_in_string = 0;       // иначе создаем новую строку
            }

            if (c1 != ' ' && c1 != '\n')    // если второй считанный символ - часть нового слова (не пробельный символ)
                word.pushBack(c1);          // добавим в слово наш символ

        } else                              // если мы считали первым символом часть слова (не пробельный символ)
            word.pushBack(c);               // добавляем его в конец слова


        if (count_symbol_in_string == MAX_SIZE_STRING)      // если количество символов = максимально допустимому
            fout << '\n', count_symbol_in_string = 0;       // создаем новую строку и обнуляем ее размер
    }

    if (!word.isEmpty()) {                  // выводим слово, если оно не вывелось в нашем цикле
        if (count_symbol_in_string + word.size() > MAX_SIZE_STRING)
            fout << '\n';
        fout << word, word.clear();
    }
    // закрываем файлы
    fin.close();
    fout.close();

    return 0;
}

