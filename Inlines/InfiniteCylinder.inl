#ifndef __INFINITE_CYLINDER_INL__
#define __INFINITE_CYLINDER_INL__

/**
 * @file    InfiniteCylinder.inl
 * @brief   Inline file for InfiniteCylinder
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GInfiniteCylinder
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr InfiniteCylinder::InfiniteCylinder    () noexcept
:	m_origin	{Vector3::Zero},
	m_direction	{Vector3::Up  },
	m_radius	{0.5f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr InfiniteCylinder::InfiniteCylinder    (const Vector3& p_origin, 
                                                 const Vector3& p_direction, 
                                                 const float    p_radius) noexcept
:	m_origin	{p_origin   },
	m_direction	{p_direction},
	m_radius	{p_radius   }
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr InfiniteCylinder::InfiniteCylinder    (const InfiniteCylinder& p_copy) noexcept
:	m_origin	{p_copy.m_origin   },
	m_direction	{p_copy.m_direction},
	m_radius	{p_copy.m_radius   }
{}

/**
 * @brief Move constructor
 * 
 */
constexpr InfiniteCylinder::InfiniteCylinder    (InfiniteCylinder&& p_move) noexcept
:	m_origin	{std::move(p_move.m_origin)   },
	m_direction	{std::move(p_move.m_direction)},
	m_radius	{std::move(p_move.m_radius)   }
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current infinite cylinder to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string	InfiniteCylinder::ToString() const noexcept
{
	return std::string("Infinite Cylinder : origin = " + m_origin   .ToString() + 
	                   ", direction = "                + m_direction.ToString() + 
					   " and radius = "                + std::to_string(m_radius));
}

/*=========================[Local Operator (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move                       The cylinder to move
 * @return constexpr InfiniteCylinder& The moved cylinder
 */
constexpr InfiniteCylinder&	InfiniteCylinder::operator=	(InfiniteCylinder&& p_move) 		noexcept
{
	m_origin    = std::move(p_move.m_origin);
	m_direction = std::move(p_move.m_direction);
	m_radius    = std::move(p_move.m_radius);

	return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy                       The cylinder to copy
 * @return constexpr InfiniteCylinder& The copied cylinder
 */
constexpr InfiniteCylinder&	InfiniteCylinder::operator=	(const InfiniteCylinder& p_copy)	noexcept
{
	m_origin    = p_copy.m_origin;
	m_direction = p_copy.m_direction;
	m_radius    = p_copy.m_radius;

	return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts an infinite cylinder to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_cylinder     The target cylinder
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&	operator<<	(std::ostream& p_flux, const InfiniteCylinder& p_cylinder) noexcept
{
	return p_flux << "Infinite Cylinder : " << "origin = "      << p_cylinder.m_origin
	                                        << ", direction = " << p_cylinder.m_direction
											<< " and radius = " << p_cylinder.m_radius;
}

#endif // !__INFINITE_CYLINDER_INL__