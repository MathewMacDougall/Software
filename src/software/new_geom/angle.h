#pragma once

#include <ostream>

/**
 * A typesafe representation of an angle.
 *
 * This class helps prevent accidentally combining values in degrees and radians
 * without proper conversion.
 */
class Angle final
{
   public:
    /**
     * The zero angle.
     */
    static Angle zero();

    /**
     * The quarter-turn angle (90°).
     */
    static Angle quarter();

    /**
     * The half-turn angle (180°).
     */
    static Angle half();

    /**
     * The three-quarter turn angle (270°).
     */
    static Angle threeQuarter();

    /**
     * The full-turn angle (360°).
     */
    static Angle full();

    /**
     * Constructs an angle from a value in radians.
     *
     * @param rad the angle in radians.
     *
     * @return the constructed angle
     */
    static Angle fromRadians(double rad);

    /**
     * Constructs an angle from a value in degrees.
     *
     * @param deg the angle in degrees
     *
     * @return the constructed angle
     */
    static Angle fromDegrees(double deg);

    /**
     * Computes the arcsine of a value.
     *
     * @param x the value.
     *
     * @return the angle.
     */
    static Angle asin(double x);

    /**
     * Computes the arccosine of a value.
     *
     * @param x the value.
     *
     * @return the angle.
     */
    static Angle acos(double x);

    /**
     * Computes the arctangent of a value.
     *
     * @param x the value.
     *
     * @return the angle.
     */
    static Angle atan(double x);

    /**
     * Constructs the "zero" angle.
     */
    explicit Angle();

    /**
     * Converts this angle to a value in radians.
     *
     * @return the number of radians in this angle in the range [0, 2PI)
     */
    double toRadians() const;

    /**
     * Converts this angle to a value in degrees.
     *
     * @return the number of degrees in this angle in the range [0,360)
     */
    double toDegrees() const;

    /**
     * Computes the modulus of a division between this angle and another
     * angle.
     *
     * @param divisor the divisor.
     *
     * @return the modulus of this Angle ÷ divisor.
     */
    Angle mod(Angle divisor) const;

    /**
     * Computes the remainder of a division between this angle and
     * another angle.
     *
     * @param divisor the divisor.
     *
     * @return the remainder of this Angle ÷ divisor.
     */
    Angle remainder(const Angle &divisor) const;

    /**
     * Returns the absolute value of this angle.
     *
     * @return the absolute value of this angle.
     */
    Angle abs() const;

    /**
     * Checks whether the angle is finite.
     *
     * @return true if the angle is finite, and false if it is ±∞ or NaN.
     */
    bool isFinite() const;

    /**
     * Computes the sine of this angle.
     *
     * @return the sine of this angle.
     */
    double sin() const;

    /**
     * Computes the cosine of this angle.
     *
     * @return the cosine of this angle.
     */
    double cos() const;

    /**
     * Computes the tangent of this angle.
     *
     * @return the tangent of this angle.
     */
    double tan() const;

    /**
     * Limits this angle to [−π, π].
     *
     * The angle is rotated by a multiple of 2π until it lies within the target
     * interval.
     *
     * @return the clamped angle.
     */
    Angle clamp() const;

    /**
     * Returns the smallest possible rotational difference between this angle
     * and another angle.
     *
     * @param other the second angle.
     *
     * @return the angle between this Angle and other, in the range [0, π].
     */
    Angle minDiff(const Angle &other) const;

   private:
    /**
     * The measurement in radians of this Angle.
     */
    double rads;

    explicit Angle(double rads);
};

/**
 * Negates an angle.
 *
 * @param angle the angle to negate.
 *
 * @return the negated angle
 */
Angle operator-(const Angle &angle) __attribute__((warn_unused_result));

/**
 * Adds two angles.
 *
 * @param x the first addend.
 * @param y the second addend.
 *
 * @return the sum of the angles
 */
Angle operator+(const Angle &x, const Angle &y)
    __attribute__((warn_unused_result));

/**
 * Subtracts two angles.
 *
 * @param x the minuend.
 *
 * @param y the subtrahend.
 *
 * @return the difference between the minuend and subtrahend.
 */
Angle operator-(const Angle &x, const Angle &y)
    __attribute__((warn_unused_result));

/**
 * Multiplies an angle by a scalar factor.
 *
 * @param angle the angle.
 * @param scale the scalar factor.
 *
 * @return the product of the angle and the scalar factor
 */
Angle operator*(const Angle &angle, double scale)
    __attribute__((warn_unused_result));

/**
 * Multiplies an angle by a scalar factor.
 *
 * @param scale the scalar factor.
 * @param angle the angle.
 *
 * @return the product of the angle and the scalar factor
 */
Angle operator*(double scale, const Angle &angle)
    __attribute__((warn_unused_result));

/**
 * Divides an angle by a scalar divisor.
 *
 * @param angle the angle.
 * @param divisor the scalar divisor.
 *
 * @return the quotient of this Angle ÷ the divisor.
 */
Angle operator/(const Angle &angle, double divisor)
    __attribute__((warn_unused_result));

/**
 * Divides two angles.
 *
 * @param x the divident.
 * @param y the divisor.
 *
 * @return the quotient of the divident ÷ the divisor.
 */
double operator/(const Angle &x, const Angle &y)
    __attribute__((warn_unused_result));

/**
 * Adds an angle to another angle.
 *
 * @param x the angle to add to.
 * @param y the angle to add.
 *
 * @return the new angle x
 */
Angle &operator+=(Angle &x, const Angle &y);

/**
 * Subtracts an angle from an angle.
 *
 * @param x the angle to subtract from.
 * @param y the angle to subtract.
 *
 * @return the new angle x
 */
Angle &operator-=(Angle &x, const Angle &y);

/**
 * Scales an angle by a factor.
 *
 * @param angle the angle to scale.
 * @param scale the scalar factor.
 *
 * @return the scaled angle.
 */
Angle &operator*=(Angle &angle, double scale);

/**
 * Divides an angle by a scalar divisor.
 *
 * @param angle the angle to scale.
 *
 * @param divisor the scalar divisor.
 *
 * @return the scaled angle.
 */
Angle &operator/=(Angle &angle, double divisor);

/**
 * Compares two angles.
 *
 * @param x the first angle.
 *
 * @param y the second angle.
 *
 * @return true if x is strictly less than y, and false otherwise
 */
bool operator<(const Angle &x, const Angle &y);

/**
 * Compares two angles.
 *
 * @param x the first angle.
 * @param y the second angle.
 *
 * @return true if x is strictly greater than y, and false otherwise.
 */
bool operator>(const Angle &x, const Angle &y);

/**
 * Compares two angles.
 *
 * @param x the first angle.
 * @param y the second angle.
 *
 * @return true if x is less than or equal to y, and false otherwise.
 */
bool operator<=(const Angle &x, const Angle &y);

/**
 * Compares two angles.
 *
 * @param x the first angle.
 * @param y the second angle.
 *
 * @return true if x is greater than or equal to y, and false otherwise.
 */
bool operator>=(const Angle &x, const Angle &y);

/**
 * Compares two angles for equality
 *
 * @param x the first angle.
 * @param y the second angle.
 *
 * @return true if x is equal to y, and false otherwise.
 */
bool operator==(const Angle &x, const Angle &y);

/**
 * Compares two angles for inequality.
 *
 * @param x the first angle.
 * @param y the second angle.
 *
 * @return true if x is not equal to y, and false otherwise
 */
bool operator!=(const Angle &x, const Angle &y);

/**
 * Prints an Angle to a stream
 *
 * @param os the stream to print to
 * @param a the Point to print
 *
 * @return the stream with the Angle printed
 */
std::ostream &operator<<(std::ostream &os, const Angle &a);
