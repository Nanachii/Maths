#ifndef __MATRIX_4x4_INL__
#define __MATRIX_4x4_INL__

/**
 * @file    Matrix4x4.inl
 * @brief   Inline file for Matrix4x4
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GMatrix4x4
 * 
 */

#include <cmath>
#include <stdexcept>
#include <iomanip>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Vector4.hpp"
#include "../Includes/Quaternion.hpp"



using namespace Maths;

/*=========================[Static Methods (Public)]=========================*/

/**
 * @brief Creates a transformation matrix that corresponds to a camera viewing the target from the source
 * 
 * @param p_from               The soure point
 * @param p_to                 The target point
 * @param p_up                 The up vector
 * @return constexpr Matrix4x4 The resulting transformation matrix
 */
constexpr Matrix4x4	    Matrix4x4::LookAt		(const Vector3& p_from, const Vector3& p_to, const Vector3& p_up) noexcept
{
    Vector3	forward ((p_to - p_from).GetNormalize());
    Vector3	up      (p_up.GetNormalize());
    Vector3	right   (up ^ forward);

    return Matrix4x4
    (
        right.m_x   ,  up.m_x   , forward.m_x   , 0.0f,
        right.m_y   ,  up.m_y   , forward.m_y   , 0.0f,
        right.m_z   ,  up.m_z   , forward.m_z   , 0.0f,
        0.0f        ,  0.0f     , 0.0f          , 1.0f
    );
}

/**
 * @brief Creates a transformation matrix that corresponds to a camera viewing the target from the source
 * 
 * @param p_fromX              The source point's x value
 * @param p_fromY              The source point's y value
 * @param p_fromZ              The source point's z value
 * @param p_toX                The target point's x value
 * @param p_toY                The target point's y value
 * @param p_toZ                The target point's z value
 * @param p_upX                The up vector's x value
 * @param p_upY                The up vector's y value
 * @param p_upZ                The up vector's z value
 * @return constexpr Matrix4x4 The resulting transformation matrix
 */
constexpr Matrix4x4	    Matrix4x4::LookAt		(const float p_fromX, const float p_fromY, const float p_fromZ,
                                                 const float p_toX,   const float p_toY,   const float p_toZ, 
                                                 const float p_upX,   const float p_upY,   const float p_upZ) noexcept
{
    Vector3	forward ((Vector3(p_toX, p_toY, p_toZ) - Vector3(p_fromX, p_fromY, p_fromZ)).GetNormalize());
    Vector3	up 	    ((Vector3(p_upX, p_upY, p_upZ)).GetNormalize());
    Vector3	right   (forward ^ up);

    return Matrix4x4
    (
        right.m_x, up.m_x, -forward.m_x, 0.0f,
        right.m_y, up.m_y, -forward.m_y, 0.0f,
        right.m_z, up.m_z, -forward.m_z, 0.0f,
        0.0f     , 0.0f  ,  0.0f       , 1.0f
    );
}

/**
 * @brief Creates an orthogonal projection matrix
 * 
 * @param p_left               The left value
 * @param p_right              The right value
 * @param p_bottom             The bottom value
 * @param p_top                The top value
 * @param p_zNear              The near value
 * @param p_zFar               The far value
 * @return constexpr Matrix4x4 The resulting orthogonal projection matrix
 */
constexpr Matrix4x4	    Matrix4x4::Ortho		(const float p_left,   const float p_right, 
                                                 const float p_bottom, const float p_top, 
                                                 const float p_zNear,  const float p_zFar) noexcept
{
    return Matrix4x4
    (
        2.0f / (p_right - p_left), 0.0f				        ,  0.0f				        , -(p_right + p_left)   / (p_right - p_left),
        0.0f			         , 2.0f / (p_top - p_bottom),  0.0f				        , -(p_top   + p_bottom) / (p_top   - p_bottom),
        0.0f				     , 0.0f				        , -2.0f / (p_zFar - p_zNear), -(p_zFar  + p_zNear)  / (p_zFar  - p_zNear),
        0.0f				     , 0.0f				        ,  0.0f				        ,  1.0f
    );
}

/**
 * @brief Creates a perspective projection matrix
 * 
 * @param p_left               The left value
 * @param p_right              The right value
 * @param p_bottom             The bottom value
 * @param p_top                The top value
 * @param p_zNear              The near value
 * @param p_zFar               The far value
 * @return constexpr Matrix4x4 The resulting perspective projection matrix
 */
constexpr Matrix4x4 	Matrix4x4::Perspective	(const float p_left,   const float p_right, 
                                                 const float p_bottom, const float p_top, 
                                                 const float p_zNear,  const float p_zFar) noexcept
{
    return Matrix4x4
    (
        (2.0f * p_zNear) / (p_right - p_left), 0.0f					                , (p_right+p_left)/(p_right-p_left) ,  0.0f,
        0.0f						         , (2.0f * p_zNear) / (p_top - p_bottom), (p_top+p_bottom)/(p_top-p_bottom) ,  0.0f,
        0.0f						         , 0.0f					                , (p_zFar+p_zNear)/(p_zFar-p_zNear) , -(2.0f * p_zNear * p_zFar) / (p_zFar - p_zNear),
        0.0f						         , 0.0f					                , 1.0f	    					    ,  0.0f
    );
}

/**
 * @brief Create a Rotation Matrix with a Quaternion
 * 
 * @param p_q Rotation Quaternion
 * @return constexpr Matrix4x4 Rotation Matrix
 */
constexpr Matrix4x4     Matrix4x4::Rotate       (const Quaternion& p_q) noexcept
{
    double sqrX  (p_q.m_x*p_q.m_x);
    double sqrY  (p_q.m_y*p_q.m_y);
    double sqrZ  (p_q.m_z*p_q.m_z);

    return Matrix4x4
    (
        1-2*(sqrY+sqrZ)                     , 2*(p_q.m_x*p_q.m_y-p_q.m_z*p_q.m_w)   , 2*(p_q.m_x*p_q.m_z+p_q.m_y*p_q.m_w)   , 0,
        2*(p_q.m_x*p_q.m_y+p_q.m_z*p_q.m_w) , 1-2*(sqrX+sqrZ)                       , 2*(p_q.m_y*p_q.m_z-p_q.m_x*p_q.m_w)   , 0,
        2*(p_q.m_x*p_q.m_z-p_q.m_y*p_q.m_w) , 2*(p_q.m_y*p_q.m_z+p_q.m_x*p_q.m_w)   , 1-2*(sqrX+sqrY)                       , 0,
        0                                   , 0                                     , 0                                     , 1
    );
}

/**
 * @brief Creates a scaling matrix
 * 
 * @param p_scale              The scale vector
 * @return constexpr Matrix4x4 The resulting scaling matrix
 */
constexpr Matrix4x4	    Matrix4x4::Scale		(const Vector3& p_scale) noexcept
{
    return Matrix4x4
    (
        p_scale.m_x, 0.0f		, 0.0f		 , 0.0f,
        0.0f	   , p_scale.m_y, 0.0f		 , 0.0f,
        0.0f	   , 0.0f		, p_scale.m_z, 0.0f,
        0.0f	   , 0.0f		, 0.0f		 , 1.0f
    ); 
}

/**
 * @brief Creates a scaling matrix
 * 
 * @param p_xScale             The scale vector's x value
 * @param p_yScale             The scale vector's y value
 * @param p_zScale             The scale vector's z value
 * @return constexpr Matrix4x4 The resulting scaling matrix
 */
constexpr Matrix4x4	    Matrix4x4::Scale		(const float p_xScale, const float p_yScale, const float p_zScale) noexcept
{
    return Matrix4x4
    (
        p_xScale, 0.0f    , 0.0f    , 0.0f,
        0.0f    , p_yScale, 0.0f    , 0.0f,
        0.0f	, 0.0f	  , p_zScale, 0.0f,
        0.0f	, 0.0f	  , 0.0f    , 1.0f
    );
}

/**
 * @brief Creates a translation matrix
 * 
 * @param p_translation        The translation vector
 * @return constexpr Matrix4x4 The resulting translation matrix
 */
constexpr Matrix4x4	    Matrix4x4::Translate	(const Vector3& p_translation) noexcept
{
    return Matrix4x4
    (
        1.0f, 0.0f, 0.0f, p_translation.m_x,
        0.0f, 1.0f, 0.0f, p_translation.m_y,
        0.0f, 0.0f, 1.0f, p_translation.m_z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

/**
 * @brief Creates a translation matrix
 * 
 * @param p_xTrans             The translation vector's x value
 * @param p_yTrans             The translation vector's y value
 * @param p_zTrans             The translation vector's z value
 * @return constexpr Matrix4x4 The resulting translation matrix
 */
constexpr Matrix4x4	    Matrix4x4::Translate	(const float p_xTrans, const float p_yTrans, const float p_zTrans) noexcept
{
    return Matrix4x4
    (
        1.0f, 0.0f, 0.0f, p_xTrans,
        0.0f, 1.0f, 0.0f, p_yTrans,
        0.0f, 0.0f, 1.0f, p_zTrans,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

/**
 * @brief Creates a translation, rotation and scaling matrix
 * 
 * @param p_translation        The translation vector
 * @param p_q                  The rotation Quaternion
 * @param p_scale              The scaling vector
 * @return constexpr Matrix4x4 The resulting translation, rotation and scaling matrix
 */
constexpr Matrix4x4	    Matrix4x4::TRS 			(const Vector3& p_translation, const Quaternion& p_q, const Vector3& p_scale) noexcept
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

    return translation * rotation * scale;
}


/*=========================[Constructors]=========================*/

/**
 * @brief Default constructor
 * 
 */
constexpr Matrix4x4::Matrix4x4  () noexcept
:    m_matrix {}
{
    for (int index = 0 ; index < 16 ; ++index)
        m_matrix[index] = 0.0f;
}

/**
 * @brief Constructor with 4D vectors
 * 
 */
constexpr Matrix4x4::Matrix4x4	(const Vector4& p_column1, const Vector4& p_column2, 
                                 const Vector4& p_column3, const Vector4& p_column4) noexcept
:   m_matrix {}
{
    m_matrix[0] = p_column1.m_x; m_matrix[4] = p_column2.m_x; m_matrix[8]  = p_column3.m_x; m_matrix[12] = p_column4.m_x;
    m_matrix[1] = p_column1.m_y; m_matrix[5] = p_column2.m_y; m_matrix[9]  = p_column3.m_y; m_matrix[13] = p_column4.m_y;
    m_matrix[2] = p_column1.m_z; m_matrix[6] = p_column2.m_z; m_matrix[10] = p_column3.m_z; m_matrix[14] = p_column4.m_z;
    m_matrix[3] = p_column1.m_w; m_matrix[7] = p_column2.m_w; m_matrix[11] = p_column3.m_w; m_matrix[15] = p_column4.m_w;
}

/**
 * @brief Constructor with specified members
 * 
 */
constexpr Matrix4x4::Matrix4x4	(const float p_m00, const float p_m01, const float p_m02, const float p_m03,
                                 const float p_m10, const float p_m11, const float p_m12, const float p_m13,
                                 const float p_m20, const float p_m21, const float p_m22, const float p_m23,
                                 const float p_m30, const float p_m31, const float p_m32, const float p_m33) noexcept
:   m_matrix {}
{
    m_matrix[0] = p_m00; m_matrix[4] = p_m01; m_matrix[8]  = p_m02; m_matrix[12] = p_m03;
    m_matrix[1] = p_m10; m_matrix[5] = p_m11; m_matrix[9]  = p_m12; m_matrix[13] = p_m13;
    m_matrix[2] = p_m20; m_matrix[6] = p_m21; m_matrix[10] = p_m22; m_matrix[14] = p_m23;
    m_matrix[3] = p_m30; m_matrix[7] = p_m31; m_matrix[11] = p_m32; m_matrix[15] = p_m33;
}

/**
 * @brief Copy constructor
 * 
 */
constexpr Matrix4x4::Matrix4x4	(const Matrix4x4& p_copy) noexcept
:   m_matrix {}
{
    for (int index = 0; index < 16; ++index)
        m_matrix[index] = p_copy[index];
}

/**
 * @brief Move constructor
 * 
 */
constexpr Matrix4x4::Matrix4x4  (Matrix4x4&& p_move) noexcept
:   m_matrix {}
{
    for (int index = 0; index < 16; ++index)
        m_matrix[index] = std::move(p_move[index]);
}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Returns the values of the current 4x4 matrix as an array
 * 
 * @return constexpr float* The resulting array
 */
constexpr float*        Matrix4x4::GetArray         () noexcept
{
    return m_matrix;
}

/**
 * @brief Creates the cofactor matrix of the current 4x4 matrix
 * 
 * @return constexpr Matrix4x4 The resulting cofactor matrix
 */
constexpr Matrix4x4	    Matrix4x4::GetCofactor	    () const noexcept
{
    return Matrix4x4
    (
         GetSubMatrix3x3(0, 0).GetDeterminant(), -GetSubMatrix3x3(0, 1).GetDeterminant(),  GetSubMatrix3x3(0, 2).GetDeterminant(), -GetSubMatrix3x3(0, 3).GetDeterminant(),
        -GetSubMatrix3x3(1, 0).GetDeterminant(),  GetSubMatrix3x3(1, 1).GetDeterminant(), -GetSubMatrix3x3(1, 2).GetDeterminant(),  GetSubMatrix3x3(1, 3).GetDeterminant(),
         GetSubMatrix3x3(2, 0).GetDeterminant(), -GetSubMatrix3x3(2, 1).GetDeterminant(),  GetSubMatrix3x3(2, 2).GetDeterminant(), -GetSubMatrix3x3(2, 3).GetDeterminant(),
        -GetSubMatrix3x3(3, 0).GetDeterminant(),  GetSubMatrix3x3(3, 1).GetDeterminant(), -GetSubMatrix3x3(3, 2).GetDeterminant(),  GetSubMatrix3x3(3, 3).GetDeterminant()
    );
}

/**
 * @brief Extracts the 4D vector corresponding to the column index
 * 
 * @param p_index            The column's index value
 * @return constexpr Vector4 The extracted vector
 */
constexpr Vector4		Matrix4x4::GetColumn	    (int p_index)	const
{
    return Vector4(m_matrix[(p_index    ) + p_index * 3], m_matrix[(p_index + 1) + p_index * 3], 
                   m_matrix[(p_index + 2) + p_index * 3], m_matrix[(p_index + 3) + p_index * 3]);
}

/**
 * @brief Calculates the determinant of the current 4x4 matrix
 * 
 * @return constexpr float The resulting determinant
 */
constexpr float		    Matrix4x4::GetDeterminant	()	const noexcept
{
    return	
    (
        m_matrix[0 ] * (m_matrix[5] * m_matrix[10] * m_matrix[15] - m_matrix[5] * m_matrix[14] * m_matrix[11] - m_matrix[9] * m_matrix[6] * m_matrix[15] + m_matrix[9] * m_matrix[14] * m_matrix[7] + m_matrix[13] * m_matrix[6] * m_matrix[11] - m_matrix[13] * m_matrix[10] * m_matrix[7]) -
        m_matrix[4 ] * (m_matrix[1] * m_matrix[10] * m_matrix[15] - m_matrix[1] * m_matrix[14] * m_matrix[11] - m_matrix[9] * m_matrix[2] * m_matrix[15] + m_matrix[9] * m_matrix[14] * m_matrix[3] + m_matrix[13] * m_matrix[2] * m_matrix[11] - m_matrix[13] * m_matrix[10] * m_matrix[3]) +
        m_matrix[8 ] * (m_matrix[1] * m_matrix[6 ] * m_matrix[15] - m_matrix[1] * m_matrix[14] * m_matrix[7 ] - m_matrix[5] * m_matrix[2] * m_matrix[15] + m_matrix[5] * m_matrix[14] * m_matrix[3] + m_matrix[13] * m_matrix[2] * m_matrix[7 ] - m_matrix[13] * m_matrix[6 ] * m_matrix[3]) -
        m_matrix[12] * (m_matrix[1] * m_matrix[6 ] * m_matrix[11] - m_matrix[1] * m_matrix[10] * m_matrix[7 ] - m_matrix[5] * m_matrix[2] * m_matrix[11] + m_matrix[5] * m_matrix[10] * m_matrix[3] + m_matrix[9 ] * m_matrix[2] * m_matrix[7 ] - m_matrix[9 ] * m_matrix[6 ] * m_matrix[3])  
    );
}

/**
 * @brief Creates the inverse of the current 4x4 matrix
 * 
 * @return constexpr Matrix4x4 The resulting inverted matrix
 */
constexpr Matrix4x4	    Matrix4x4::GetInverse		()	const noexcept
{
    float determinant (GetDeterminant());

    if (determinant == 0.0f)
        return *this;

    return GetCofactor().GetTranspose() / determinant;
}

/**
 * @brief Extracts the 4D vector corresponding to the row index
 * 
 * @param p_index            The row's index value
 * @return constexpr Vector4 The extracted vector
 */
constexpr Vector4 	    Matrix4x4::GetRow	        (int p_index) const
{
    return Vector4(m_matrix[p_index    ], m_matrix[p_index + 4 ], 
                   m_matrix[p_index + 8], m_matrix[p_index + 12]);
}

/**
 * @brief Creates the submatrix of the current 4x4 matrix ignoring a specific row and column
 * 
 * @param row                  The row's index value to ignore
 * @param column               The column's index value to ignore
 * @return constexpr Matrix4x4 The resulting submatrix
 */
constexpr Matrix4x4	    Matrix4x4::GetSubMatrix3x3	(const int row, const int column) const
{
    if (row >= 4 || column >= 4)
        throw std::out_of_range("No value available!");

    Matrix4x4 m (Matrix4x4::Identity);
    int       k (0);

    for (int i = 0 ; i < 3 ; ++i)
    {
        int l (0);

        if (i == row)
            k = 1;

        for (int j = 0 ; j < 3 ; ++j)
        {
            if (j == column) 
                l = 1;

            m(i, j) = m_matrix[(i + k) + (j + l) * 4];
        }
    }

    return m;
}

/**
 * @brief Creates the transpose of the current 4x4 matrix
 * 
 * @return constexpr Matrix4x4 The resulting transposed matrix
 */
constexpr Matrix4x4 	Matrix4x4::GetTranspose	    () const noexcept
{
    return Matrix4x4
    (
        m_matrix[0 ], m_matrix[1 ], m_matrix[2 ], m_matrix[3 ], 
        m_matrix[4 ], m_matrix[5 ], m_matrix[6 ], m_matrix[7 ], 
        m_matrix[8 ], m_matrix[9 ], m_matrix[10], m_matrix[11], 
        m_matrix[12], m_matrix[13], m_matrix[14], m_matrix[15] 
    );
}

/**
 * @brief Checks if this 4x4 matrix is an identity matrix
 * 
 * @return true  This is an identity matrix
 * @return false This is not an identity matrix
 */
constexpr bool 		    Matrix4x4::IsIdentity   	() const noexcept
{
    return 
    (
        m_matrix[0]	== 1.0f && m_matrix[4] == 0.0f && m_matrix[8 ] == 0.0f && m_matrix[12] == 0.0f &&
        m_matrix[1]	== 0.0f && m_matrix[5] == 1.0f && m_matrix[9 ] == 0.0f && m_matrix[13] == 0.0f &&
        m_matrix[2] == 0.0f && m_matrix[6] == 0.0f && m_matrix[10] == 1.0f && m_matrix[14] == 0.0f &&
        m_matrix[3] == 0.0f && m_matrix[7] == 0.0f && m_matrix[11] == 0.0f && m_matrix[15] == 1.0f                
    );
}

/**
 * @brief Converts the current 4x4 matrix to a string
 * 
 * @return std::string The resulting string of the conversion
 */
inline std::string      Matrix4x4::ToString         () const noexcept
{
    return std::string(std::to_string(m_matrix[0 ]) + "\t|\t" + std::to_string(m_matrix[4 ]) + "\t|\t" + 
                       std::to_string(m_matrix[8 ]) + "\t|\t" + std::to_string(m_matrix[12]) + "\n"    +
                       std::to_string(m_matrix[1 ]) + "\t|\t" + std::to_string(m_matrix[5 ]) + "\t|\t" + 
                       std::to_string(m_matrix[9 ]) + "\t|\t" + std::to_string(m_matrix[13]) + "\n"    +
                       std::to_string(m_matrix[2 ]) + "\t|\t" + std::to_string(m_matrix[6 ]) + "\t|\t" + 
                       std::to_string(m_matrix[10]) + "\t|\t" + std::to_string(m_matrix[14]) + "\n"    +
                       std::to_string(m_matrix[3 ]) + "\t|\t" + std::to_string(m_matrix[7 ]) + "\t|\t" + 
                       std::to_string(m_matrix[11]) + "\t|\t" + std::to_string(m_matrix[15]) + "\n");
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move                The matrix to move
 * @return constexpr Matrix4x4& The moved matrix
 */
constexpr Matrix4x4&    Matrix4x4::operator=    (Matrix4x4&& p_move) noexcept
{
    for (int index = 0; index < 16; ++index)
        m_matrix[index] = std::move(p_move[index]);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy                The matrix to copy
 * @return constexpr Matrix4x4& The copied matrix
 */
constexpr Matrix4x4& 	Matrix4x4::operator=    (const Matrix4x4& p_copy) noexcept
{
    for (int index = 0; index < 16; ++index)
        m_matrix[index] = p_copy[index];

    return *this;	
}

/**
 * @brief Read only accessor
 * 
 * @param p_row            The row's index value
 * @param p_column         The column's index value
 * @return constexpr float The value to read
 */
constexpr float 		Matrix4x4::operator()	(const int p_row, const int p_column) const
{
    return m_matrix[p_row + p_column * 4];
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_row             The row's index value
 * @param p_column          The column's index value
 * @return constexpr float& The value to modify
 */
constexpr float&     	Matrix4x4::operator()	(const int p_row, const int p_column)
{
    return m_matrix[p_row + p_column * 4];
}

/**
 * @brief Read only accessor
 * 
 * @param p_index          The index value
 * @return constexpr float The value to read
 */
constexpr float     	Matrix4x4::operator()	(const int p_index) const
{
    return m_matrix[p_index];
}

/**
 * @brief Modifiable accesor
 * 
 * @param p_index           The index value
 * @return constexpr float& The value to modify
 */
constexpr float&     	Matrix4x4::operator()	(const int p_index)
{
    return m_matrix[p_index];
}

/**
 * @brief Read only accessor
 * 
 * @param p_index          The index value
 * @return constexpr float The value to read
 */
constexpr float     	Matrix4x4::operator[]	(const int p_index) const
{
    return m_matrix[p_index];
}

/**
 * @brief Modifiable accesor
 * 
 * @param p_index           The index value
 * @return constexpr float& The value to modify
 */
constexpr float&     	Matrix4x4::operator[]	(const int p_index)
{
    return m_matrix[p_index];
}

/*=========================[General Operators]=========================*/

/**
 * @brief Checks if two 4x4 matrices are equal
 * 
 * @param p_a    The left handed matrix
 * @param p_b    The light handed matrix
 * @return true  The matrices are approximately equal
 * @return false The matrices are not equal
 */
constexpr bool 			Maths::operator==	(const Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    double epsilon (__DBL_EPSILON__ * __DBL_EPSILON__);

    for (int index = 0; index < 16; ++index)
    {
        double value ((p_a[index] - p_b[index]) * (p_a[index] - p_b[index]));

        if (value > epsilon)
            return false;
    }

    return true;
}

/**
 * @brief Checks if two 4x4 matrices are different
 * 
 * @param p_a    The left handed matrix
 * @param p_b    The right handed matrix
 * @return true  The matrices are not equal
 * @return false The matrices are approximately equal
 */
constexpr bool 			Maths::operator!=	(const Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    double epsilon (__DBL_EPSILON__ * __DBL_EPSILON__);

    for (int index = 0; index < 16; ++index)
    {
        double value ((p_a[index] - p_b[index]) * (p_a[index] - p_b[index]));

        if (value > epsilon)
            return true;
    }

    return false;
}

/**
 * @brief Adds two 4x4 matrices
 * 
 * @param p_a                  The left handed matrix
 * @param p_b                  The right handed matrix
 * @return constexpr Matrix4x4 The resulting matrix of the addition
 */
constexpr Matrix4x4		Maths::operator+	(const Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    Matrix4x4 result;

    for (int index = 0; index < 16; ++index)
        result[index] = p_a[index] + p_b[index];

    return result;		
}

/**
 * @brief Adds a 4x4 matrix to the current one
 * 
 * @param p_a                   The target matrix
 * @param p_b                   The matrix to add
 * @return constexpr Matrix4x4& The resulting matrix of the addition
 */
constexpr Matrix4x4&	Maths::operator+=	(Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    for (int index = 0; index < 16; ++index)
        p_a[index] += p_b[index];

    return p_a;
}

/**
 * @brief Computes the opposite matrix of the current 4x4 matrix
 * 
 * @param p_a                   The target matrix
 * @return constexpr Matrix4x4& The opposite matrix
 */
constexpr Matrix4x4&	Maths::operator-	(Matrix4x4& p_a) noexcept
{
    for (int i = 0 ; i < 16 ; ++i)
        p_a[i] = -p_a[i];

    return p_a;
}

/**
 * @brief Substracts a 4x4 matrix from another one
 * 
 * @param p_a                   The target matrix
 * @param p_b                   The matrix to substract
 * @return constexpr Matrix4x4& The resulting matrix of the substraction
 */
constexpr Matrix4x4		Maths::operator-	(const Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    Matrix4x4 result;

    for (int index = 0; index < 16; ++index)
        result[index] = p_a[index] - p_b[index];

    return result;		
}

/**
 * @brief Substracts a 4x4 matrix to the current one
 * 
 * @param p_a                   The target matrix
 * @param p_b                   The matrix to substract
 * @return constexpr Matrix4x4& The resulting matrix of the substraction
 */
constexpr Matrix4x4&	Maths::operator-=	(Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    for (int index = 0; index < 16; ++index)
        p_a[index] -= p_b[index];

    return p_a;
}

/**
 * @brief Multiplies a 4x4 matrix by another one
 * 
 * @param p_a                  The target matrix
 * @param p_b                  The matrix to multiply
 * @return constexpr Matrix4x4 The resulting matrix of the multiplication
 */
constexpr Matrix4x4  	Maths::operator*	(const Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            for (int i = 0; i < 4; ++i)
                result(row, column) += p_a(row, i) * p_b(i, column);

    return result;
}

/**
 * @brief Multiplies the current 4x4 matrix by another one
 * 
 * @param p_a                   The target matrix
 * @param p_b                   The matrix to multiply
 * @return constexpr Matrix4x4& The resulting matrix of the multiplication
 */
constexpr Matrix4x4&  	Maths::operator*=	(Matrix4x4& p_a, const Matrix4x4& p_b) noexcept
{
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            for (int i = 0; i < 4; ++i)
                result(row, column) += p_a(row, i) * p_b(i, column);

    return p_a = std::move(result);
}

/**
 * @brief Multiplies a 4x4 matrix by a number
 * 
 * @param p_k                  The value to multiply
 * @param p_a                  The target matrix
 * @return constexpr Matrix4x4 The resulting matrix of the multiplication
 */
constexpr Matrix4x4 	Maths::operator*	(const float p_k, const Matrix4x4& p_a) noexcept
{
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            result(row, column) = p_k * p_a(row, column);

    return result;
}

/**
 * @brief Multiplies a 4x4 matrix by a number
 * 
 * @param p_a                  The target matrix
 * @param p_k                  The value to multiply
 * @return constexpr Matrix4x4 The resulting matrix of the multiplication
 */
constexpr Matrix4x4 	Maths::operator*	(const Matrix4x4& p_a, const float p_k) noexcept
{
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            result(row, column) = p_k * p_a(row, column);

    return result;
}

/**
 * @brief Multiplies the current 4x4 matrix by a number
 * 
 * @param p_a                   The target matrix
 * @param p_k                   The value to multiply
 * @return constexpr Matrix4x4& The resulting matrix of the multiplication
 */
constexpr Matrix4x4& 	Maths::operator*=	(Matrix4x4& p_a, const float p_k) noexcept
{
    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            p_a(row, column) *= p_k;

    return p_a;
}

/**
 * @brief Multiplies a 4x4 matrix by a 3D vector
 * 
 * @param p_m                The target matrix
 * @param p_v                The vector to multiply
 * @return constexpr Vector3 The resulting vecor of the multiplication
 */
constexpr Vector3		Maths::operator*	(const Matrix4x4& p_m, const Vector3& p_v) noexcept
{
    float w (p_m(3, 0) * p_v.m_x + p_m(3, 1) * p_v.m_y + p_m(3, 2) * p_v.m_z + p_m(3, 3));

    return Vector3
    (
        p_m(0, 0) * p_v.m_x + p_m(0, 1) * p_v.m_y + p_m(0, 2) * p_v.m_z + p_m(0, 3), 
        p_m(1, 0) * p_v.m_x + p_m(1, 1) * p_v.m_y + p_m(1, 2) * p_v.m_z + p_m(1, 3), 
        p_m(2, 0) * p_v.m_x + p_m(2, 1) * p_v.m_y + p_m(2, 2) * p_v.m_z + p_m(2, 3)
    ) / w;
}

/**
 * @brief Multiplies a 4x4 matrix by a 4D vector
 * 
 * @param p_m                The target matrix
 * @param p_v                The ector to multiply
 * @return constexpr Vector4 The resulting vector of the multiplication
 */
constexpr Vector4 		Maths::operator*	(const Matrix4x4& p_m, const Vector4& p_v) noexcept
{
    return Vector4
    (
        p_m(0, 0) * p_v.m_x + p_m(0, 1) * p_v.m_y + p_m(0, 2) * p_v.m_z + p_m(0, 3) * p_v.m_w, 
        p_m(1, 0) * p_v.m_x + p_m(1, 1) * p_v.m_y + p_m(1, 2) * p_v.m_z + p_m(1, 3) * p_v.m_w,   
        p_m(2, 0) * p_v.m_x + p_m(2, 1) * p_v.m_y + p_m(2, 2) * p_v.m_z + p_m(2, 3) * p_v.m_w,   
        p_m(3, 0) * p_v.m_x + p_m(3, 1) * p_v.m_y + p_m(3, 2) * p_v.m_z + p_m(3, 3) * p_v.m_w
    );
}

/**
 * @brief Divides a 4x4 matrix by another one
 * 
 * @param p_a                  The target matrix
 * @param p_b                  The matrix to divide
 * @return constexpr Matrix4x4 The resulting matrix of the division
 */
[[deprecated("This operator is not implemented yet!")]]
constexpr Matrix4x4		Maths::operator/	(const Matrix4x4& p_a, const Matrix4x4& p_b)
{
    (void)p_a;
    (void)p_b;

    return Matrix4x4::Zero;
}

/**
 * @brief Divides a 4x4 matrix by a number
 * 
 * @param p_a                  The target matrix
 * @param p_k                  The value to divide
 * @return constexpr Matrix4x4 The resulting matrix of the division
 */
constexpr Matrix4x4		Maths::operator/	(const Matrix4x4& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            result(row, column) =  p_a(row, column) / p_k;

    return result;
}

/**
 * @brief Divides the current 4x4 matrix by another one
 * 
 * @param p_a                   The target matrix
 * @param p_b                   The matrix to divide
 * @return constexpr Matrix4x4& The resulting matrix of the division
 */
[[deprecated("This operator is not implemented yet!")]]
constexpr Matrix4x4&    Maths::operator/=   (Matrix4x4& p_a, const Matrix4x4& p_b)
{
    (void)p_b;

    return p_a;
}

/**
 * @brief Divides this 4x4 matrix by a number
 * 
 * @param p_a                   The target matrix
 * @param p_k                   The value to divide
 * @return constexpr Matrix4x4& The resulting matrix of the division
 */
constexpr Matrix4x4&	Maths::operator/=	(Matrix4x4& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            p_a(row, column) /= p_k;

    return p_a;
}

/**
 * @brief Converts a 4x4 matrix to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target matrix
 * @return std::ostream& The resulting stream of the conversion
 */
inline std::ostream&    Maths::operator<<   (std::ostream& p_flux, const Matrix4x4& p_a) noexcept
{
    return p_flux	<< std::fixed 
                    << p_a(0)  << "  " << p_a(4) << "  "  << p_a(8)  << "  " << p_a(12) << "  " << "\n"
                    << p_a(1)  << "  " << p_a(5) << "  "  << p_a(9)  << "  " << p_a(13) << "  " << "\n"
                    << p_a(2)  << "  " << p_a(6) << "  "  << p_a(10) << "  " << p_a(14) << "  " << "\n"
                    << p_a(3)  << "  " << p_a(7) << "  "  << p_a(11) << "  " << p_a(15) << "  " 
                    << std::defaultfloat <<std::endl;
}

#endif // !__MATRIX_4x4_INL__