#ifndef __VECTOR_2_HPP__
#define __VECTOR_2_HPP__

/**
 * @file     Vector2.hpp
 * @brief    Include file for Vector2
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GVector2 Vector2
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class Vector4;
    
    class Vector2
    {
        /**
         * @class Maths::Vector2 Vector2.hpp Vector2.cpp Vector2.inl
         * @brief Used for 2D vectors
         * 
         * @ingroup GVector2
         * 
         */

        public:
        // Static properties (Public) //
            static const    Vector2 Up;    ///< Shorthand writing for Vector2(0.0f, 1.0f)
            static const    Vector2 Down;  ///< Shorthand writing for Vector2(0.0f, -1.0f)

            static const    Vector2 Right; ///< Shorthand writing for Vector2(1.0f, 0.0f)
            static const    Vector2 Left;  ///< Shorthand writing for Vector2(-1.0f, 0.0f)

            static const    Vector2 One;   ///< Shorthand writing for Vector2(1.0f, 1.0f)
            static const    Vector2 Zero;  ///< Shorthand writing for Vector2(0.0f, 0.0f)

        // Static Methods (Public) //
            static constexpr    float   AngleDegree         (const Vector2& p_from, const Vector2& p_to);
            static constexpr    float   AngleRadian         (const Vector2& p_from, const Vector2& p_to);

            static constexpr    Vector2 ClampMagnitude		(const Vector2& p_vector, const float p_maxLength)          noexcept;

            static constexpr    float   Distance            (const Vector2& p_a, const Vector2& p_b)                    noexcept;
            static constexpr    float   DistanceSqr         (const Vector2& p_a, const Vector2& p_b)                    noexcept;
            static constexpr    float   Dot                 (const Vector2& p_a, const Vector2& p_b)                    noexcept;
            static constexpr    bool    IsColinear          (const Vector2& p_a, const Vector2& p_b)                    noexcept;

            static constexpr    Vector2 LerpUnclamped       (const Vector2& p_a, const Vector2& p_b, const float p_t)   noexcept;
            static constexpr    Vector2 Lerp                (const Vector2& p_a, const Vector2& p_b, const float p_t)   noexcept;

            static constexpr    Vector2 Max                 (const Vector2& p_a, const Vector2& p_b)                    noexcept;
            static constexpr    Vector2 Min                 (const Vector2& p_a, const Vector2& p_b)                    noexcept;

            static constexpr    Vector2 MoveTowards         (const Vector2& p_current, 
                                                             const Vector2& p_target, 
                                                             const float    p_maxDistanceDelta)                         noexcept;

            static constexpr    Vector2 Project             (const Vector2& p_vector,    const Vector2& p_onNormal)     noexcept;
            static constexpr    Vector2 Reflect             (const Vector2& p_direction, const Vector2& p_normal);
            static constexpr    Vector2 ReflectInvert       (const Vector2& p_direction, const Vector2& p_normal);

            static constexpr    Vector2 Scale               (const Vector2& p_a, const Vector2& p_b)                    noexcept;

            static constexpr    float   SignedAngleDegree   (const Vector2& p_from, const Vector2& p_to);
            static constexpr    float   SignedAngleRadian   (const Vector2& p_from, const Vector2& p_to);

        // Local Variables (Public) //
            float   m_x; ///< The x value
            float   m_y; ///< The y value

        // Constructors + Destructor //
            constexpr   Vector2   ()                                              noexcept;
            constexpr   Vector2   (const float p_x, const float p_y)              noexcept;
            constexpr   Vector2   (const float p_value)                           noexcept;
            constexpr   Vector2   (const Vector2& p_from, const Vector2& p_to)    noexcept;
            constexpr   Vector2   (const Vector2& p_copy)                         noexcept;
            constexpr   Vector2   (const Vector3& p_copy)                         noexcept;
            constexpr   Vector2   (const Vector4& p_copy)                         noexcept;
            constexpr   Vector2   (Vector2&& p_move)                              noexcept;
            
            ~Vector2() noexcept = default;

        // Local Methods (Public) //
            constexpr   float       GetMagnitude    ()                                  const noexcept;
            constexpr   Vector2     GetNormalize    ()									const noexcept;
            constexpr   float       GetSqrMagnitude ()									const noexcept;
            constexpr   Vector2 	Normalize       ()                                        noexcept;
            constexpr   Vector2     Set				(const float p_x, const float p_y)        noexcept;
            
            inline      std::string ToString		()                                  const noexcept;

        // Local Operators (Public) //
            constexpr   Vector2&    operator=   (Vector2&& p_move)          noexcept;

            constexpr   Vector2&    operator=   (const Vector2& p_copy)     noexcept;
            constexpr   Vector2&    operator=   (const Vector3& p_copy)     noexcept;
            constexpr   Vector2&    operator=   (const Vector4& p_copy)     noexcept;
            
            constexpr   float	    operator[]	(const int p_index)         const;
            constexpr   float&	 	operator[]	(const int p_index);
    };

        // General Operators //
            constexpr   bool            operator==  (const Vector2& p_a, const Vector2& p_b)    noexcept;
            constexpr   bool            operator!=  (const Vector2& p_a, const Vector2& p_b)    noexcept;

            constexpr   Vector2&        operator++  (Vector2& p_a)                              noexcept;
            constexpr   Vector2&        operator--  (Vector2& p_a)                              noexcept;

            constexpr   Vector2         operator+   (const Vector2& p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2         operator+   (const Vector2& p_a, const float    p_k)    noexcept;
            constexpr   Vector2         operator+   (const float    p_k, const Vector2& p_a)    noexcept;
            constexpr   Vector2&        operator+=  (Vector2&       p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2&        operator+=  (Vector2&       p_a, const float    p_k)    noexcept;

            constexpr   Vector2         operator-   (const Vector2& p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2         operator-   (const Vector2& p_a, const float p_k)       noexcept;
            constexpr   Vector2         operator-   (const Vector2& p_a)                        noexcept;
            constexpr   Vector2&        operator-=  (Vector2&       p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2&        operator-=  (Vector2&       p_a, const float p_k)       noexcept; 

            constexpr   Vector2         operator*   (const Vector2& p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2         operator*   (const float    p_k, const Vector2& p_a)    noexcept;
            constexpr   Vector2         operator*   (const Vector2& p_a, const float    p_k)    noexcept;
            constexpr   Vector2&        operator*=  (Vector2&       p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2&        operator*=  (Vector2&       p_a, const float    p_k)    noexcept;

            constexpr   Vector2         operator/   (const Vector2& p_a, const Vector2& p_b);            
            constexpr   Vector2         operator/   (const Vector2& p_a, const float    p_k);
            constexpr   Vector2&        operator/=  (Vector2&       p_a, const Vector2& p_b);
            constexpr   Vector2&        operator/=  (Vector2&       p_a, const float    p_k);

            constexpr   Vector2         operator%   (const Vector2& p_a, const Vector2& p_b)    noexcept;            
            constexpr   Vector2         operator%   (const Vector2& p_a, const float    p_k)    noexcept;
            constexpr   Vector2&        operator%=  (Vector2&       p_a, const Vector2& p_b)    noexcept;
            constexpr   Vector2&        operator%=  (Vector2&       p_a, const float    p_k)    noexcept;  

            inline      std::ostream&   operator<<  (std::ostream& p_flux, const Vector2& p_a)  noexcept;
}

#include "../Inlines/Vector2.inl"

#endif // !__VECTOR_2_HPP__