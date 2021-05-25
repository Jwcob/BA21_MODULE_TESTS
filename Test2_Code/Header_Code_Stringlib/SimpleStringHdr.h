#ifndef SIMPLESTRING
#define SIMPLESTRING

#include <ostream>

class SimpleString {
private:
    char* _strData;
    std::size_t _strLength;
    SimpleString(char const* firstString, char const* secondString, std::size_t combinedLength);
public:
    SimpleString();
    SimpleString(char const* string);
    SimpleString(SimpleString const& other);
    SimpleString& operator =(SimpleString const& other);
    SimpleString(SimpleString&& other) noexcept;
    ~SimpleString();
    SimpleString& operator =(SimpleString&& other) noexcept;
    SimpleString concatenate(SimpleString const& string) const;
    SimpleString concatenate(char const* string) const;
    std::size_t getLength() const;
    std::size_t getLength(char const* string) const;
    char const* c_str() const;
};

#endif