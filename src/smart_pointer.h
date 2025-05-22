#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class SmartPointer {
private:
    T* ptr;
    std::size_t* count;

    void release() {
        if (count != nullptr) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
            ptr = nullptr;
            count = nullptr;
        }
    }

public:
    explicit SmartPointer(T* raw_ptr = nullptr) : ptr(nullptr), count(nullptr) {
        if (raw_ptr != nullptr) {
            try {
                count = new std::size_t(1);
                ptr = raw_ptr;
            } catch (...) {
                delete raw_ptr;
                throw;
            }
        }
    }

    SmartPointer(const SmartPointer& other) noexcept 
        : ptr(other.ptr), count(other.count) {
        if (count != nullptr) {
            ++(*count);
        }
    }

    SmartPointer(SmartPointer&& other) noexcept : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }
    
    ~SmartPointer() noexcept {
        release();
    }

    T* get_ptr() const noexcept { return ptr; }
    std::size_t get_count() const noexcept { return count == nullptr ? 0 : *count; }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this == &other) {
            return *this;
        }

        release();
        ptr = other.ptr;
        count = other.count;
        if (count != nullptr) {
            ++(*count);
        }

        return *this;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        release();
        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr;
        other.count = nullptr;
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const noexcept {
        return ptr;
    }

    explicit operator bool() const noexcept {
        return ptr != nullptr;
    }

    friend bool operator==(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr == second.ptr;
    }
    friend bool operator!=(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr != second.ptr;
    }
    friend bool operator<(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr < second.ptr;
    }
    friend bool operator<=(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr <= second.ptr;
    }
    friend bool operator>(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr > second.ptr;
    }
    friend bool operator>=(const SmartPointer& first, const SmartPointer& second) noexcept {
        return first.ptr >= second.ptr;
    }

    void swap(SmartPointer& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(count, other.count);
    }
};

template<typename T>
void swap(SmartPointer<T>& first, SmartPointer<T>& second) noexcept {
    first.swap(second);
}
