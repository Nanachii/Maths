#ifndef __OBB_INL__
#define __OBB_INL__

/**
 * @file    OBB.inl
 * @brief   Inline file for OBB
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GOBB
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr OBB::OBB	() noexcept
:	m_origin  {Vector3::Zero},
	m_extents {Vector3::One / 2.0f},
	m_angle	  {Vector3::Zero}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr OBB::OBB	(const Vector3& p_origin, 
                     const Vector3& p_extents, 
			         const Vector3& p_angle) noexcept
:	m_origin  {p_origin },
	m_extents {p_extents},
	m_angle	  {p_angle  }
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr OBB::OBB	(const OBB& p_copy) noexcept
:	m_origin  {p_copy.m_origin },
	m_extents {p_copy.m_extents},
	m_angle	  {p_copy.m_angle  }
{}

/**
 * @brief Move constructor
 * 
 */
constexpr OBB::OBB  (OBB&& p_move) noexcept
:	m_origin  {std::move(p_move.m_origin) },
	m_extents {std::move(p_move.m_extents)},
	m_angle   {std::move(p_move.m_angle)  }
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current oriented box to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  OBB::ToString() const noexcept
{
    return std::string("OBB : origin = " + m_origin .ToString() + 
                       ", extents = "    + m_extents.ToString() + 
                       " and angle = "   + m_angle  .ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move          The box to move
 * @return constexpr OBB& The moved box
 */
constexpr OBB&  OBB::operator=   (OBB&& p_move) noexcept
{
    m_origin  = std::move(p_move.m_origin);
    m_extents = std::move(p_move.m_extents);
    m_angle   = std::move(p_move.m_angle);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy          The box to copy
 * @return constexpr OBB& The copied box
 */
constexpr OBB&  OBB::operator=   (const OBB& p_copy) noexcept
{
    m_origin  = p_copy.m_origin;
    m_extents = p_copy.m_extents;
    m_angle   = p_copy.m_angle;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts an oriented box to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_obb          The target oriented box
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<  (std::ostream& p_flux, const OBB& p_obb) noexcept
{
    return p_flux << "OBB : " << "origin = "     << p_obb.m_origin
                              << ", extents = "  << p_obb.m_extents
                              << " and angle = " << p_obb.m_angle;
}

#endif // !__OBB_INL__