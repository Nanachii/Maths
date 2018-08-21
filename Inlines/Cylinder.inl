#ifndef __CYLINDER_INL__
#define __CYLINDER_INL__

/**
 * @file    Cylinder.inl
 * @brief   Inline file for Cylinder
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GCylinder
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default Constructor
 * 
 */
constexpr Cylinder::Cylinder    () noexcept
:	m_origin	{Vector3::Zero},
	m_direction	{Vector3::Up  },
	m_height	{1.0f},
	m_radius	{0.5f}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Cylinder::Cylinder    (const Vector3& p_origin, 
                                 const Vector3& p_direction, 
                                 const float    p_height, 
                                 const float    p_radius) noexcept
:	m_origin	{p_origin   },
	m_direction	{p_direction},
	m_height	{p_height   },
	m_radius	{p_radius   }
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Cylinder::Cylinder    (const Cylinder& p_copy) noexcept
:	m_origin	{p_copy.m_origin   },
	m_direction	{p_copy.m_direction},
	m_height	{p_copy.m_height   },
	m_radius	{p_copy.m_radius   }
{}

/**
 * @brief Move Constructor
 * 
 */
constexpr Cylinder::Cylinder    (Cylinder&& p_move) noexcept
:	m_origin	{std::move(p_move.m_origin)   },
	m_direction	{std::move(p_move.m_direction)},
	m_height	{std::move(p_move.m_height)   },
	m_radius	{std::move(p_move.m_radius)   }
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current cylinder to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Cylinder::ToString() const noexcept
{
    return std::string("Cylinder : origin = " + m_origin   .ToString()   + 
                       ", direction = "       + m_direction.ToString()   +
                       ", height = "          + std::to_string(m_height) +
                       " and radius = "       + std::to_string(m_radius));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move               The cylinder to move
 * @return constexpr Cylinder& The moved cylinder
 */
constexpr Cylinder& Cylinder::operator= (Cylinder&& p_move) noexcept
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
 * @param p_copy               The cylinder to copy
 * @return constexpr Cylinder& The copied cylinder
 */
constexpr Cylinder& Cylinder::operator= (const Cylinder& p_copy) noexcept
{
    m_origin    = p_copy.m_origin;
    m_direction = p_copy.m_direction;
    m_height    = p_copy.m_height;
    m_radius    = p_copy.m_radius;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a cylinder to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_cylinder     The target cylinder
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Cylinder& p_cylinder) noexcept
{
    return p_flux << "Cylinder : " << "origin = "      << p_cylinder.m_origin
                                   << ", direction = " << p_cylinder.m_direction
                                   << ", height = "    << p_cylinder.m_height
                                   << " and radius = " << p_cylinder.m_radius;
}

#endif // !__CYLINDER_INL__