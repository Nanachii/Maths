#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

/**
 * @file     Matrix.hpp
 * @brief    Include file for Matrix
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GMatrix Matrix
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector2;
    class Vector3;
    class Vector4;

    class Matrix
    {
        /**
         * @class Maths::Matrix Matrix.hpp Matrix.cpp
         * @brief Used for general matrices
         * 
         * @ingroup GMatrix
         * 
         */
        
        private:
        // Local Variables (private) //
            int	    m_row;
            int 	m_column;
            float*  m_matrix;

        public:
        // Constructors + Destructor //
            Matrix  ()                                      noexcept;
            Matrix  (const int p_row, const int p_column)   noexcept;
            Matrix  (const int p_squareSize)                noexcept;
            Matrix  (const Vector2& p_vector2)              noexcept;
            Matrix  (const Vector3& p_vector3)              noexcept;
            Matrix  (const Vector4& p_vector4)              noexcept;
            Matrix  (const Matrix&  p_copy)                 noexcept;
            Matrix  (Matrix&&       p_move)                 noexcept;

            ~Matrix() noexcept;

        // Local Methods (Public) //
            float*	        GetArray        ()                                      const noexcept;
            Matrix  	    GetCofactor     ()					                    const noexcept;
            int		        GetColumn       ()                                  	const noexcept;
            float   	    GetDeterminant  ()				                        const noexcept;
            Matrix  	    GetInverse      ()					                    const noexcept;
            int		        GetRow          ()                                  	const noexcept;
            Matrix  	    GetSubMatrix    (const int p_row, const int p_column)	const;
            Matrix  	    GetTranspose    ()					                    const noexcept;

            std::string     ToString        ()                                      const noexcept;

        // Local Operators (Public) //
            Matrix& operator=   (Matrix&& p_move);

            Matrix& operator=   (const Matrix& p_copy);

            float   operator()  (const int p_row, const int p_column)	const;
            float&  operator() 	(const int p_row, const int p_column);

            float   operator() 	(const int p_index)                     const;
            float&  operator() 	(const int p_index);

            float   operator[] 	(const int p_index)                     const;
            float&  operator[] 	(const int p_index);
        };

        // General Operators //
            bool		    operator==  (const Matrix& p_a, const Matrix& p_b);
            bool		    operator!=  (const Matrix& p_a, const Matrix& p_b);

            Matrix  	    operator+   (const Matrix& p_a, const Matrix& p_b);
            Matrix& 	    operator+=	(Matrix&       p_a, const Matrix& p_b);

            Matrix&  	    operator-   (Matrix&       p_a)                         noexcept;
            Matrix  	    operator-   (const Matrix& p_a, const Matrix& p_b);
            Matrix& 	    operator-=	(Matrix&       p_a, const Matrix& p_b);

            Matrix  	    operator*   (const Matrix& p_a, const Matrix& p_b);
            Matrix&  	    operator*=  (Matrix&       p_a, const Matrix& p_b);

            Matrix  	    operator*   (const Matrix& p_a, const float   p_k)      noexcept;
            Matrix  	    operator*  	(const float   p_k, const Matrix& p_m)      noexcept;
            Matrix& 	    operator*= 	(Matrix&       p_m, const float   p_k)      noexcept;

            Matrix  	    operator/   (const Matrix& p_a, const Matrix& p_b);
            Matrix  	    operator/  	(const Matrix& p_a, const float   p_k);
            Matrix&         operator/=  (Matrix&       p_a, const Matrix& p_b);
            Matrix&         operator/= 	(Matrix&       p_m, const float   p_k);

            std::ostream&   operator<<  (std::ostream& p_flux, const Matrix& p_a)   noexcept;
}

#endif // !__MATRIX_HPP__