#include <iostream>
#include <fstream>
#include "include/include.h"

#define MAX_SIZE_STRING 10

void write_word(String &word, std::ofstream &file) {
    for (char i : word)
        file << i;
}

void create_paragraph(const uint32_t count_left_paragraph, const uint32_t count_up_paragraph, std::ofstream &file) {
    for (uint32_t i = 0; i <= count_up_paragraph; i++)
        file << '\n';
    for (uint32_t i = 0; i < count_left_paragraph; i++)
        file << ' ';
}

int main() {
    uint32_t count_left_paragraph, count_right_paragraph, count_up_paragraph;
    String input_file, output_file;

    std::cin >> count_left_paragraph >> count_right_paragraph >> count_up_paragraph >> input_file >> output_file;

    std::ifstream fin;
    std::ofstream fout;
    fin.open(input_file.c_str(), std::ios_base::in);
    fout.open(output_file.c_str(), std::ios_base::out | std::ios_base::trunc);


    if (!fin.is_open())
        return std::cerr << "Error: the file " << input_file << " cannot be opened" << std::endl, 0;
    if (!fout.is_open())
        return std::cerr << "Error: the file " << output_file << " cannot be opened" << std::endl, 0;


    uint32_t count_symbol_in_string = 0;
    String word;
    while (fin) {
        char c;
        fin.get(c);

        if (c == ' ' or c == '\n') {
            char c1;
            fin.get(c1);

            if (c1 == ' ' && c == ' ') {
                create_paragraph(count_left_paragraph, count_up_paragraph, fout);
                for (uint32_t i = 0; i < MAX_SIZE_STRING - 2; i++)
                    fin.get(c);
                count_symbol_in_string = count_left_paragraph + count_right_paragraph;

                continue;
            }

            if (!word.isEmpty()) {
                if (count_symbol_in_string + word.size() > MAX_SIZE_STRING)
                    fout << '\n', count_symbol_in_string = 0;
                write_word(word, fout), count_symbol_in_string += word.size(), word.clear();
            }

            if (count_symbol_in_string < MAX_SIZE_STRING && count_symbol_in_string)
                fout << ' ', count_symbol_in_string++;

            if (c1 != ' ' && c1 != '\n')
                word.pushBack(c1);

        } else
            word.pushBack(c);


        if (count_symbol_in_string == MAX_SIZE_STRING)
            fout << '\n', count_symbol_in_string = 0;
    }

    fin.close();
    fout.close();

    return 0;
}

