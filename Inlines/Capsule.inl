#ifndef __CAPSULE_INL__
#define __CAPSULE_INL__

/**
 * @file    Capsule.inl
 * @brief   Inline file for Capsule
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GCapsule
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Capsule::Capsule  () noexcept
:	m_origin	{Vector3::Zero},
	m_direction	{Vector3::Up  },
	m_height	{1.0f},
	m_radius	{0.5f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Capsule::Capsule  (const Vector3& p_origin, 
                             const Vector3& p_direction, 
                             const float    p_height, 
                             const float    p_radius) noexcept 
:	m_origin	{p_origin   },
	m_direction	{p_direction},
	m_height	{p_height   },
	m_radius	{p_radius   }
{}

/**
 * @brief Constructor with two points
 * 
 */
constexpr Capsule::Capsule  (const Vector3& p_origin, 
                             const Vector3& p_target, 
                             const float    p_radius) noexcept
:   m_origin	{p_origin},
	m_direction	{(p_target - p_origin).Normalize()},
	m_height	{(p_target - p_origin).GetMagnitude()},
	m_radius	{p_radius}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Capsule::Capsule  (const Capsule& p_copy) noexcept
:   m_origin	{p_copy.m_origin   },
	m_direction	{p_copy.m_direction},
	m_height	{p_copy.m_height   },
	m_radius	{p_copy.m_radius   }
{}     

/**
 * @brief Move constructor
 * 
 */
constexpr Capsule::Capsule  (Capsule&& p_move) noexcept
:   m_origin	{std::move(p_move.m_origin)   },
	m_direction	{std::move(p_move.m_direction)},
	m_height	{std::move(p_move.m_height)   },
	m_radius	{std::move(p_move.m_radius)   }
{}      

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current capsule to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Capsule::ToString() const noexcept
{
    return std::string("Capsule : origin = " + m_origin   .ToString()   + 
                       ", direction = "      + m_direction.ToString()   +
                       ", height = "         + std::to_string(m_height) +
                       " and radius = "      + std::to_string(m_radius));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The capsule to move
 * @return constexpr Capsule& The moved capsule
 */
constexpr Capsule&  Capsule::operator=  (Capsule&& p_move) noexcept
{
    m_origin    = std::move(p_move.m_origin);
    m_direction = std::move(p_move.m_direction);
    m_height    = std::move(p_move.m_height);
    m_radius    = std::move(p_move.m_radius);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy              The capsule to copy
 * @return constexpr Capsule& The copied capsule
 */
constexpr Capsule&  Capsule::operator=  (const Capsule& p_copy) noexcept
{
    m_origin    = p_copy.m_origin;
    m_direction = p_copy.m_direction;
    m_height    = p_copy.m_height;
    m_radius    = p_copy.m_radius;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a capsule to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_capsule      The target capsule
 * @return std::ostream& The resulting stream of  the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Capsule& p_capsule) noexcept
{
    return p_flux << "Capsule : " << "origin = "      << p_capsule.m_origin
                                  << ", direction = " << p_capsule.m_direction
                                  << ", height = "    << p_capsule.m_height
                                  << " and radius = " << p_capsule.m_radius;
}

#endif // !__CAPSULE_INL__