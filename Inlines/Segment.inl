#ifndef __SEGMENT_INL__
#define __SEGMENT_INL__

/**
 * @file    Segment.inl
 * @brief   Inline file for Segment
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GSegment
 * 
 */

#include "../Includes/Vector3.hpp"

using namespace Maths;

/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Segment::Segment() noexcept
:   m_ptA {Vector3::Zero},
    m_ptB {Vector3::Zero}
{}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Segment::Segment  (const Vector3& p_ptA, const Vector3& p_ptB) noexcept
:   m_ptA {p_ptA},
    m_ptB {p_ptB}
{}

/**
 * @brief Copy constructor
 * 
 */
constexpr Segment::Segment  (const Segment& p_copy) noexcept
:   m_ptA {p_copy.m_ptA},
    m_ptB {p_copy.m_ptA}
{}

/**
 * @brief Move constructor
 * 
 */
constexpr Segment::Segment  (Segment&& p_move) noexcept
:   m_ptA {std::move(p_move.m_ptA)},
    m_ptB {std::move(p_move.m_ptA)}
{}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Converts the current segment to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string  Segment::ToString() const noexcept
{
    return std::string("Segment : point 1 = " + m_ptA.ToString() + " and point 2 = " + m_ptB.ToString());
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move              The segment to move
 * @return constexpr Segment& The moved segment
 */
constexpr Segment&  Segment::operator=  (Segment&& p_move) noexcept
{
    m_ptA = std::move(p_move.m_ptA);
    m_ptB = std::move(p_move.m_ptB);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy              The segment to copy
 * @return constexpr Segment& The copied segment
 */
constexpr Segment&  Segment::operator=  (const Segment& p_copy) noexcept
{
    m_ptA = p_copy.m_ptA;
    m_ptB = p_copy.m_ptB;

    return *this;
}

/*=========================[General Operators (Public)]=========================*/

/**
 * @brief Converts a segment to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_segment      The target segment
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Segment& p_segment) noexcept
{
    return p_flux << "Segment : point 1 = " << p_segment.m_ptA << " and point 2 = " << p_segment.m_ptB;
}

#endif // !__SEGMENT_INL__