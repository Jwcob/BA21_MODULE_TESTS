module;
#include <ostream>
export module SimpleStringMod;

/*
    if18b171
*/

export class SimpleStringMod
{
    private:
        char* _strData;
        std::size_t _strLength;

        // constructor from two strings for concatenation
        // is private as user does not need access  
        SimpleStringMod(char const* firstString, char const* secondString, std::size_t combinedLength)
        {
            this->_strLength = combinedLength;
            this->_strData = this->concatenate(firstString, secondString, combinedLength);
        }

        char* concatenate(char const* firstString, char const* secondString, std::size_t length)
        {
            std::size_t margin = 0;

            char* newData = new char[length + 1];

            for (std::size_t i = 0; firstString[i] != '\0'; i++)
            {
                newData[margin++] = firstString[i];
            }

            for (std::size_t i = 0; secondString[i] != '\0'; i++)
            {
                newData[margin++] = secondString[i];
            }

            newData[length] = '\0';

            return newData;
        }

    public:
        // default constructor
        SimpleStringMod() : _strData(new char[1]), _strLength(0)
        {
            this->_strData[0] = '\0';
        }

        // constructor from char array
        SimpleStringMod(char const* string)
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
        SimpleStringMod(SimpleStringMod const& other) : _strLength(other._strLength)
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
        SimpleStringMod& operator =(SimpleStringMod const& other)
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
        SimpleStringMod(SimpleStringMod&& other) noexcept : _strData(std::move(other._strData)), _strLength(std::move(other._strLength))
        {
            other._strData = nullptr;
            // setting strLength to 0 wouldnt actually be needed as the value shouldnt be accessed after being moved
            other._strLength = 0;
        }

        // move assignment operator
        SimpleStringMod& operator =(SimpleStringMod&& other)
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
        ~SimpleStringMod()
        {
            // delete char array on delete to free used heap memory
            delete[](this->_strData);
        }

        // concatenate for SimpleString objects
        // passes values to its own constructor to prevent unnecessary copying of data
        SimpleStringMod concatenate(SimpleStringMod const& string) const
        {
            std::size_t const newLen = this->_strLength + string._strLength;
            return SimpleStringMod(this->_strData, string._strData, newLen);
        }

        // concatenate overload for char arrays to prevent unnecessary creation of new SimpleString object
        // passes values to its own constructor to prevent unnecessary copying of data
        SimpleStringMod concatenate(char const* string) const
        {
            std::size_t const newLen = this->_strLength + this->getLength(string);
            return SimpleStringMod(this->_strData, string, newLen);
        }

        SimpleStringMod& operator += (SimpleStringMod const& other)
        {
            this->_strLength = this->_strLength + other._strLength;

            char* newData = this->concatenate(this->_strData, other.c_str(), this->_strLength);

            delete[] this->_strData;
            this->_strData = newData;

            return *this;
        }

        SimpleStringMod& operator += (char const* other)
        {
            this->_strLength = this->_strLength + getLength(other);

            char* newData = this->concatenate(this->_strData, other, this->_strLength);

            delete[] this->_strData;
            this->_strData = newData;

            return *this;
        }

        operator const char* () const
        {
            return this->c_str();
        }

        std::size_t getLength() const
        {
            return this->_strLength;
        }

        std::size_t getLength(char const* string) const
        {
            std::size_t charCount = 0;
            while (string[charCount] != '\0') charCount++;

            return charCount;
        }

        char const* c_str() const
        {
            return this->_strData;
        }

        // friend function to overload << operator to print SimpleStrings
        friend std::ostream& operator <<(std::ostream& os, const SimpleStringMod& str);
};
