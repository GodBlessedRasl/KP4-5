#include <iostream>
#include <iomanip>
#include <fstream>


template<typename T>
class Vector {
public:
    //������ �����������
	Vector() {
		arr_ = new T[1];
		size_ = 1;
        capacity_ = 1;
	}

    //������������� ����� ����
    Vector(std::initializer_list<T>& lst) {
        size_ = lst.size();
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            arr_[i] = lst[i];
        }
    }
    
    //����������� �����������
    Vector(Vector& other) {
        delete[] arr_;
        arr_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            arr_[i] = other.arr_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    // ����������� ��������
    Vector(Vector&&  other) {
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

    // �������� ������������
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

    // �������� ��������
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

    // ������ �� �������
    T& operator[](size_t ind) {
        return arr_[ind];
    }

    const T& operator[](size_t ind) const {
        return arr_[ind];
    }

    // �������� ������
    friend std::ostream& operator << (std::ostream& out, const Vector<T>& vec) {
        for (size_t i = 0; i < size_; i++) {
            out << vec[i] << " ";
        }
        out << "\n";
        return out;
    }

    // ������� �����
    friend std::ifstream& operator >> (std::ifstream& in, const Vector<T>& vec) {
        for (size_t i = 0; i < size_; i++) {
            in >> vec[i];
        }
        return in;
    }

    // ����������
	~Vector() {
		delete[] arr_;
	}

    // �������� �� �������
	bool isEmpty() const {
		return size_ == 0;
	}

    // ��������� ����� �������
    size_t size() const {
        return size_;
    }
   
    // ��������� ������ � ��������� ������������ ����� �������
    void MemoryIncrease() {
        capacity_ *= 2;
        T* tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr_[i] = tmp[i];
        }
        delete[] tmp;
    }

    // ������� ��������
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

    // �������� ��������
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
    // ������������
    Money() {
        ruble_ = 0;
        penny_ = 0;
    }

    Money(const long ruble, const int penny) {
        ruble_ = ruble;
        penny_ = penny;
    }

    Money(Money& other) {
        ruble_ = other.ruble_;
        penny_ = other.penny_;
    }
    // �������� ������
    friend std::ostream& operator << (std::ostream& out, const Money& value) {
        out << value.ruble_ << "," << value.penny_ << "\n";
        return out;
    }

    // ������� �����
    friend std::ifstream& operator >> (std::ifstream& in, Money& value) {
        in >> value.ruble_;
        in >> value.penny_;
    }
private:
    long ruble_;
    int penny_;
};


int main() {
    Vector<int> a({ 1,2,3,4 });
	return 0;
}