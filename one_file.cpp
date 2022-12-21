#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_SIZE_STRING 10


template<typename T>
class Vector {
    void addMemory() {
        capacity_ = capacity_ * 2 + 1;
        T *tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
        delete[] tmp;
    }

    T *arr_;
    size_t size_{};
    size_t capacity_{};

public:
    Vector() {
        arr_ = new T[1];
        capacity_ = 1;
    }

    ~Vector() { delete[] arr_; }

    [[nodiscard]] bool isEmpty() const { return size_ == 0; }
    [[nodiscard]] size_t size() const { return size_; }

    void pushBack(const T &value) {
        if (size_ >= capacity_) addMemory();
        arr_[size_++] = value;
    }

    void popBack() {
        if (size_) {
            arr_[size_ - 1].~T();
            --size_;
        }
    }

    void clear() { while (size_) popBack(); }

    const T *begin() const { return &arr_[0]; }
    const T *end() const { return &arr_[size_]; }
    const T *data() { return arr_; }
};


class String {
    Vector<char> m_chars;
public:
    String() = default;

    const char *begin() const { return m_chars.begin(); }
    const char *end() const { return m_chars.end(); }

    bool isEmpty() const noexcept { return m_chars.isEmpty(); }
    std::size_t size() const noexcept { return m_chars.size(); }
    void pushBack(const char c) { m_chars.pushBack(c); }
    void clear() noexcept { m_chars.clear(); }

    const char *c_str() { return m_chars.data(); }

    String &operator=(char *str) {
        std::strcpy(const_cast<char *>(m_chars.data()), str);
        return *this;
    }

    std::istream& getline(std::istream& is) {
        char c;
        is.get(c);

        while (!isgraph(c))
            is.get(c);

        while (std::isgraph(c)) {
            m_chars.pushBack(c);
            is.get(c);
        }
        m_chars.pushBack('\0');

        return is;
    }
};

std::ostream& operator<<(std::ostream& os, String &s) {
    for (auto i : s)
        os << i;
    return os;
}

std::istream& operator>>(std::istream& is, String &s) {
    s.getline(is);
    return is;
}

////////////////////////////////////////////////////////////////////////////////////

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
    char c;
    while (fin.get(c)) {
        if (c == ' ' || c == '\n') {
            char c1;
            fin.get(c1);

            if (c1 == ' ' && c == ' ') {
                create_paragraph(count_left_paragraph, count_up_paragraph - (count_symbol_in_string == 0), fout);
                for (uint32_t i = 0; i < MAX_SIZE_STRING - 2; i++)
                    fin.get(c);
                count_symbol_in_string = count_left_paragraph + count_right_paragraph;
            }

            if (!word.isEmpty()) {
                if (count_symbol_in_string + word.size() > MAX_SIZE_STRING)
                    fout << '\n', count_symbol_in_string = 0;
                write_word(word, fout), count_symbol_in_string += word.size(), word.clear();

                if (count_symbol_in_string < MAX_SIZE_STRING)
                    fout << ' ', count_symbol_in_string++;
                else
                    fout << '\n', count_symbol_in_string = 0;
            }

            if (c1 != ' ' && c1 != '\n')
                word.pushBack(c1);

        } else
            word.pushBack(c);


        if (count_symbol_in_string == MAX_SIZE_STRING)
            fout << '\n', count_symbol_in_string = 0;
    }

    if (!word.isEmpty()) {
        if (count_symbol_in_string + word.size() > MAX_SIZE_STRING)
            fout << '\n';
        write_word(word, fout), word.clear();
    }


    fin.close();
    fout.close();


    return 0;
}

