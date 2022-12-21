#ifndef WORK2_STRING_H
#define WORK2_STRING_H

#include <cstring>
#include "../../data_structures/Vector/Vector.h"

class String {
    Vector<char> m_chars;
public:
    String();

    [[nodiscard]] const char *begin() const;
    [[nodiscard]] const char *end() const;
    [[nodiscard]] bool isEmpty() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

    void clear() noexcept;
    void pushBack(char c);
    void popBack();

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream& is, String& s);

    const char *c_str();

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

#endif
