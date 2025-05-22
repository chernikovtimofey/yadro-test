#include "../src/smart_pointer.h"
#include <iostream>
#include <cassert>

class SomeClass {
public:
    int field = 42;
};

void test_SmartPointer() {
    // testing default constructor
    SmartPointer<int> ptr1;
    assert(!ptr1);
    assert(ptr1.get_ptr() == nullptr);
    assert(ptr1.get_count() == 0);
    
    // testing constructor from raw pointer
    SmartPointer<int> ptr2(new int(42));
    assert(ptr2);
    assert(*ptr2 == 42);
    assert(ptr2.get_count() == 1);

    // testing constructor from another pointer
    SmartPointer<int> ptr3(ptr2);
    assert(ptr3);
    assert(*ptr3 == 42);
    assert(ptr2.get_count() == 2);
    assert(ptr3.get_count() == 2);

    // testing constructor from move
    SmartPointer<int> ptr4(std::move(ptr3));
    assert(ptr4);
    assert(*ptr4 == 42);
    assert(ptr4.get_count() == 2);
    assert(!ptr3);
    assert(ptr3.get_count() == 0);

    // testing deconstructor
    {
        SmartPointer<int> ptr(ptr4);
        assert(ptr);
        assert(*ptr == 42);
        assert(ptr.get_count() == 3);
        assert(!ptr3);
        assert(ptr4.get_count() == 3);
    }
    assert(ptr4);
    assert(*ptr4 == 42);
    assert(ptr4.get_count() == 2);

    // testing self assignment
    ptr4 = ptr4;
    assert(*ptr4 == 42);
    assert(ptr4.get_count() == 2);

    // testing pointer assignment
    SmartPointer<int> ptr5;
    ptr5 = ptr2;
    assert(ptr5);
    assert(*ptr5 == 42);
    assert(ptr5.get_count() == 3);
    assert(ptr2.get_count() == 3);

    // testing move assignment
    SmartPointer<int> ptr6;
    ptr6 = std::move(ptr2);
    assert(ptr6);
    assert(*ptr6 == 42);
    assert(ptr6.get_count() == 3);
    assert(!ptr2);
    assert(ptr2.get_count() == 0);

    // testing swap
    SmartPointer<int> ptr7(new int(100));
    swap(ptr6, ptr7);
    assert(*ptr6 == 100);
    assert(*ptr7 == 42);
}

int main() {
    test_SmartPointer();
    std::cout << "SmartPointer tests successfully passed" << std::endl;
}