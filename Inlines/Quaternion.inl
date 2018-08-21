#ifndef __QUATERNION_INL__
#define __QUATERNION_INL__

/**
 * @file    Quaternion.inl
 * @brief   Inline file for Quaternion
 * @author  Alexis Beracochea
 * 
 * @ingroup GQuaternion
 * 
 */

#include <stdexcept>
#include <cmath>

#include "../Includes/Vector3.hpp"
#include "../Includes/Vector4.hpp"
#include "../Includes/Utilities.hpp"

/**
 * @file    Quaternion.inl
 * @brief   Inline file for Quaternion
 * @author  Alexis Beracochea
 * 
 * @ingroup GQuaternion
 * 
 */

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Give the angle between
 * 
 * @param p_a Fist Quaternion
 * @param p_b Second Quaternion
 * @return constexpr Quaternion 
 */
constexpr   Quaternion  Quaternion::Angle           (const Quaternion& p_a, const Quaternion& p_b) noexcept
{
    return p_b * p_a.GetInverse();
}

/**
 * @brief Give the angle in degree between two quaternion
 * 
 * @param p_a Fist Quaternion
 * @param p_b Second Quaternion
 * @return constexpr float Angle beetween two Quaternion
 */
constexpr   float       Quaternion::AngleDeg        (const Quaternion& p_a, const Quaternion& p_b) noexcept
{
    return ToDegrees(std::acos((p_b * p_a.GetInverse()).m_w) * 2);
}

/**
 * @brief Give the angle in radian between two quaternion
 * 
 * @param p_a Fist Quaternion
 * @param p_b Second Quaternion
 * @return constexpr float Angle beetween two Quaternion
 */
constexpr   float       Quaternion::AngleRad        (const Quaternion& p_a, const Quaternion& p_b) noexcept
{
    return std::acos((p_b * p_a.GetInverse()).m_w) * 2;
}

/**
 * @brief Gives a rotation of the specified angle around an axis
 * 
 * @param p_axis  The axis to rotate on
 * @param p_angle The angle to rotate in degrees
 * @return constexpr Quaternion The rotation quaternion
 */
constexpr   Quaternion  Quaternion::AngleAxis       (const Vector3& p_axis, const float p_angle)    noexcept
{
    if (p_axis.GetSqrMagnitude() < __FLT_EPSILON__)
        return Quaternion(0,0,0,1);

    double  halfAngle       (ToRadians(0.5f * p_angle));
    double  sinHalfAngle    (std::sin(halfAngle));

    Vector3 vecNormalized   (p_axis.GetNormalize());

    return Quaternion
    (
        vecNormalized.m_x * sinHalfAngle,
        vecNormalized.m_y * sinHalfAngle,
        vecNormalized.m_z * sinHalfAngle,
        std::cos(halfAngle)
    );
}

/**
 * @brief Get the Quaternion Rotation from Euler Rotation vector
 * 
 * @param p_eulerRotation Euler Angles on Degree 
 * @return Quaternion Rotation that rotates z degrees around the z axis, x degrees around the x axis, and y degrees around the y axis.
 */
constexpr	Quaternion  Quaternion::Euler           (const Vector3& p_eulerRotation) noexcept
{
    Vector3 halfRadEulerAngle   (ToRadians(p_eulerRotation.m_x * 0.5f),
                                 ToRadians(p_eulerRotation.m_y * 0.5f), 
                                 ToRadians(p_eulerRotation.m_z * 0.5f));

    double cosX  (std::cos(halfRadEulerAngle.m_x)); 
    double cosY  (std::cos(halfRadEulerAngle.m_y)); 
    double cosZ  (std::cos(halfRadEulerAngle.m_z));

    double sinX  (std::sin(halfRadEulerAngle.m_x)); 
    double sinY  (std::sin(halfRadEulerAngle.m_y)); 
    double sinZ  (std::sin(halfRadEulerAngle.m_z));

    return Quaternion
    (
        sinX * cosY * cosZ + cosX * sinY * sinZ,
        cosX * sinY * cosZ - sinX * cosY * sinZ,
        cosX * cosY * sinZ - sinX * sinY * cosZ,
        cosX * cosY * cosZ + sinX * sinY * sinZ
    );
}

/**
 * @brief Get the Quaternion Rotation from Euler Rotation vector
 * 
 * @param p_xRot X Euler angle
 * @param p_yRot Y Euler angle
 * @param p_zRot Z Euler angle
 * @return constexpr Quaternion 
 */
constexpr	Quaternion  Quaternion::Euler           (const float p_xRot, const float p_yRot, const float p_zRot) noexcept
{
    Vector3 halfRadEulerAngle   (ToRadians(p_xRot * 0.5f),
                                 ToRadians(p_yRot * 0.5f), 
                                 ToRadians(p_zRot * 0.5f));

    double cosX  (std::cos(halfRadEulerAngle.m_x)); 
    double cosY  (std::cos(halfRadEulerAngle.m_y)); 
    double cosZ  (std::cos(halfRadEulerAngle.m_z));

    double sinX  (std::sin(halfRadEulerAngle.m_x)); 
    double sinY  (std::sin(halfRadEulerAngle.m_y)); 
    double sinZ  (std::sin(halfRadEulerAngle.m_z));

    return Quaternion
    (
        sinX * cosY * cosZ + cosX * sinY * sinZ,
        cosX * sinY * cosZ - sinX * cosY * sinZ,
        cosX * cosY * sinZ - sinX * sinY * cosZ,
        cosX * cosY * cosZ + sinX * sinY * sinZ
    );

}

/**
 * @brief Dot Production between two quaternion
 * 
 * @param p_a First  Quaternion
 * @param p_b Second Quaternion
 * @return constexpr float Dot Product
 */
constexpr	float       Quaternion::Dot             (const Quaternion& p_a, const Quaternion& p_b)  noexcept
{
    return (p_a.m_x*p_b.m_x) + (p_a.m_y*p_b.m_y) + (p_a.m_z*p_b.m_z) + (p_a.m_w*p_b.m_w);
}

/**
 * @brief Creates a rotation which rotates from fromDirection to toDirection
 * 
 * @param p_fromDirection Start of the rotation 
 * @param p_toDirection End of the Rotation
 * @return constexpr Quaternion Rotation in Quaternion
 */
constexpr   Quaternion  Quaternion::FromToRotation  (const Vector3& p_fromDirection, const Vector3& p_toDirection) noexcept
{
    Vector3     w   (p_fromDirection ^ p_toDirection);
    Quaternion  q   (w.m_x, w.m_y, w.m_z,Vector3::Dot(p_fromDirection,p_toDirection));
    q.m_w += q.GetMagnitude();
    return q.GetNormalize();
}

/**
 * @brief Interpolates between a and b by t and normalizes the result afterwards. The parameter t is clamped to the range [0, 1]
 * 
 * @param p_a Start of the interpolation
 * @param p_b End of the interpolation
 * @param p_t ratio of the interpolation (Clamp in the range [0,1])
 * @return constexpr Quaternion Result of the Lerp
 */
constexpr   Quaternion  Quaternion::Lerp            (const Quaternion& p_a, const Quaternion& p_b, const float p_t) noexcept
{
    float lerp              ((p_t <= 0.0f) ? 0.0f : (p_t >= 1.0f) ? 1.0f : p_t);
    float oneMinusLerp      (1.0f - lerp);

    return Quaternion
    (
        oneMinusLerp * p_a.m_x + lerp * p_b.m_x,
        oneMinusLerp * p_a.m_y + lerp * p_b.m_y,
        oneMinusLerp * p_a.m_z + lerp * p_b.m_z,
        oneMinusLerp * p_a.m_w + lerp * p_b.m_w
    ).GetNormalize();
}

/**
 * @brief Interpolates between a and b by t and normalizes the result afterwards. The parameter t is not clamped.
 * 
 * @param p_a Start of the interpolation
 * @param p_b End of the interpolation
 * @param p_t ratio of the interpolation
 * @return constexpr Quaternion Result of the Lerp

 */
constexpr   Quaternion  Quaternion::LerpUnclamped            (const Quaternion& p_a, const Quaternion& p_b, const float p_t) noexcept
{
    return Quaternion
    (
        (1.0f - p_t) * p_a.m_x + p_t * p_b.m_x,
        (1.0f - p_t) * p_a.m_y + p_t * p_b.m_y,
        (1.0f - p_t) * p_a.m_z + p_t * p_b.m_z,
        (1.0f - p_t) * p_a.m_w + p_t * p_b.m_w
    ).GetNormalize();
}


/*=========================[Constructors + Destructor]=========================*/

/**
 * @brief Construct a new Quaternion:: Default Constructor
 * 
 */
constexpr	Quaternion::Quaternion	() noexcept
:	m_x	{0},
    m_y	{0},
    m_z	{0},
    m_w	{0}
{}

/**
 * @brief Construct a new Quaternion:: Quaternion object
 * 
 * @param p_x X value
 * @param p_y Y Value
 * @param p_z Z Value
 * @param p_scalar W Value
 */
constexpr	Quaternion::Quaternion	(const float p_x, const float p_y, const float p_z, const float p_scalar) noexcept
:	m_x {p_x},
    m_y {p_y},
    m_z {p_z},
    m_w {p_scalar}
{}

/**
 * @brief Construct a new Quaternion:: Quaternion object
 * 
 * @param p_vector3 XYZ value in Vector 3 
 * @param p_scalar W value
 */
constexpr	Quaternion::Quaternion	(const Vector3& p_vector3, const float p_scalar) noexcept
:	m_x {p_vector3.m_x},
    m_y {p_vector3.m_y},
    m_z {p_vector3.m_z},
    m_w {p_scalar}
{}

/**
 * @brief Construct a new Quaternion:: Constructor with a Vector4
 * 
 * @param p_vector4 Value in vector4
 */
constexpr	Quaternion::Quaternion	(const Vector4& p_vector4) noexcept
:	m_x {p_vector4.m_x},
    m_y {p_vector4.m_y},
    m_z {p_vector4.m_z},
    m_w {p_vector4.m_w}
{}

/**
 * @brief Construct a new Quaternion:: Copy Constructor
 * 
 * @param p_copy Value to copy
 */
constexpr	Quaternion::Quaternion  (const Quaternion& p_copy) noexcept
:	m_x {p_copy.m_x},
    m_y {p_copy.m_y},
    m_z {p_copy.m_z},
    m_w {p_copy.m_w}  
{}

/**
 * @brief Construct a new Quaternion:: Move Constructor
 * 
 * @param p_move Value to move
 */
constexpr	Quaternion::Quaternion  (const Quaternion&& p_move) noexcept
:   m_x {std::move(p_move.m_x)},
    m_y {std::move(p_move.m_y)},
    m_z {std::move(p_move.m_z)},
    m_w {std::move(p_move.m_w)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Conjugate the Quaternion
 */
constexpr	void        Quaternion::Conjugate       ()			noexcept
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

/**
 * @brief Computes the euler angles 
 * 
 * @return constexpr Vector3 The euler angles vector
 */
constexpr	Vector3     Quaternion::GetEulerAngles  ()	const	noexcept
{
    double sqrX (m_x*m_x);
    double sqrY (m_y*m_y);
    double sqrZ (m_z*m_z);

    double x     (-std::asin ((2*(m_y*m_z-m_x*m_w))));
    double y     (std::atan2 (2*(m_x*m_z+m_y*m_w), 1-2*(sqrX+sqrY)));
    double z     (std::atan2 (2*(m_x*m_y+m_z*m_w), 1-2*(sqrX+sqrZ)));

    return Vector3  (ToDegrees(x),ToDegrees(y),ToDegrees(z));
}

/**
 * @brief Get the conjugate of the Quaternion
 * 
 * @return Quaternion Conjugated Transform
 */
constexpr	Quaternion  Quaternion::GetConjugate    ()  const	noexcept
{
    return Quaternion (-m_x, -m_y, -m_z, m_w);
}

/**
 * @brief 
 * 
 * @return Quaternion 
 */
constexpr	Quaternion  Quaternion::GetInverse      () 	const	noexcept
{
    return Quaternion(-m_x, -m_y, -m_z, m_w) / (m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

/**
 * @brief Get the Length of the Quaternion
 * 
 * @return float Length of the Quaternion
 */
constexpr	float       Quaternion::GetMagnitude    ()  const	noexcept
{
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

/**
 * @brief Get the Normalized Quaternion
 * 
 * @return Quaternion 
 */
constexpr	Quaternion  Quaternion::GetNormalize    ()  const	noexcept
{
    float length (std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w));

    return Quaternion(m_x/length, m_y/length, m_z/length, m_w/length);
}

/**
 * @brief Get the Square Length of the Quaternion
 * 
 * @return float Square Length of the Quaternion
 */
constexpr	float       Quaternion::GetSqrMagnitude	()  const	noexcept
{
    return (m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

/**
 * @brief Inverse the Quaternion
 * 
 */
constexpr	void        Quaternion::Inverse			()			noexcept
{
    float sqrtMagnitude (m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
    m_x /= -sqrtMagnitude;
    m_y /= -sqrtMagnitude;
    m_z /= -sqrtMagnitude;
    m_w /= sqrtMagnitude;
}

/**
 * @brief Normalize the Quaternion
 * 
 */
constexpr	void        Quaternion::Normalize       ()			noexcept
{
    float length (std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w));

    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;
}

/**
 * @brief Sets the components of the current Quaternions with the new values
 * 
 * @param p_x New X
 * @param p_y New Y
 * @param p_z New Z
 * @param p_w New W
 */
constexpr	void        Quaternion::Set             (const float p_x,
													 const float p_y, 
													 const float p_z, 
													 const float p_w)	noexcept
{
    m_x = p_x;
    m_y = p_y;
    m_z = p_z;
    m_w = p_w;
}

/**
 * @brief Set the quaternion with Eulers Angle
 * 
 * @param p_euler Eulers angles in vector;
 */
constexpr   void        Quaternion::SetEulersAngles (const Vector3& p_euler)    noexcept
{
    Vector3 halfRadEulerAngle   (ToRadians(p_euler.m_x * 0.5f),
                                 ToRadians(p_euler.m_y * 0.5f), 
                                 ToRadians(p_euler.m_z * 0.5f));

    double cosX  (std::cos(halfRadEulerAngle.m_x)); 
    double cosY  (std::cos(halfRadEulerAngle.m_y)); 
    double cosZ  (std::cos(halfRadEulerAngle.m_z));

    double sinX  (std::sin(halfRadEulerAngle.m_x)); 
    double sinY  (std::sin(halfRadEulerAngle.m_y)); 
    double sinZ  (std::sin(halfRadEulerAngle.m_z));

    m_x = sinX * cosY * cosZ + cosX * sinY * sinZ;
    m_y = cosX * sinY * cosZ - sinX * cosY * sinZ;
    m_z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    m_w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

/**
 * @brief Set the quaternion with Eulers Angle
 * 
 * @param p_xRot X Euler Angle
 * @param p_yRot Y Euler Angle
 * @param p_zRot Z Euler Angle
 */
constexpr   void        Quaternion::SetEulersAngles (const float p_xRot,
                                                     const float p_yRot, 
                                                     const float p_zRot)    noexcept
{
    Vector3 halfRadEulerAngle   (ToRadians(p_xRot * 0.5f),
                                 ToRadians(p_yRot * 0.5f), 
                                 ToRadians(p_zRot * 0.5f));

    double cosX  (std::cos(halfRadEulerAngle.m_x)); 
    double cosY  (std::cos(halfRadEulerAngle.m_y)); 
    double cosZ  (std::cos(halfRadEulerAngle.m_z));

    double sinX  (std::sin(halfRadEulerAngle.m_x)); 
    double sinY  (std::sin(halfRadEulerAngle.m_y)); 
    double sinZ  (std::sin(halfRadEulerAngle.m_z));

    m_x = sinX * cosY * cosZ + cosX * sinY * sinZ;
    m_y = cosX * sinY * cosZ - sinX * cosY * sinZ;
    m_z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    m_w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}



/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Copy operator
 * 
 * @param p_copy                 The quaternion to copy
 * @return constexpr Quaternion& This quaternion
 */
constexpr	Quaternion& Quaternion::operator=   (const Quaternion& p_copy)	noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = p_copy.m_z;
    m_w = p_copy.m_w;

    return *this;
}

/**
 * @brief Move operator
 * 
 * @param p_move                 The quaternion to move
 * @return constexpr Quaternion& This quaternion
 */
constexpr	Quaternion& Quaternion::operator=   (const Quaternion&& p_move)	noexcept
{
    m_x = std::move(p_move.m_x);
    m_y = std::move(p_move.m_y);
    m_z = std::move(p_move.m_z);
    m_w = std::move(p_move.m_w);

    return *this;
}

/**
 * @brief Access the x, y, z, w components using [0], [1], [2], [3] respectively.
 * 
 * @param p_index index of the component: [0] = m_x | [1] = m_y; | [2] = m_z | [3] = m_w 
 * @return float Value corresponding to the index
 */
constexpr	float       Quaternion::operator[]  (const int p_index) const
{
    float value (0.0f);

    switch (p_index)
    {
        case 0	: value = m_x;	break;
        case 1	: value = m_y;	break;
        case 2	: value = m_z;	break;
        case 3	: value = m_w;	break;
        default : throw std::out_of_range(std::string("Invalid Quaternion Index: " + std::to_string(p_index) + ", can use only 0,1,2,3"));;
    }
    return value;
}

/**
 * @brief Access the x, y, z, w components using [0], [1], [2], [3] respectively.
 * 
 * @param p_index index of the component: [0] = m_x | [1] = m_y; | [2] = m_z | [3] = m_w 
 * @return float& Value corresponding to the index
 */
constexpr	float&      Quaternion::operator[]  (const int p_index)
{
    switch (p_index)
    {
        case 0	: return m_x;	break;
        case 1	: return m_y;	break;
        case 2	: return m_z;	break;
        case 3	: return m_w;	break;
        default : throw std::out_of_range(std::string("Invalid Quaternion Index: " + std::to_string(p_index) + ", can use only 0,1,2,3"));;
    }
    return m_x;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Are two quaternions equal to each other ?
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return true Both are equal
 * @return false Both are different
 */
constexpr	bool            Maths::operator==   (const Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    float dot   ((p_a.m_x*p_b.m_x) + (p_a.m_y*p_b.m_y) + (p_a.m_z*p_b.m_z) + (p_a.m_w*p_b.m_w));
    float test  (dot -1);

    return std::abs(test) < 0.001;
}

/**
 * @brief Are two quaternions different to each other ?
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return true Both are different
 * @return false Both are equal
 */
constexpr	bool            Maths::operator!=   (const Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    float dot   ((p_a.m_x*p_b.m_x) + (p_a.m_y*p_b.m_y) + (p_a.m_z*p_b.m_z));
    float test  (dot -1);

    return std::abs(test) > 0.001;
}

/**
 * @brief Add both Quaternions
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of Addition
 */
constexpr	Quaternion      Maths::operator+    (const Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    return Quaternion  (p_a.m_x + p_b.m_x, 
                        p_a.m_y + p_b.m_y, 
                        p_a.m_z + p_b.m_z, 
                        p_a.m_w + p_b.m_w);
}

/**
 * @brief Add the second Quaternion to the first
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of Addition
 */
constexpr	Quaternion&     Maths::operator+=   (Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    p_a.m_x += p_b.m_x;
    p_a.m_y += p_b.m_y;
    p_a.m_z += p_b.m_z;
    p_a.m_w += p_b.m_w;

    return p_a;
}

/**
 * @brief Computes the opposite Quaternion
 * 
 * @param p_a The target Quaternion
 * @return Quaternion The opposite Quaternion
 */
constexpr	Quaternion      Maths::operator-    (const Quaternion& p_a)	noexcept
{
   return Quaternion    (-p_a.m_x, 
                         -p_a.m_y, 
                         -p_a.m_z, 
                         -p_a.m_w); 
}

/**
 * @brief Subtract both Quaternions
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of Subtraction
 */
constexpr	Quaternion      Maths::operator-    (const Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    return Quaternion  (p_a.m_x - p_b.m_x, 
                        p_a.m_y - p_b.m_y, 
                        p_a.m_z - p_b.m_z, 
                        p_a.m_w - p_b.m_w);
}

/**
 * @brief Subtract the second Quaternion to the first
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of Subtraction
 */
constexpr	Quaternion&     Maths::operator-=   (Quaternion& p_a, const Quaternion& p_b)	noexcept
{
    p_a.m_x -= p_b.m_x;
    p_a.m_y -= p_b.m_y;
    p_a.m_z -= p_b.m_z;
    p_a.m_w -= p_b.m_w;

    return p_a;
}

/**
 * @brief Multiply both Quaternion
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of the multiplication
 */
constexpr	Quaternion      Maths::operator*    (const Quaternion& p_a, const Quaternion& p_b)	noexcept
{   
    return Quaternion
    (
        p_a.m_w*p_b.m_x + p_a.m_x*p_b.m_w + p_a.m_y*p_b.m_z - p_a.m_z*p_b.m_y,
        p_a.m_w*p_b.m_y - p_a.m_x*p_b.m_z + p_a.m_y*p_b.m_w + p_a.m_z*p_b.m_x,
        p_a.m_w*p_b.m_z + p_a.m_x*p_b.m_y - p_a.m_y*p_b.m_x + p_a.m_z*p_b.m_w,
        p_a.m_w*p_b.m_w - p_a.m_x*p_b.m_x - p_a.m_y*p_b.m_y - p_a.m_z*p_b.m_z
    );
}

/**
 * @brief Scale the Quaternion
 * 
 * @param p_a Quaternion to Scale
 * @param p_k Scale factor
 * @return Quaternion  Scaled Quaternion
 */
constexpr	Quaternion      Maths::operator*    (const Quaternion& p_a, const float p_k)	noexcept
{
    return Quaternion
    (
        p_a.m_x * p_k,
        p_a.m_y * p_k,
        p_a.m_z * p_k,
        p_a.m_w * p_k
    );
}

/**
 * @brief Scale the Quaternion
 * 
 * @param p_k Scale factor
 * @param p_a Quaternion to Scale
 * @return Quaternion  Scaled Quaternion
 */
constexpr	Quaternion      Maths::operator*    (const float p_k, const Quaternion& p_a)	noexcept
{
    return Quaternion
    (
        p_a.m_x * p_k,
        p_a.m_y * p_k,
        p_a.m_z * p_k,
        p_a.m_w * p_k
    );
}

/**
 * @brief Scale the Quaternion
 * 
 * @param p_k Scale factor
 * @param p_a Quaternion to Scale
 * @return Quaternion  Scaled Quaternion
 */
constexpr	Quaternion&     Maths::operator*=   (Quaternion& p_a, const float p_k)	noexcept
{
    p_a.m_x *= p_k;
    p_a.m_y *= p_k;
    p_a.m_z *= p_k;
    p_a.m_w *= p_k;

    return p_a;
}

/**
 * @brief Multiply the first Quarternier by the Second
 * 
 * @param p_a First Quaternion
 * @param p_b Second Quaternion
 * @return Quaternion Result of the multiplication
 */
constexpr	Quaternion&     Maths::operator*=   (Quaternion& p_a, const Quaternion& p_b)	noexcept
{   
    Quaternion result
    (
        p_a.m_w*p_b.m_x + p_a.m_x*p_b.m_w + p_a.m_y*p_b.m_z - p_a.m_z*p_b.m_y,
        p_a.m_w*p_b.m_y - p_a.m_x*p_b.m_z + p_a.m_y*p_b.m_w + p_a.m_z*p_b.m_x,
        p_a.m_w*p_b.m_z + p_a.m_x*p_b.m_y - p_a.m_y*p_b.m_x + p_a.m_z*p_b.m_w,
        p_a.m_w*p_b.m_w - p_a.m_x*p_b.m_x - p_a.m_y*p_b.m_y - p_a.m_z*p_b.m_z
    );

    return (p_a = std::move(result));
}

/**
 * @brief Divide the Quaternion by Scale Factor
 * 
 * @param p_a Quaternion to Scale
 * @param p_k Scale factor
 * @return Quaternion Quaternion divided by scale factor
 */
constexpr	Quaternion      Maths::operator/    (const Quaternion& p_a, const float p_k)	noexcept
{
    return Quaternion
    (
        p_a.m_x / p_k,
        p_a.m_y / p_k,
        p_a.m_z / p_k,
        p_a.m_w / p_k
    );
}

/**
 * @brief Divide the Quaternion by Scale Factor
 * 
 * @param p_a Quaternion to Scale
 * @param p_k Scale factor
 * @return Quaternion Quaternion divided by scale factor
 */
constexpr	Quaternion&     Maths::operator/=   (Quaternion& p_a, const float p_k)	noexcept
{
    p_a.m_x /= p_k;
    p_a.m_y /= p_k;
    p_a.m_z /= p_k;
    p_a.m_w /= p_k;

    return p_a;
}

/**
 * @brief Converts a Quaternion to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target Quaternion
 * @return std::ostream& The resulting stream of the conversion
 */
inline		std::ostream&   Maths::operator<<   (std::ostream& p_flux, const Quaternion& p_a)	noexcept
{
    return p_flux << "Quaternion (" << p_a.m_x << "," 
                                    << p_a.m_y << "," 
                                    << p_a.m_z  << "," 
                                    << p_a.m_w << ")";
}

#endif // !__QUATERNION_INL__
