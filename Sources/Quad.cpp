/**
 * @file    Quad.cpp
 * @brief   Source file for Quad
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GQuad
 * 
 */

#include "../Includes/Vector2.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Matrix4x4.hpp"
#include "../Includes/Quad.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Checks if a point is included in the current quad
 * 
 * @param p_pt   The target point
 * @return true  The point is inside of the quad
 * @return false The point is outside of the quad
 */
bool	Quad::IsPointInclude    (const Vector3& p_pt)	const noexcept
{
    bool isPoinInclude	(false);

    float distance		(-(m_up.m_x * m_origin.m_x + 
                           m_up.m_y * m_origin.m_y + 
                           m_up.m_z * m_origin.m_z));
    float cartesian 	(  m_up.m_x * p_pt.m_x + 
                           m_up.m_y * p_pt.m_y + 
                           m_up.m_z * p_pt.m_z + distance);

    if (cartesian == 0.0f)
    {
        Vector3 max(m_right   * m_size.m_x / 2.0f + 
                    m_up      * m_size.m_y / 2.0f + 
                    m_forward * m_size.m_y / 2.0f);

        if (-max.m_x <= p_pt.m_x && p_pt.m_x <= max.m_x &&
            -max.m_y <= p_pt.m_y && p_pt.m_y <= max.m_y &&
            -max.m_z <= p_pt.m_z && p_pt.m_z <= max.m_z)
            isPoinInclude = true;
    }

    return isPoinInclude;
}

/**
 * @brief Rotates the current quad
 * 
 * @param p_rotation The rotation vector
 */
void	Quad::Rotate		    (const Vector3& p_rotation) noexcept
{
    Matrix4x4 rotation(Matrix4x4::Rotate(Quaternion::Euler(p_rotation)));

    m_up		= rotation * m_up;
    m_right		= rotation * m_right;
    m_forward	= rotation * m_forward;
}

/**
 * @brief Rotates the current quad
 * 
 * @param p_xRot The rotation's x value
 * @param p_yRot The rotation's y value
 * @param p_zRot The rotation's z value
 */
void	Quad::Rotate		    (const float p_xRot, 
                                 const float p_yRot, 
                                 const float p_zRot) noexcept
{
    Matrix4x4 rotation(Matrix4x4::Rotate(Quaternion::Euler(p_xRot,p_yRot,p_zRot)));

    m_up		= rotation * m_up;
    m_right		= rotation * m_right;
    m_forward	= rotation * m_forward;
}