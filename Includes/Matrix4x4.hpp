#ifndef __MATRIX_4X4_HPP__
#define __MATRIX_4X4_HPP__

/**
 * @file     Matrix4x4.hpp
 * @brief    Include file for Matrix4x4
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GMatrix4x4 Matrix4x4
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class Vector4;
    class Quaternion;

    class Matrix4x4
    {
        /**
         * @class Maths::Matrix4x4 Matrix4x4.hpp Matrix4x4.cpp Matrix4x4.inl
         * @brief Used for 4x4 matrices
         * 
         * @ingroup GMatrix4x4
         * 
         */

        private:
        // Local Variables (Private) //
            float m_matrix[16];

        public:
        // Static Properties (Public) //
            static const    Matrix4x4 Identity; ///< Shorthand writing for the identity matrix
            static const    Matrix4x4 Zero;     ///< Shorthand writing for a matrix with all elements set to zero

        // Static Methods (Public) //
            static  constexpr   Matrix4x4	LookAt		(const Vector3& p_from,  const Vector3& p_to,    const Vector3& p_up)               noexcept;
            static  constexpr   Matrix4x4	LookAt		(const float    p_fromX, const float    p_fromY, const float    p_fromZ, 
                                                         const float    p_toX,   const float    p_toY,   const float    p_toZ, 
                                                         const float    p_upX,   const float    p_upY,   const float    p_upZ)              noexcept;

            static  constexpr   Matrix4x4 	Ortho		(const float p_left, const float p_right, const float p_bottom, 
                                                         const float p_top,  const float p_zNear, const float p_zFar)                       noexcept;
            static  constexpr   Matrix4x4 	Perspective	(const float p_left, const float p_right, const float p_bottom,
                                                         const float p_top,  const float p_zNear, const float p_zFar)                       noexcept;

            static  constexpr   Matrix4x4   Rotate      (const Quaternion& p_q)                                                             noexcept;

            static  constexpr   Matrix4x4	Scale		(const Vector3& p_scale)                                                            noexcept;
            static  constexpr   Matrix4x4	Scale		(const float    p_xScale, const float p_yScale, const float p_zScale)               noexcept;

            static  constexpr   Matrix4x4	Translate	(const Vector3&p_translation)                                                       noexcept;
            static  constexpr   Matrix4x4	Translate	(const float     p_xTrans, const float p_yTrans, const float p_zTrans)              noexcept;

            static  constexpr   Matrix4x4	TRS 		(const Vector3& p_tranlation, const Quaternion& p_q, const Vector3& p_scale)        noexcept;

        // Constructors + Destructor //
            constexpr   Matrix4x4	()                                                                              noexcept;
            constexpr   Matrix4x4	(const Vector4& p_column1, const Vector4& p_column2, 
                                     const Vector4& p_column3, const Vector4& p_column4)                            noexcept;
            constexpr   Matrix4x4	(const float p_m00, const float p_m01, const float p_m02, const float p_m03,
                                     const float p_m10, const float p_m11, const float p_m12, const float p_m13,
                                     const float p_m20, const float p_m21, const float p_m22, const float p_m23,
                                     const float p_m30, const float p_m31, const float p_m32, const float p_m33)    noexcept;
            constexpr   Matrix4x4	(const Matrix4x4& p_copy)                                                       noexcept;
            constexpr   Matrix4x4   (Matrix4x4&&      p_move)                                                       noexcept;
            
            ~Matrix4x4() noexcept = default;

        // Local Methods (Public) //
            constexpr   float*		    GetArray 	    ()                                            noexcept;
            constexpr   Matrix4x4       GetCofactor		()							            const noexcept;  
            constexpr   Vector4 	    GetColumn	    (const int p_index) 					const;
            constexpr   float 	        GetDeterminant	()										const noexcept; 
            constexpr   Matrix4x4	    GetInverse		()										const noexcept;
            constexpr   Vector4 		GetRow		    (const int p_index)						const;
            constexpr   Matrix4x4	    GetSubMatrix3x3 (const int p_row, const int p_column) 	const;
            constexpr   Matrix4x4       GetTranspose 	()  									const noexcept;
            constexpr   bool   		    IsIdentity		()										const noexcept;  

            void		                SetColumn	    (int p_index, const Vector4& p_column);
            void			            SetRow		    (int p_index, const Vector4& p_row);
            void 			            SetTRS		    (const Vector3& p_translation, 
                                                         const Quaternion& p_q, 
                                                         const Vector3& p_scale)                      noexcept;

            inline      std::string     ToString		()                                      const noexcept;
            
        // Local Operators (Public) //	
            constexpr   Matrix4x4&  operator=   (Matrix4x4&& p_move)                    noexcept;

            constexpr   Matrix4x4&	operator=	(const Matrix4x4& p_copy)               noexcept;

            constexpr   float		operator()	(const int p_row, const int p_column)	const;
            constexpr   float& 		operator()	(const int p_row, const int p_column);

            constexpr   float 		operator()	(const int p_index)						const;
            constexpr   float& 		operator()	(const int p_index);

            constexpr   float 		operator[]	(const int p_index)						const;
            constexpr   float& 		operator[]	(const int p_index);
    };

        // General Operators //
            constexpr   bool 			operator==  (const Matrix4x4& p_a, const Matrix4x4& p_b)    noexcept;
            constexpr   bool 			operator!=	(const Matrix4x4& p_a, const Matrix4x4& p_b)    noexcept;

            constexpr   Matrix4x4		operator+	(const Matrix4x4& p_a, const Matrix4x4& p_b)    noexcept;
            constexpr   Matrix4x4&		operator+=	(Matrix4x4&       p_a, const Matrix4x4& p_b)    noexcept;

            constexpr   Matrix4x4&		operator-	(Matrix4x4&       p_a)                          noexcept;
            constexpr   Matrix4x4		operator-	(const Matrix4x4& p_a, const Matrix4x4& p_b)    noexcept;
            constexpr   Matrix4x4&		operator-=	(Matrix4x4&       p_a, const Matrix4x4& p_b)    noexcept;

            constexpr   Matrix4x4  		operator*   (const Matrix4x4& p_a, const Matrix4x4& p_b)    noexcept;
            constexpr   Matrix4x4&  	operator*=  (Matrix4x4&       p_a, const Matrix4x4& p_b)    noexcept;
            constexpr   Matrix4x4  		operator*   (const float      p_k, const Matrix4x4& p_a)    noexcept;
            constexpr   Matrix4x4  		operator*   (const Matrix4x4& p_a, const float      p_k)    noexcept;
            constexpr   Matrix4x4& 		operator*=  (Matrix4x4&       p_a, const float      p_k)    noexcept;

            constexpr   Matrix4x4		operator/	(const Matrix4x4& p_a, const Matrix4x4& p_b);
            constexpr   Matrix4x4		operator/	(const Matrix4x4& p_a, const float      p_k);
            constexpr   Matrix4x4&		operator/=	(Matrix4x4&       p_a, const Matrix4x4& p_b);
            constexpr   Matrix4x4&		operator/=	(Matrix4x4&       p_a, const float      p_k);

            constexpr   Vector3			operator*	(const Matrix4x4& p_m, const Vector3&   p_v)    noexcept;
            constexpr   Vector4			operator*	(const Matrix4x4& p_m, const Vector4&   p_v)    noexcept;

            inline      std::ostream&	operator<<	(std::ostream& flux, const Matrix4x4& p_a)      noexcept;
}

#include "../Inlines/Matrix4x4.inl"

#endif // !__MATRIX_4X4_HPP__