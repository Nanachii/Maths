#ifndef __VECTOR_3_INL__
#define __VECTOR_3_INL__

/**
 * @file    Vector3.inl
 * @brief   Inline file for Vector3
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GVector3
 * 
 */

#include <cmath>
#include <stdexcept>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector2.hpp"
#include "../Includes/Vector4.hpp"

using namespace Maths;

/*==========================[Static Methods (Public)]===========================*/

/**
 * @brief Calculates the unsigned angle between two 3D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting unsigned angle in degrees
 */
constexpr float	    Vector3::AngleDegree   		    (const Vector3& p_from, const Vector3& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y +
                                p_from.m_z * p_from.m_z));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y +
                                p_to  .m_z * p_to  .m_z));

    float dotProduct (p_from.m_x * p_to.m_x + 
                      p_from.m_y * p_to.m_y + 
                      p_from.m_z * p_to.m_z);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    return std::acos(dotProduct / (fromLength * toLength)) * 180.0f / (float)PI;
}

/**
 * @brief Calculates the unsigned angle between two 3D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @return constexpr float The resulting unsigned angle in radians
 */
constexpr float     Vector3::AngleRadian    	    (const Vector3& p_from, const Vector3& p_to)
{
    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y +
                                p_from.m_z * p_from.m_z));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y +
                                p_to  .m_z * p_to  .m_z));

    float dotProduct (p_from.m_x * p_to.m_x + 
                      p_from.m_y * p_to.m_y +
                      p_from.m_z * p_to.m_z);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    return std::acos(dotProduct / (fromLength * toLength));
}

/**
 * @brief Creates a vector its magnitude clamped
 * 
 * @param p_vector           The base vector
 * @param p_maxLength        The clamp value
 * @return constexpr Vector3 The resulting vector of the clamping
 */
constexpr Vector3   Vector3::ClampMagnitude 	    (const Vector3& p_vector, const float p_maxLength) noexcept
{
    Vector3 vector (p_vector);

    float   length (std::sqrt(vector.m_x * vector.m_x + 
                              vector.m_y * vector.m_y +
                              vector.m_z * vector.m_z));

    if (length > p_maxLength && p_maxLength > 0.0f)
        (vector /= length) *= p_maxLength;

    return vector;
}   

/**
 * @brief Computes the cross product between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the cross product
 */
constexpr Vector3   Vector3::Cross                  (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return Vector3(p_a.m_y * p_b.m_z - p_a.m_z * p_b.m_y, 
                   p_a.m_z * p_b.m_x - p_a.m_x * p_b.m_z, 
                   p_a.m_x * p_b.m_y - p_a.m_y * p_b.m_x);
}

/**
 * @brief Calculates the distance between two 3D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting distance's value
 */
constexpr float     Vector3::Distance       	    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);
    float z (p_b.m_z - p_a.m_z);

    return std::sqrt(x * x + y * y + z * z);
}

/**
 * @brief Calculates the squared distance between two 3D points
 * 
 * @param p_a              The left handed point
 * @param p_b              The right handed point
 * @return constexpr float The resulting squared distance's value
 */
constexpr float	    Vector3::DistanceSqr    	    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    float x (p_b.m_x - p_a.m_x);
    float y (p_b.m_y - p_a.m_y);
    float z (p_b.m_z - p_a.m_z);

    return x * x + y * y + z * z;
}

/**
 * @brief Calculates the dot product between two 3D vectors
 *  
 * @param p_a              The left handed vector
 * @param p_b              The right handed vector
 * @return constexpr float The resulting dot product's value
 */
constexpr float     Vector3::Dot            	    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return p_a.m_x * p_b.m_x + 
           p_a.m_y * p_b.m_y + 
           p_a.m_z * p_b.m_z;
}

/**
 * @brief Computes the unsigned euler angles between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting unsigned euler angles vector in degrees
 */
constexpr Vector3   Vector3::EulerAngleDegree       (const Vector3& p_a, const Vector3& p_b)
{
    float x (Vector2::AngleDegree(Vector2(p_a.m_y, p_a.m_z), Vector2(p_b.m_y, p_b.m_z)));
    float y (Vector2::AngleDegree(Vector2(p_a.m_x, p_a.m_z), Vector2(p_b.m_x, p_b.m_z)));
    float z (Vector2::AngleDegree(Vector2(p_a.m_x, p_a.m_y), Vector2(p_b.m_x, p_b.m_y)));

    return Vector3 (x,y,z);
}

/**
 * @brief Computes the unsigned euler angles between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting unsigned euler angles vector in radians
 */
constexpr Vector3   Vector3::EulerAngleRadian       (const Vector3& p_a, const Vector3& p_b)
{
    float x (Vector2::AngleRadian(Vector2(p_a.m_y, p_a.m_z), Vector2(p_b.m_y, p_b.m_z)));
    float y (Vector2::AngleRadian(Vector2(p_a.m_x, p_a.m_z), Vector2(p_b.m_x, p_b.m_z)));
    float z (Vector2::AngleRadian(Vector2(p_a.m_x, p_a.m_y), Vector2(p_b.m_x, p_b.m_y)));

    return Vector3 (x,y,z);
}

/**
 * @brief Checks if two 3D vectors are colinear
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  Both vectors are colinear
 * @return false Both vectors are not colinear
 */
constexpr bool	    Vector3::IsColinear     	    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    Vector3 cross(p_a.m_y * p_b.m_z - p_a.m_z * p_b.m_y, 
                  p_a.m_z * p_b.m_x - p_a.m_x * p_b.m_z, 
                  p_a.m_x * p_b.m_y - p_a.m_y * p_b.m_x);

    return !(cross.m_x * cross.m_x > __FLT_EPSILON__ * __FLT_EPSILON__ || 
             cross.m_y * cross.m_y > __FLT_EPSILON__ * __FLT_EPSILON__ || 
             cross.m_z * cross.m_z > __FLT_EPSILON__ * __FLT_EPSILON__);
}

/**
 * @brief Linearly interpolates between two 3D vectors its value clamped
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector3   Vector3::Lerp        		    (const Vector3& p_a, const Vector3& p_b, const float p_t) noexcept
{
    float value ((p_t <= 0.0f) ? 0.0f : (p_t >= 1.0f) ?  1.0f : p_t);

    return (1.0f - value) * p_a + value * p_b;
}

/**
 * @brief Linearly interpolates between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector3   Vector3::LerpUnclamped		    (const Vector3& p_a, const Vector3& p_b, const float p_t) noexcept
{
    return (1.0f - p_t) * p_a + p_t * p_b;
}

/**
 * @brief Computes the greatest 3D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the comparison
 */
constexpr Vector3   Vector3::Max				    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    float xMax ((p_a.m_x > p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMax ((p_a.m_y > p_b.m_y) ? p_a.m_y : p_b.m_y);
    float zMax ((p_a.m_z > p_b.m_z) ? p_a.m_z : p_b.m_z);

    return Vector3(xMax, yMax, zMax);
}

/**
 * @brief Computes the smallest 3D vector two other vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the comparison
 */
constexpr Vector3   Vector3::Min				    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    float xMin ((p_a.m_x < p_b.m_x) ? p_a.m_x : p_b.m_x);
    float yMin ((p_a.m_y < p_b.m_y) ? p_a.m_y : p_b.m_y);
    float zMin ((p_a.m_z < p_b.m_z) ? p_a.m_z : p_b.m_z);

    return Vector3(xMin, yMin, zMin);
}

/**
 * @brief Moves a 3D point towards another one its speed limited
 * 
 * @param p_current          The current point
 * @param p_target           The target point
 * @param p_maxDistanceDelta The maximum speed
 * @return constexpr Vector3 The resulting point of the movement
 */
constexpr Vector3   Vector3::MoveTowards		    (const Vector3& p_current, 
                                                     const Vector3& p_target, 
                                                     const float    p_maxDistanceDelta) noexcept
{
    Vector3 direction (p_current, p_target);

    float magnitude (std::sqrt(direction.m_x * direction.m_x + 
                               direction.m_y * direction.m_y));

    if (magnitude <= p_maxDistanceDelta || magnitude == 0.0f)
        return p_target;

    return p_current + (direction / magnitude) * p_maxDistanceDelta;
}

/**
 * @brief Projects a 3D vector on another one
 * 
 * @param p_vector           The vector to project
 * @param p_onNormal         The vector to project on
 * @return constexpr Vector3 The resulting vector of the projection 
 */
constexpr Vector3   Vector3::Project			    (const Vector3& p_vector, const Vector3& p_onNormal) noexcept
{
    if (p_onNormal == Vector3::Zero)
        return p_onNormal;

    float dot 		   (p_vector  .m_x * p_onNormal.m_x + 
                        p_vector  .m_y * p_onNormal.m_y +
                        p_vector  .m_z * p_onNormal.m_z);
    float sqrMagnitude (p_onNormal.m_x * p_onNormal.m_x + 
                        p_onNormal.m_y * p_onNormal.m_y +
                        p_onNormal.m_z * p_onNormal.m_z);

    return (dot / sqrMagnitude) * p_onNormal;
}

/**
 * @brief Projects a 3D vector on a plane defined by a normal
 * 
 * @param p_vector           The vector to project
 * @param p_planeNormal      The normal of the plane
 * @return constexpr Vector3 The resulting vector of the projection
 */
constexpr Vector3   Vector3::ProjectOnPlane         (const Vector3& p_vector, const Vector3& p_planeNormal) noexcept
{
    if (p_planeNormal == Vector3::Zero)
        return p_planeNormal;

    float dot 			{p_vector.m_x*p_planeNormal.m_x + p_vector.m_y*p_planeNormal.m_y + p_vector.m_z*p_planeNormal.m_z};
    float sqrMagnitude 	{p_planeNormal.m_x*p_planeNormal.m_x + p_planeNormal.m_y*p_planeNormal.m_y + p_planeNormal.m_z*p_planeNormal.m_z};

    return p_vector - (dot/sqrMagnitude * p_planeNormal);
}

/**
 * @brief Reflects a 3D vector on another one defined by a normal
 * 
 * @param p_direction        The vector to reflect
 * @param p_normal           The normal defining the point to reflect on
 * @return constexpr Vector3 The resulting vector of the reflection
 */
constexpr Vector3   Vector3::Reflect			    (const Vector3& p_direction, const Vector3& p_normal)
{
    float dot 	       (p_direction.m_x * p_normal.m_x + 
                        p_direction.m_y * p_normal.m_y +
                        p_direction.m_z * p_normal.m_z);
    float sqrMagnitude (p_normal   .m_x * p_normal.m_x + 
                        p_normal   .m_y * p_normal.m_y +
                        p_normal   .m_z * p_normal.m_z);

    if (sqrMagnitude == 0.0f)
        throw std::domain_error("Normal's magnitude is null!");

    return p_direction - (dot / sqrMagnitude * p_normal) * 2.0f;
}

/**
 * @brief Reflects a 3D vector on another one defined by a normal and inverts it
 * 
 * @param p_direction        The vector to reflect
 * @param p_normal           The normal defining the point to reflect on
 * @return constexpr Vector3 The resulting vector of the inverted reflection
 */
constexpr Vector3   Vector3::ReflectInvert		    (const Vector3& p_direction, const Vector3& p_normal)
{
    float dot          (p_direction.m_x * p_normal.m_x + 
                        p_direction.m_y * p_normal.m_y +
                        p_direction.m_z * p_normal.m_z);
    float sqrMagnitude (p_normal   .m_x * p_normal.m_x + 
                        p_normal   .m_y * p_normal.m_y +
                        p_normal   .m_z * p_normal.m_z);

    if (sqrMagnitude == 0.0f)
        throw std::domain_error("Normal's magnitude is null!");

    return (dot / sqrMagnitude * p_normal) * 2.0f - p_direction;
}

/**
 * @brief Rotates a 3D The vector towards another one
 * 
 * @param p_current          The vector to rotate
 * @param p_target           The target vector
 * @param p_maxRadiansDelta  The distance between the vectors 
 * @param p_maxDistanceDelta The length of the radian 
 * @return constexpr Vector3 The resulting vector of the rotation
 */
[[deprecated("This functions is not implemented yet!")]]
constexpr Vector3   Vector3::RotateTowards          (const Vector3& p_current, 
                                                     const Vector3& p_target, 
                                                     const float    p_maxRadiansDelta, 
                                                     const float    p_maxDistanceDelta) noexcept
{
    (void)p_current;
    (void)p_target;
    (void)p_maxRadiansDelta;
    (void)p_maxDistanceDelta;

    return Vector3::Zero;
}

/**
 * @brief Scales a 3D vector another one
 * 
 * @param p_a                The vector to scale
 * @param p_b                the scaling vector
 * @return constexpr Vector3 The resulting vector of the scaling
 */
constexpr Vector3   Vector3::Scale				    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return Vector3(p_a.m_x * p_b.m_x, p_a.m_y * p_b.m_y);
}

/**
 * @brief Calculates the signed angle between two 3D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @param p_axis           The vector around which the other vectors are rotated
 * @return constexpr float The resulting signed angle in degrees
 */
constexpr float 	Vector3::SignedAngleDegree	    (const Vector3& p_from, 
                                                     const Vector3& p_to, 
                                                     const Vector3& p_axis)
{
    Vector3 cross(p_from.m_y * p_to.m_z - p_from.m_z * p_to.m_y, 
                  p_from.m_z * p_to.m_x - p_from.m_x * p_to.m_z, 
                  p_from.m_x * p_to.m_y - p_from.m_y * p_to.m_x);

    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y +
                                p_from.m_z * p_from.m_z));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y +
                                p_to  .m_z * p_to  .m_z));

    float dotProduct (p_from.m_x * p_to.m_x + 
                      p_from.m_y * p_to.m_y + 
                      p_from.m_z * p_to.m_z);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    float angle (std::acos(dotProduct / (fromLength * toLength)) * 180.0f / (float)PI);
    
    return (cross == -p_axis) ? angle * -1.0f : angle;
}

/**
 * @brief Calculates the signed angle between two 3D vectors
 * 
 * @param p_from           The left handed vector
 * @param p_to             The right handed vector
 * @param p_axis           The vector around which the other vectors are rotated
 * @return constexpr float The resulting signed angle in radians
 */
constexpr float 	Vector3::SignedAngleRadian	    (const Vector3& p_from, 
                                                     const Vector3& p_to, 
                                                     const Vector3& p_axis)
{
    Vector3 cross(p_from.m_y * p_to.m_z - p_from.m_z * p_to.m_y, 
                  p_from.m_z * p_to.m_x - p_from.m_x * p_to.m_z, 
                  p_from.m_x * p_to.m_y - p_from.m_y * p_to.m_x);

    float fromLength (std::sqrt(p_from.m_x * p_from.m_x + 
                                p_from.m_y * p_from.m_y +
                                p_from.m_z * p_from.m_z));
    float toLength   (std::sqrt(p_to  .m_x * p_to  .m_x + 
                                p_to  .m_y * p_to  .m_y +
                                p_to  .m_z * p_to  .m_z));

    float dotProduct (p_from.m_x * p_to.m_x + 
                      p_from.m_y * p_to.m_y + 
                      p_from.m_z * p_to.m_z);

    if (toLength == 0.0f || fromLength == 0.0f)
        return 0;

    float angle (std::acos(dotProduct / (fromLength * toLength)));

    return (cross == -p_axis) ? angle * -1.0f : angle;
}

/**
 * @brief Computes the signed euler angles between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting sined euler angles vector in degrees
 */
constexpr Vector3   Vector3::SignedEulerAngleDegree (const Vector3& p_a, const Vector3& p_b)
{
    float x (Vector2::SignedAngleDegree(Vector2(p_a.m_y, p_a.m_z), Vector2(p_b.m_y, p_b.m_z)));
    float y (Vector2::SignedAngleDegree(Vector2(p_a.m_x, p_a.m_z), Vector2(p_b.m_x, p_b.m_z)));
    float z (Vector2::SignedAngleDegree(Vector2(p_a.m_x, p_a.m_y), Vector2(p_b.m_x, p_b.m_y)));

    return Vector3(x, y, z);
}

/**
 * @brief Computes the signed euler angles between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting signed euler angles vector in radians
 */
constexpr Vector3   Vector3::SignedEulerAngleRadian (const Vector3& p_a, const Vector3& p_b)
{
    float x (Vector2::SignedAngleDegree(Vector2(p_a.m_y, p_a.m_z), Vector2(p_b.m_y, p_b.m_z)));
    float y (Vector2::SignedAngleDegree(Vector2(p_a.m_x, p_a.m_z), Vector2(p_b.m_x, p_b.m_z)));
    float z (Vector2::SignedAngleDegree(Vector2(p_a.m_x, p_a.m_y), Vector2(p_b.m_x, p_b.m_y)));

    return Vector3(x, y, z);
}

/**
 * @brief Spherically interpolates between two 3D vectors its value clamped
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector3   Vector3::Slerp				    (const Vector3& p_a, const Vector3& p_b, const float p_t) noexcept
{
    float clamp         ((p_t < 0.0f) ? 0.0f : (p_t > 1.0f) ? 1.0f : p_t);
    
    float fromLength    (std::sqrt(p_a.m_x * p_a.m_x + 
                                   p_a.m_y * p_a.m_y + 
                                   p_a.m_z * p_a.m_z));
    float toLength   	(std::sqrt(p_b.m_x * p_b.m_x + 
                                   p_b.m_y * p_b.m_y + 
                                   p_b.m_z * p_b.m_z));

    float dotProduct 	(p_a.m_x * p_b.m_x + 
                         p_a.m_y * p_b.m_y + 
                         p_a.m_z * p_b.m_z);

    float teta 	 		(std::acos(dotProduct / (fromLength * toLength)));

    return std::sin((1.0f - clamp) * teta) / std::sin(teta) * 
                    p_a + std::sin(clamp * teta) / std::sin(teta) * p_b;
}

/**
 * @brief Spherically interpolates between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @param p_t                The lerp value
 * @return constexpr Vector3 The resulting vector of the lerping
 */
constexpr Vector3   Vector3::SlerpUnclamped		    (const Vector3& p_a, const Vector3& p_b, const float p_t) noexcept
{	
    float fromLength 	(std::sqrt(p_a.m_x * p_a.m_x + 
                                   p_a.m_y * p_a.m_y + 
                                   p_a.m_z * p_a.m_z));
    float toLength   	(std::sqrt(p_b.m_x * p_b.m_x + 
                                   p_b.m_y * p_b.m_y + 
                                   p_b.m_z * p_b.m_z));

    float dotProduct    (p_a.m_x * p_b.m_x + 
                         p_a.m_y * p_b.m_y + 
                         p_a.m_z * p_b.m_z);

    float teta 	 		(std::acos(dotProduct / (fromLength * toLength)));

    return std::sin((1.0f - p_t) * teta) / std::sin(teta) * 
                    p_a + std::sin(p_t * teta) / std::sin(teta) * p_b;
}

/*==========================[Constructors + Destructor]==========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Vector3::Vector3  () noexcept
:   m_x {0.0f},
    m_y {0.0f},
    m_z {0.0f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Vector3::Vector3  (const float p_x, 
                             const float p_y, 
                             const float p_z) noexcept
:   m_x {p_x}, 
    m_y {p_y},
    m_z {p_z}
{}

/**
 * @brief Constructor with one value applied to all members
 * 
 */
constexpr Vector3::Vector3  (const float p_value) noexcept
:   m_x {p_value}, 
    m_y {p_value},
    m_z {p_value}
{}

/**
 * @brief Constructor with two points
 * 
 */
constexpr Vector3::Vector3  (const Vector3& p_a, const Vector3& p_b) noexcept
:   m_x {p_b.m_x - p_a.m_x}, 
    m_y {p_b.m_y - p_a.m_y},
    m_z {p_b.m_z - p_a.m_z}
{}

/**
 * @brief Copy constructor with a 2D vector
 * 
 */
constexpr Vector3::Vector3  (const Vector2& p_copy, const float p_z) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y},
    m_z {p_z}
{}

/**
 * @brief Copy constructor with another 3D vector
 * 
 */
constexpr Vector3::Vector3  (const Vector3& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y},
    m_z {p_copy.m_z}
{}

/**
 * @brief Copy constructor with a 4D vector
 * 
 */
constexpr Vector3::Vector3  (const Vector4& p_copy) noexcept
:   m_x {p_copy.m_x}, 
    m_y {p_copy.m_y},
    m_z {p_copy.m_z}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Vector3::Vector3  (Vector3&& p_move) noexcept
:   m_x {std::move(p_move.m_x)},
    m_y {std::move(p_move.m_y)},
    m_z {std::move(p_move.m_z)}
{}

/*===========================[Local Methods (Public)]==========================*/

/**
 * @brief Calculates the length of the current 3D vector
 * 
 * @return constexpr float The resulting length's value
 */
constexpr float   	Vector3::GetMagnitude   () const noexcept
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

/**
 * @brief Computes the normalized vector of the current 3D vector
 * 
 * @return constexpr Vector3 The normalized vector
 */
constexpr Vector3 	Vector3::GetNormalize   () const noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z));

    if (length == 0.0f)
        return Vector3::Zero;

    return Vector3(m_x / length, m_y / length, m_z / length);
}

/**
 * @brief Calculates the squared length of the current 3D vector
 * 
 * @return constexpr float The resulting squared length's value
 */
constexpr float   	Vector3::GetSqrMagnitude() const noexcept
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

/**
 * @brief Normalizes the current 3D vector
 * 
 * @return constexpr Vector3 The normalized vector
 */
constexpr Vector3 	Vector3::Normalize      () noexcept
{
    float length (std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z));

    if (length != 0.0f)
    {
        m_x /= length;
        m_y /= length;
        m_z /= length;
    }

    return *this;
}

/**
 * @brief Sets the components of the current 3D vector to the new values
 * 
 * @param p_x                The x value
 * @param p_y                The y value
 * @param p_z                The z value
 * @return constexpr Vector3 The modified vector
 */
constexpr Vector3   Vector3::Set            (const float p_x, 
                                             const float p_y, 
                                             const float p_z) noexcept
{
    m_x = p_x;
    m_y = p_y;
    m_z = p_z;

    return *this;
}

/**
 * @brief Converts the current 3D vector to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Vector3::ToString       () const noexcept
{
    return std::string("Vector3 (" + std::to_string(m_x) + "," + 
                                     std::to_string(m_y) + "," +
                                     std::to_string(m_z) + ").");
}

/*==============================[Local Operators (Public)]============================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The vector to move
 * @return constexpr Vector3& The moved vector
 */
constexpr Vector3&  Vector3::operator=  (Vector3&& p_move) noexcept
{
    m_x = std::move(p_move.m_x);
    m_y = std::move(p_move.m_y);
    m_z = std::move(p_move.m_z);

    return *this;
}

/**
 * @brief Copy operator with a 2D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector3&  Vector3::operator=  (const Vector2& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = 0.0f;

    return *this;
}

/**
 * @brief Copy operator with another 3D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector3&  Vector3::operator=  (const Vector3& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = p_copy.m_z;

    return *this;
}

/**
 * @brief Copy operator with a 4D vector
 * 
 * @param p_copy              The vector to copy
 * @return constexpr Vector3& The copied vector
 */
constexpr Vector3&  Vector3::operator=  (const Vector4& p_copy) noexcept
{
    m_x = p_copy.m_x;
    m_y = p_copy.m_y;
    m_z = p_copy.m_z;

    return *this;
}

/**
 * @brief Read only accessor
 * 
 * @param p_index          The index value
 * @return constexpr float The value to read
 */
constexpr float     Vector3::operator[] (const int p_index) const
{
    float value (0.0f);

    switch (p_index)
    {
        case 0	: value = m_x;  break;
        case 1	: value = m_y;	break;
        case 2	: value = m_z;	break;
        default : throw std::out_of_range("Value is out of Vector3's index range : [0,2]"); break;
    }

    return value;
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_index           The index value
 * @return constexpr float& The value to read
 */
constexpr float&    Vector3::operator[] (const int p_index)
{
    switch (p_index)
    {
        case 0	: return m_x;	break;
        case 1	: return m_y;	break;
        case 2	: return m_z;	break;
        default : throw std::out_of_range("Value is out of Vector3's index range : [0,2]"); break;
    }
}

/*==============================[General Operators]============================*/

/**
 * @brief Increments the components of the current 3D vector
 * 
 * @param p_a                 The target vector
 * @return constexpr Vector3& The incremented vector
 */
constexpr Vector3&      Maths::operator++	(Vector3& p_a) noexcept
{
    p_a.m_x++;
    p_a.m_y++;
    p_a.m_z++;

    return p_a;
}

/**
 * @brief Decrements the components of the current 3D vector
 * 
 * @param p_a                 The target vector
 * @return constexpr Vector3& The decremented vector
 */
constexpr Vector3&      Maths::operator--   (Vector3& p_a) noexcept
{
    p_a.m_x--;
    p_a.m_y--;
    p_a.m_z--;

    return p_a;
}

/**
 * @brief Checks if two 3D vectors are equal
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are approximately equal
 * @return false The vectors are not equal
 */
constexpr bool          Maths::operator==   (const Vector3& p_a, const Vector3& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));
    double z        ((p_a.m_z - p_b.m_z) * (p_a.m_z - p_b.m_z));

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return !((x > epsilon) || (y > epsilon) || (z > epsilon));
}

/**
 * @brief Checks if two 3D vectors are different
 * 
 * @param p_a    The left handed vector
 * @param p_b    The right handed vector
 * @return true  The vectors are not equal
 * @return false The vectors are approximately equal
 */
constexpr bool          Maths::operator!=   (const Vector3& p_a, const Vector3& p_b) noexcept
{
    double x        ((p_a.m_x - p_b.m_x) * (p_a.m_x - p_b.m_x));
    double y        ((p_a.m_y - p_b.m_y) * (p_a.m_y - p_b.m_y));
    double z        ((p_a.m_z - p_b.m_z) * (p_a.m_z - p_b.m_z));

    double epsilon  (__DBL_EPSILON__ * __DBL_EPSILON__);

    return ((x > epsilon) || (y > epsilon) || (z > epsilon));
}

/**
 * @brief Adds two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the addition
 */
constexpr Vector3       Maths::operator+    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return Vector3(p_a.m_x + p_b.m_x, 
                   p_a.m_y + p_b.m_y,
                   p_a.m_z + p_b.m_z);
}

/**
 * @brief Adds a value to the components of a 3D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to add
 * @return constexpr Vector3 The resulting vector of the addition
 */
constexpr Vector3       Maths::operator+    (const Vector3& p_a, const float p_k) noexcept
{
    return Vector3(p_a.m_x + p_k, 
                   p_a.m_y + p_k,
                   p_a.m_z + p_k);
}

/**
 * @brief Adds a value to the components of a 3D vector
 * 
 * @param p_k                The value to add
 * @param p_a                The target vector
 * @return constexpr Vector3 The resulting vector of the addition
 */
constexpr Vector3 	    Maths::operator+	(const float p_k, const Vector3& p_a) noexcept
{
    return Vector3(p_a.m_x + p_k, 
                   p_a.m_y + p_k,
                   p_a.m_z + p_k);
}

/**
 * @brief Adds a 3D The vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to add
 * @return constexpr Vector3& The resulting vector of the addition
 */
constexpr Vector3&      Maths::operator+=   (Vector3& p_a, const Vector3& p_b) noexcept
{
    p_a.m_x += p_b.m_x;
    p_a.m_y += p_b.m_y;
    p_a.m_z += p_b.m_z;

    return p_a;
}

/**
 * @brief Adds a value to the components of the current 3D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to add
 * @return constexpr Vector3& The resulting vector of the addition
 */
constexpr Vector3&      Maths::operator+=   (Vector3& p_a, const float p_k) noexcept
{
    p_a.m_x += p_k;
    p_a.m_y += p_k;
    p_a.m_z += p_k;

    return p_a;
}

/**
 * @brief Substracts a 3D vector from another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector3& The resulting vector of the substraction
 */
constexpr Vector3       Maths::operator-    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return Vector3(p_a.m_x - p_b.m_x, 
                   p_a.m_y - p_b.m_y,
                   p_a.m_z - p_b.m_z);
}

/**
 * @brief Substracts a value to the components of a 3D vector
 * 
 * @param p_a                The target vector
 * @param p_k                The value to substract
 * @return constexpr Vector3 The resulting vector of the substraction
 */
constexpr Vector3       Maths::operator-	(const Vector3& p_a, const float p_k) noexcept
{
    return Vector3(p_a.m_x - p_k, 
                   p_a.m_y - p_k, 
                   p_a.m_z - p_k);
}

/**
 * @brief Computes the opposite vector of the current 3D vector
 * 
 * @param p_a                The target vector
 * @return constexpr Vector3 The opposite vector
 */
constexpr Vector3       Maths::operator-    (const Vector3& p_a) noexcept
{
    return Vector3(-p_a.m_x, -p_a.m_y, -p_a.m_z);
}

/**
 * @brief Substracts a 3D vector to the current one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to substract
 * @return constexpr Vector3& The resulting vector of the substraction
 */
constexpr Vector3&      Maths::operator-=   (Vector3& p_a, const Vector3& p_b) noexcept
{
    p_a.m_x -= p_b.m_x;
    p_a.m_y -= p_b.m_y;
    p_a.m_z -= p_b.m_z;

    return p_a;
}

/**
 * @brief Substracts a value to the components of the current 3D vector
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to substract
 * @return constexpr Vector3& The resulting vector of the substraction
 */
constexpr Vector3&      Maths::operator-=   (Vector3& p_a, const float p_k) noexcept
{
    p_a.m_x -= p_k;
    p_a.m_y -= p_k;
    p_a.m_z -= p_k;

    return p_a;
}

/**
 * @brief Multiplies a 3D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to multiply
 * @return constexpr Vector3 The resulting vector of the multiplication
 */
constexpr Vector3       Maths::operator*	(const Vector3&	p_a, const Vector3&	p_b) noexcept
{
    return Vector3(p_a.m_x * p_b.m_x, 
                   p_a.m_y * p_b.m_y,
                   p_a.m_z * p_b.m_z);
}

/**
 * @brief Multiplies a 3D vector by a number
 * 
 * @param p_k                The value to multiply
 * @param p_a                The target vector
 * @return constexpr Vector3 The resulting vector of the multiplication
 */
constexpr Vector3       Maths::operator*    (const float p_k, const Vector3& p_a) noexcept
{
    return Vector3(p_a.m_x * p_k, 
                   p_a.m_y * p_k,
                   p_a.m_z * p_k);
}

/**
 * @brief Multiplies a 3D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to multiply
 * @return constexpr Vector3 The resulting vector of the multiplication
 */
constexpr Vector3       Maths::operator*    (const Vector3& p_a, const float p_k) noexcept
{
    return Vector3(p_a.m_x * p_k, 
                   p_a.m_y * p_k,  
                   p_a.m_z * p_k);    
}

/**
 * @brief Multiplies the current 3D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to multiply
 * @return constexpr Vector3& The resulting vector of the multiplication
 */
constexpr Vector3&      Maths::operator*=   (Vector3& p_a, const Vector3& p_b) noexcept
{
    p_a.m_x *= p_b.m_x;
    p_a.m_y *= p_b.m_y;
    p_a.m_z *= p_b.m_y;

    return p_a;
}

/**
 * @brief Multiplies the current 3D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to multiply
 * @return constexpr Vector3& The resulting vector of the multiplication
 */
constexpr Vector3&      Maths::operator*=   (Vector3& p_a, const float p_k) noexcept
{
    p_a.m_x *= p_k;
    p_a.m_y *= p_k;
    p_a.m_z *= p_k;

    return p_a;
}

/**
 * @brief Divides a 3D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to divide
 * @return constexpr Vector3 The resulting vector of the division
 */
constexpr Vector3       Maths::operator/	(const Vector3&	p_a, const Vector3&	p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector3(p_a.m_x / p_b.m_x, 
                   p_a.m_y / p_b.m_y,
                   p_a.m_z / p_b.m_z);
}

/**
 * @brief Divides a 3D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to divide
 * @return constexpr Vector3 The resulting vector of the division
 */
constexpr Vector3       Maths::operator/    (const Vector3& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    return Vector3(p_a.m_x / p_k, 
                   p_a.m_y / p_k,  
                   p_a.m_z / p_k);    
}

/**
 * @brief Divides the current 3D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to divide
 * @return constexpr Vector3& The resulting vector of the division
 */
constexpr Vector3&      Maths::operator/=   (Vector3& p_a, const Vector3& p_b)
{
    if (p_b.m_x == 0.0f || p_b.m_y == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_b.m_x;
    p_a.m_y /= p_b.m_y;
    p_a.m_z /= p_b.m_z;

    return p_a;
}

/**
 * @brief Divides the current 3D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The value to divide
 * @return constexpr Vector3& The resulting vector of the division
 */
constexpr Vector3&      Maths::operator/=   (Vector3& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    p_a.m_x /= p_k;
    p_a.m_y /= p_k;
    p_a.m_z /= p_k;

    return p_a;
}

/**
 * @brief Computes the modulo of a 3D vector by a number
 * 
 * @param p_a                The target vector
 * @param p_k                The value to modulo
 * @return constexpr Vector3 The resulting vector of the modulo operation
 */
constexpr Vector3       Maths::operator%	(const Vector3&	p_a, const float p_k) noexcept
{
    return Vector3(std::fmod(p_a.m_x, p_k), 
                   std::fmod(p_a.m_y, p_k),
                   std::fmod(p_a.m_z, p_k));
}

/**
 * @brief Computes the modulo of a 3D vector by another one
 * 
 * @param p_a                The target vector
 * @param p_b                The vector to modulo
 * @return constexpr Vector3 The resulting vector of the modulo operation
 */
constexpr Vector3       Maths::operator%	(const Vector3&	p_a, const Vector3& p_b) noexcept
{
    return Vector3(std::fmod(p_a.m_x, p_b.m_x), 
                   std::fmod(p_a.m_y, p_b.m_y),
                   std::fmod(p_a.m_z, p_b.m_z));
}

/**
 * @brief Computes the modulo of the current 3D vector by another one
 * 
 * @param p_a                 The target vector
 * @param p_b                 The vector to modulo
 * @return constexpr Vector3& The resulting vector of the modulo operation
 */
constexpr Vector3&      Maths::operator%=   (Vector3& p_a, const Vector3& p_b) noexcept
{
    p_a.m_x = std::fmod(p_a.m_x, p_b.m_x);
    p_a.m_y = std::fmod(p_a.m_y, p_b.m_y);
    p_a.m_z = std::fmod(p_a.m_z, p_b.m_z);

    return p_a;
}

/**
 * @brief Computes the modulo of the current 3D vector by a number
 * 
 * @param p_a                 The target vector
 * @param p_k                 The vector to modulo
 * @return constexpr Vector3& The resulting vector of the modulo operation
 */
constexpr Vector3&	    Maths::operator%=	(Vector3& p_a, const float p_k) noexcept
{
    p_a.m_x = std::fmod(p_a.m_x, p_k);
    p_a.m_y = std::fmod(p_a.m_y, p_k);
    p_a.m_z = std::fmod(p_a.m_z, p_k);

    return p_a;
}

/**
 * @brief Computes the cross product between two 3D vectors
 * 
 * @param p_a                The left handed vector
 * @param p_b                The right handed vector
 * @return constexpr Vector3 The resulting vector of the cross product
 */
constexpr Vector3       Maths::operator^    (const Vector3& p_a, const Vector3& p_b) noexcept
{
    return Vector3(p_a.m_y * p_b.m_z - p_a.m_z * p_b.m_y, 
                   p_a.m_z * p_b.m_x - p_a.m_x * p_b.m_z, 
                   p_a.m_x * p_b.m_y - p_a.m_y * p_b.m_x);
}

/**
 * @brief Converts a 3D vector to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target vector
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Vector3& p_a) noexcept
{
    return p_flux << "Vector3(" << p_a.m_x << ", " 
                                << p_a.m_y << ", " 
                                << p_a.m_z << ").";
}  

#endif // !__VECTOR_3_INL__ 