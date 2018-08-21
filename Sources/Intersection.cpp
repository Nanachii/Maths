/**
 * @file    Intersection.cpp
 * @brief   Source file for Intersection
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GIntersection
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Intersection.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Sets new values to the members
 * 
 * @param p_impact      The new impact
 * @param p_normal      The new normal
 * @return Intersection The new intersection
 */
Intersection	Intersection::Set	(const Vector3&	p_impact, const Vector3& p_normal) noexcept
{
    m_impact = p_impact;
    m_normal = p_normal;

    return *this;
}

/**
 * @brief Resets the values of all members
 * 
 */
void 	        Intersection::Reset () noexcept
{
    m_impact.Set(0.0f, 0.0f, 0.0f);
    m_normal.Set(0.0f, 0.0f, 0.0f);
}