#ifndef __SPHERE_INL__
#define __SPHERE_INL__

/**
 * @file    Sphere.inl
 * @brief   Inline file for Sphere
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GSphere
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Sphere::Sphere    () noexcept
:   m_origin {Vector3::Zero},
    m_radius {0.5f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Sphere::Sphere    (const Vector3& p_origin, const float p_radius) noexcept
:   m_origin {p_origin},
    m_radius {p_radius}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Sphere::Sphere    (const Sphere& p_copy) noexcept
:   m_origin {p_copy.m_origin},
    m_radius {p_copy.m_radius}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Sphere::Sphere    (Sphere&& p_move) noexcept
:   m_origin {std::move(p_move.m_origin)},
    m_radius {std::move(p_move.m_radius)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current sphere to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Sphere::ToString() const noexcept
{
    return std::string("Sphere : origin = " + m_origin.ToString() + 
                       " and radius = "     + std::to_string(m_radius));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move             The sphere to move
 * @return constexpr Sphere& The moved sphere
 */
constexpr Sphere&   Sphere::operator=   (Sphere&& p_move) noexcept
{
    m_origin = std::move(p_move.m_origin);
    m_radius = std::move(p_move.m_radius);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy             The sphere to copy
 * @return constexpr Sphere& The copied sphere
 */
constexpr Sphere&   Sphere::operator=   (const Sphere& p_copy) noexcept
{
    m_origin = p_copy.m_origin;
    m_radius = p_copy.m_radius;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a sphere to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_sphere       The target sphere
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Sphere& p_sphere) noexcept
{
    return p_flux << "Sphere : " << "origin = "      << p_sphere.m_origin
                                 << " and radius = " << p_sphere.m_radius;
}

#endif // !__SPHERE_INL__