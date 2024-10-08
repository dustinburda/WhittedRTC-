//
// Created by Dustin on 8/10/24.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <array>
#include <string>
#include <initializer_list>

template<typename T, size_t N>
class Vector {
public:
     Vector() { std::memset(data_.data(), 0, N * sizeof (T)); }

     Vector(const std::initializer_list<T>& data) {
        if(data.size() != N) {
            std::string error_msg = "Must intitialize " + std::to_string(N) +
                                    "-tuple with " + std::to_string(N) + " elements, not "
                                    + std::to_string(data.size()) + " elements";
            throw std::logic_error(error_msg);
        }

        for(size_t index = 0; const T& element : data) {
            data_[index] = element;
            index++;
        }
    }

    Vector(const Vector<T, N - 1>& v, T val) {
         std::memcpy(data_.data(), v.data_.data(), (N - 1) * sizeof(T));
         data_[N - 1] = val;
    }

    T& operator[](size_t i) {
        if(i >= N || i < 0)
            throw std::logic_error("Index must be within bounds!");

        return data_[i];
     }

    T operator[](size_t i) const {
        if(i >= N || i < 0)
            throw std::logic_error("Index must be within bounds!");

        return data_[i];
    }

    Vector<T, N> operator-() const {
        Vector<T, N> negative;
        std::for_each(negative.data_.begin(), negative.data_.end(), [](T& elem) {
            elem = -elem;
        });

        return negative;
    }

    Vector<T, N>& operator+=(const Vector<T, N>& other) {
        size_t index = 0;
        std::for_each(data_.begin(), data_.end(), [&other, &index](T& elem){
            elem += other[index];
            index++;
        });

        return *this;
    }

    Vector<T, N>& operator-=(const Vector<T, N>& other) {
        return (*this += -other);
    }

    Vector<T, N>& operator*=(const T& scalar) {
        std::for_each(data_.begin(), data_.end(), [&scalar](T& elem){
            elem *= scalar;
        });

        return *this;
    }

    Vector<T, N>& operator/=(const T& scalar) {
        return *this *= 1/scalar;
    }

private:
    std::array<T, N> data_;
};

template<typename T, size_t N>
static Vector<T, N> operator+(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    Vector<T, N> v_plus;
    for(int i = 0; i < N; i++) {
        v_plus[i] = v1[i] + v2[i];
    }

    return v_plus;
}

template<typename T, size_t N>
static Vector<T, N>operator-(const Vector<T,N>& v1, const Vector<T, N>& v2){
    return v1 + (-v2);
}

template<typename T, size_t N>
static T dot(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    T dot_product = 0;
    for(size_t i = 0; i < N; i++) {
        dot_product += v1[i] * v2[i];
    }

    return dot_product;
}

template<typename  T, size_t N = 3>
static Vector<T, N> cross(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    if (N != 3)
        throw std::logic_error("The cross product is defined for vectors of dimension 3!");


}




#endif //TUPLE_H
