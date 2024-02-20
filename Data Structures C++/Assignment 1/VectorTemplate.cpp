#include <iostream>
#include <assert.h>

template <typename T>
class MyVector {
private:
    T* data;        // Pointer to the dynamically allocated array
    int capacity;   // Current capacity of the array
    int size;       // Number of elements in the vector

public:
    // Default constructor
    MyVector() : data(nullptr), capacity(0), size(0) {}

    // Constructor that takes size as input
    MyVector(int sz) : capacity(sz), size(sz) {
        data = new T[capacity];
    }

    // Copy constructor
    MyVector(const MyVector& vin) : capacity(vin.capacity), size(vin.size) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = vin.data[i];
        }
    }

    // Appends to the end of the array
    void pushBack(const T& ele) {
        if (size == capacity) {
            // Increace capacity if necessary
            capacity = (capacity == 0) ? 1 : capacity + 7;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = ele;
    }

    // Inserts at the i-th position in the array
    void insert(int i, const T& ele) {
        if (i < 0 || i > size) {
            throw std::out_of_range("Index out of range");
        }

        if (size == capacity) {
            // Double the capacity if needed
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (int j = 0; j < i; ++j) {
                newData[j] = data[j];
            }
            newData[i] = ele;
            for (int j = i; j < size; ++j) {
                newData[j + 1] = data[j];
            }
            delete[] data;
            data = newData;
        } else {
            for (int j = size; j > i; --j) {
                data[j] = data[j - 1];
            }
            data[i] = ele;
        }
        size++;
    }

    // Reads the i-th element
    T at(int i) const {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    // Overloaded [] operator that reads the i-th element
    T operator[](int i) const {
        return at(i);
    }

    // Overloaded = copy assignment operator
    MyVector& operator=(const MyVector& other) {
        if (this == &other) {
            return *this; // Self-assignment, no action needed
        }

        // Deallocate existing resources
        delete[] data;

        // Copy data from the other vector
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // Deletes the i-th element
    void erase(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (int j = i; j < size - 1; ++j) {
            data[j] = data[j + 1];
        }
        size--;

        // Shrink the capacity if size is less than half of capacity
        if (size < capacity / 2) {
            capacity /= 2;
            T* newData = new T[capacity];
            for (int j = 0; j < size; ++j) {
                newData[j] = data[j];
            }
            delete[] data;
            data = newData;
        }
    }

    // Returns the number of elements
    int getSize() const {
        return size;
    }

    // Returns true if empty else false
    bool isEmpty() const {
        return size == 0;
    }

    // Destructor
    ~MyVector() {
        delete[] data;
        // Reset capacity and size to zero
        capacity = 0;
        size = 0;
        data = nullptr;
    }
};



// Test cases for the MyVector class
int main() {
    MyVector<int> vec;
    vec.pushBack(1);
    vec.pushBack(2);
    vec.pushBack(3);

    // Test pushBack and getSize
    assert(vec.getSize() == 3);

    // Test at and operator[]
    assert(vec.at(0) == 1);
    assert(vec[1] == 2);

    // Test insert
    vec.insert(1, 5);
    assert(vec.at(1) == 5);
    assert(vec.at(2) == 2);

    // Test erase
    vec.erase(0);
    assert(vec.at(0) == 5);
    assert(vec.getSize() == 3);

    // Test isEmpty
    assert(!vec.isEmpty());

    // Test copy constructor
    MyVector<int> vec2 = vec;
    assert(vec2.getSize() == 3);
    assert(vec2.at(0) == 5);

    // Test 2nd constructor
    MyVector<int> vec3(2);
    vec.pushBack(9);
    vec.pushBack(8);

    // Test copy assignment
    vec3 = vec2;
    assert(vec3.getSize() == 3);
    assert(vec3.at(1) == 2);

    // Test destructor
    vec2.~MyVector();
    assert(vec2.isEmpty());

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
