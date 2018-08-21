#ifndef __VECTOR_4_HPP__
#define __VECTOR_4_HPP__

/**
 * @file     Vector4.hpp
 * @brief    Include file for Vector4
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GVector4 Vector4
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector2;
    class Vector3;

    class Vector4
    {
        /**
         * @class Maths::Vector4 Vector4.hpp Vector4.cpp Vector4.inl
         * @brief Used for 4D vectors
         * 
         * @ingroup GVector4
         * 
         */

        public:
        // Static Properties (Public) //
            static const    Vector4 One;  ///< Shorthand for writing Vector4(1.0f, 1.0f, 1.0f, 1.0f)
            static const    Vector4 Zero; ///< Shorthand for writing Vector4(0.0f, 0.0f, 0.0f, 0.0f)

        // Static Methods (Public) //
            constexpr static    float	    Distance		(const Vector4& p_a, const Vector4& p_b)                    noexcept;
            constexpr static    float	    DistanceSqr		(const Vector4& p_a, const Vector4& p_b)                    noexcept;
            constexpr static    float       Dot				(const Vector4& p_a, const Vector4& p_b)                    noexcept;

            constexpr static    Vector4     Lerp			(const Vector4& p_a, const Vector4& p_b, const float p_t)   noexcept;
            constexpr static    Vector4 	LerpUnclamped	(const Vector4& p_a, const Vector4& p_b, const float p_t)   noexcept;

            constexpr static    Vector4 	Max				(const Vector4& p_a, const Vector4& p_b)                    noexcept;
            constexpr static    Vector4 	Min				(const Vector4& p_a, const Vector4& p_b)                    noexcept;

            constexpr static    Vector4 	MoveTowards		(const Vector4& p_current, 
                                                             const Vector4& p_target, 
                                                             const float    p_maxDistanceDelta)                         noexcept;

            constexpr static    Vector4 	Project			(const Vector4& p_vector, const Vector4& p_onNormal)        noexcept;
            constexpr static    Vector4 	Scale			(const Vector4& p_a,      const Vector4& p_b)               noexcept;

        // Local Variables (Public) //
            float   m_x; ///< The x value
            float   m_y; ///< The y value
            float   m_z; ///< The z value
            float   m_w; ///< The w value

        // Constructors + Destructor //
            constexpr   Vector4	    ()                                              noexcept;
            constexpr   Vector4	    (const float p_x, 
                                     const float p_y, 
                                     const float p_z, 
                                     const float p_w = 1.0f)                        noexcept;
            constexpr   Vector4	    (const float p_value)                           noexcept;
            constexpr   Vector4	    (const Vector4& p_a, const Vector4& p_b)        noexcept;
            constexpr   Vector4	    (const Vector2& p_copy)                         noexcept;
            constexpr   Vector4	    (const Vector3& p_copy, const float p_w = 1)    noexcept;
            constexpr   Vector4	    (const Vector4& p_copy)                         noexcept;
            constexpr   Vector4	    (Vector4&& p_move)                              noexcept;

            ~Vector4() noexcept = default;

        // Local Methods (Public) //
            constexpr   Vector4 	GetHomogenize	()                  const;
            constexpr   float 		GetMagnitude	()                  const noexcept;
            constexpr   Vector4 	GetNormalize	()                  const noexcept;
            constexpr   float 		GetSqrMagnitude	()                  const noexcept;
            constexpr   Vector4 	Homogenize		();
            constexpr   Vector4 	Normalize		()                        noexcept;
            constexpr   Vector4 	Set				(const float p_x, 
                                                     const float p_y, 
                                                     const float p_z, 
                                                     const float p_w)         noexcept;
            
            inline      std::string ToString		()                  const noexcept;

        // Local Operators (Public) //
            constexpr   Vector4&    operator=   (Vector4&& p_move)          noexcept;

            constexpr   Vector4&    operator=	(const Vector2& p_copy)     noexcept;
            constexpr   Vector4&	operator=	(const Vector3& p_copy)     noexcept;
            constexpr   Vector4&	operator=	(const Vector4& p_copy)     noexcept;

            constexpr   float 	    operator[]	(const int p_index)	        const;
            constexpr   float&	    operator[]	(const int p_index);
    };
    
        // General Operators //
            constexpr   bool            operator==  (const Vector4& p_a, const Vector4& p_b)    noexcept;
            constexpr   bool            operator!=  (const Vector4& p_a, const Vector4& p_b)    noexcept;

            constexpr   Vector4&        operator++  (Vector4& p_a)                              noexcept;
            constexpr   Vector4&        operator--  (Vector4& p_a)                              noexcept;

            constexpr   Vector4         operator+   (const Vector4& p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4         operator+   (const Vector4& p_a, const float    p_k)    noexcept;
            constexpr   Vector4         operator+   (const float    p_k, const Vector4& p_a)    noexcept;
            constexpr   Vector4&        operator+=  (Vector4&       p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4&        operator+=  (Vector4&       p_a, const float    p_k)    noexcept;

            constexpr   Vector4         operator-   (const Vector4& p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4         operator-   (const Vector4& p_a, const float    p_k)    noexcept;
            constexpr   Vector4         operator-   (const Vector4& p_a)                        noexcept;
            constexpr   Vector4&        operator-=  (Vector4&       p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4&        operator-=  (Vector4&       p_a, const float    p_k)    noexcept;

            constexpr   Vector4         operator*   (const Vector4& p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4         operator*   (const float    p_k, const Vector4& p_a)    noexcept;
            constexpr   Vector4         operator*   (const Vector4& p_a, const float    p_k)    noexcept;
            constexpr   Vector4&        operator*=  (Vector4&       p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4&        operator*=  (Vector4&       p_a, const float    p_k)    noexcept;

            constexpr   Vector4         operator/   (const Vector4& p_a, const Vector4& p_b);            
            constexpr   Vector4         operator/   (const Vector4& p_a, const float    p_k);
            constexpr   Vector4&        operator/=  (Vector4&       p_a, const Vector4& p_b);
            constexpr   Vector4&        operator/=  (Vector4&       p_a, const float    p_k);  
  
            constexpr   Vector4         operator%   (const Vector4& p_a, const Vector4& p_b)    noexcept;            
            constexpr   Vector4         operator%   (const Vector4& p_a, const float    p_k)    noexcept;
            constexpr   Vector4&        operator%=  (Vector4&       p_a, const Vector4& p_b)    noexcept;
            constexpr   Vector4&        operator%=  (Vector4&       p_a, const float    p_k)    noexcept;

            inline      std::ostream&   operator<<  (std::ostream& p_flux, const Vector4& p_a)  noexcept;
}

#include "../Inlines/Vector4.inl"

#endif // !__VECTOR_4_HPP__