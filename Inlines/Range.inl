#ifndef __RANGE_INL__
#define __RANGE_INL__

/**
 * @file    Range.inl
 * @brief   Inline file for Range
 * @author  Philippe Yi
 * 
 * @ingroup GRange
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/OBB.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Range::Range  (float p_min, float p_max) noexcept
:   m_min {p_min}, m_max {p_max}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Range::Range  (const Range& p_copy) noexcept
:   m_min {p_copy.m_min}, m_max {p_copy.m_max}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Range::Range  (Range&& p_move) noexcept
:   m_min {std::move(p_move.m_min)}, m_max {std::move(p_move.m_max)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Checks if the current range is overlapping with another one
 * 
 * @param p_other The target range
 * @return true   The ranges are overlapping
 * @return false  The ranges are not overlapping
 */
constexpr bool      Range::IsOverlapping   (const Range& p_other) const noexcept
{
    return (m_max < p_other.m_min || m_min > p_other.m_max) ? false : true;
}

/**
 * @brief Converts the current range to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Range::ToString         () const noexcept
{
    return std::string("Range : min = " + std::to_string(m_min) + 
                       " and max = "    + std::to_string(m_max));
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move            The range to move
 * @return constexpr Range& The moved range
 */
constexpr Range&    Range::operator=    (Range&& p_move) noexcept
{
    m_min = std::move(p_move.m_min);
    m_max = std::move(p_move.m_max);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy            The range to copy
 * @return constexpr Range& The copied range
 */
constexpr Range&    Range::operator=    (const Range& p_copy) noexcept
{
    m_min = p_copy.m_min;
    m_max = p_copy.m_max;

    return *this;
}

/*=========================[General Operators]=========================*/

/**
 * @brief Converts a range to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_range        The target range
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Range& p_range) noexcept
{
    return p_flux << "Range : " << "min = "      << p_range.m_min
                                << " and max = " << p_range.m_max; 
}

#endif // !__RANGE_INL__