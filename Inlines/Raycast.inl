#ifndef __RAYCAST_INL__
#define __RAYCAST_INL__

/**
 * @file    Raycast.inl
 * @brief   Inline file for Raycast
 * @author  Philippe Yi
 * 
 * @ingroup GRaycast
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Raycast::Raycast    () noexcept
:   m_origin      {Vector3::Zero}, 
    m_direction   {Vector3::Zero},
    m_maxDistance {0.0f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Raycast::Raycast    (const Vector3& p_origin, 
                               const Vector3& p_direction, 
                               const float    p_maxDistance) noexcept
:   m_origin      {p_origin     }, 
    m_direction   {p_direction  },
    m_maxDistance {p_maxDistance}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Raycast::Raycast    (const Raycast& p_copy) noexcept
:   m_origin      {p_copy.m_origin     }, 
    m_direction   {p_copy.m_direction  },
    m_maxDistance {p_copy.m_maxDistance}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Raycast::Raycast    (Raycast&& p_move) noexcept
:   m_origin      {std::move(p_move.m_origin)     }, 
    m_direction   {std::move(p_move.m_direction)  },
    m_maxDistance {std::move(p_move.m_maxDistance)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current raycast to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Raycast::ToString              () const noexcept
{
    return std::string("Raycast : origin = "  + m_origin   .ToString() +
                       ", direction = "       + m_direction.ToString() +
                       " and maxDistance = "  + std::to_string(m_maxDistance));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The raycast to move
 * @return constexpr Raycast& The moved racayst
 */
constexpr Raycast&     Raycast::operator=     (Raycast&& p_move) noexcept
{
    m_origin      = std::move(p_move.m_origin);
    m_direction   = std::move(p_move.m_direction);
    m_maxDistance = std::move(p_move.m_maxDistance);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy           The raycast to copy
 * @return constexpr Raycast& The copied raycast
 */
constexpr Raycast&     Raycast::operator=     (const Raycast& p_copy) noexcept
{
    m_origin      = p_copy.m_origin;
    m_direction   = p_copy.m_direction;
    m_maxDistance = p_copy.m_maxDistance;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a raycast to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_raycast      The target raycast
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Raycast& p_raycast) noexcept
{
    return p_flux << "Raycast : " << "origin = "           << p_raycast.m_origin 
                                  << ", direction = "      << p_raycast.m_direction
                                  << " and maxDistance = " << p_raycast.m_maxDistance;
}

#endif // !__RAYCAST_INL__