#ifndef POINTER_H
#define POINTER_H

#include <cassert>
#include <utility>

//if18b171

/* 
- Tested with multiple compilers at www.godbolt.org 
- Checked for MemoryLeaks with Valgrind
- Reference used: https://thecandcppclub.com/deepeshmenon/chapter-9-introduction-to-template-specialization-in-c/754/
*/

template <typename Type>
class DefaultDeleter
{
    public:
        void operator () (Type* ptr)
        {
            if (ptr != nullptr) { delete ptr; }
        }
};

template <typename Type, typename DefaultDeleter = DefaultDeleter<Type>>
class UniquePointer
{
    private:
        Type* ptr = nullptr;
        DefaultDeleter deleter;

    public:
        // uses the given Deleter
        ~UniquePointer()
        {
            this->deleter(this->ptr);
        }

        UniquePointer() = default;

        UniquePointer(Type* ptr) : ptr(ptr) {}

        UniquePointer(Type* ptr, DefaultDeleter deleter) : ptr(ptr), deleter(deleter) {}

        // Copy Constructor deleted as only one UniquePointer may exist for each RawPointer
        UniquePointer(const UniquePointer& other) = delete;

        // Copy Assignment Operator deleted as only one UniquePointer may exist for each RawPointer
        UniquePointer& operator = (const UniquePointer& other) = delete;
        
        UniquePointer(UniquePointer&& other) : ptr(std::move(other.ptr)), deleter(std::move(other.deleter))
        {
            other.ptr = nullptr;
        }

        // When using the Assign Operator, the referenced Pointer must be freed from other
        UniquePointer& operator = (UniquePointer&& other)
        {
            this->reset();
            this->ptr = other.release();
            this->deleter = other.deleter;
            return *this;
        }

        // Referenced Object gets deleted as there are no other pointers left to point at it
        void reset()
        {
            this->deleter(this->ptr);
            this->ptr = nullptr;
        }

        // Raw Pointer ownership gets released and returned
        Type* release()
        {
            Type* tmp_ptr = this->ptr;
            this->ptr = nullptr;
            return tmp_ptr;
        }

        void swap(Type*& other)
        {
            std::swap(this->ptr, other);
        }

        Type* operator -> () const
        {
            return this->ptr;
        }

        Type& operator * () const
        {
            return *this->ptr;
        }

        operator bool () const
        {
            return this->ptr != nullptr;
        }

        DefaultDeleter& getDeleter()
        {
            return this->deleter;
        }
};

#endif
