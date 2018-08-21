/**
 * @file    Range.cpp
 * @brief   Source file for Range
 * @author  Philippe Yi
 * 
 * @ingroup GRange
 * 
 */

#include <vector>

#include "../Includes/Vector3.hpp"
#include "../Includes/OBB.hpp"
#include "../Includes/Range.hpp"

using namespace Maths;

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Computes SAT between a 3D vector and an oriented box
 * 
 * @param p_vector The target vector
 * @param p_obb    The target box
 * @return Range   The resulting range of the SAT
 */
Range   Range::SAT(const Vector3& p_vector, const OBB& p_obb) noexcept
{
    Range range(__FLT_MAX__, __FLT_MIN__);

    std::vector<Vector3> vertices = p_obb.GetVertices();

    for (unsigned int i = 0u; i < vertices.size(); ++i)
    {
        float dot (Vector3::Dot(p_vector, vertices[i]));

        range.m_min = Min(range.m_min, dot);
        range.m_max = Max(range.m_max, dot);
    }

    return range;
}