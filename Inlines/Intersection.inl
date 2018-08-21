#ifndef __INTERSECTION_INL__
#define __INTERSECTION_INL__

/**
 * @file    Intersection.inl
 * @brief   Inline file for Intersection
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GIntersection
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Intersection::Intersection    () noexcept
:   m_impact {Vector3::Zero}, m_normal {Vector3::Zero}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Intersection::Intersection    (const Vector3& p_impact, const Vector3& p_normal) noexcept
:   m_impact {p_impact}, m_normal {p_normal}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Intersection::Intersection    (const Intersection& p_copy) noexcept
:   m_impact {p_copy.m_impact}, m_normal {p_copy.m_normal}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Intersection::Intersection    (Intersection&& p_move) noexcept
:   m_impact {std::move(p_move.m_impact)}, m_normal {std::move(p_move.m_normal)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current intersection to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Intersection::ToString() const noexcept
{
    return std::string("Intersection : impact = " + m_impact.ToString() + 
                       " and normal = "           + m_normal.ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator 
 * 
 * @param p_move                   The intersection to move
 * @return constexpr Intersection& The moved intersection
 */
constexpr Intersection&     Intersection::operator=     (Intersection&& p_move) noexcept
{
    m_impact = std::move(p_move.m_impact);
    m_normal = std::move(p_move.m_normal);

    return *this;
}

/**
 * @brief Copy operator 
 * 
 * @param p_copy                   The intersection to copy
 * @return constexpr Intersection& The copied intersection
 */
constexpr Intersection&     Intersection::operator=     (const Intersection& p_copy) noexcept
{
    m_impact = p_copy.m_impact;
    m_normal = p_copy.m_normal;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Checks if two intersections are equal
 * 
 * @param p_a    The left handed intersection
 * @param p_b    The right handed intersection
 * @return true  The intersections are equal
 * @return false The intersections are not equal
 */
constexpr bool          Maths::operator==    (const Intersection& p_a, const Intersection& p_b) noexcept
{
    return p_a.m_impact == p_b.m_impact && p_a.m_normal == p_b.m_normal;
}

/**
 * @brief Checks if two intersections are different
 * 
 * @param p_a    The left handed intersection
 * @param p_b    The right handed intersection
 * @return true  The intersections are not equal
 * @return false The intersections are equal
 */
constexpr bool          Maths::operator!=    (const Intersection& p_a, const Intersection& p_b) noexcept
{
    return !(p_a.m_impact == p_b.m_impact && p_a.m_normal == p_b.m_normal);
}

/**
 * @brief Converts an intersection to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_intersection The target intersection
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Intersection& p_intersection) noexcept
{
    return p_flux << "Intersection : " << "impact = "      << p_intersection.m_impact
                                       << " and normal = " << p_intersection.m_normal;
}

#endif // !__INTERSECTION_INL__