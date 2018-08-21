#ifndef __LINE_INL__
#define __LINE_INL__

/**
 * @file    Line.inl
 * @brief   Inline file for Line
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GLine
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Line::Line    () noexcept
:   m_origin    {Vector3::Zero}, 
    m_direction {Vector3::Zero}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Line::Line    (const Vector3& p_origin, const Vector3& p_direction) noexcept
:   m_origin    {p_origin   }, 
    m_direction {p_direction}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Line::Line    (const Line& p_copy) noexcept
:   m_origin    {p_copy.m_origin   }, 
    m_direction {p_copy.m_direction}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Line::Line    (Line&& p_move) noexcept
:   m_origin    {std::move(p_move.m_origin)   }, 
    m_direction {std::move(p_move.m_direction)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Computes the closest point on the current line to a point
 * 
 * @param p_pt               The target point
 * @return constexpr Vector3 The closest point found on the line
 */
constexpr Vector3	Line::ClosestPointOnLine    (const Vector3& p_pt) const noexcept
{
    return m_origin + (m_direction * Vector3::Dot(Vector3(m_origin, p_pt), m_direction));
}

/**
 * @brief Calculates the distance between the current line and a point
 * 
 * @param p_pt             The target point
 * @return constexpr float The resulting distance's value
 */
constexpr float	    Line::DistancePoint			(const Vector3& p_pt) const noexcept
{
    return ((Vector3(m_origin, p_pt) ^ m_direction)).GetMagnitude() / (m_direction.GetSqrMagnitude());
}

/**
 * @brief Calculates the squared distance between the current line and a point
 * 
 * @param p_pt             The target point
 * @return constexpr float The resulting squared distance's value
 */
constexpr float	    Line::DistancePointSqr		(const Vector3& p_pt) const noexcept
{
    return ((Vector3(m_origin, p_pt) ^ m_direction)).GetSqrMagnitude() / (m_direction.GetSqrMagnitude());
}

/**
 * @brief Converts the current line to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Line::ToString              () const noexcept
{
    return std::string("Line : origin = "  + m_origin   .ToString() +
                       " and direction = " + m_direction.ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move           The line to move
 * @return constexpr Line& The moved line
 */
constexpr Line&     Line::operator=     (Line&& p_move) noexcept
{
    m_origin    = std::move(p_move.m_origin);
    m_direction = std::move(p_move.m_direction);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy           The line to copy
 * @return constexpr Line& The copied line
 */
constexpr Line&     Line::operator=     (const Line& p_copy) noexcept
{
    m_origin    = p_copy.m_origin;
    m_direction = p_copy.m_direction;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Checks if two lines are equal
 * 
 * @param p_a    The left handed line
 * @param p_b    The right handed line
 * @return true  The lines are equal
 * @return false The lines are not equal
 */
constexpr bool          Maths::operator==   (const Line& p_a, const Line& p_b) noexcept
{
    return !((Vector3(p_a.m_origin, p_b.m_origin) ^ p_a.m_direction)).GetSqrMagnitude() / (p_a.m_direction.GetSqrMagnitude());
}

/**
 * @brief Checks if two line are different
 * 
 * @param p_a    The left handed line
 * @param p_b    The right handed line
 * @return true  The lines are not equal
 * @return false The lines are equal
 */
constexpr bool          Maths::operator!=   (const Line& p_a, const Line& p_b) noexcept
{
    return ((Vector3(p_a.m_origin, p_b.m_origin) ^ p_a.m_direction)).GetSqrMagnitude() / (p_a.m_direction.GetSqrMagnitude());
}

/**
 * @brief Converts a line to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_line         The target line
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Line& p_line) noexcept
{
    return p_flux << "Line : " << "origin = "         << p_line.m_origin 
                               << " and direction = " << p_line.m_direction;
}

#endif // !__LINE_INL__