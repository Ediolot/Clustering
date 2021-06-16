//
// Created by jsier on 10/06/2021.
//

#include <cassert>

#ifndef CLUSTERING_VECTOR_H
#define CLUSTERING_VECTOR_H


template<class T, size_t dims>
class Vector {
public:
    Vector() = default;

    // https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference
    explicit Vector(std::array<T, dims> elements)
        : data(std::move(elements))
    {}

    Vector(const Vector& v)
        : data(v.data)
    {}

    Vector(Vector&& v) noexcept
        : data(std::move(v.data))
    {}

    virtual ~Vector() = default;

    Vector operator+(const Vector& v) {
        Vector result;
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            result[i] = (*this)[i] + v[i];
        }
        return result;
    }

    Vector operator+(Vector&& v) {
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            v[i] += this[i];
        }
        return std::move(v);
    }

    Vector operator-(const Vector& v) {
        Vector result;
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            result[i] = (*this)[i] - v[i];
        }
        return result;
    }

    Vector operator-(Vector&& v) {
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            v[i] -= this[i];
        }
        return std::move(v);
    }

    Vector operator+=(const Vector& v) noexcept {
        // We dont need a move += operator
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            this[i] += v[i];
        }
        return *this;
    }

    Vector operator-=(const Vector& v) noexcept {
        // We dont need a move -= operator
        #pragma loop( ivdep )
        for (int i = 0; i < dims; ++i) {
            this[i] -= v[i];
        }
        return *this;
    }

    Vector& operator=(const Vector& v) {
        data = v.data;
        return *this;
    }

    Vector& operator=(Vector&& v) noexcept {
        data = std::move(v.data);
        return *this;
    }

    const T& operator[](size_t i) const {
        assert(("point access out of index", i < dims));
        return data[i];
    }

    T& operator[](size_t i) {
        assert(("point access out of index", i < dims));
        return data[i];
    }

    [[nodiscard]] constexpr size_t size() const {
        return dims;
    }

    typename std::array<T, dims>::iterator begin() { return data.begin(); }
    typename std::array<T, dims>::iterator end() { return data.end(); }
    typename std::array<T, dims>::const_iterator begin() const { return data.begin(); }
    typename std::array<T, dims>::const_iterator end() const { return data.end(); }

private:
    std::array<T, dims> data;
};

using Vector2D = Vector<double, 2>;
using Vector3D = Vector<double, 3>;
using Vector4D = Vector<double, 4>;


#endif //CLUSTERING_VECTOR_H
