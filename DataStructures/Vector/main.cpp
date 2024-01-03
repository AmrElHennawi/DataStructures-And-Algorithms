#include <iostream>

using namespace std;

template <typename Object>
class Vector
{
private:
    int size;
    int capacity;
    Object *object;
    static const int SPARE_CAPACITY = 16;
public:
    explicit Vector(int initSize = 0) : size{initSize},
                                        capacity{initSize + SPARE_CAPACITY}
    {
        object = new Object[capacity];
    }

    Vector(const Vector &rhs) : size{rhs.size},
                                capacity{rhs.capacity}, object{nullptr}
    {
        object = new Object[capacity];
        for (int i = 0; i < size; ++i)
            object[i] = rhs.object[i];
    }

    Vector &operator=(const Vector &rhs)
    {
        if (this != &rhs)
        {
            Vector copy = rhs;
            swap(*this, copy);
        }
        return *this;
    }

    Vector(Vector &&rhs) noexcept : size{rhs.size},
                                    capacity{rhs.capacity}, object{rhs.object}
    {
        rhs.object = nullptr;
        rhs.size = 0;
        rhs.capacity = 0;
    }

    Vector &operator=(Vector &&rhs) noexcept
    {
        if (this != &rhs)
        {
            swap(size, rhs.size);
            swap(capacity, rhs.capacity);
            swap(object, rhs.object);
        }
        return *this;
    }

    void resize(int newSize)
    {
        if (newSize > capacity)
            reserve(newSize * 2);
        size = newSize;
    }

    void reserve(int newCapacity)
    {
        if (newCapacity <= size)
            return;

        Object *newArray = new Object[newCapacity];
        for (int i = 0; i < size; ++i)
            newArray[i] = move(object[i]);

        capacity = newCapacity;
        swap(object, newArray);
        delete[] newArray;
    }

    Object &operator[](int index)
    {
        return object[index];
    }

    const Object &operator[](int index) const
    {
        return object[index];
    }

    bool empty() const
    {
        return Size() == 0;
    }

    int Size() const
    {
        return size;
    }

    int Capacity() const
    {
        return capacity;
    }

    void push_back(const Object &element)
    {
        if (size == capacity)
            reserve(2 * capacity + 1);
        object[size++] = element;
    }

    void push_back(Object &&element)
    {
        if (size == capacity)
            reserve(2 * capacity + 1);
        object[size++] = move(element);
    }

    void pop_back()
    {
        --size;
    }

    const Object &back() const
    {
        return object[size - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin()
    {
        return &object[0];
    }

    const_iterator begin() const
    {
        return &object[0];
    }

    iterator end()
    {
        return &object[Size()];
    }

    const_iterator end() const
    {
        return &object[Size()];
    }
    ~Vector()
    {
        delete[] object;
    }
};

int main() {
    // Test default constructor
    Vector<int> vec;

    // Test push_back
    for (int i = 1; i <= 10; ++i) {
        vec.push_back(i);
    }

    // Test iterator and const_iterator
    cout << "Vector elements using iterator: ";
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Vector elements using const_iterator: ";
    for (Vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Test resize and Capacity
    vec.resize(15);
    cout << "Vector size: " << vec.Size() << ", Capacity: " << vec.Capacity() << endl;

    // Test operator[]
    for (int i = 9; i < 15; ++i) {
        vec[i] = i + 1;
    }

    // Test pop_back
    vec.pop_back();
    cout << "Vector size after pop_back: " << vec.Size() << ", Back element: " << vec.back() << endl;

    // Test copy assignment
    Vector<int> vecCopy = vec;

    // Test move assignment
    Vector<int> vecMove = move(vec);

    // Test empty
    cout << "Is vec empty? " << (vec.empty() ? "Yes" : "No") << endl;
    cout << "Is vecCopy empty? " << (vecCopy.empty() ? "Yes" : "No") << endl;

    return 0;
}