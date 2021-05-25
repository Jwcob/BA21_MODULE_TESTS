#include "SimpleStringHdr.h"

/*
    if18b171
*/

// constructor from two strings for concatenation
// is private as user does not need access
SimpleString::SimpleString(char const* firstString, char const* secondString, std::size_t combinedLength)
{
    this->_strLength = combinedLength;
    this->_strData = new char[combinedLength + 1];

    std::size_t margin = 0;

    //Inserting first String into new array
    for (std::size_t i = 0; firstString[i] != '\0'; i++)
    {
        this->_strData[margin++] = firstString[i];
    }

    //Inserting second String into new array
    for (std::size_t i = 0; secondString[i] != '\0'; i++)
    {
        this->_strData[margin++] = secondString[i];
    }

    //appending null-terminator at the end of the string
    this->_strData[this->_strLength] = '\0';
}

// default constructor
SimpleString::SimpleString() : _strData(new char[1]), _strLength(0)
{
    this->_strData[0] = '\0';
}

// constructor from char array
SimpleString::SimpleString(char const* string)
{
    //'\0' is ignored by the String Length
    this->_strLength = this->getLength(string);
    this->_strData = new char[this->_strLength + 1];

    for (std::size_t i = 0; i < this->getLength(); i++) {
        this->_strData[i] = string[i];
    }

    //appending null-terminator at the end of the string
    this->_strData[this->_strLength] = '\0';
}

// copy constructor
SimpleString::SimpleString(SimpleString const& other) : _strLength(other._strLength)
{
    // create new char array
    this->_strData = new char[this->_strLength + 1];

    // deep copy other char array into this one
    for (std::size_t i = 0; i <= this->_strLength; i++)
    {
        this->_strData[i] = other._strData[i];
    }
}

// copy assignment operator
SimpleString& SimpleString::operator =(SimpleString const& other)
{
    // check if trying to copy self
    if (this != &other)
    {
        this->_strLength = other._strLength;

        // delete old char array to free memory
        delete[](this->_strData);

        this->_strData = new char[this->_strLength + 1];

        // deep copy
        for (std::size_t i = 0; i <= other._strLength; i++)
        {
            this->_strData[i] = other._strData[i];
        }
    }

    return *this;
}

// move constructor
SimpleString::SimpleString(SimpleString&& other) noexcept : _strData(std::move(other._strData)), _strLength(std::move(other._strLength))
{
    other._strData = nullptr;
    // setting strLength to 0 wouldnt actually be needed as the value shouldnt be accessed after being moved
    other._strLength = 0;
}

// move assignment operator
SimpleString& SimpleString::operator =(SimpleString&& other) noexcept
{
    // check if trying to move self into self 
    if (this != &other)
    {
        // delete old char array to free memory and prevent leak
        delete[](this->_strData);

        // pass pointer ownership
        this->_strData = std::move(other._strData);

        this->_strLength = std::move(other._strLength);

        // set old pointer to nullptr to pass its ownership
        other._strData = nullptr;
        // setting strLength to 0 wouldnt actually be needed as the value shouldnt be accessed after being moved
        other._strLength = 0;
    }

    return *this;
}

// destructor
SimpleString::~SimpleString()
{
    // delete char array on delete to free used heap memory
    delete[](this->_strData);
}

// concatenate for SimpleString objects
// passes values to its own constructor to prevent unnecessary copying of data
SimpleString SimpleString::concatenate(SimpleString const& string) const
{
    std::size_t const newLen = this->_strLength + string.getLength();
    return SimpleString(this->_strData, string._strData, newLen);
}

// concatenate overload for char arrays to prevent unnecessary creation of new SimpleString object
// passes values to its own constructor to prevent unnecessary copying of data
SimpleString SimpleString::concatenate(char const* string) const
{
    std::size_t const newLen = this->_strLength + this->getLength(string);
    return SimpleString(this->_strData, string, newLen);
}

// getter for _strLength
std::size_t SimpleString::getLength() const
{
    return this->_strLength;
}

// getLength overload for char arrays to get its length
std::size_t SimpleString::getLength(char const* string) const
{
    std::size_t charCount = 0;
    while (string[charCount] != '\0') charCount++;

    return charCount;
}

// getter for _strData
char const* SimpleString::c_str() const
{
    return this->_strData;
}
