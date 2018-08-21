#ifndef __VECTOR_4_INL__
#define __VECTOR_4_INL__

/**
 * @file    Vector4.inl
 * @brief   Inline file for Vector4
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GVector4
 * 
 */

#include <cmath>
#include <stdexcept>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector2.hpp"
#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Calculates the distance between two 4D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting distance's value
 */
constexpr float     Vector4::Distance           (const Vector4& p_a, const Vector4& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);
    float z (p_b.m_z - p_a.m_z);
    float w (p_b.m_w - p_a.m_w);

    return std::sqrt(x * x + y * y + z * z + w * w);
}

/**
 * @brief Calculates the squared distance between two 4D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting squared distance's value
 */
constexpr float	    Vector4::DistanceSqr        (const Vector4& p_a, const Vector4& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);
    float z (p_b.m_z - p_a.m_z);
    float w (p_b.m_w - p_a.m_w);

    return x * x + y * y + z * z + w * w;
}

/**
 * @brief Calculates the dot product between two 4D vectors
 *  
 * @param p_a              The left handed vector
 * @param p_b              The right handed vector
 * @return constexpr float The resulting dot product's value
 */
constexpr float     Vector4::Dot                (const Vector4& p_a, const Vector4& p_b) noexcept
{
    return p_a.m_x * p_b.m_x + 
           p_a.m_y * p_b.m_y + 
           p_a.m_z * p_b.m_z + 
           p_a.m_w * p_b.m_w;
}

/**
 * @brief Linearly interpolates between two 4D vectors its value clamped
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector4	Vector4::Lerp        		(const Vector4& p_a, const Vector4& p_b, const float p_t) noexcept
{
    float lerp ((p_t <= 0.0f) ? 0.0f : (p_t >= 1.0f) ?  1.0f : p_t);

    return (1.0f - lerp) * p_a + lerp * p_b;
}

/**
 * @brief Linearly interpolates between two 4D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector4   Vector4::LerpUnclamped		(const Vector4& p_a, const Vector4& p_b, const float p_t) noexcept
{
    return (1.0f - p_t) * p_a + p_t * p_b;
}

/**
 * @brief Computes the greatest 4D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the comparison
 */
constexpr Vector4   Vector4::Max				(const Vector4& p_a, const Vector4& p_b) noexcept
{
    float xMax ((p_a.m_x > p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMax ((p_a.m_y > p_b.m_y) ? p_a.m_y : p_b.m_y);
    float zMax ((p_a.m_z > p_b.m_z) ? p_a.m_z : p_b.m_z);
    float wMax ((p_a.m_w > p_b.m_w) ? p_a.m_w : p_b.m_w);

    return Vector4(xMax, yMax, zMax, wMax);
}

/**
 * @brief Computes the smallest 4D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the comparison
 */
constexpr Vector4   Vector4::Min				(const Vector4& p_a, const Vector4& p_b) noexcept
{
    float xMin ((p_a.m_x < p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMin ((p_a.m_y < p_b.m_y) ? p_a.m_y : p_b.m_y);
    float zMin ((p_a.m_z < p_b.m_z) ? p_a.m_z : p_b.m_z);
    float wMin ((p_a.m_w < p_b.m_w) ? p_a.m_w : p_b.m_w);

    return Vector4(xMin, yMin, zMin, wMin);
}

/**
 * @brief Moves a 4D point towards another one its speed limited
 * 
 * @param p_current          The current point
 * @param p_target           The target point
 * @param p_maxDistanceDelta The aximum speed
 * @return constexpr Vector3 The resulting point of the movement
 */
constexpr Vector4   Vector4::MoveTowards		(const Vector4& p_current, 
                                                 const Vector4& p_target, 
                                                 const float    p_maxDistanceDelta) noexcept
{
    Vector4 direction(p_current, p_target);

    float magnitude (std::sqrt(direction.m_x * direction.m_x + 
                               direction.m_y * direction.m_y + 
                               direction.m_z * direction.m_z + 
                               direction.m_w * direction.m_w));

    if (magnitude <= p_maxDistanceDelta || magnitude == 0.0f)
        return p_target;

    return p_current + (direction / magnitude) * p_maxDistanceDelta;
}

/**
 * @brief Projects a 4D vector on another one
 * 
 * @param p_vector           The vector to project
 * @param p_onNormal         The vector to project on
 * @return constexpr Vector3 The projected vector 
 */
constexpr Vector4   Vector4::Project			(const Vector4& p_vector, const Vector4& p_onNormal) noexcept
{
    if (p_onNormal == Vector4::Zero)
        return p_onNormal;

    float dot 		   (p_vector  .m_x * p_onNormal.m_x + 
                        p_vector  .m_y * p_onNormal.m_y + 
                        p_vector  .m_z * p_onNormal.m_z + 
                        p_vector  .m_w * p_onNormal.m_w);
    float sqrMagnitude (p_onNormal.m_x * p_onNormal.m_x + 
                        p_onNormal.m_y * p_onNormal.m_y + 
                        p_onNormal.m_z * p_onNormal.m_z + 
                        p_onNormal.m_w * p_onNormal.m_w);

    return (dot / sqrMagnitude) * p_onNormal;
}

/**
 * @brief Scales a 4D vector with another one
 * 
 * @param p_a                The vector to scale
 * @param p_b                The scaling vector
 * @return constexpr Vector3 The scaled vector
 */
constexpr Vector4   Vector4::Scale				(const Vector4& p_a, const Vector4& p_b) noexcept
{
    return Vector4(p_a.m_x * p_b.m_x, 
                   p_a.m_y * p_b.m_y, 
                   p_a.m_z * p_b.m_z, 
                   p_a.m_w * p_b.m_w);
}

/*=========================[Constructors + Destructor]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Vector4::Vector4  () noexcept
:   m_x {0.0f},
    m_y {0.0f},
    m_z {0.0f},
    m_w {0.0f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Vector4::Vector4  (const float p_x, 
                             const float p_y, 
                             const float p_z, 
                             const float p_w) noexcept
:   m_x {p_x}, 
    m_y {p_y}, 
    m_z {p_z},
    m_w {p_w}
{}

/**
 * @brief Constructor with one value applied to all members
 * 
 */
constexpr Vector4::Vector4  (const float p_value) noexcept
:   m_x {p_value}, 
    m_y {p_value}, 
    m_z {p_value},
    m_w {p_value}
{}

/**
 * @brief Constructor with two points
 * 
 */
constexpr Vector4::Vector4  (const Vector4& p_a, const Vector4& p_b) noexcept
:   m_x {p_b.m_x - p_a.m_x}, 
    m_y {p_b.m_y - p_a.m_y},
    m_z {p_b.m_z - p_a.m_z},
    m_w {p_b.m_w - p_a.m_w}
{}

/**
 * @brief Copy constructor with a 2D vector
 * 
 */
constexpr Vector4::Vector4  (const Vector2& p_vector2) noexcept
:   m_x {p_vector2.m_x}, 
    m_y {p_vector2.m_y}, 
    m_z {0.0f},
    m_w {1.0f}
{}

/**
 * @brief Copy constructor with a 3D vector
 * 
 */
constexpr Vector4::Vector4  (const Vector3& p_vector3, const float p_w) noexcept
:   m_x {p_vector3.m_x}, 
    m_y {p_vector3.m_y}, 
    m_z {p_vector3.m_z},
    m_w {p_w}
{}

/**
 * @brief Copy constructor with another 4D vector
 * 
 */
constexpr Vector4::Vector4  (const Vector4& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y}, 
    m_z {p_copy.m_z},
    m_w {p_copy.m_z}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Vector4::Vector4  (Vector4&& p_move) noexcept
:   m_x {std::move(p_move.m_x)},
    m_y {std::move(p_move.m_y)},
    m_z {std::move(p_move.m_z)},
    m_w {std::move(p_move.m_w)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Computes the homogenized vector of the current 4D vector
 * 
 * @return constexpr Vector4 The homogenized vector 
 */
constexpr Vector4   Vector4::GetHomogenize      () const
{
    if (m_w == 0.0f)
        throw std::domain_error("Divisiob by 0 is impossible!");

    return Vector4(m_x / m_w, m_y / m_w, m_z / m_w, 1.0f);
}

/**
 * @brief Calculates the length of the current 4D vector
 * 
 * @return constexpr float The resulting length's value
 */
constexpr float     Vector4::GetMagnitude       () const noexcept
{
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

/**
 * @brief Computes the normalized vector of the current 4D vector
 * 
 * @return constexpr Vector3 The normalized vector
 */
constexpr Vector4   Vector4::GetNormalize       ()	const noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));

    if (length == 0.0f)
        return Vector3::Zero;

    return Vector4(m_x / length, m_y / length, m_z / length, m_w / length);
}

/**
 * @brief Calculates the squared length of the current 4D vector
 * 
 * @return constexpr float The resulting squared length's value
 */
constexpr float     Vector4::GetSqrMagnitude    () const noexcept
{
    return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
}

/**
 * @brief Homogenizes the current 4D vector
 * 
 * @return constexpr Vector4 The homogenized vector
 */
constexpr Vector4   Vector4::Homogenize         ()
{
    if (m_w == 0.0f)
        throw std::domain_error("Division by 0 is impossbiel!");

    m_x /= m_w;
    m_y /= m_w;
    m_z /= m_w;
    m_w /= m_w;

    return *this;
}

/**
 * @brief Normalizes the current 4D vector
 * 
 * @return constexpr Vector3 The normalized vector
 */
constexpr Vector4 	Vector4::Normalize          () noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));

    if (length == 0.0f)
        return Vector3::Zero;

    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;

    return *this;
}

/**
 * @brief Sets the components of the current 4D vector to the new values
 * 
 * @param p_x                The x value
 * @param p_y                The y value
 * @param p_z                The z value
 * @param p_w                The w value
 * @return constexpr Vector4 The modified vector
 */
constexpr Vector4   Vector4::Set                (const float p_x, 
                                                 const float p_y, 
                                                 const float p_z, 
                                                 const float p_w) noexcept
{
    m_x = p_x;
    m_y = p_y;
    m_z = p_z;
    m_z = p_w;

    return *this;
}

/**
 * @brief Converts the current 4D vector to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Vector4::ToString           () const noexcept
{
    return std::string("Vector4 (" + std::to_string(m_x) + "," + 
                                     std::to_string(m_y) + "," +
                                     std::to_string(m_z) + "," +
                                     std::to_string(m_w) + ").");
}

/*=========================[Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The vector to move
 * @return constexpr Vector3& The moved vector
 */
constexpr Vector4&  Vector4::operator=  (Vector4&& p_move) noexcept
{
    m_x = std::move(p_move.m_x);
    m_y = std::move(p_move.m_y);
    m_z = std::move(p_move.m_z);
    m_w = std::move(p_move.m_w);

    return *this;
}

/**
 * @brief Copy operator with a 2D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector4&  Vector4::operator=  (const Vector2& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = 0.0f;
    m_w = 1.0f;

    return *this;
}

/**
 * @brief Copy operator with a 3D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector4&  Vector4::operator=  (const Vector3& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = p_copy.m_z;
    m_w = 1.0f;

    return *this;
}

/**
 * @brief Copy operator with another 4D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector4&  Vector4::operator=  (const Vector4& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = p_copy.m_z;
    m_w = p_copy.m_w;

    return *this;
}

/**
 * @brief Read only accessor
 * 
 * @param p_index          The index value
 * @return constexpr float The value to read
 */
constexpr float     Vector4::operator[] (const int p_index) const
{
    float value (0.0f);

    switch (p_index)
    {
        case 0	: value = m_x;	break;
        case 1	: value = m_y;	break;
        case 2	: value = m_z;	break;
        case 3	: value = m_w;	break;
        default : throw std::out_of_range("Value is out of Vector4 Index Range [0,3]"); break;
    }

    return value;
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_index           The index value
 * @return constexpr float& The value to read
 */
constexpr float&    Vector4::operator[] (const int p_index)
{
    switch (p_index)
    {
        case 0	: return m_x;	break;
        case 1	: return m_y;	break;
        case 2	: return m_z;	break;
        case 3	: return m_w;	break;
        default : throw std::out_of_range("Value is out of Vector4 Index Range [0,3]"); break;        
    }

    return m_x;
}

/*[General Operators]=========================*/

/**
 * @brief Increments the components of the current 4D vector
 * 
 * @param p_a                 The The target vector
 * @return constexpr Vector4& The incremented vector
 */
constexpr Vector4&		    Maths::operator++	(Vector4& p_a) noexcept
{
    p_a.m_x++;
    p_a.m_y++;
    p_a.m_z++;
    p_a.m_w++;

    return p_a;
}

/**
 * @brief Decrements the components of the current 4D vector
 * 
 * @param p_a                 The The target vector
 * @return constexpr Vector4& The decremented vector
 */
constexpr Vector4&		    Maths::operator--	(Vector4& p_a) noexcept
{
    p_a.m_x--;
    p_a.m_y--;
    p_a.m_z--;
    p_a.m_w--;

    return p_a;
}

/**
 * @brief Checks if two 4D vectors are equal
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are approximately equal
 * @return false The vectors are not equal
 */
constexpr bool              Maths::operator==   (const Vector4& p_a, const Vector4& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));
    double z        ((p_a.m_z - p_b.m_z) * (p_a.m_z - p_b.m_z));
    double w        ((p_a.m_w - p_b.m_w) * (p_a.m_w - p_b.m_w));

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return !((x > epsilon) || (y > epsilon) || (z > epsilon) || (w > epsilon));
}

/**
 * @brief Checks if two 4D vectors are different
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are not equal
 * @return false The vectors are approximately equal
 */
constexpr bool              Maths::operator!=   (const Vector4& p_a, const Vector4& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));
    double z        ((p_a.m_z - p_b.m_z) * (p_a.m_z - p_b.m_z));
    double w        ((p_a.m_w - p_b.m_w) * (p_a.m_w - p_b.m_w));    

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return ((x > epsilon) || (y > epsilon) || (z > epsilon) || (w > epsilon));
}

/**
 * @brief Adds two 4D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector4 The resulting vector of the addition
 */
constexpr Vector4           Maths::operator+    (const Vector4& p_a, const Vector4& p_b) noexcept 
{
    return Vector4(p_a.m_x + p_b.m_x, 
                   p_a.m_y + p_b.m_y, 
                   p_a.m_z + p_b.m_z, 
                   p_a.m_w + p_b.m_w);
}

/**
 * @brief Adds a value to the components of a 4D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to add
 * @return constexpr Vector4 The resulting vector of the addition
 */
constexpr Vector4 		    Maths::operator+	(const Vector4& p_a, const float p_k) noexcept
{
    return Vector4	(p_a.m_x + p_k, 
                     p_a.m_y + p_k, 
                     p_a.m_z + p_k, 
                     p_a.m_w + p_k);
}

/**
 * @brief Adds a value to the components of a 4D vector
 * 
 * @param p_k                The value to add
 * @param p_a                The target vector
 * @return constexpr Vector4 The resulting vector of the addition
 */
constexpr Vector4 		    Maths::operator+	(const float p_k, const Vector4& p_a) noexcept
{
    return Vector4	(p_a.m_x + p_k, 
                     p_a.m_y + p_k, 
                     p_a.m_z + p_k, 
                     p_a.m_w + p_k);
}

/**
 * @brief Adds a 4D vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to add
 * @return constexpr Vector4& The resulting vector of the addition
 */
constexpr Vector4&          Maths::operator+=   (Vector4& p_a, const Vector4& p_b) noexcept
{
    p_a.m_x += p_b.m_x;
    p_a.m_y += p_b.m_y;
    p_a.m_z += p_b.m_z;
    p_a.m_w += p_b.m_w;

    return p_a;
}

/**
 * @brief Adds a value to the components of the current 4D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to add
 * @return constexpr Vector4& The resulting vector of the addition
 */
constexpr Vector4&          Maths::operator+=   (Vector4& p_a, const float p_k) noexcept
{
    p_a.m_x += p_k;
    p_a.m_y += p_k;
    p_a.m_z += p_k;
    p_a.m_w += p_k;

    return p_a;
}

/**
 * @brief Substracts a 4D vector from another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector4& The resulting vector of the substraction
 */
constexpr Vector4           Maths::operator-    (const Vector4& p_a, const Vector4& p_b) noexcept
{
    return Vector4(p_a.m_x - p_b.m_x, 
                   p_a.m_y - p_b.m_y, 
                   p_a.m_z - p_b.m_z, 
                   p_a.m_w - p_b.m_w);
}

/**
 * @brief Substracts a value to the components of a 4D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to substract
 * @return constexpr Vector4 The resulting vector of the substraction
 */
constexpr Vector4 		    Maths::operator-	(const Vector4& p_a, const float p_k) noexcept
{
    return Vector4(p_a.m_x - p_k, 
                   p_a.m_y - p_k, 
                   p_a.m_z - p_k, 
                   p_a.m_w - p_k);
}

/**
 * @brief Computes the opposite vector of the current 4D vector
 * 
 * @param p_a                The target vector
 * @return constexpr Vector4 The opposite vector
 */
constexpr Vector4           Maths::operator-    (const Vector4& p_a) noexcept
{
    return Vector4(-p_a.m_x, -p_a.m_y, -p_a.m_z, -p_a.m_w);
}

/**
 * @brief Substracts a 4D vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector4& The resulting vector of the substraction
 */
constexpr Vector4&          Maths::operator-=   (Vector4& p_a, const Vector4& p_b) noexcept
{
    p_a.m_x -= p_b.m_x;
    p_a.m_y -= p_b.m_y;
    p_a.m_z -= p_b.m_z;
    p_a.m_w -= p_b.m_w;

    return p_a;
}

/**
 * @brief Substracts a value to the components of the current 4D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to substract
 * @return constexpr Vector4& The resulting vector of the substraction
 */
constexpr Vector4&          Maths::operator-=   (Vector4& p_a, const float p_k) noexcept
{
    p_a.m_x -= p_k;
    p_a.m_y -= p_k;
    p_a.m_z -= p_k;
    p_a.m_w -= p_k;

    return p_a;
}

/**
 * @brief Multiplies a 4D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to multiply
 * @return constexpr Vector4 The resulting vector of the multiplication
 */
constexpr Vector4 		    Maths::operator*	(const Vector4&	p_a, const Vector4&	p_b) noexcept
{
    return Vector4(p_a.m_x * p_b.m_x, 
                   p_a.m_y * p_b.m_y, 
                   p_a.m_x * p_b.m_x, 
                   p_a.m_w * p_b.m_w);
}

/**
 * @brief Multiplies a 4D vector by a number
 * 
 * @param p_k                The value to multiply
 * @param p_a                The target vector
 * @return constexpr Vector4 The resulting vector of the multiplication
 */
constexpr Vector4           Maths::operator*    (const float p_k, const Vector4& p_a) noexcept
{
    return Vector4(p_a.m_x * p_k, 
                   p_a.m_y * p_k, 
                   p_a.m_z * p_k, 
                   p_a.m_w * p_k);
}

/**
 * @brief Multiplies a 4D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to multiply
 * @return constexpr Vector4 The resulting vector of the multiplication
 */
constexpr Vector4           Maths::operator*    (const Vector4& p_a, const float p_k) noexcept
{
    return Vector4(p_a.m_x * p_k, 
                   p_a.m_y * p_k, 
                   p_a.m_z * p_k, 
                   p_a.m_w * p_k);    
}

/**
 * @brief Multiplies the current 4D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to multiply
 * @return constexpr Vector4& The resulting vector of the multiplication
 */
constexpr Vector4&          Maths::operator*=   (Vector4& p_a, const Vector4& p_b) noexcept
{
    p_a.m_x *= p_b.m_x;
    p_a.m_y *= p_b.m_y;
    p_a.m_z *= p_b.m_z;
    p_a.m_w *= p_b.m_w;

    return p_a;
}

/**
 * @brief Multiplies the current 4D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to multiply
 * @return constexpr Vector4& The resulting vector of the multiplication
 */
constexpr Vector4&          Maths::operator*=   (Vector4& p_a, const float p_k) noexcept
{
    p_a.m_x *= p_k;
    p_a.m_y *= p_k;
    p_a.m_z *= p_k;
    p_a.m_w *= p_k;

    return p_a;
}

/**
 * @brief Divides a 4D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to divide
 * @return constexpr Vector4 The resulting vector of the division
 */
constexpr Vector4 		    Maths::operator/	(const Vector4&	p_a, const Vector4&	p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f || p_b.m_z == 0.0f || p_b.m_w == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector4(p_a.m_x / p_b.m_x, 
                   p_a.m_y / p_b.m_y, 
                   p_a.m_z / p_b.m_z, 
                   p_a.m_w / p_b.m_w);
}

/**
 * @brief Divides a 4D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to divide
 * @return constexpr Vector4 The resulting vector of the division
 */
constexpr Vector4           Maths::operator/    (const Vector4& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector4(p_a.m_x / p_k, 
                   p_a.m_y / p_k, 
                   p_a.m_z / p_k, 
                   p_a.m_w / p_k);    
}

/**
 * @brief Divides the current 4D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to divide
 * @return constexpr Vector4& The resulting vector of the division
 */
constexpr Vector4&          Maths::operator/=   (Vector4& p_a, const Vector4& p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f || p_b.m_z == 0.0f || p_b.m_w == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_b.m_x;
    p_a.m_y /= p_b.m_y;
    p_a.m_z /= p_b.m_z;
    p_a.m_w /= p_b.m_w;

    return p_a;
}

/**
 * @brief Divides the current 4D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to divide
 * @return constexpr Vector3& The resulting vector of the division
 */
constexpr Vector4&          Maths::operator/=   (Vector4& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_k;
    p_a.m_y /= p_k;
    p_a.m_z /= p_k;
    p_a.m_w /= p_k;

    return p_a;
}

/**
 * @brief Computes the modulo of a 4D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to modulo
 * @return constexpr Vector4 The resulting vector of the modulo operation
 */
constexpr Vector4 		    Maths::operator%	(const Vector4&	p_a, const float p_k) noexcept
{
    return Vector4(fmod(p_a.m_x, p_k), 
                   fmod(p_a.m_y, p_k), 
                   fmod(p_a.m_z, p_k), 
                   fmod(p_a.m_w, p_k));
}

/**
 * @brief Computes the modulo of a 4D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to modulo
 * @return constexpr Vector4 The resulting vector of the modulo operation
 */
constexpr Vector4 		    Maths::operator%	(const Vector4&	p_a, const Vector4& p_b) noexcept
{
    return Vector4(fmod(p_a.m_x, p_b.m_x), 
                   fmod(p_a.m_y, p_b.m_y), 
                   fmod(p_a.m_z, p_a.m_z), 
                   fmod(p_a.m_w, p_a.m_w));
}

/**
 * @brief Computes the modulo of the current 4D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to modulo
 * @return constexpr Vector4& The resulting vector of the modulo operation
 */
constexpr Vector4&          Maths::operator%=   (Vector4& p_a, const Vector4& p_b) noexcept
{
    p_a.m_x = fmod(p_a.m_x, p_b.m_x);
    p_a.m_y = fmod(p_a.m_y, p_b.m_y);
    p_a.m_z = fmod(p_a.m_z, p_b.m_z);
    p_a.m_w = fmod(p_a.m_w, p_b.m_w);

    return p_a;
}

/**
 * @brief Computes the modulo of the current 4D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to modulo
 * @return constexpr Vector4& The resulting vector of the modulo operation
 */
constexpr Vector4&		    Maths::operator%=	(Vector4& p_a, const float p_k) noexcept
{
    p_a.m_x = fmod(p_a.m_x, p_k);
    p_a.m_y = fmod(p_a.m_y, p_k);
    p_a.m_z = fmod(p_a.m_z, p_k);
    p_a.m_w = fmod(p_a.m_w, p_k);

    return p_a;
}

/**
 * @brief Converts a 4D vector to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target vector
 * @return std::ostream& The resulting stream of the conversion
 */
inline    std::ostream&     Maths::operator<<	(std::ostream& p_flux, const Vector4& p_a) noexcept
{
    return p_flux << "Vector4(" << p_a.m_x << ", " 
                                << p_a.m_y << ", " 
                                << p_a.m_z  << ", " 
                                << p_a.m_w << ").";
}

#endif // !__VECTOR_4_INL__