/**
 * @file    AABB.cpp
 * @brief   Source file for AABB
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GAABB
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/OBB.hpp"
#include "../Includes/Sphere.hpp"
#include "../Includes/Cylinder.hpp"
#include "../Includes/InfiniteCylinder.hpp"
#include "../Includes/Capsule.hpp"

#include "../Includes/AABB.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Computes the closest point from the current AABB to a point
 * 
 * @param p_point  The target point
 * @return Vector3 The resulting point
 */
Vector3		            AABB::ClosestPoint  (const Vector3& p_point) const noexcept
{
    Vector3	closestPoint;

    for (int i = 0 ; i < 3 ; ++i)
    {
        float value (p_point[i]);

        if		(value < m_min[i]) value = m_min[i]; 
        else if	(value > m_max[i]) value = m_max[i];

        closestPoint[i] = value;
    }

    return closestPoint;
}

/**
 * @brief Checks if a point is inside the current AABB
 * 
 * @param p_point The target point
 * @return true   The point is inside the AABB
 * @return false  The point is outside the AABB
 */
bool		            AABB::Contains		(const Vector3& p_point) const noexcept
{
    return 	m_min.m_x <= p_point.m_x && p_point.m_x <= m_max.m_x &&
            m_min.m_y <= p_point.m_y && p_point.m_y <= m_max.m_y &&
            m_min.m_z <= p_point.m_z && p_point.m_z <= m_max.m_z;
}

/**
 * @brief Computes the desired corner of the current AABB
 * 
 * @param p_n      The target corner
 * @return Vector3 The resulting corner
 */
Vector3		            AABB::Corner		(const int p_n) const noexcept
{
    Vector3 corner;

    corner.m_x = ((p_n & 1) ? m_max.m_x : m_min.m_x);
    corner.m_y = ((p_n & 1) ? m_max.m_y : m_min.m_y);
    corner.m_z = ((p_n & 1) ? m_max.m_z : m_min.m_z);

    return corner;
}

/**
 * @brief Calculates the distance between the current AABB and a point
 * 
 * @param p_point The target point
 * @return float  The resulting distance's value
 */
float		            AABB::Distance		(const Vector3& p_point) const noexcept
{
    float sqrDistance (0.0f);
    
    for (int i = 0 ; i < 3 ; ++i)
    {
        float value (p_point[i]);

        if 		(value < m_min[i]) sqrDistance += (m_min[i] - value) * (m_min[i] - value);
        else if (value > m_max[i]) sqrDistance += (value - m_max[i]) * (value - m_max[i]);
    }
    return std::sqrt(sqrDistance);
}

/**
 * @brief Calculates the squared distance between the current AABB and a point
 * 
 * @param p_point The target point
 * @return float  The resulting squared distance's value
 */
float                   AABB::DistanceSqr   (const Vector3& p_point) const noexcept
{
    float sqrDistance (0.0f);

    for (int i = 0 ; i < 3 ; ++i)
    {
        float value (p_point[i]);

        if 		(value < m_min[i]) sqrDistance += (m_min[i] - value) * (m_min[i] - value);
        else if (value > m_max[i]) sqrDistance += (value - m_max[i]) * (value - m_max[i]);
    }

    return sqrDistance;
}

/**
 * @brief Expands the current AABB until it contains a point
 * 
 * @param p_point The point to encapsulate
 */
[[deprecated("This method is not implemented yet!")]]
void		            AABB::Encapsulate	(const Vector3& p_point) const noexcept
{
    (void)p_point;
}

/**
 * @brief Expands the current AABB until it contains another AABB
 * 
 * @param p_aabb The aabb to encapsulate
 */
[[deprecated("This method is not implemented yet!")]]
void                    AABB::Encapsulate   (const AABB& p_aabb) const noexcept
{
    (void)p_aabb;
}

/**
 * @brief Expands the current AABB with a value
 * 
 * @param p_amount The value to expand
 */
void                    AABB::Expand        (const float p_amount) noexcept
{
    m_size    += p_amount * 2.0f;
    m_extents += p_amount;
    m_max      = Vector3(m_origin + m_extents);
    m_min      = Vector3(m_origin - m_extents);
}

/**
 * @brief Expands the current AABB with a vector
 * 
 * @param p_amount The vector to expand
 */
void                    AABB::Expand        (const Vector3& p_amount) noexcept
{
    m_size    += p_amount * 2.0f;
    m_extents += p_amount;
    m_max      = Vector3(m_origin + m_extents);
    m_min      = Vector3(m_origin - m_extents);
}

/**
 * @brief Return the extents of the current AABB
 * 
 * @return Vector3 The extents vector
 */
Vector3 	            AABB::GetExtents	() 	const noexcept
{
    return m_extents;
}

/**
 * @brief Returns the maximum point of the current AABB
 * 
 * @return Vector3 The top-right corner
 */
Vector3 	            AABB::GetMax		() 	const noexcept
{
    return m_max;
}

/**
 * @brief Returns the minimum point of the current AABB
 * 
 * @return Vector3 The bottom-left corner
 */
Vector3 	            AABB::GetMin		() 	const noexcept
{
    return m_min;
}

/**
 * @brief Returns the size of the current AABB
 * 
 * @return Vector3 The size vector
 */
Vector3 	            AABB::GetSize		() 	const noexcept
{
    return m_size;
}

/**
 * @brief Computes the vertices of the current AABB
 * 
 * @return std::vector<Vector3> The array of vertices
 */
std::vector<Vector3>    AABB::GetVertices   () const noexcept
{
    std::vector<Maths::Vector3> vertices;

    // Front
    vertices.push_back(m_origin + Maths::Vector3(-m_extents.m_x,  m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3( m_extents.m_x,  m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3(-m_extents.m_x, -m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3( m_extents.m_x, -m_extents.m_y,  m_extents.m_z));

    // Back
    vertices.push_back(m_origin + Maths::Vector3( m_extents.m_x,  m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3(-m_extents.m_x,  m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3( m_extents.m_x, -m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + Maths::Vector3(-m_extents.m_x, -m_extents.m_y, -m_extents.m_z));


    return vertices;
}

/**
 * @brief Checks if there is collision with another AABB
 * 
 * @param p_other The target AABB
 * @return true   There is collision with the other AABB
 * @return false  There is no collision with the other AABB
 */
bool                    AABB::IsColliding   (const AABB& p_other) const noexcept
{
    Vector3 otherExtents(p_other.GetExtents());

    if (m_origin.m_x - p_other.m_origin.m_x > m_extents.m_x + otherExtents.m_x &&
        m_origin.m_y - p_other.m_origin.m_y > m_extents.m_y + otherExtents.m_y &&
        m_origin.m_z - p_other.m_origin.m_z > m_extents.m_z + otherExtents.m_z)
        return false;
    else
        return true;
}

/**
 * @brief Checks if there is collision with an oriented box
 * 
 * @param p_obb  The target box
 * @return true  There is collision with the box
 * @return false There is no collision with box
 */
[[deprecated("This method is not implemented yet!")]]
bool                    AABB::IsColliding   (const OBB& p_obb) const noexcept
{
    (void)p_obb;

    return false;
}

/**
 * @brief Checks if there is collision with a sphere
 * 
 * @param p_sphere The target sphere
 * @return true    There is collision with the sphere
 * @return false   There is no collision with sphere
 */
[[deprecated("This method is not implemented yet!")]]
bool                    AABB::IsColliding   (const Sphere& p_sphere) const noexcept
{
    (void)p_sphere;

    return false;
}

/**
 * @brief Checks if there is collision with a cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool                    AABB::IsColliding   (const Cylinder& p_cylinder) const noexcept
{
    (void)p_cylinder;

    return false;
}

/**
 * @brief Checks if there is collision with an infinite cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the infinite cylinder
 * @return false     There is no collision with infintie cylidner
 */
[[deprecated("This method is not implemented yet!")]]
bool                    AABB::IsColliding   (const InfiniteCylinder& p_cylinder) const noexcept
{
    (void)p_cylinder;

    return false;
}

/**
 * @brief Checks if there is collision with a capsule
 * 
 * @param p_capsule The target capsule
 * @return true     There is collision with the capsule
 * @return false    There is no collision with capsule
 */
[[deprecated("This method is not implemented yet!")]]
bool                    AABB::IsColliding   (const Capsule& p_capsule) const noexcept
{
    (void)p_capsule;

    return false;
}

/**
 * @brief Computes the normal from the origin to a point
 * 
 * @param p_point  The target point
 * @return Vector3 The resulting normal
 */
Vector3                 AABB::Normal        (const Vector3& p_point) const noexcept
{
    Vector3 normal;

    // Vector3 v   (m_origin, p_point);
    // float dotX  (Maths::Vector3::Dot(v,Maths::Vector3::Right));
    // float dotY  (Maths::Vector3::Dot(v,Maths::Vector3::Up));
    // float dotZ  (Maths::Vector3::Dot(v,Maths::Vector3::Forward));

    // std::cout << "V" <<  v << '\n';
    // std::cout << dotX << '\n';
    // std::cout << dotY << '\n';
    // std::cout << dotZ << '\n';

    // float dotX2 (dotX * dotX);
    // float dotY2 (dotY * dotY);
    // float dotZ2 (dotZ * dotZ);

    // if      (dotX2 <= dotY2 && dotX2 >= dotY2)
    // {
    //     if (dotX >= 0)
    //         normal  = Maths::Vector3::Right;
    //     else
    //         normal  = Maths::Vector3::Left;
    // }

    // else if (dotY2 <= dotZ2)
    // {
    //     if (dotY >= 0)
    //         normal = Maths::Vector3::Up;
    //     else
    //         normal = Maths::Vector3::Down;
    // }

    // else if (dotZ != 0)
    // {
    //     if (dotZ >= 0)
    //         normal = Maths::Vector3::Forward;
    //     else
    //         normal = Maths::Vector3::Backward;
    // }


    Vector3 localPoint (p_point - m_origin);
 
    float   min        (__FLT_MAX__);
 

 
    for (int i = 0; i < 3; ++i)
 
    {
 
        float distance = std::abs(m_extents[i] - std::abs(localPoint[i]));
 

 
        if (distance < min)
 
        {
 
            min = distance;
 

 
            if (i == 0)
 
                normal = Vector3::Right * localPoint[i];
 
            else if (i == 1)
 
                normal = Vector3::Up * localPoint[i];
 
            else
 
                normal = Vector3::Forward * localPoint[i];
 
        }
 
    }
 

    return normal.GetNormalize();
}