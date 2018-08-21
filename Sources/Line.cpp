/**
 * @file    Line.cpp
 * @brief   Source file for Line
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GLine
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Plane.hpp"
#include "../Includes/Quad.hpp"
#include "../Includes/OBB.hpp"
#include "../Includes/AABB.hpp"
#include "../Includes/Sphere.hpp"
#include "../Includes/Cylinder.hpp"
#include "../Includes/InfiniteCylinder.hpp"
#include "../Includes/Capsule.hpp"
#include "../Includes/Intersection.hpp"

#include "../Includes/Line.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Checks if there is collision with a plane
 * 
 * @param p_plane The target plane
 * @param p_hit   The intersection of the collision
 * @return true   There is collision with the plane
 * @return false  There is no collision with the plane
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const Plane& p_plane, Intersection& p_hit) const noexcept
{
    (void)p_plane;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with a quad
 * 
 * @param p_quad The target quad
 * @param p_hit  The intersection of the collision
 * @return true  There is collision with the quad
 * @return false There is no collision with the quad
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const Quad& p_quad, Intersection& p_hit) const noexcept
{
    (void)p_quad;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an oriented box
 * 
 * @param p_obb  The target box
 * @param p_hit  The intersection of the collision
 * @return true  There is collision with the box
 * @return false There is no collision with the box
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const OBB& p_obb, Intersection& p_hit) const noexcept
{
    (void)p_obb;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an AABB
 * 
 * @param p_aabb The target AABB
 * @param p_hit  The intersection of the collision
 * @return true  There is collision with the AABB
 * @return false There is no collision with the AABB
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const AABB& p_aabb, Intersection& p_hit) const noexcept
{
    (void)p_aabb;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with a sphere
 * 
 * @param p_sphere The target sphere
 * @param p_hit    The intersection of the collision
 * @return true    There is collision with the sphere
 * @return false   There is no collision with the sphere
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const Sphere& p_sphere, Intersection& p_hit) const noexcept
{
    (void)p_sphere;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with a cylinder
 * 
 * @param p_cylinder The target cylinder
 * @param p_hit      The intersection of the collision
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with the cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const Cylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    (void)p_cylinder;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with an infinite cylinder
 * 
 * @param p_cylinder The target cylinder
 * @param p_hit      The intersection of the collision
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with the cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const InfiniteCylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    (void)p_cylinder;
    (void)p_hit;

    return false;
}

/**
 * @brief Checks if there is collision with a capsule
 * 
 * @param p_capsule The target capsule
 * @param p_hit     The intersection of the collision
 * @return true     There is collision with the capsule
 * @return false    There is no collision with the capsule
 */
[[deprecated("This method is not implemented yet!")]]
bool    Line::IsIntersecting    (const Capsule& p_capsule, Intersection& p_hit) const noexcept
{
    (void)p_capsule;
    (void)p_hit;

    return false;
}