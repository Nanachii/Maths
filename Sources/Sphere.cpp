/**
 * @file    Sphere.cpp
 * @brief   Source file for Sphere
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GSphere
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Segment.hpp"
#include "../Includes/OBB.hpp"
#include "../Includes/AABB.hpp"
#include "../Includes/Cylinder.hpp"
#include "../Includes/InfiniteCylinder.hpp"
#include "../Includes/Capsule.hpp"
#include "../Includes/Intersection.hpp"

#include "../Includes/Sphere.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Creates an AABB for the current sphere
 * 
 * @return AABB The new AABB
 */
AABB    Sphere::GetAABB                 () const noexcept
{
    return AABB(m_origin, m_radius * 2.0f);
}

/**
 * @brief Checks if there is collisison with another sphere
 * 
 * @param p_other The target sphere
 * @return true   There is collision with the other sphere
 * @return false  There is no collision with the other sphere
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const Sphere& p_other) const noexcept
{
    (void)p_other;

    return false;
}

/**
 * @brief Checks if there is collision with an oriented box
 * 
 * @param p_obb  The target box
 * @return true  There is collision with the box
 * @return false There is no collision with the box
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const OBB& p_obb) const noexcept
{
    (void)p_obb;

    return false;
}

/**
 * @brief Checks if there is collision with an AABB
 * 
 * @param p_aabb The target AABB
 * @return true  There is collision with the AABB
 * @return false There is no collision with the AABB
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const AABB& p_aabb) const noexcept
{
    (void)p_aabb;

    return false;
}

/**
 * @brief Checks if there is collision with a cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with the cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const Cylinder& p_cylinder) const noexcept
{
    (void)p_cylinder;

    return false;
}

/**
 * @brief Checks if there is collision with an infinite cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with the cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const InfiniteCylinder& p_cylinder) const noexcept
{
    (void)p_cylinder;

    return false;
}

/**
 * @brief Checks if there is collision with a capsule
 * 
 * @param p_capsule The target capsule
 * @return true     There is collision with the capsule
 * @return false    There is no collision with the capsule
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsColliding             (const Capsule& p_capsule) const noexcept
{
    (void)p_capsule;

    return false;
}

/**
 * @brief Checks if there is collision with a sphere while the current one is moving
 * 
 * @param p_other The target sphere
 * @param p_speed The movement vector
 * @param p_hit   The intersection of the collision
 * @return true   There is collision with the other sphere
 * @return false  There is no collision with the other sphere
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsMovingSphereColliding (const Sphere&  p_other, 
                                         const Vector3& p_speed,
                                         Intersection&  p_hit) const noexcept
{
    (void)p_other;
    (void)p_speed;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an oriented box while the current sphere is moving
 * 
 * @param p_obb   The target box
 * @param p_speed The movement vector
 * @param p_hit   The intersection of the collision
 * @return true   There is collision with the other box
 * @return false  There is no collision with the other box
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsMovingSphereColliding (const OBB&     p_obb, 
                                         const Vector3& p_speed,
                                         Intersection&  p_hit) const noexcept
{
    (void)p_obb;
    (void)p_speed;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an AABB while the current sphere is moving
 * 
 * @param p_aabb  The target AABB
 * @param p_speed The movement vector
 * @param p_hit   The intersection of the collision
 * @return true   There is collision with the other AABB
 * @return false  There is no collision with the other AABB
 */
bool    Sphere::IsMovingSphereColliding (const AABB&    p_aabb, 
                                         const Vector3& p_speed,
                                         Intersection&  p_hit) const noexcept
{
    AABB    expandedAABB(p_aabb);
    Segment movement    (m_origin, m_origin + p_speed);

    expandedAABB.Expand(m_radius);

    // Checks if there is intersection with the expanded box
    if (!movement.IsIntersecting(expandedAABB, p_hit))
        return false;

    // Computes the area where the intersection is
    int u (0), v (0);

    Vector3 min(p_aabb.GetMin());
    Vector3 max(p_aabb.GetMax());

    if (p_hit.m_impact.m_x < min.m_x) u |= 1;
    if (p_hit.m_impact.m_x > max.m_x) v |= 1;

    if (p_hit.m_impact.m_y < min.m_y) u |= 2;
    if (p_hit.m_impact.m_y > max.m_y) v |= 2;

    if (p_hit.m_impact.m_z < min.m_z) u |= 4;
    if (p_hit.m_impact.m_z > max.m_z) v |= 4;

    int m = u + v;

    // Intersection with a vertex region
    if (m == 7)
    {
        Intersection tmpHit;

        p_hit.m_impact.Set(__FLT_MAX__, __FLT_MAX__, __FLT_MAX__);

        if (movement.IsIntersecting(Capsule(p_aabb.Corner(v), p_aabb.Corner(v ^ 1), m_radius), tmpHit))
        {
            if (Maths::Vector3::DistanceSqr(m_origin, tmpHit.m_impact) < Maths::Vector3::DistanceSqr(m_origin, p_hit.m_impact))
                p_hit = tmpHit;
        }

        if (movement.IsIntersecting(Capsule(p_aabb.Corner(v), p_aabb.Corner(v ^ 2), m_radius), tmpHit))
        {
            if (Maths::Vector3::DistanceSqr(m_origin, tmpHit.m_impact) < Maths::Vector3::DistanceSqr(m_origin, p_hit.m_impact))
                p_hit = tmpHit;
        }

        if (movement.IsIntersecting(Capsule(p_aabb.Corner(v), p_aabb.Corner(v ^ 4), m_radius), tmpHit))
        {
            if (Maths::Vector3::DistanceSqr(m_origin, tmpHit.m_impact) < Maths::Vector3::DistanceSqr(m_origin, p_hit.m_impact))
                p_hit = tmpHit;
        }

        // No intersection was found
        if (p_hit.m_impact == Maths::Vector3(__FLT_MAX__, __FLT_MAX__, __FLT_MAX__))
        {
            p_hit.Reset();

            return false;
        }
        return true;
    }

    // Intersection with a face of the cube
    if ((m & (m - 1)) == 0)
    {
        p_hit.m_impact = p_aabb.ClosestPoint(p_hit.m_impact);
        // p_hit.m_normal = p_aabb.Normal      (p_hit.m_impact);

        return true;
    }

    // Intersection with an edge area
    return movement.IsIntersecting(Capsule(p_aabb.Corner(u ^ 7), p_aabb.Corner(v), m_radius), p_hit);
}

/**
 * @brief Checks if there is collision with a cylinder while the current sphere is moving
 * 
 * @param p_cylinder The target cylinder
 * @param p_speed    The movement vector
 * @param p_hit      The intersection of the collision
 * @return true      There is collision with the other cylinder
 * @return false     There is no collision with the other cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsMovingSphereColliding (const Cylinder& p_cylinder, 
                                         const Vector3&  p_speed,
                                         Intersection&   p_hit) const noexcept
{
    (void)p_cylinder;
    (void)p_speed;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an infinite cylinder while the current sphere is moving
 * 
 * @param p_cylinder The target cylinder
 * @param p_speed    The movement vector
 * @param p_hit      The intersection of the collision
 * @return true      There is collision with the other cylinder
 * @return false     There is no collision with the other cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsMovingSphereColliding (const InfiniteCylinder& p_cylinder, 
                                         const Vector3&          p_speed,
                                         Intersection&           p_hit) const noexcept
{
    (void)p_cylinder;
    (void)p_speed;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with a capsule while the current sphere is moving
 * 
 * @param p_capsule The target capsule
 * @param p_speed   The movement vector
 * @param p_hit     The intersection of the collision
 * @return true     There is collision with the other capsule
 * @return false    There is no collision with the other capsule
 */
[[deprecated("This method is not implemented yet!")]]
bool    Sphere::IsMovingSphereColliding (const Capsule& p_capsule, 
                                         const Vector3& p_speed,
                                         Intersection&  p_hit) const noexcept
{
    (void)p_capsule;
    (void)p_speed;
    (void)p_hit;

    return false;
}