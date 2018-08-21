#ifndef __QUAD_INL__
#define __QUAD_INL__

/**
 * @file    Quad.inl
 * @brief   Inline file for Quad
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GQuad
 * 
 */

#include "../Includes/Vector2.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Matrix4x4.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Quad::Quad    () noexcept
:	m_forward {Vector3::Forward},
    m_right	  {Vector3::Right  },
    m_up	  {Vector3::Up     },
    m_origin  {Vector3::Zero   },
    m_size	  {Vector2::One    }
{}

/**
 * @brief Default constructor with specified origin and size
 * 
 */
constexpr Quad::Quad	(const Vector3& p_origin, const Vector2& p_size) noexcept
:	m_forward	{Vector3::Forward},
    m_right		{Vector3::Right  },
    m_up		{Vector3::Up     },
    m_origin	{p_origin        },
    m_size		{p_size          }
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Quad::Quad	(const Vector3& p_origin, 
                         const Vector2& p_size, 
                         const Vector3&	p_up, 
                         const Vector3& p_right, 
                         const Vector3& p_forward) noexcept
:	m_forward	{p_up     },
    m_right		{p_right  },
    m_up		{p_forward},
    m_origin	{p_origin },
    m_size		{p_size   }
{}

/**
 * @brief Constructor with specified rotation
 * 
 */
constexpr Quad::Quad	(const Vector3& p_origin, const Vector2& p_size, const  Vector3& p_rotation) noexcept
:	m_forward	{Matrix4x4::Rotate(Quaternion::Euler(p_rotation)) * Vector3::Forward},
    m_right		{Matrix4x4::Rotate(Quaternion::Euler(p_rotation)) * Vector3::Right},
    m_up		{Matrix4x4::Rotate(Quaternion::Euler(p_rotation)) * Vector3::Up},
    m_origin	{p_origin},
    m_size		{p_size}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Quad::Quad	(const Quad& p_copy) noexcept 
:	m_forward	{p_copy.m_up     },
    m_right		{p_copy.m_right  },
    m_up		{p_copy.m_forward},
    m_origin	{p_copy.m_origin },
    m_size		{p_copy.m_size   }
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Quad::Quad	(Quad&& p_move) noexcept 
:	m_forward	{std::move(p_move.m_up)     },
    m_right		{std::move(p_move.m_right)  },
    m_up		{std::move(p_move.m_forward)},
    m_origin	{std::move(p_move.m_origin) },
    m_size		{std::move(p_move.m_size)   }
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Read only accessor
 * 
 * @return constexpr Vector3 The forward vector
 */
constexpr Vector3   Quad::GetForward    () const noexcept
{
	return m_forward;
}

/**
 * @brief Read only accessor
 * 
 * @return constexpr Vector3 The right vector
 */
constexpr Vector3   Quad::GetRight      () const noexcept
{
	return m_right;
}

/**
 * @brief Read only accessor
 * 
 * @return constexpr Vector3 The up vector
 */
constexpr Vector3   Quad::GetUp		    () const noexcept
{
	return m_up;
}

/**
 * @brief Converts the current quad to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Quad::ToString      () const noexcept
{
    return std::string("Quad : origin = " + m_origin .ToString() + 
                       ", size ) "        + m_size   .ToString() + 
                       ", forward = "     + m_forward.ToString() +
                       ", right = "       + m_right  .ToString() + 
                       " and up = "       + m_up     .ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move           The quad to move
 * @return constexpr Quad& The moved quad
 */
constexpr Quad&     Quad::operator=   (Quad&& p_move) noexcept
{
    m_origin  = std::move(p_move.m_origin);
    m_size    = std::move(p_move.m_size);
    m_forward = std::move(p_move.m_forward);
    m_right   = std::move(p_move.m_right);
    m_up      = std::move(p_move.m_up);

    return *this;
}   

/**
 * @brief Copy operator
 * 
 * @param p_copy           The quad to copy
 * @return constexpr Quad& The copied quad
 */
constexpr Quad&     Quad::operator=   (const Quad& p_copy) noexcept
{
    m_origin  = p_copy.m_origin;
    m_size    = p_copy.m_size;
    m_forward = p_copy.m_forward;
    m_right   = p_copy.m_right;
    m_up      = p_copy.m_up;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a quad to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_quad         The target quad
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<  (std::ostream& p_flux, const Quad& p_quad) noexcept
{
    return p_flux << "Quad : " << "origin = "    << p_quad.m_origin
                               << ", size = "    << p_quad.m_size
                               << ", forward = " << p_quad.GetForward()
                               << ", right = "   << p_quad.GetRight()
                               << " and up = "   << p_quad.GetUp();
}

#endif // !__QUAD_INL__