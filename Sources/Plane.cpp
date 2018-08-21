/**
 * @file    Plane.cpp
 * @brief   Source file for Plane
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GPlane
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Matrix4x4.hpp"
#include "../Includes/Line.hpp"
#include "../Includes/Plane.hpp"

using namespace Maths;

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Checks if there is intersection between two planes
 * 
 * @param p_plane1 The left handed plane
 * @param p_plane2 The right handed plane
 * @return true    There is an intersection between the planes
 * @return false   There is no intersection between the planes
 */
bool		Plane::Crossing2Plane		(const Plane& p_plane1, const Plane& p_plane2) noexcept
{
    return !Vector3::IsColinear(p_plane1.m_normal, p_plane2.m_normal); 
}

/**
 * @brief Checks if there is intersection between three planes
 * 
 * @param p_plane1 The left handed plane
 * @param p_plane2 The middlle handed plane
 * @param p_plane3 The right handed plane
 * @return true    There is an intersection between the planes
 * @return false   There is no intersection between the planes
 */
bool		Plane::Crossing3Plane		(const Plane& p_plane1, const Plane& p_plane2, const Plane& p_plane3) noexcept
{
    Matrix4x4 matrix(
        p_plane1.m_normal.m_x, p_plane1.m_normal.m_x, p_plane1.m_normal.m_x, 0.0f,
        p_plane2.m_normal.m_y, p_plane2.m_normal.m_y, p_plane2.m_normal.m_y, 0.0f,
        p_plane3.m_normal.m_z, p_plane3.m_normal.m_z, p_plane3.m_normal.m_z, 0.0f,
        0.0f                 , 0.0f                 , 0.0f                 , 1.0f
    );

    return (matrix.GetDeterminant() != 0.0f);
}

/**
 * @brief Computes the intersection of two planes
 * 
 * @param p_plane1 The left handed plane
 * @param p_plane2 The right handed plane
 * @return Line    The resulting line of the intersection
 */
Line		Plane::GetLineWith2Plane	(const Plane& p_plane1, const Plane& p_plane2) noexcept
{
    if (!Vector3::IsColinear(Vector3::Forward, p_plane1.m_normal) && !Vector3::IsColinear(Vector3::Forward, p_plane2.m_normal))
    {
        Vector3 pt1(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Forward, 0.0f)));
        Vector3 pt2(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Forward, 1.0f)));

        return   Line(pt1, (pt2 - pt1).GetNormalize());
    }

    if (!Vector3::IsColinear(Vector3::Up, p_plane1.m_normal) && !Vector3::IsColinear(Vector3::Up, p_plane2.m_normal))
    {
        Vector3 pt1(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Up, 0.0f)));
        Vector3 pt2(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Up, 1.0f)));

        return  Line(pt1, (pt2 - pt1).GetNormalize());
    }

    Vector3 pt1(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Right, 0.0f)));
    Vector3 pt2(GetPointWith3Plane(p_plane1, p_plane2, Plane(Vector3::Right, 1.0f)));

    return	Line(pt1, (pt2 - pt1).GetNormalize());
}

/**
 * @brief Computes the intersection of three planes
 * 
 * @param p_plane1 The left handed plane
 * @param p_plane2 The middle handed plane
 * @param p_plane3 The right handed plane
 * @return Vector3 The resulting point of the intersection
 */
Vector3		Plane::GetPointWith3Plane	(const Plane& p_plane1, const Plane& p_plane2, const Plane& p_plane3) noexcept
{
    Matrix4x4 matrix(
        p_plane1.m_normal.m_x, p_plane1.m_normal.m_x, p_plane1.m_normal.m_x, 0.0f,
        p_plane2.m_normal.m_y, p_plane2.m_normal.m_y, p_plane2.m_normal.m_y, 0.0f,
        p_plane3.m_normal.m_z, p_plane3.m_normal.m_z, p_plane3.m_normal.m_z, 0.0f,
        0.0f                 , 0.0f                 , 0.0f                 , 1.0f
    );

    if (matrix.GetDeterminant() == 0.0f)
        return Vector3::Zero;
    
    return matrix.GetInverse() * Vector3(-p_plane1.m_distance, -p_plane2.m_distance, -p_plane3.m_distance);
}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Computes the closest point on the current plane to a point
 * 
 * @param p_pt     The target point
 * @return Vector3 The closest point on plane
 */
[[deprecated("This method is not implemented yet!")]]
Vector3     Plane::ClosestPointOnPlane      (const Vector3& p_pt) const noexcept
{
    (void)p_pt;

    return Vector3::Zero;
}

/**
 * @brief Calculates the smallest distance between a point and the current plane
 * 
 * @param p_pt   The target point
 * @return float The resulting distance's value
 */
float       Plane::DistanceToPoint          (const Vector3& p_pt) const noexcept
{
    float cartesian (m_normal.m_x * p_pt.m_x + 
                     m_normal.m_y * p_pt.m_y + 
                     m_normal.m_z * p_pt.m_z + m_distance);

    return cartesian / m_normal.GetMagnitude();
}

/**
 * @brief Checks which side of the plane the point is
 * 
 * @param p_pt   The target point
 * @return float The resulting value corresponding to the side
 */
float       Plane::GetSide			        (const Vector3& p_pt) const noexcept   
{   
    // Value > 0 : the point is above the plane 
    // Value = 0 : the point is included in the plane 
   	// Value < 0 : the point is below the plane
    return m_normal.m_x * p_pt.m_x + m_normal.m_y * p_pt.m_y + m_normal.m_z * p_pt.m_z + m_distance;
}

/**
 * @brief Flips the plane (the normal is inverted)
 * 
 * @return Plane The flipped plane
 */
Plane       Plane::Flip                     () noexcept
{
    m_normal *= -1.0f;

    return *this;
}

/**
 * @brief Checks if two points are in the same side of a plane
 * 
 * @param p_pt1 
 * @param p_pt2 
 * @return true 
 * @return false 
 */
bool        Plane::SameSide			        (const Vector3& p_pt1, const Vector3& p_pt2) const noexcept
{
    float side_pt1 (GetSide(p_pt1));
    float side_pt2 (GetSide(p_pt2));

    return (side_pt1 > 0.0f && side_pt2 > 0.0f) || (side_pt1 < 0.0f && side_pt2 < 0.0f) || (side_pt1 == 0.0f && side_pt2 == 0.0f);
}

/**
 * @brief Calculates the smallest signed distance between a point and the current plane
 * 
 * @param p_pt   The target point
 * @return float The resulting signed distance's value
 */
[[deprecated("This method is not implemented yet!")]]
float       Plane::SignedDistanceToPoint    (const Vector3& p_pt) const noexcept
{
    (void)p_pt;

    return 0.0f;
}

/**
 * @brief Translates the current plane
 * 
 * @param p_translation The value to translate
 */
void        Plane::Translate                (const float p_translation) noexcept
{
    m_distance += p_translation;
}