#ifndef __VECTOR_2_INL__
#define __VECTOR_2_INL__

/**
 * @file    Vector2.inl
 * @brief   Inline file for Vector2
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GVector2
 * 
 */

#include <cmath>
#include <stdexcept>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Vector4.hpp"

using namespace Maths;

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Calculates the unsigned angle between two 2D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting unsigned angle in degrees
 */
constexpr float	    Vector2::AngleDegree   		(const Vector2& p_from, const Vector2& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y));

    float dotProduct (p_from.m_x * p_to.m_x + p_from.m_y * p_to.m_y);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;        

    return std::acos(dotProduct / (fromLength * toLength)) * 180.0f / (float)PI;
}

/**
 * @brief Calculates the unsigned angle between two 2D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting unsigned angle in radians
 */
constexpr float     Vector2::AngleRadian    	(const Vector2& p_from, const Vector2& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y));

    float dotProduct (p_from.m_x * p_to.m_x + p_from.m_y * p_to.m_y);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;        

    return std::acos(dotProduct / (fromLength * toLength));
}

/**
 * @brief Creates a vector its magnitude clamped
 * 
 * @param p_vector           The base vector
 * @param p_maxLength        The clamp value
 * @return constexpr Vector2 The resulting vector of the clamping
 */
constexpr Vector2   Vector2::ClampMagnitude 	(const Vector2& p_vector, const float p_maxLength) noexcept
{
    Vector2 vector (p_vector);

    float   length (std::sqrt(vector.m_x * vector.m_x + 
                              vector.m_y * vector.m_y));

    if (length > p_maxLength && p_maxLength > 0.0f)
        (vector /= length) *= p_maxLength;

    return vector;
}   

/**
 * @brief Calculates the distance between two 2D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting distance's value
 */
constexpr float     Vector2::Distance       	(const Vector2& p_a, const Vector2& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);

    return std::sqrt(x * x + y * y);
}

/**
 * @brief Calculates the squared distance between two 2D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting squared distance's value
 */
constexpr float	    Vector2::DistanceSqr    	(const Vector2& p_a, const Vector2& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);

    return x * x + y * y;
}

/**
 * @brief Calculates the dot product between two 2D vectors
 *  
 * @param p_a              The left handed vector
 * @param p_b              The right handed vector
 * @return constexpr float The resulting dot product's value
 */
constexpr float     Vector2::Dot            	(const Vector2& p_a, const Vector2& p_b) noexcept
{
    return p_a.m_x * p_b.m_x + p_a.m_y * p_b.m_y;
}

/**
 * @brief Checks if two 2D vectors are colinear
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  Both vectors are colinear
 * @return false Both vectors are not colinear
 */
constexpr bool	    Vector2::IsColinear     	(const Vector2& p_a, const Vector2& p_b) noexcept
{
    float colinear (p_a.m_x * p_b.m_y - p_a.m_y * p_b.m_x);

    return colinear * colinear <= __FLT_EPSILON__ * __FLT_EPSILON__;
}

/**
 * @brief Linearly interpolates between two 2D vectors its value clamped
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector2 The resulting vector of the lerping
 */
constexpr Vector2   Vector2::Lerp        		(const Vector2& p_a, const Vector2& p_b, const float p_t) noexcept
{
    float value ((p_t <= 0.0f) ? 0.0f : (p_t >= 1.0f) ?  1.0f : p_t);

    return (1.0f - value) * p_a + value * p_b;
}

/**
 * @brief Linearly interpolates between two 2D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector2 The resulting vector of the lerping
 */
constexpr Vector2   Vector2::LerpUnclamped		(const Vector2& p_a, const Vector2& p_b, const float p_t) noexcept
{
    return (1.0f - p_t) * p_a + p_t * p_b;
}

/**
 * @brief Computes the greatest 2D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector2 The resulting vector of the comparison
 */
constexpr Vector2   Vector2::Max				(const Vector2& p_a, const Vector2& p_b) noexcept
{
    float xMax ((p_a.m_x > p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMax ((p_a.m_y > p_b.m_y) ? p_a.m_y : p_b.m_y);

    return Vector2(xMax, yMax);
}

/**
 * @brief Computes the smallest 2D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector2 The resulting vector of the comparison
 */
constexpr Vector2   Vector2::Min				(const Vector2& p_a, const Vector2& p_b) noexcept
{
    float xMin ((p_a.m_x < p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMin ((p_a.m_y < p_b.m_y) ? p_a.m_y : p_b.m_y);

    return Vector2(xMin, yMin);
}

/**
 * @brief Moves a 2D point towards another one its speed limited
 * 
 * @param p_current          The current point
 * @param p_target           The target point
 * @param p_maxDistanceDelta The maximum speed
 * @return constexpr Vector2 The resulting point of the movement
 */
constexpr Vector2   Vector2::MoveTowards		(const Vector2& p_current, 
                                                 const Vector2& p_target, 
                                                 const float    p_maxDistanceDelta) noexcept
{
    Vector2 direction (p_current, p_target);

    float magnitude (std::sqrt(direction.m_x * direction.m_x + 
                               direction.m_y * direction.m_y));

    if (magnitude <= p_maxDistanceDelta || magnitude == 0.0f)
        return p_target;

    return p_current + (direction / magnitude) * p_maxDistanceDelta;
}

/**
 * @brief Projects a 2D vector on another one
 * 
 * @param p_vector           The vector to project
 * @param p_onNormal         The vector to project on
 * @return constexpr Vector2 The resulting vector of the projection
 */
constexpr Vector2   Vector2::Project			(const Vector2& p_vector, const Vector2& p_onNormal) noexcept
{
    if (p_onNormal == Vector2::Zero)
        return p_onNormal;

    float dot 		   (p_vector  .m_x * p_onNormal.m_x + 
                        p_vector  .m_y * p_onNormal.m_y);
    float sqrMagnitude (p_onNormal.m_x * p_onNormal.m_x + 
                        p_onNormal.m_y * p_onNormal.m_y);

    return (dot / sqrMagnitude) * p_onNormal;
}

/**
 * @brief Reflects a 2D vector on another one defined by a normal
 * 
 * @param p_direction        The vector to reflect
 * @param p_normal           The normal defining the point to reflect on
 * @return constexpr Vector2 The resulting vector of the reflection
 */
constexpr Vector2   Vector2::Reflect			(const Vector2& p_direction, const Vector2& p_normal)
{
    float dot 	       (p_direction.m_x * p_normal.m_x + 
                        p_direction.m_y * p_normal.m_y);
    float sqrMagnitude (p_normal   .m_x * p_normal.m_x + 
                        p_normal   .m_y * p_normal.m_y);

    if (sqrMagnitude == 0.0f)
        throw std::domain_error("Normal's magnitude is null!");

    return p_direction - (dot / sqrMagnitude * p_normal) * 2.0f;
}

/**
 * @brief Reflects a 2D vector on another one defined by a normal and inverts it
 * 
 * @param p_direction        The vector to reflect
 * @param p_normal           The normal defining the point to reflect on
 * @return constexpr Vector2 The resulting vector of the inverted reflection
 */
constexpr Vector2   Vector2::ReflectInvert		(const Vector2& p_direction, const Vector2& p_normal)
{
    float dot          (p_direction.m_x * p_normal.m_x + 
                        p_direction.m_y * p_normal.m_y);
    float sqrMagnitude (p_normal   .m_x * p_normal.m_x + 
                        p_normal   .m_y * p_normal.m_y);

    if (sqrMagnitude == 0.0f)
        throw std::domain_error("Normal's magnitude is null!");

    return (dot / sqrMagnitude * p_normal) * 2.0f - p_direction;
}

/**
 * @brief Scales a 2D vector another one
 * 
 * @param p_a                The vector to scale
 * @param p_b                The scaling vector
 * @return constexpr Vector2 The resulting vector of the scaling
 */
constexpr Vector2   Vector2::Scale				(const Vector2& p_a, const Vector2& p_b) noexcept
{
    return Vector2(p_a.m_x * p_b.m_x, p_a.m_y * p_b.m_y);
}

/**
 * @brief Calculates the signed angle between two 2D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting signed angle in degrees
 */
constexpr float 	Vector2::SignedAngleDegree	(const Vector2& p_from, const Vector2& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y));


    float dotProduct (p_from.m_x * p_to.m_x + p_from.m_y * p_to.m_y);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    float angle (std::acos(dotProduct / (fromLength * toLength)) * 180.0f / (float)PI);
    
    return (p_to.m_y < 0.0f) ? angle * -1.0f : angle;
}

/**
 * @brief Calculates the signed angle between two 2D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting signed angle in radians
 */
constexpr float 	Vector2::SignedAngleRadian  (const Vector2& p_from, const Vector2& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y));
    
    float dotProduct (p_from.m_x * p_to.m_x + p_from.m_y * p_to.m_y);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    float angle (std::acos(dotProduct / (fromLength * toLength)));

    return (p_to.m_y < 0.0f) ? angle * -1.0f : angle;
}

/*=========================[Constructors + Destructor]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Vector2::Vector2  () noexcept
:   m_x {0.0f},
    m_y {0.0f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Vector2::Vector2  (const float p_x, const float p_y) noexcept
:   m_x {p_x}, 
    m_y {p_y}
{}

/**
 * @brief Constructor with one value applied to all members
 * 
 */
constexpr Vector2::Vector2  (const float p_value) noexcept
:   m_x {p_value}, 
    m_y {p_value}
{}

/**
 * @brief Constructor with two points
 * 
 */
constexpr Vector2::Vector2  (const Vector2& p_a, const Vector2& p_b) noexcept
:   m_x {p_b.m_x - p_a.m_x}, 
    m_y {p_b.m_y - p_a.m_y}
{}

/**
 * @brief Copy constructor with another 2D vector
 * 
 */
constexpr Vector2::Vector2  (const Vector2& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y}
{}

/**
 * @brief Copy constructor with a 3D vector
 * 
 */
constexpr Vector2::Vector2  (const Vector3& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y}
{}

/**
 * @brief Copy constructor with a 4D vector
 * 
 */
constexpr Vector2::Vector2  (const Vector4& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Vector2::Vector2  (Vector2&& p_move) noexcept
:   m_x {std::move(p_move.m_x)},
    m_y {std::move(p_move.m_y)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Calculates the length of the current 2D vector
 * 
 * @return constexpr float The resulting length's value
 */
constexpr float   	Vector2::GetMagnitude   () const noexcept
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

/**
 * @brief Creates the normalized vector of the current 2D vector
 * 
 * @return constexpr Vector2 The normalized vector
 */
constexpr Vector2 	Vector2::GetNormalize   () const noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y));

    if (length == 0.0f)
        return Vector2::Zero;

    return Vector2(m_x / length, m_y / length);
}

/**
 * @brief Calculates the squared length of the current 2D vector
 * 
 * @return constexpr float The resulting squared length's value
 */
constexpr float   	Vector2::GetSqrMagnitude() const noexcept
{
    return m_x * m_x + m_y * m_y;
}

/**
 * @brief Normalizes the current 2D vector
 * 
 * @return constexpr Vector2 The normalized vector
 */
constexpr Vector2 	Vector2::Normalize      () noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y));

    if (length != 0.0f)
    {
        m_x /= length;
        m_y /= length;
    }

    return *this;
}

/**
 * @brief Sets the components of the current 2D vector to the new values
 * 
 * @param p_x                The x value
 * @param p_y                The y value
 * @return constexpr Vector2 The modified vector
 */
constexpr Vector2   Vector2::Set            (const float p_x, const float p_y) noexcept
{
    m_x = p_x;
    m_y = p_y;

    return *this;
}

/**
 * @brief Converts the current 2D vector to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Vector2::ToString       () const noexcept
{
    return std::string("Vector2 (" + std::to_string(m_x) + "," + 
                                     std::to_string(m_y) + ").");
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The vector to move
 * @return constexpr Vector2& The moved vector
 */
constexpr Vector2&  Vector2::operator=  (Vector2&& p_move) noexcept
{
    m_x = std::move(p_move.m_x);
    m_y = std::move(p_move.m_y);

    return *this;
}

/**
 * @brief Copy operator with another 2D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector2& The copied vector
 */
constexpr Vector2&  Vector2::operator=  (const Vector2& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;

    return *this;
}

/**
 * @brief Copy operator with a 3D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector2& The copied vector
 */
constexpr Vector2&  Vector2::operator=  (const Vector3& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;

    return *this;
}

/**
 * @brief Copy operator with a 4D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector2& The copied vector
 */
constexpr Vector2&  Vector2::operator=  (const Vector4& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;

    return *this;
}

/**
 * @brief Read only accessor
 * 
 * @param p_index          The index value
 * @return constexpr float The value to read
 */
constexpr float     Vector2::operator[] (const int p_index) const
{
    float value (0.0f);

    switch (p_index)
    {
        case 0	: value = m_x;  break;
        case 1	: value = m_y;	break;
        default : throw std::out_of_range("Value is out of Vector2's index range : [0,1]"); break;
    }

    return value;
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_index           The index value
 * @return constexpr float& The value to modify
 */
constexpr float&    Vector2::operator[] (const int p_index)
{
    switch (p_index)
    {
        case 0	: return m_x;	break;
        case 1	: return m_y;	break;
        default : throw std::out_of_range("Value is out of Vector2's index range : [0,1]"); break;
    }
}

/*=========================[General Operators]=========================*/

/**
 * @brief Increments the components of the current 2D vector
 * 
 * @param p_a                 The target vector
 * @return constexpr Vector2& The incremented vector
 */
constexpr Vector2&      Maths::operator++   (Vector2& p_a) noexcept
{
    p_a.m_x++;
    p_a.m_y++;

    return p_a;
}

/**
 * @brief Decrements the components of the current 2D vector
 * 
 * @param p_a                 The target vector
 * @return constexpr Vector2& The decremented vector
 */
constexpr Vector2&      Maths::operator--   (Vector2& p_a) noexcept
{
    p_a.m_x--;
    p_a.m_y--;

    return p_a;
}

/**
 * @brief Checks if two 2D vectors are equal
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are approximately equal
 * @return false The vectors are not equal
 */
constexpr bool          Maths::operator==   (const Vector2& p_a, const Vector2& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return !((x > epsilon) || (y > epsilon));
}

/**
 * @brief Checks if two 2D vectors are different
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are not equal
 * @return false The vectors are approximately equal
 */
constexpr bool          Maths::operator!=   (const Vector2& p_a, const Vector2& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return ((x > epsilon) || (y > epsilon));
}

/**
 * @brief Adds two 2D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector2 The resulting vector of the addition
 */
constexpr Vector2       Maths::operator+    (const Vector2& p_a, const Vector2& p_b) noexcept
{
    return Vector2(p_a.m_x + p_b.m_x, p_a.m_y + p_b.m_y);
}

/**
 * @brief Adds a value to the components of a 2D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to add
 * @return constexpr Vector2 The resulting vector of the addition
 */
constexpr Vector2       Maths::operator+    (const Vector2& p_a, const float p_k) noexcept
{
    return Vector2(p_a.m_x + p_k, p_a.m_y + p_k);
}

/**
 * @brief Adds a value to the components of a 2D vector
 * 
 * @param p_k                The value to add
 * @param p_a                The target vector
 * @return constexpr Vector2 The resulting vector of the addition
 */
constexpr Vector2 	    Maths::operator+	(const float p_k, const Vector2& p_a) noexcept
{
    return Vector2(p_a.m_x + p_k, p_a.m_y + p_k);
}

/**
 * @brief Adds a 2D vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to add
 * @return constexpr Vector2& The resulting vector of the addition
 */
constexpr Vector2&      Maths::operator+=   (Vector2& p_a, const Vector2& p_b) noexcept
{
    p_a.m_x += p_b.m_x;
    p_a.m_y += p_b.m_y;

    return p_a;
}

/**
 * @brief Adds a value to the components of the current 2D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to add
 * @return constexpr Vector2& The resulting vector of the addition
 */
constexpr Vector2&      Maths::operator+=   (Vector2& p_a, const float p_k) noexcept
{
    p_a.m_x += p_k;
    p_a.m_y += p_k;

    return p_a;
}

/**
 * @brief Substracts a 2D vector from another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector2& The resulting vector of the substraction
 */
constexpr Vector2       Maths::operator-    (const Vector2& p_a, const Vector2& p_b) noexcept
{
    return Vector2(p_a.m_x - p_b.m_x, p_a.m_y - p_b.m_y);
}

/**
 * @brief Substracts a value to the components of a 2D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to substract
 * @return constexpr Vector2 The resulting vector of the substraction
 */
constexpr Vector2       Maths::operator-	(const Vector2& p_a, const float p_k) noexcept
{
    return Vector2(p_a.m_x - p_k, p_a.m_y - p_k);
}

/**
 * @brief Computes the opposite vector of a 2D vector
 * 
 * @param p_a                The target vector
 * @return constexpr Vector2 The opposite vector
 */
constexpr Vector2       Maths::operator-    (const Vector2& p_a) noexcept
{
    return Vector2(-p_a.m_x, -p_a.m_y);
}

/**
 * @brief Substracts a 2D vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector2& The resulting vector of the substraction
 */
constexpr Vector2&      Maths::operator-=   (Vector2& p_a, const Vector2& p_b) noexcept
{
    p_a.m_x -= p_b.m_x;
    p_a.m_y -= p_b.m_y;

    return p_a;
}

/**
 * @brief Substracts a value to the components of the current 2D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to substract
 * @return constexpr Vector2& The resulting vector of the substraction
 */
constexpr Vector2&      Maths::operator-=   (Vector2& p_a, const float p_k) noexcept
{
    p_a.m_x -= p_k;
    p_a.m_y -= p_k;

    return p_a;
}

/**
 * @brief Multiplies a 2D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to multiply
 * @return constexpr Vector2 The resulting vector of the multiplication
 */
constexpr Vector2       Maths::operator*	(const Vector2&	p_a, const Vector2&	p_b) noexcept
{
    return Vector2(p_a.m_x * p_b.m_x, p_a.m_y * p_b.m_y);
}

/**
 * @brief Multiplies a 2D vector by a number
 * 
 * @param p_k                The value to multiply
 * @param p_a                The target vector
 * @return constexpr Vector2 The resulting vector of the multiplication
 */
constexpr Vector2       Maths::operator*    (const float p_k, const Vector2& p_a) noexcept
{
    return Vector2(p_a.m_x * p_k, p_a.m_y * p_k);
}

/**
 * @brief Multiplies a 2D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to multiply
 * @return constexpr Vector2 The resulting vector of the multiplication
 */
constexpr Vector2       Maths::operator*    (const Vector2& p_a, const float p_k) noexcept
{
    return Vector2(p_a.m_x * p_k, p_a.m_y * p_k);    
}

/**
 * @brief Multiplies the current 2D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to multiply
 * @return constexpr Vector2& The resulting vector of the multiplication
 */
constexpr Vector2&      Maths::operator*=   (Vector2& p_a, const Vector2& p_b) noexcept
{
    p_a.m_x *= p_b.m_x;
    p_a.m_y *= p_b.m_y;

    return p_a;
}

/**
 * @brief Multiplies the current 2D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to multiply
 * @return constexpr Vector2& The resulting vector of the multiplication
 */
constexpr Vector2&      Maths::operator*=   (Vector2& p_a, const float p_k) noexcept
{
    p_a.m_x *= p_k;
    p_a.m_y *= p_k;

    return p_a;
}

/**
 * @brief Divides a 2D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to divide
 * @return constexpr Vector2 The resulting vector of the division
 */
constexpr Vector2       Maths::operator/	(const Vector2&	p_a, const Vector2&	p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector2(p_a.m_x / p_b.m_x, p_a.m_y / p_b.m_y);
}

/**
 * @brief Divides a 2D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to divide
 * @return constexpr Vector2 The resulting vector of the division
 */
constexpr Vector2       Maths::operator/    (const Vector2& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector2(p_a.m_x / p_k, p_a.m_y / p_k);    
}

/**
 * @brief Divides the current 2D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to divide
 * @return constexpr Vector2& The resulting vector of the division
 */
constexpr Vector2&      Maths::operator/=   (Vector2& p_a, const Vector2& p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_b.m_x;
    p_a.m_y /= p_b.m_y;

    return p_a;
}

/**
 * @brief Divides the current 2D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to divide
 * @return constexpr Vector2& The resulting vector of the division
 */
constexpr Vector2&      Maths::operator/=   (Vector2& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_k;
    p_a.m_y /= p_k;

    return p_a;
}

/**
 * @brief Computes the modulo of a 2D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to modulo
 * @return constexpr Vector2 The resulting vector of the modulo operation
 */
constexpr Vector2       Maths::operator%	(const Vector2&	p_a, const float p_k) noexcept
{
    return Vector2(std::fmod(p_a.m_x, p_k), std::fmod(p_a.m_y, p_k));
}

/**
 * @brief Computes the modulo of a 2D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to modulo
 * @return constexpr Vector2 The resulting vector of the modulo operation
 */
constexpr Vector2       Maths::operator%	(const Vector2&	p_a, const Vector2& p_b) noexcept
{
    return Vector2(std::fmod(p_a.m_x, p_b.m_x), std::fmod(p_a.m_y, p_b.m_y));
}

/**
 * @brief Computes the modulo of the current 2D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to modulo
 * @return constexpr Vector2& The resulting vector of the modulo operation
 */
constexpr Vector2&      Maths::operator%=   (Vector2& p_a, const Vector2& p_b) noexcept
{
    p_a.m_x = std::fmod(p_a.m_x, p_b.m_x);
    p_a.m_y = std::fmod(p_a.m_y, p_b.m_y);

    return p_a;
}

/**
 * @brief Computes the modulo operation of the current 2D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The vector to modulo
 * @return constexpr Vector2& The resulting vector of the modulo operation
 */
constexpr Vector2&	    Maths::operator%=	(Vector2& p_a, const float p_k) noexcept
{
    p_a.m_x = std::fmod(p_a.m_x, p_k);
    p_a.m_y = std::fmod(p_a.m_y, p_k);

    return p_a;
}

/**
 * @brief Converts a 2D vector to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target vector
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Vector2& p_a) noexcept
{
    return p_flux << "Vector2(" << p_a.m_x << ", " << p_a.m_y << ").";
}   

#endif // !__VECTOR_2_INL__