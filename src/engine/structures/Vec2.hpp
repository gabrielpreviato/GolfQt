#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include <numbers>

template <class T>
class Vec2
{
public:
    T x, y;

    Vec2() : x(0), y(0) {};
    Vec2(T x, T y) : x(x), y(y) {
        //qDebug() << "Called double constructor" ;
    }

    Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {
        //qDebug() << "Called copy constructor" ;
    }

    Vec2(Vec2<T>&& v) noexcept : x(std::move(v.x)), y(std::move(v.y)) {}

    Vec2<T>& operator=(const Vec2<T>& v) {
        x = v.x;
        y = v.y;

        //qDebug() << "Called assignment" ;

        return *this;
    }

    Vec2<T>& operator=(Vec2<T>&& v) noexcept
    {
        //qDebug() << "Called move" ;
        x = std::move(v.x);
        y = std::move(v.y);

        return *this;
    }

    Vec2<T> operator+(const Vec2<T>& v) const {
        return Vec2<T>(x + v.x, y + v.y);
    }

    const Vec2<T>& operator+(Vec2<T>&& v) const {
        return Vec2<T>(x + v.x, y + v.y);
    }

    Vec2<T>& operator+(Vec2<T>&& v) {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vec2<T> operator-(const Vec2<T>& v) const {
        return Vec2<T>{x - v.x, y - v.y};
    }

    const Vec2<T>& operator-(Vec2<T>&& v) const {
        return Vec2<T>(x - v.x, y - v.y);
    }

    Vec2<T>& operator-(Vec2<T>&& v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    const Vec2<T> operator/(double v) const {
        return Vec2<T>(x / v, y / v);
    }

    Vec2<T>& operator/(double v) {
        x /= v;
        y /= v;

        return *this;
    }

    Vec2<T>& operator+=(Vec2<T>&& v) {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vec2<T>& operator+=(const Vec2<T>& v) {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vec2<T>& operator-=(Vec2<T>&& v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    Vec2<T>& operator-=(const Vec2<T>& v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    void rotate(double deg) {
        double theta = deg / 180.0 * std::numbers::pi;
        double c = std::cos(theta);
        double s = std::sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    double squared() const {
        return x * x + y * y;
    }

    double dist(Vec2<T> v) const {
        Vec2<T> d(v.x - x, v.y - y);
        return d.length();
    }

    void truncate(double length) {
        double angle = std::atan2f(y, x);
        x = length * std::cos(angle);
        y = length * std::sin(angle);
    }

    Vec2<T> unit() const {
        double len = length();
        if (len == 0) {
            return Vec2<T>(0, 0);
        }
        return Vec2<T>(x, y) / len;
    }

    Vec2<T> ortho() const {
        return Vec2<T>(y, -x);
    }

    T dot(const Vec2<T>& v) {
        return x * v.x + y * v.y;
    }
    T cross(const Vec2<T>& v) {
        return (x * v.y) - (y * v.x);
    }

    void zero_normalize(const double sigma) {
        std::abs(x) <= sigma ? x = 0.0 : 0;
        std::abs(y) <= sigma ? y = 0.0 : 0;
    }

    Vec2<T> reflect(const Vec2<T>& normal) {
        // Assuming Vec2d has a dot product method
        T speedDotNormal = this->dot(normal);
		if (speedDotNormal < 0) {
			// The angle is greater than 90 degrees, normal points inward, reflection needed.
            speedDotNormal *= -1;
		}
        Vec2<T> reflection = *this - (normal * 2.0 * speedDotNormal);
        
        return reflection;
    }

private:

};

template <class T>
Vec2<T> operator*(const Vec2<T>& v, double m) {
    //qDebug() << "Const\n";
    return Vec2<T>(v.x * m, v.y * m);
}

template <class T>
Vec2<T>&& operator*(Vec2<T>&& v, const double m) {
    //qDebug() << "lvalue\n";

    v.x *= m;
    v.y *= m;

    return std::move(v);
}

using Vec2d = Vec2<double>;
