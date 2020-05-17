#include <cmath>

#include "software/new_geom/geom_constants.h"
#include "software/new_geom//angle.h"

Angle Angle::zero()
{
    return Angle();
}

Angle Angle::quarter()
{
    return Angle(M_PI / 2.0);
}

Angle Angle::half()
{
    return Angle(M_PI);
}

Angle Angle::threeQuarter()
{
    return Angle(3.0 / 2.0 * M_PI);
}

Angle Angle::full()
{
    return Angle(2.0 * M_PI);
}

Angle Angle::fromRadians(double rad)
{
    return Angle(rad);
}

Angle Angle::fromDegrees(double deg)
{
    return Angle(deg / 180.0 * M_PI);
}

Angle Angle::asin(double x)
{
    return Angle::fromRadians(std::asin(x));
}

Angle Angle::acos(double x)
{
    return fromRadians(std::acos(x));
}

Angle Angle::atan(double x)
{
    return Angle::fromRadians(std::atan(x));
}

Angle::Angle() : rads(0.0) {}

double Angle::toRadians() const
{
    return rads;
}

double Angle::toDegrees() const
{
    return rads / M_PI * 180.0;
}

Angle Angle::mod(Angle divisor) const
{
    return Angle::fromRadians(toRadians() - static_cast<double>(static_cast<long>(
                                                toRadians() / divisor.toRadians())) *
                                                divisor.toRadians());
}

Angle Angle::remainder(const Angle &divisor) const
{
    return Angle::fromRadians(toRadians() -
                              static_cast<double>(static_cast<long>(
                                  (toRadians() / divisor.toRadians()) >= 0
                                      ? (toRadians() / divisor.toRadians() + 0.5)
                                      : (toRadians() / divisor.toRadians() - 0.5))) *
                                  divisor.toRadians());
}

Angle Angle::abs() const
{
    return Angle::fromRadians(toRadians() < 0 ? -toRadians() : toRadians());
}

bool Angle::isFinite() const
{
    return std::isfinite(toRadians());
}

double Angle::sin() const
{
    return std::sin(toRadians());
}

double Angle::cos() const
{
    return std::cos(toRadians());
}

double Angle::tan() const
{
    return std::tan(toRadians());
}

Angle Angle::clamp() const
{
    return remainder(Angle::full());
}

Angle Angle::minDiff(const Angle &other) const
{
    return (*this - other).clamp().abs();
}

Angle::Angle(double rads) : rads(rads) {}

Angle operator-(const Angle &angle)
{
    return Angle::fromRadians(-angle.toRadians());
}

Angle operator+(const Angle &x, const Angle &y)
{
    return Angle::fromRadians(x.toRadians() + y.toRadians());
}

Angle operator-(const Angle &x, const Angle &y)
{
    return Angle::fromRadians(x.toRadians() - y.toRadians());
}

Angle operator*(const Angle &angle, double scale)
{
    return Angle::fromRadians(angle.toRadians() * scale);
}

Angle operator*(double scale, const Angle &angle)
{
    return Angle::fromRadians(scale * angle.toRadians());
}

Angle operator/(const Angle &angle, double divisor)
{
    return Angle::fromRadians(angle.toRadians() / divisor);
}

double operator/(const Angle &x, const Angle &y)
{
    return x.toRadians() / y.toRadians();
}

Angle &operator+=(Angle &x, const Angle &y)
{
    return x = x + y;
}

Angle &operator-=(Angle &x, const Angle &y)
{
    return x = x - y;
}

Angle &operator*=(Angle &angle, double scale)
{
    return angle = angle * scale;
}

Angle &operator/=(Angle &angle, double divisor)
{
    return angle = angle / divisor;
}

bool operator<(const Angle &x, const Angle &y)
{
    return x.toRadians() < y.toRadians();
}

bool operator>(const Angle &x, const Angle &y)
{
    return x.toRadians() > y.toRadians();
}

bool operator<=(const Angle &x, const Angle &y)
{
    return x.toRadians() <= y.toRadians();
}

bool operator>=(const Angle &x, const Angle &y)
{
    return x.toRadians() >= y.toRadians();
}

bool operator==(const Angle &x, const Angle &y)
{
    Angle diff = x.clamp().minDiff(y.clamp());
    return diff.toRadians() <= GeomConstants::FIXED_EPSILON;
}

bool operator!=(const Angle &x, const Angle &y)
{
    return x.toRadians() != y.toRadians();
}

std::ostream &operator<<(std::ostream &os, const Angle &a)
{
    os << a.toRadians() << "R";
    return os;
}
