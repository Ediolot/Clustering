//
// Created by jsier on 10/06/2021.
//

#ifndef CLUSTERING_VECTOR_H
#define CLUSTERING_VECTOR_H

#include <cassert>
#include <cmath>


template<class T, size_t dims>
class Vector {
public:
    explicit Vector(std::array<T, dims> elements);
    Vector(const Vector& v);
    Vector(Vector&& v) noexcept;
    Vector() = default;
    ~Vector() = default;

    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator=(const Vector& v);

    Vector operator+(const T& value);
    Vector operator-(const T& value);
    Vector& operator/=(const T& value);
    Vector& operator*=(const T& value);

    Vector operator+(Vector&& v);
    Vector operator-(Vector&& v);
    Vector& operator=(Vector&& v) noexcept;

    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);

    const T& operator[](size_t i) const;
    T& operator[](size_t i);
    [[nodiscard]] constexpr size_t size() const;

    double euclidean_distance(const Vector& v) const;
    void fill(const T& value);

    typename std::array<T, dims>::iterator begin();
    typename std::array<T, dims>::iterator end();
    typename std::array<T, dims>::const_iterator begin() const;
    typename std::array<T, dims>::const_iterator end() const;

private:
    std::array<T, dims> data;
};

// see https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference
template<class T, size_t dims>
Vector<T, dims>::Vector(std::array<T, dims> elements)
    : data(std::move(elements))
{}

template<class T, size_t dims>
Vector<T, dims>::Vector(const Vector &v)
    : data(v.data)
{}

template<class T, size_t dims>
Vector<T, dims>::Vector(Vector &&v) noexcept
    : data(std::move(v.data))
{}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator+(const Vector &v) {
    Vector result;
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        result[i] = (*this)[i] + v[i];
    }
    return result;
}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator+(Vector &&v) {
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        v[i] += (*this)[i];
    }
    return std::move(v);
}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator-(const Vector &v) {
    Vector result;
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        result[i] = (*this)[i] - v[i];
    }
    return result;
}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator-(Vector &&v) {
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        v[i] -= (*this)[i];
    }
    return std::move(v);
}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator+(const T& value) {
    Vector result;
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        result[i] = (*this)[i] + value;
    }
    return result;
}

template<class T, size_t dims>
Vector<T, dims> Vector<T, dims>::operator-(const T& value) {
    Vector result;
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        result[i] = (*this)[i] + value;
    }
    return result;
}

template<class T, size_t dims>
Vector<T, dims>& Vector<T, dims>::operator+=(const Vector &v) {
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        (*this)[i] += v[i];
    }
    return *this;
}

template<class T, size_t dims>
Vector<T, dims>& Vector<T, dims>::operator-=(const Vector &v) {
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        (*this)[i] -= v[i];
    }
    return *this;
}

template<class T, size_t dims>
Vector<T, dims>& Vector<T, dims>::operator/=(const T& value) {
    #pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        (*this)[i] /= value;
    }
    return *this;
}

template<class T, size_t dims>
Vector<T, dims>& Vector<T, dims>::operator*=(const T& value) {
#pragma loop( ivdep )
    for (int i = 0; i < dims; ++i) {
        (*this)[i] /= value;
    }
    return *this;
}

template<class T, size_t dims>
Vector<T, dims> &Vector<T, dims>::operator=(const Vector &v) {
    data = v.data;
    return *this;
}

template<class T, size_t dims>
Vector<T, dims> &Vector<T, dims>::operator=(Vector &&v) noexcept {
    data = std::move(v.data);
    return *this;
}

template<class T, size_t dims>
bool Vector<T, dims>::operator==(const Vector& v) {
    if (this == &v) {
        return true;
    }
    #pragma loop( ivdep )
    for (size_t i = 0; i < dims; ++i) {
        if ((*this)[i] != v[i]) {
            return false;
        }
    }
    return true;
}

template<class T, size_t dims>
bool Vector<T, dims>::operator!=(const Vector& v) {
    return !operator==(v);
}

template<class T, size_t dims>
const T &Vector<T, dims>::operator[](size_t i) const {
    assert(("point access out of index", i < dims));
    return data[i];
}

template<class T, size_t dims>
T &Vector<T, dims>::operator[](size_t i) {
    assert(("point access out of index", i < dims));
    return data[i];
}

template<class T, size_t dims>
constexpr size_t Vector<T, dims>::size() const {
    return dims;
}

template<class T, size_t dims>
typename std::array<T, dims>::iterator Vector<T, dims>::begin() {
    return data.begin();
}

template<class T, size_t dims>
typename std::array<T, dims>::iterator Vector<T, dims>::end() {
    return data.end();
}

template<class T, size_t dims>
typename std::array<T, dims>::const_iterator Vector<T, dims>::begin() const {
    return data.begin();
}

template<class T, size_t dims>
typename std::array<T, dims>::const_iterator Vector<T, dims>::end() const {
    return data.end();
}

template<class T, size_t dims>
double Vector<T, dims>::euclidean_distance(const Vector &v) const {
    double acc = 0;
    #pragma loop( ivdep )
    for (size_t i = 0; i < dims; ++i) {
        acc += ((*this)[i] - v[i]) * ((*this)[i] - v[i]);
    }
    return std::sqrt(acc);
}

template<class T, size_t dims>
void Vector<T, dims>::fill(const T &value) {
    #pragma loop( ivdep )
    for (size_t i = 0; i < dims; ++i) {
        (*this)[i] = value;
    }
}

using Vector2D = Vector<double, 2>;
using Vector3D = Vector<double, 3>;
using Vector4D = Vector<double, 4>;


#endif //CLUSTERING_VECTOR_H
