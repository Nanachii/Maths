/**
 * @file    Matrix4x4.cpp
 * @brief   Source file for Matrix4x4
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GMatrix4x4
 * 
 */

#include "../Includes/Matrix4x4.hpp"

using namespace Maths;

/*=========================[Static Properties (Public)]=========================*/

const Matrix4x4 Matrix4x4::Identity {Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                                               0.0f, 1.0f, 0.0f, 0.0f, 
                                               0.0f, 0.0f, 1.0f, 0.0f, 
                                               0.0f, 0.0f, 0.0f, 1.0f)};

const Matrix4x4 Matrix4x4::Zero		{Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
                                               0.0f, 0.0f, 0.0f, 0.0f, 
                                               0.0f, 0.0f, 0.0f, 0.0f, 
                                               0.0f, 0.0f, 0.0f, 0.0f)};


/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Sets the values of a column with a 4D vector
 * 
 * @param p_index  The column's index value
 * @param p_column The vector with new values
 */
void		    Matrix4x4::SetColumn    (int p_index, const Vector4& p_column)
{
    if (p_index >= 4)
        throw std::out_of_range("No value available!");

    m_matrix[p_index    ] = p_column.m_x;
    m_matrix[p_index + 1] = p_column.m_y;
    m_matrix[p_index + 2] = p_column.m_z;
    m_matrix[p_index + 3] = p_column.m_w;
} 

/**
 * @brief Sets the values of a row with a 4D vector
 * 
 * @param p_index The row's index value
 * @param p_row   The vector with new values
 */
void		    Matrix4x4::SetRow       (int p_index, const Vector4& p_row)
{
    if (p_index >= 4)
        throw std::out_of_range("No value avaible!");

    m_matrix[p_index     ] = p_row.m_x;
    m_matrix[p_index + 4 ] = p_row.m_y;
    m_matrix[p_index + 8 ] = p_row.m_z;
    m_matrix[p_index + 12] = p_row.m_w;
} 

/**
 * @brief Updates the current TRS
 * 
 * @param p_translation The new translation vector
 * @param p_q           The new rotation quaternion
 * @param p_scale       The new scaling vector
 */
void            Matrix4x4::SetTRS       (const Vector3&    p_translation, 
                                         const Quaternion& p_q, 
                                         const Vector3&    p_scale) noexcept
{
     // Create translation matrix
    Matrix4x4 translation 
    (   1.0f, 0.0f, 0.0f, p_translation.m_x,
        0.0f, 1.0f, 0.0f, p_translation.m_y,
        0.0f, 0.0f, 1.0f, p_translation.m_z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // Create rotation matrix
    double sqrX  (p_q.m_x*p_q.m_x);
    double sqrY  (p_q.m_y*p_q.m_y);
    double sqrZ  (p_q.m_z*p_q.m_z);

    Matrix4x4 rotation
    (
        1-2*(sqrY+sqrZ)                     , 2*(p_q.m_x*p_q.m_y-p_q.m_z*p_q.m_w)   , 2*(p_q.m_x*p_q.m_z+p_q.m_y*p_q.m_w)   , 0,
        2*(p_q.m_x*p_q.m_y+p_q.m_z*p_q.m_w) , 1-2*(sqrX+sqrZ)                       , 2*(p_q.m_y*p_q.m_z-p_q.m_x*p_q.m_w)   , 0,
        2*(p_q.m_x*p_q.m_z-p_q.m_y*p_q.m_w) , 2*(p_q.m_y*p_q.m_z+p_q.m_x*p_q.m_w)   , 1-2*(sqrX+sqrY)                       , 0,
        0                                   , 0                                     , 0                                     , 1
    );
   
    // Create scaling matrix
    Matrix4x4 scale
    (
        p_scale.m_x, 0.0f		, 0.0f		 , 0.0f,
        0.0f	   , p_scale.m_y, 0.0f		 , 0.0f,
        0.0f	   , 0.0f		, p_scale.m_z, 0.0f,
        0.0f	   , 0.0f		, 0.0f		 , 1.0f
    );

    *this = translation * rotation * scale;
}