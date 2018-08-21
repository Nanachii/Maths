#ifndef __PLANE_INL__
#define __PLANE_INL__

/**
 * @file    Plane.inl
 * @brief   Inline file for Plane
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GPlane
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Plane::Plane  () noexcept
:   m_normal {Vector3::Zero}, m_distance {0.0f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Plane::Plane  (const Vector3& p_normal, const float p_distance) noexcept
:   m_normal {p_normal}, m_distance {p_distance}
{}

/**
 * @brief Constructor with a point
 * 
 */
constexpr Plane::Plane  (const Vector3& p_normal, const Vector3& p_point) noexcept
:   m_normal {p_normal}, m_distance {-Vector3::Dot(p_point, p_normal)}
{}

/**
 * @brief Constructor with three points
 * 
 */
constexpr Plane::Plane  (const Vector3& p_pt1, const Vector3& p_pt2, const Vector3& p_pt3) noexcept
:   m_normal {((p_pt2 - p_pt1) ^ (p_pt3 - p_pt1)).GetNormalize()}, m_distance {-Vector3::Dot(p_pt1, m_normal)}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Plane::Plane  (const Plane& p_copy) noexcept
:   m_normal {p_copy.m_normal}, m_distance {p_copy.m_distance}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Plane::Plane  (Plane&& p_move) noexcept
:   m_normal {std::move(p_move.m_normal)}, m_distance {std::move(p_move.m_distance)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current plane to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Plane::ToString() const noexcept
{
    return std::string("Plane : normal = " + m_normal.ToString() + 
                       " and distance = "  + std::to_string(m_distance));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move            The plane to move
 * @return constexpr Plane& The moved operator
 */
constexpr Plane&    Plane::operator=    (Plane&& p_move) noexcept
{
    m_normal   = std::move(std::move(p_move.m_normal));
    m_distance = std::move(std::move(p_move.m_distance));

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy            The plane to copy
 * @return constexpr Plane& The copied operator
 */
constexpr Plane&    Plane::operator=    (const Plane& p_copy) noexcept
{
    m_normal   = p_copy.m_normal;
    m_distance = p_copy.m_distance;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a plane to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_plane        The target plane
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Plane& p_plane) noexcept
{
    return p_flux << "Plane : " << "normal = "        << p_plane.m_normal
                                << " and distance = " << p_plane.m_distance;
}

#endif // !__PLANE_INL__