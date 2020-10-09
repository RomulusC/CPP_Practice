#include "rstring.h"

#ifdef _DEBUG
#include <iostream>
#endif

#include <cassert>

    String::String()
        : m_smallBuff()
        , m_buffer(nullptr)
        , m_size(0u)
        , m_nReserve(BUFF_SIZE)
    {
        m_buffer = &m_smallBuff[0];
#ifdef _DEBUG
        std::cout << "Default Constructor\nSmallString\n";
#endif
        for (size_t i = 0; i < BUFF_SIZE; i++)
            m_smallBuff[i] = '\0';
    }

    String::String(size_t _reserve)
    {
        for (size_t i = 0; i < BUFF_SIZE; i++)
            m_smallBuff[i] = '\0';

        m_buffer = &m_smallBuff[0];
        m_nReserve = BUFF_SIZE;
        m_size = 0u;

        if (_reserve > BUFF_SIZE)
        {
            IncreaseBufferIfLarger(_reserve); // m_nReserve changed            
        }
    }

    String::String(const char* _string)
    {
#ifdef _DEBUG
        std::cout << "Constructor\n";
#endif
        m_size = strlen(_string);
        if (m_size + 1 <= BUFF_SIZE)
        {
#ifdef _DEBUG
            std::cout << "Small String \n";
#endif
            m_buffer = &m_smallBuff[0];
            m_nReserve = BUFF_SIZE;
        }
        else
        {
            m_nReserve = BUFF_SIZE;
            while (m_size + 1 > m_nReserve)
            {
                m_nReserve *= 2;
            }
            m_buffer = new char[m_nReserve];
        }

        memcpy(m_buffer, _string, m_size + (size_t)1);
    }

    String::String(const String& _str)
        : m_size(_str.m_size)
        , m_nReserve(_str.m_nReserve)
    {
#ifdef _DEBUG
        std::cout << "Copy Constructor\n";
#endif
        if (m_nReserve <= BUFF_SIZE) // If small string
        {

#ifdef _DEBUG
            std::cout << "Small String \n";
#endif
            m_buffer = &m_smallBuff[0];
        }
        else
        {
            m_buffer = new char[m_nReserve];
        }

        memcpy(m_buffer, _str.m_buffer, m_size + (size_t)1);
    }

    String::String(String&& _str) noexcept
        : m_size(_str.m_size)
        , m_nReserve(_str.m_nReserve)
    {
#ifdef _DEBUG
        std::cout << "Move Constructor\n";
#endif
        if (m_nReserve <= BUFF_SIZE) // If small string
        {
#ifdef _DEBUG
            std::cout << "Small String \n";
#endif
            m_buffer = &m_smallBuff[0];
            memcpy(m_buffer, _str.m_buffer, m_size + 1);
        }
        else
        {
            m_buffer = _str.m_buffer;
            _str.m_buffer = nullptr;
        }

        _str.~String();
    }

    String& String::operator=(const String& _str)
    {
#ifdef _DEBUG
        std::cout << "Copy Assignment\n";
#endif
        if (_str.m_size + 1 > m_nReserve)
        {
            if (m_nReserve == BUFF_SIZE)
            {
#ifdef _DEBUG
                std::cout << "Small String deletion\n";
#endif
                for (size_t i = 0; i < BUFF_SIZE; i++)
                    m_smallBuff[i] = '\0';
                m_buffer = nullptr;
            }

            delete[] m_buffer;
            m_nReserve = _str.m_nReserve;
            m_buffer = new char[m_nReserve];
        }

        memcpy(m_buffer, _str.m_buffer, _str.m_size + 1);

        return *this;
    }

    String& String::operator=(String&& _str) noexcept
    {
#ifdef _DEBUG
        std::cout << "Move Assignment\n";
#endif

        if (m_buffer != &m_smallBuff[0])
        {
#ifdef _DEBUG
            std::cout << "Deletion occured\n";
#endif
            delete[] m_buffer;
        }

        m_size = _str.m_size;
        m_nReserve = _str.m_nReserve;

        if (_str.m_buffer == &_str.m_smallBuff[0])
        {
            m_buffer = &m_smallBuff[0];
            memcpy(m_buffer, _str.m_buffer, m_size + 1);
        }
        else
        {
            m_buffer = _str.m_buffer;
        }
        _str.m_buffer = nullptr;

        return *this;
    }

    String::~String()
    {
#ifdef _DEBUG
        std::cout << "Destructor: ";
#endif

        if (m_buffer != nullptr && m_buffer != &m_smallBuff[0])
        {
            delete[] m_buffer;
        }
        else
        {
#ifdef _DEBUG
            std::cout << "No heap allocated memory deleted.\n";
#endif
        }
        m_buffer = nullptr;
        m_nReserve = 0u;
        m_size = 0u;

        for (size_t i = 0; i < BUFF_SIZE; i++)
            m_smallBuff[i] = '\0';

    }

    std::ostream& operator<<(std::ostream& _out, const String& _src)
    {
        return _out << _src.m_buffer;
    }

#define IN_BUFF 256
    std::istream& operator>>(std::istream& _is, String& _src)
    {
        char buff[IN_BUFF];
        _is.get(buff, IN_BUFF);

        assert(_is.gcount() < IN_BUFF - 1); // Exceeded buffer

        _src.Append(buff);
        return _is;    
    }

    const char* String::c_str()
    {
        return m_buffer;
    }

    size_t String::Size()
    {
        return m_size;
    }

    size_t String::ReservedSize()
    {
        return m_nReserve;
    }

    void String::Append(const char* _src)
    {
        size_t old_nReserve = m_nReserve;
        while (strlen(_src) + m_size + 1 > m_nReserve)
        {
            m_nReserve *= 2;
        }

        if (old_nReserve < m_nReserve)
        {
            char* oldBuff = m_buffer;
            m_buffer = new char[m_nReserve];
            memcpy(m_buffer, oldBuff, m_size + 1);

            if (old_nReserve == BUFF_SIZE)
            {
                for (size_t i = 0; i < BUFF_SIZE; i++)
                    m_smallBuff[i] = '\0';
#ifdef _DEBUG
                std::cout << "SmallString deleted\n";
#endif   
            }
            else
            {
                delete[] oldBuff;
            }

        }

        memcpy(&m_buffer[m_size], _src, strlen(_src));
        m_size += strlen(_src);
        m_buffer[m_size] = '\0';
    }

    void String::Append(const String& _str)
    {
        size_t old_nReserve = m_nReserve;
        while (_str.m_size + m_size + 1 > m_nReserve)
        {
            m_nReserve *= 2;
        }

        if (old_nReserve < m_nReserve)
        {
            char* oldBuff = m_buffer;
            m_buffer = new char[m_nReserve]();
            memcpy(m_buffer, oldBuff, m_size);

            if (old_nReserve == BUFF_SIZE)
            {
                for (size_t i = 0; i < BUFF_SIZE; i++)
                    m_smallBuff[i] = '\0';
#ifdef _DEBUG
                std::cout << "SmallString deleted\n";
#endif 
            }
            else
            {
                delete[] oldBuff;
            }
        }

        memcpy(&m_buffer[m_size], _str.m_buffer, _str.m_size);
        m_size += _str.m_size;
        m_buffer[m_size] = '\0';
    }

    String& String::operator=(const char* _str)
    {
        size_t old_nReserve = m_nReserve;
        while (strlen(_str) + m_size + 1 > m_nReserve)
        {
            m_nReserve *= 2;
        }

        if (old_nReserve < m_nReserve)
        {
            if (old_nReserve == BUFF_SIZE)
            {
                for (size_t i = 0; i < BUFF_SIZE; i++)
                    m_smallBuff[i] = '\0';
                m_buffer = nullptr;
            }
            delete[] m_buffer;
            m_buffer = new char[m_nReserve]();
        }

        m_size = strlen(_str);
        memcpy(m_buffer, _str, m_size);
        m_buffer[m_size] = '\0';

        return *this;
    }

    String& String::operator+=(const char* _str)
    {
        this->IncreaseBufferIfLarger(strlen(_str) + m_size + 1);
        this->Append(_str);
        return *this;
    }

    String& String::operator+=(const String& _src)
    {
        this->IncreaseBufferIfLarger(_src.m_size + m_size + 1);
        this->Append(_src);
        return *this;
    }

    String operator+(const String& _lhs, const String& _rhs)
    {
        String str(_lhs.m_size + _rhs.m_size + 1);
        str += _lhs;
        str += _rhs;
        return str;
    }

    String operator+(const String& _lhs, const char* _rhs)
    {
        String str(_lhs.m_size + strlen(_rhs) + 1);
        str += _lhs;
        str += _rhs;
        return str;
    }

    String operator+(const char* _lhs, String& _rhs)
    {
        String str(strlen(_lhs) + _rhs.m_size + 1);
        str += _lhs;
        str += _rhs;
        return str;
    }

    bool operator==(const String& _lhs, const String& _rhs)
    {
        if (strcmp(_lhs.m_buffer, _rhs.m_buffer) == 0)
            return true;
        else
            return false;
    }

    char* String::operator[](size_t _i)
    {
        assert(_i < m_size);
        return &m_buffer[_i];
    }

    void String::IncreaseBufferIfLarger(size_t _n)
    {
        if (m_nReserve >= _n)
        {
            return;
        }
#ifdef _DEBUG
        std::cout << "IncreaseBufferIfLarger fn FROM: " << m_nReserve << "| TO: " << _n << std::endl;
#endif 
        m_nReserve = _n;
        if (m_buffer == &m_smallBuff[0])
        {
            m_buffer = new char[m_nReserve];
            if (m_size > 0)
                memcpy(m_buffer, &m_smallBuff[0], m_size + 1);
            for (size_t i = 0; i < BUFF_SIZE; i++)
                m_smallBuff[i] = '\0';
        }
        else if (m_buffer != nullptr)
        {
            char* oldBuff = m_buffer;
            m_buffer = new char[m_nReserve];
            if (m_size > 0)
                memcpy(m_buffer, oldBuff, m_size + 1);
            delete[] oldBuff;
        }
    }

    StringView::StringView(const char* _buffStart, size_t _size)
        : m_buffStart(_buffStart)
        , m_size(_size)
    {}

    std::ostream& operator<<(std::ostream& _out, const StringView& _src)
    {
        if (_src.m_size > 0)
        {
            return _out.write(_src.m_buffStart, _src.m_size);
        }
        else
        {
            return _out << _src.m_buffStart;
        }
    }
