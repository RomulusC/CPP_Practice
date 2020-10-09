#pragma once

#include <ostream>
#include <istream>

class String
{
#define BUFF_SIZE 16u
private:
    char m_smallBuff[BUFF_SIZE]{};
    char* m_buffer;
    size_t m_size;
    size_t m_nReserve;

public:
    String();

    String(size_t _reserve);   

    String(const char* _string);

    String(const String& _str);

    String(String&& _str) noexcept;

    String& operator=(const String& _str);

    String& operator=(String&& _str) noexcept;

    ~String();

    friend std::ostream& operator<<(std::ostream& _out, const String& _src);

    friend std::istream& operator>>(std::istream& _is, String& _src);

    const char* c_str();

    size_t Size();

    size_t ReservedSize();

    void Append(const char* _src);

    void Append(const String& _str);

    String& operator=(const char* _str);

    String& operator+=(const char* _str);

    String& operator+=(const String& _src);

    friend String operator+(const String& _lhs, const String& _rhs);

    friend String operator+(const String& _lhs, const char* _rhs);

    friend String operator+(const char* _lhs, String& _rhs);

    friend bool operator==(const String& _lhs, const String& _rhs);

    char* operator[](size_t _i);

    void IncreaseBufferIfLarger(size_t _n);
};

class StringView
{  
private:
    const char* m_buffStart;
    size_t m_size;
public:
    StringView(const char* _buffStart, size_t _size);

    friend std::ostream& operator<<(std::ostream& _out, const StringView& _src);
};