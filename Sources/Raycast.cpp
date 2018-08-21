/**
 * @file    Raycast.cpp
 * @brief   Source file for Raycast
 * @author  Philippe Yi
 * 
 * @ingroup GRaycast
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Line.hpp"
#include "../Includes/Plane.hpp"
#include "../Includes/Quad.hpp"
#include "../Includes/OBB.hpp"
#include "../Includes/AABB.hpp"
#include "../Includes/Sphere.hpp"
#include "../Includes/Cylinder.hpp"
#include "../Includes/InfiniteCylinder.hpp"
#include "../Includes/Capsule.hpp"
#include "../Includes/Intersection.hpp"

#include "../Includes/Raycast.hpp"

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
bool    Raycast::IsIntersecting    (const Plane& p_plane, Intersection& p_hit) const noexcept
{
    Vector3 ray (m_direction * m_maxDistance);
    float   dot (Vector3::Dot(ray, p_plane.m_normal));

    if (dot == 0.0f)
        return false;
    
    float t (p_plane.m_distance - Vector3::Dot(m_origin, p_plane.m_normal) / dot);

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_origin + ray * t;
        
        if (dot > 0.0f)
            p_hit.m_normal = -p_plane.m_normal;
        else
            p_hit.m_normal = p_plane.m_normal;

        return true;
    }

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
bool    Raycast::IsIntersecting    (const Quad& p_quad, Intersection& p_hit) const noexcept
{
    if (IsIntersecting(Plane(p_quad.GetUp(), p_quad.m_origin), p_hit) && p_quad.IsPointInclude(p_hit.m_impact))
        return true;

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
bool    Raycast::IsIntersecting    (const OBB& p_obb, Intersection& p_hit) const noexcept
{
    Matrix4x4   rotation (Matrix4x4::Rotate(Quaternion::Euler(p_obb.m_angle)));
    Raycast     localRay      (rotation * m_origin,rotation * m_direction, m_maxDistance);

    if (localRay.IsIntersecting(AABB(p_obb.m_origin, p_obb.m_extents * 2.0f), p_hit))
    {
        Matrix4x4 invertedRotation (Matrix4x4::Rotate(Quaternion::Euler(-p_obb.m_angle)));

        p_hit.m_impact = invertedRotation * p_hit.m_impact;
        p_hit.m_normal = invertedRotation * p_hit.m_normal;

        return true;
    }

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
bool    Raycast::IsIntersecting    (const AABB& p_aabb, Intersection& p_hit) const noexcept
{
    Vector3 target (m_origin + m_direction * m_maxDistance);
    float   tmin   (0.0f);
    float   tmax   (1.0f);

    for (int i = 0; i < 3; ++i)
    {
        float t1 ((p_aabb.GetMin()[i] - m_origin[i]) / (target[i] - m_origin[i]));
        float t2 ((p_aabb.GetMax()[i] - m_origin[i]) / (target[i] - m_origin[i]));

        if (target[i] - m_origin[i] != 0.0f)
        {
            if (t2 < t1)
                std::swap(t2, t1);

            if (t2 < tmin || t1 > tmax)
                return false;

            tmin  = Max(tmin,  t1);
            tmax = Min(tmax, t2);

            if (tmin > tmax)
                return false;
        }
    }

    if (tmin == 0.0f)
        return false;

    p_hit.m_impact = m_origin + m_direction * tmin;
    p_hit.m_normal = p_aabb.Normal(p_hit.m_impact);

    return true;
}

/**
 * @brief Checks if there is collision with a sphere
 * 
 * @param p_sphere The target sphere
 * @param p_hit    The intersection of the collision
 * @return true    There is collision with the sphere
 * @return false   There is no collision with the sphere
 */
bool    Raycast::IsIntersecting    (const Sphere& p_sphere, Intersection& p_hit) const noexcept
{
    Vector3 ray          (m_direction * m_maxDistance);
    Vector3 sphereVector (p_sphere.m_origin - m_origin);

    // Computes equation's variables
    float a     (ray.GetSqrMagnitude());
    float b     (2.0f * Vector3::Dot(sphereVector, ray));
    float c     (sphereVector.GetSqrMagnitude() - p_sphere.m_radius * p_sphere.m_radius);
    float delta (b * b - 4.0f * a * c);

    if (delta < 0.0f)
        return false;
    
    float t ((-b - std::sqrt(delta)) / (2.0f * a));

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_origin + ray * t;
        p_hit.m_normal = (p_hit.m_impact - p_sphere.m_origin).GetNormalize();

        return true;
    }
    
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
bool    Raycast::IsIntersecting    (const Cylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    Vector3 ray    (m_direction * m_maxDistance);
    Vector3 target (m_origin + ray);
    Vector3 pointP (p_cylinder.m_origin + p_cylinder.m_direction * p_cylinder.m_height / 2.0f);
    Vector3 pointQ (p_cylinder.m_origin - p_cylinder.m_direction * p_cylinder.m_height / 2.0f);
    Plane   planeP ( p_cylinder.m_direction, pointP);
    Plane   planeQ (-p_cylinder.m_direction, pointQ);

    // The second point is outside of the cylinder
    if (planeP.GetSide(target) >= 0.0f || planeQ.GetSide(target) >= 0.0f)
        return false;

    // Outside of the 'p' side
    if (planeP.GetSide(m_origin) >= 0.0f)
    {
        if (IsIntersecting(planeP, p_hit))
        {
            if (Vector3::DistanceSqr(p_hit.m_impact, pointP) <= p_cylinder.m_radius * p_cylinder.m_radius)
                return true;
        }

        else
            return false;
    }

    // Outsde of the 'q' side
    if (planeQ.GetSide(m_origin) >= 0.0f)
    {
        if (IsIntersecting(planeQ, p_hit))
        {
            if (Vector3::DistanceSqr(p_hit.m_impact, pointQ) <= p_cylinder.m_radius * p_cylinder.m_radius)
                return true;
        }

        else
            return false;
    }

    // Insides of the planes
    if (IsIntersecting(InfiniteCylinder(p_cylinder.m_origin, 
                                        p_cylinder.m_direction, 
                                        p_cylinder.m_radius), p_hit))
        return true;


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
bool    Raycast::IsIntersecting    (const InfiniteCylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    Vector3 ray               (m_direction * m_maxDistance);
    Vector3 cylinderToSegment (m_origin - p_cylinder.m_origin);
    Vector3 direction         (p_cylinder.m_direction);

    float   dot1              (Vector3::Dot(ray, direction));
    float   dot2              (Vector3::Dot(cylinderToSegment, direction));

    // Computes equation's variables
    float a     (ray.GetSqrMagnitude() - dot1 * dot1);
    float b     (2.0f * Vector3::Dot(cylinderToSegment, ray) - 2.0f * dot1 * dot2);
    float c     (cylinderToSegment.GetSqrMagnitude() - dot2 * dot2 - p_cylinder.m_radius * p_cylinder.m_radius);
    float delta (b * b - 4.0f * a * c);

    if (delta < 0.0f)
        return false;

    float t ((-b - std::sqrt(delta)) / (2.0f * a));

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_origin + ray * t;
        p_hit.m_normal = (p_hit.m_impact - Line(p_cylinder.m_origin, p_cylinder.m_direction).ClosestPointOnLine(p_hit.m_impact)).GetNormalize();

        return true;
    }
    
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
bool    Raycast::IsIntersecting    (const Capsule& p_capsule, Intersection& p_hit) const noexcept
{
    Vector3 ray    (m_direction * m_maxDistance);
    Vector3 pointP (p_capsule.m_origin + p_capsule.m_direction * p_capsule.m_height / 2.0f);
    Vector3 pointQ (p_capsule.m_origin - p_capsule.m_direction * p_capsule.m_height / 2.0f);
    Plane   planeP ( p_capsule.m_direction, pointP);
    Plane   planeQ (-p_capsule.m_direction, pointQ);

    // Outside of 'p' side
    if (planeP.GetSide(m_origin) >= 0.0f)
    {
        if (IsIntersecting(Sphere(pointP, p_capsule.m_radius), p_hit))
            return true;

        if (IsIntersecting(Cylinder(p_capsule.m_origin, 
                                    p_capsule.m_direction, 
                                    p_capsule.m_height, 
                                    p_capsule.m_radius), p_hit))
            return true;
        
        if (IsIntersecting(Sphere(pointQ, p_capsule.m_radius), p_hit))
            return true;

        return false;
    }

    // Outside of 'q' side
    if (planeQ.GetSide(m_origin) >= 0.0f)
    {
        if (IsIntersecting(Sphere(pointQ, p_capsule.m_radius), p_hit))
            return true;

        if (IsIntersecting(Cylinder(p_capsule.m_origin, 
                                    p_capsule.m_direction, 
                                    p_capsule.m_height, 
                                    p_capsule.m_radius), p_hit))
            return true;

        if (IsIntersecting(Sphere(pointP, p_capsule.m_radius), p_hit))
            return true;

        return false;
    }

    // Inside of the planes 
    if (IsIntersecting(Cylinder(p_capsule.m_origin, 
                                p_capsule.m_direction, 
                                p_capsule.m_height, 
                                p_capsule.m_radius), p_hit))
        return true;
        
    if (IsIntersecting(Sphere(pointP, p_capsule.m_radius), p_hit))
        return true;

    if (IsIntersecting(Sphere(pointQ, p_capsule.m_radius), p_hit))
        return true;

    return false;
}