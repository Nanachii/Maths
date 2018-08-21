/**
 * @file    Segment.cpp
 * @brief   Source file for Segment
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GSegment
 * 
 */

#include <algorithm>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Matrix4x4.hpp"

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

#include "../Includes/Segment.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Calculates the smallest distance between a point and the current segment
 * 
 * @param p_point The target point
 * @return float  The resulting distance's value
 */
float       Segment::DistancePoint	    (const Vector3& p_point) const noexcept
{
    Vector3 segmentVector   (m_ptB - m_ptA);
    float   t               (Clamp01(Vector3::Dot(Vector3(m_ptA, p_point), segmentVector) / segmentVector.GetSqrMagnitude()));
    Vector3 projection      (m_ptA + segmentVector * t);

    return Vector3(projection, p_point).GetMagnitude();
}

/**
 * @brief Calculates the smallest squared distance between a point and the current segment
 * 
 * @param p_point The target point
 * @return float  The resulting squared distance's value
 */
float       Segment::DistancePointSqr   (const Vector3& p_point) const noexcept
{
    Vector3 segmentVector   (m_ptB - m_ptA);
    float   t               (Clamp01(Vector3::Dot(Vector3(m_ptA, p_point), segmentVector) / segmentVector.GetSqrMagnitude()));
    Vector3 projection      (m_ptA + segmentVector * t);

    return Vector3(projection, p_point).GetSqrMagnitude();
}

/**
 * @brief Computes the current segment's positive vector
 * 
 * @return Vector3 The new vector
 */
Vector3     Segment::GetAB              () const noexcept
{
    return Vector3(m_ptB - m_ptA);
}

/**
 * @brief Computes the current segment's negative vector
 * 
 * @return Vector3 The new vector
 */
Vector3     Segment::GetBA              () const noexcept
{
    return Vector3(m_ptA - m_ptB);
}

/**
 * @brief Computes a line with the current segment
 * 
 * @return Line The new line
 */
Line        Segment::GetLine            () const noexcept
{
    return Line(m_ptA, (m_ptB - m_ptA).Normalize());
}

/**
 * @brief Checks if there is collision with a plane
 * 
 * @param p_plane The target plane
 * @param p_hit   The intersection of the collision
 * @return true   There is collision with the plane
 * @return false  There is no collision with the plane
 */
bool        Segment::IsIntersecting     (const Plane& p_plane, Intersection& p_hit) const noexcept
{
    Vector3 segmentVector   (m_ptB - m_ptA);
    float   dot             (Vector3::Dot(segmentVector, p_plane.m_normal));

    if (dot == 0.0f)
        return false;
    
    float t (p_plane.m_distance - Vector3::Dot(m_ptA, p_plane.m_normal) / dot);

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_ptA + segmentVector * t;
        
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
bool        Segment::IsIntersecting     (const Quad& p_quad, Intersection& p_hit) const noexcept
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
bool        Segment::IsIntersecting     (const OBB& p_obb, Intersection& p_hit) const noexcept
{
    Matrix4x4   rotation        (Matrix4x4::Rotate(Quaternion::Euler(p_obb.m_angle)));
    Segment     localSegment    (rotation * m_ptA,rotation * m_ptB);

    if (localSegment.IsIntersecting(AABB(p_obb.m_origin, p_obb.m_extents * 2.0f), p_hit))
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
bool        Segment::IsIntersecting     (const AABB& p_aabb, Intersection& p_hit) const noexcept
{
    float tmin (0.0f);
    float tmax (1.0f);

    for (int i = 0; i < 3; ++i)
    {
        float t1 ((p_aabb.GetMin()[i] - m_ptA[i]) / (m_ptB[i] - m_ptA[i]));
        float t2 ((p_aabb.GetMax()[i] - m_ptA[i]) / (m_ptB[i] - m_ptA[i]));

        if (m_ptB[i] - m_ptA[i] != 0.0f)
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

    p_hit.m_impact = m_ptA + GetAB() * tmin;
    p_hit.m_normal = p_aabb.Normal(p_hit.m_impact);

    return true;
}

/**
 * @brief Checks if there is collision with a sphere
 * 
 * @param p_sphere The target sphere
 * @param p_hit    The interection of the collision
 * @return true    There is collision with the sphere
 * @return false   There is no collision with the sphere
 */
bool        Segment::IsIntersecting     (const Sphere& p_sphere, Intersection& p_hit) const noexcept
{
    Vector3 segmentVector (m_ptB - m_ptA);
    Vector3 sphereVector  (p_sphere.m_origin - m_ptA);

    // Computes equation's variables
    float a     (segmentVector.GetSqrMagnitude());
    float b     (2.0f * Vector3::Dot(sphereVector, segmentVector));
    float c     (sphereVector.GetSqrMagnitude() - p_sphere.m_radius * p_sphere.m_radius);
    float delta (b * b - 4.0f * a * c);

    if (delta < 0.0f)
        return false;
    
    float t ((-b - std::sqrt(delta)) / (2.0f * a));

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_ptA + segmentVector * t;
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
bool        Segment::IsIntersecting     (const Cylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    Vector3 segmentVector   (m_ptB - m_ptA);
    Vector3 pointP          (p_cylinder.m_origin + p_cylinder.m_direction * p_cylinder.m_height / 2.0f);
    Vector3 pointQ          (p_cylinder.m_origin - p_cylinder.m_direction * p_cylinder.m_height / 2.0f);
    Plane   planeP          ( p_cylinder.m_direction, pointP);
    Plane   planeQ          (-p_cylinder.m_direction, pointQ);

    // The second point is outside of the cylinder
    if (planeP.GetSide(m_ptB) >= 0.0f || planeQ.GetSide(m_ptB) >= 0.0f)
        return false;

    // Outside of the 'p' side
    if (planeP.GetSide(m_ptA) >= 0.0f)
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
    if (planeQ.GetSide(m_ptA) >= 0.0f)
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
bool        Segment::IsIntersecting     (const InfiniteCylinder& p_cylinder, Intersection& p_hit) const noexcept
{
    Vector3 segmentVector       (m_ptB - m_ptA);
    Vector3 cylinderToSegment   (m_ptA - p_cylinder.m_origin);
    Vector3 direction           (p_cylinder.m_direction);

    float   dot1                (Vector3::Dot(segmentVector, direction));
    float   dot2                (Vector3::Dot(cylinderToSegment, direction));

    // Computes equation's variables
    float a     (segmentVector.GetSqrMagnitude() - dot1 * dot1);
    float b     (2.0f * Vector3::Dot(cylinderToSegment, segmentVector) - 2.0f * dot1 * dot2);
    float c     (cylinderToSegment.GetSqrMagnitude() - dot2 * dot2 - p_cylinder.m_radius * p_cylinder.m_radius);
    float delta (b * b - 4.0f * a * c);

    if (delta < 0.0f)
        return false;

    float t ((-b - std::sqrt(delta)) / (2.0f * a));

    if (t >= 0.0f && t <= 1.0f)
    {
        p_hit.m_impact = m_ptA + segmentVector * t;
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
bool        Segment::IsIntersecting     (const Capsule& p_capsule, Intersection& p_hit) const noexcept
{
    Vector3 segmentVector   (m_ptB - m_ptA);
    Vector3 pointP          (p_capsule.m_origin + p_capsule.m_direction * p_capsule.m_height / 2.0f);
    Vector3 pointQ          (p_capsule.m_origin - p_capsule.m_direction * p_capsule.m_height / 2.0f);
    Plane   planeP          ( p_capsule.m_direction, pointP);
    Plane   planeQ          (-p_capsule.m_direction, pointQ);

    // Outside of 'p' side
    if (planeP.GetSide(m_ptA) >= 0.0f)
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
    if (planeQ.GetSide(m_ptA) >= 0.0f)
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

/**
 * @brief Calculates the length of the current segment's vector
 * 
 * @return float The resulting length's value
 */
float       Segment::Length             () const noexcept
{
    float x (m_ptB.m_x - m_ptA.m_x);
    float y (m_ptB.m_y - m_ptA.m_y);
    float z (m_ptB.m_z - m_ptA.m_z);

    return std::sqrt(x * x + y * y + z * z);
}

/**
 * @brief Calculates the squared length of the current segment's vector
 * 
 * @return float The resulting squared length's value
 */
float       Segment::LengthSqr          () const noexcept
{
    float x (m_ptB.m_x - m_ptA.m_x);
    float y (m_ptB.m_y - m_ptA.m_y);
    float z (m_ptB.m_z - m_ptA.m_z);

    return x * x + y * y + z * z;
}