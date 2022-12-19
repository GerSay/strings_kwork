#include "String.h"

String::String() = default;

const char *String::begin() const {
    return m_chars.begin();
}

const char *String::end() const {
    return m_chars.end();
}

bool String::isEmpty() const noexcept {
    return m_chars.isEmpty();
}

std::size_t String::size() const noexcept {
    return m_chars.size();
}

void String::pushBack(const char c) {
    m_chars.pushBack(c);
}

void String::clear() noexcept {
    m_chars.clear();
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    for (auto i : s)
        os << i;

    return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    s.getline(is);

    return is;
}

const char *String::c_str() {
    return m_chars.data();
}
