#include <iostream>
#include <algorithm>
#include <cstring>

struct String {
private:

    size_t sz = 0;
    size_t reserved = 1;
    char* symbols;

public:

    void check_null() {
        symbols[sz] = '\0';
    }

    String() : symbols(new char[1]){
        check_null();
    }

    String(size_t n, char symbol) : sz(n), reserved(n + 1), symbols(new char[reserved]) {
        std::fill(symbols, symbols + sz, symbol);
        check_null();
    }

    String(char symbol) : sz(1), reserved(2), symbols(new char[2]) {
        symbols[0] = symbol;
        check_null();
    }

    String(const char* array) : sz(strlen(array)), reserved(sz + 1), symbols(new char[reserved]) {
        std::copy(array, array + sz, symbols);
        check_null();
    }

    String(const String& string) : sz(string.sz), reserved(string.reserved), symbols(new char[reserved]) {
        std::copy(string.symbols, string.symbols + reserved, symbols);
    }

    void swap(String& string2) {
        std::swap(sz, string2.sz);
        std::swap(reserved, string2.reserved);
        std::swap(symbols, string2.symbols);
    }

    String& operator=(const String& string) {
        if (string.sz < reserved) {
            std::copy(string.symbols, string.symbols + string.sz + 1, symbols);
            sz = string.sz;
        }
        else {
            String string1(string);
            swap(string1);
        }
        return *this;
    }

    char& operator[](size_t ind) {
        return symbols[ind];
    }

    const char& operator[](size_t ind) const {
        return symbols[ind];
    }

    size_t length() const {
        return sz;
    }

    size_t capacity() const {
        return reserved - 1;
    }

    size_t size() const {
        return sz;
    }

    friend bool operator==(const String& first, const String& second) {
        return strcmp(first.symbols, second.symbols) == 0;
    }

    friend bool operator<(const String& first, const String& second) {
        return strcmp(first.symbols, second.symbols) < 0;
    }

    void resize(size_t new_reserved) {
        char* old_symbols = symbols;
        symbols = new char[new_reserved];
        std::copy(old_symbols, old_symbols + std::min(new_reserved, reserved), symbols);
        delete[] old_symbols;
        reserved = new_reserved;
    }

    void push_back(char symbol) {
        if (sz == reserved - 1) {
            resize(2 * reserved);
        }
        symbols[sz++] = symbol;
        check_null();
    }

    void pop_back() {
        sz--;
        check_null();
    }

    char& front() {
        return symbols[0];
    }

    const char& front() const {
        return symbols[0];
    }

    char& back() {
        return symbols[sz - 1];
    }

    const char& back() const {
        return symbols[sz - 1];
    }

    String& operator+=(const String& string) {
        size_t new_sz = sz + string.sz;
        if (reserved < new_sz + 1) {
            size_t new_reserved = new_sz * 2;
            resize(new_reserved);
        }
        std::copy(string.symbols, string.symbols + string.sz, symbols + sz);
        sz = new_sz;
        check_null();
        return *this;
    }

    bool empty() const {
        return sz == 0;
    }

    void shrink_to_fit() {
        resize(sz + 1);
    }

    char* data() {
        return symbols;
    }

    const char* data() const {
        return symbols;
    }

    String substr(size_t start, size_t count) const {
        String answer(count, '1');
        std::copy(symbols + start, symbols + start + count,
                  answer.symbols);
        return answer;
    }

    size_t delta_find(const String& string, int start, int finish, int delta) const {
        if (string.size() > sz) {
            return sz;
        }
        for (int i = start;; i += delta) {
            bool equal = true;
            for (size_t j = 0; j < string.sz; ++j) {
                if (symbols[static_cast<size_t>(i) + j] != string[j]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                return static_cast<size_t>(i);
            }
            if (i == finish) {
                break;
            }
        }
        return sz;
    }

    size_t find(const String& string) const {
        return delta_find(string, 0, static_cast<int>(sz) - static_cast<int>(string.size()), 1);
    }

    size_t rfind(const String& string) const {
        return delta_find(string, static_cast<int>(sz) - static_cast<int>(string.size()), 0, -1);
    }

    void clear() {
        sz = 0;
        check_null();
    }

    ~String() {
        delete[] symbols;
    }
};

String operator+(String first, const String& second) {
    return first += second;
}

bool operator!=(const String& first, const String& second) {
    return !(first == second);
}

bool operator>(const String& first, const String& second) {
    return second < first;
}

bool operator>=(const String& first, const String& second) {
    return !(first < second);
}

bool operator<=(const String& first, const String& second) {
    return !(first > second);
}

std::istream& operator>>(std::istream& cin, String& string) {
    string.clear();
    char symbol;
    while (cin.get(symbol)) {
        if (symbol != ' ' && symbol != '\n') {
            string.push_back(symbol);
        }
        else if (!string.empty()) {
            break;
        }
    }
    return cin;
}

std::ostream& operator<<(std::ostream& cout, const String& string) {
    cout << string.data();
    return cout;
}
