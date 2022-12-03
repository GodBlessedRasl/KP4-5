#include <iostream>
#include <iomanip>
#include <fstream>


template<typename T>
class Vector {
public:
    //empty constructor
	Vector() {
		arr_ = new T[1];
		size_ = 1;
        capacity_ = 1;
	}

    //initialization using list
    Vector(std::initializer_list<T>& lst) {
        size_ = lst.size();
        capacity_ = 2 * size_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_;i++) {
            arr_[i] = *(lst.begin() + i);
        }
    }
    
    //copy constructor
    Vector(Vector& other) {
        delete[] arr_;
        arr_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            arr_[i] = other.arr_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    // move constructor
    Vector(Vector&&  other) noexcept{
        arr_ = other.arr_;
        for (size_t i = 0; i < other.size_; ++i) {
            arr_[i] = other.arr_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] other.arr_;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // assignment operator
    Vector& operator=(Vector& other) {
        if (this != &other) {
            delete[] arr_;
            arr_ = new T[other.capacity_];
            for (size_t i = 0; i < other.size_; ++i) {
                arr_[i] = other.arr_[i];
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    // move operator
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // accessment by the index
    T& operator[](size_t ind) {
        return arr_[ind];
    }

    const T& operator[](size_t ind) const {
        return arr_[ind];
    }

    // output operator
    friend std::ostream& operator << (std::ostream& out, Vector<T>& vec) {
        for (size_t i = 0; i < vec.size_; i++) {
            out << vec.arr_[i] << " ";
        }
        return out;
    }

    // input operator
    friend std::ifstream& operator >> (std::ifstream& in, const Vector<T>& vec) {
        for (size_t i = 0; i < vec.size_; i++) {
            in >> vec.arr_[i];
        }
        return in;
    }

    // destructor
	~Vector() {
		delete[] arr_;
	}

    // checking if the vector is empty
	bool isEmpty() const {
		return size_ == 0;
	}

    // getting the size of the vector
    size_t size() const {
        return size_;
    }
   
    // memory allocating and max vector size increasing 
    void MemoryIncrease() {
        capacity_ *= 2;
        T* tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr_[i] = tmp[i];
        }
        delete[] tmp;
    }

    // insert element
    bool insert(const int position, const T element) {
        if (position < 0 || position > size_) {
            return false;
        }
        else {
            if (size_ >= capacity_) MemoryIncrease();
            for (size_t i = size_; i >= position; i--) {
                arr_[i] = arr_[i - 1];
            }
            arr_[position] = element;
            ++size_;
        }
    }

    // delete element
    bool erase(const int position) {
        if (position < 0 || position >= size_) {
            return false;
        }
        else {
            for (size_t i = position + 1; i < size_; i++) {
                arr_[i - 1] = arr_[i];
            }
            --size_;
        }
    }

private:
	T* arr_;
	size_t size_;
    size_t capacity_;
};

class Money {
public:
    // constructors
    Money() {
        ruble_ = 0;
        penny_ = 0;
    }

    Money(const long ruble, const int penny) {
        ruble_ = ruble;
        penny_ = penny;
    }
    // copy
    Money(const Money& other) {
        ruble_ = other.ruble_;
        penny_ = other.penny_;
    }

    // move
    Money(Money&& other) noexcept{
        ruble_ = other.ruble_;
        penny_ = other.penny_;
        other.ruble_ = 0;
        other.penny_ = 0;
    }
    // assignment
    Money& operator=(const Money& other) {
        if (this != &other) {
            ruble_ = other.ruble_;
            penny_ = other.penny_;
        }
        return *this;
    }

    // assignmnt operator
    Money& operator=(Money&& other) noexcept {
        if (this != &other) {
            ruble_ = other.ruble_;
            penny_ = other.penny_;
            other.ruble_ = 0;
            other.penny_ = 0;
        }
        return *this;
    }

    // input operator
    friend std::ostream& operator << (std::ostream& out, const Money& value) {
        out << value.ruble_ << "," << value.penny_;
        return out;
    }

    // output operator
    friend std::ifstream& operator >> (std::ifstream& in, Money& value) {
        in >> value.ruble_;
        in >> value.penny_;
    }
private:
    long ruble_;
    int penny_;
};


int main() {
    setlocale(LC_ALL, "Russian");
    // testing program for container class
    std::initializer_list<double>a = { 2.9, 4.6 };
    Vector<double> vec(a);
    std::cout << vec << "\n";

    vec.insert(2, 3);
    std::cout << vec << "\n";

    vec.insert(2, 0);
    std::cout << vec << "\n";

    vec.erase(2);
    std::cout << vec << "\n";

    std::cout << vec.size() << "\n";

    std::cout << vec[1] << "\n";

    std::cout << vec.isEmpty() << "\n";

    std::initializer_list<float>b = { 2e3, 3e3 };
    Vector<float> vec2(b);
    std::cout << vec2 << "\n";

    std::initializer_list<int>c = { 2, 3 };
    Vector<int> vec3(c);
    std::cout << vec3 << "\n";

    // testing program for custom class

    Money denga(2, 30);
    std::cout << denga;

    std::initializer_list<Money>d = { Money(2,30), Money(3,30), Money(4,30)};
    Vector<Money> vec4(d);
    std::cout << vec4 << "\n";
	return 0;
}