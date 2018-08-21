#ifndef __AABB_INL__
#define __AABB_INL__

/**
 * @file    AABB.inl
 * @brief   Inline file for AABB
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GAABB
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr AABB::AABB    () noexcept
:   m_extents {Vector3::One / 2.0f},
    m_max     {Vector3::One},
    m_min     {Vector3::One * -1.0f},
    m_size    {Vector3::One},
    m_origin  {Vector3::Zero}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr AABB::AABB    (const Vector3& p_origin, const Vector3& p_size) noexcept
:   m_extents {p_size / 2.0f},
    m_max     {Vector3(p_origin + m_extents)},
    m_min     {Vector3(p_origin - m_extents)},
    m_size    {p_size},
    m_origin  {p_origin}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr AABB::AABB    (const AABB& p_copy) noexcept
:   m_extents {p_copy.m_extents},
    m_max     {p_copy.m_max    },
    m_min     {p_copy.m_min    },
    m_size    {p_copy.m_size   },
    m_origin  {p_copy.m_origin } 
{}

/**
 * @brief Move constructor
 * 
 */
constexpr AABB::AABB    (AABB&& p_move) noexcept
:   m_extents {std::move(p_move.m_extents)},
    m_max     {std::move(p_move.m_max)    },
    m_min     {std::move(p_move.m_min)    },
    m_size    {std::move(p_move.m_size)   },
    m_origin  {std::move(p_move.m_origin) }
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current aabb to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string      AABB::ToString() const noexcept
{
    return std::string("AABB : origin = " + m_origin.ToString() + 
                       " and size = "     + m_size  .ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move           The aabb to move
 * @return constexpr AABB& The moved aabb
 */
constexpr AABB&     AABB::operator=     (AABB&& p_move) noexcept
{
    m_extents = std::move(p_move.m_extents);
    m_max     = std::move(p_move.m_max);
    m_min     = std::move(p_move.m_min);
    m_size    = std::move(p_move.m_size);
    m_origin  = std::move(p_move.m_origin);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy           The aabb to copy
 * @return constexpr AABB& The copied aabb
 */
constexpr AABB&     AABB::operator=     (const AABB& p_copy) noexcept
{
    m_extents = p_copy.m_extents;
    m_max     = p_copy.m_max;
    m_min     = p_copy.m_min;
    m_size    = p_copy.m_size;
    m_origin  = p_copy.m_origin;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts an aabb to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_aabb         The target aabb
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<  (std::ostream& p_flux, const AABB& p_aabb) noexcept
{
    return p_flux << "AABB : " << "origin = "    << p_aabb.m_origin 
                               << " and size = " << p_aabb.GetSize();
}

#endif // !__AABB_INL__