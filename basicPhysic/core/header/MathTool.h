#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
    const float Pi = 3.141592653f;
    const float TwoPi = Pi * 2.0f;
    const float PiOver2 = Pi / 2.0f;
    
    const float NegInfinity = -std::numeric_limits<float>::infinity();
	const float Infinity = std::numeric_limits<float>::infinity();


	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}
	
	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}
	
	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}


class Vector2
{
public:
    float x;
    float y;

    Vector2(): x(0.0f), y(0.0f) {}
    
    explicit Vector2(float inX, float inY): x(inX), y(inY) {}

    void Set(float inX, int inY)
    {
        x = inX;
        y = inY;
    }

    friend Vector2 operator+ (const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x + b.x, a.y + b.y);
    }

    friend Vector2 operator- (const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x - b.x, a.y - b.y);
    }

    friend Vector2 operator* (const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }

    friend Vector2 operator* (const Vector2& vec, const float scale)
    {
        return Vector2(vec.x * scale, vec.y * scale);
    }

    friend Vector2 operator* (const float scale, const Vector2& vec)
    {
        return Vector2(vec.x * scale, vec.y * scale);
    }

	Vector2& operator/ (const float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

    Vector2& operator*= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2& operator+= (const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    Vector2& operator-= (const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    float LengthSq() const 
    {
        return (x * x + y * y);
    }

    float Length() const
    {
        return Math::Sqrt(LengthSq());
    }

    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
    }

    static Vector2 Normalize(const Vector2& vec)
    {
        Vector2 temp = vec;
        temp.Normalize();
        return temp;
    }

    static float Dot(const Vector2& a, const Vector2& b)
    {
        return (a.x * b.x + a.y * b.y);
    }

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
    {
        return Vector2(a + f * (b - a));
    }

    static Vector2 Reflect(const Vector2& v, const Vector2& n)
    {
        return v - 2.0f * Vector2::Dot(v, n) * n;
    }

    static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegUnitX;
    static const Vector2 NegUnitY;
};

class Matrix3
{
public:
    float mat[3][3];

    Matrix3()
    {
        *this = Matrix3::Identity;
    }

    explicit Matrix3(float inMat[3][3])
    {
        memcpy(mat, inMat, 9 * sizeof(float));
    }

    const float* GetAsFloatPtr() const
    {
        return reinterpret_cast<const float*>(&mat[0][0]);
    }

    friend Matrix3 operator* (const Matrix3& left, const Matrix3& right)
    {
        Matrix3 retVal;

        // row 0
		retVal.mat[0][0] = 
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0];

		retVal.mat[0][1] = 
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1];

		retVal.mat[0][2] = 
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2];
		
		// row 1
		retVal.mat[1][0] = 
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0];

		retVal.mat[1][1] = 
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1];

		retVal.mat[1][2] = 
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2];
		
		// row 2
		retVal.mat[2][0] = 
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0];

		retVal.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1];

		retVal.mat[2][2] = 
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2];

		return retVal;
    }

    Matrix3& operator*= (const Matrix3 right)
    {
        *this = *this * right;
        return *this;
    }

    static Matrix3 CreateScale(float xScale, float yScale)
    {
        float temp[3][3] = 
        {
            {xScale, 0.0f, 0.0f},
            {0.0f, yScale, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        return Matrix3(temp);
    }

    static Matrix3 CreateScale(const Vector2& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y);
	}

    static Matrix3 CreateScale(float scale)
	{
		return CreateScale(scale, scale);
	}

    static Matrix3 CreateRotation(float theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

    static Matrix3 CreateTranslation(const Vector2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

    static const Matrix3 Identity;

};


namespace Math
{
	inline bool NearZero(const Vector2 &val, float epsilon = 0.001f)
	{
		if (fabs(val.x) <= epsilon && fabs(val.y) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
} // namespace Math

