#ifndef __VECTOR_3_HPP__
#define __VECTOR_3_HPP__

/**
 * @file     Vector3.hpp
 * @brief    Include file for Vector3
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GVector3 Vector3
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector2;
    class Vector4;
    
    class Vector3
    {
        /**
         * @class Maths::Vector3 Vector3.hpp Vector3.cpp Vector3.inl
         * @brief Used for 3D vectors
         * 
         * @ingroup GVector3
         * 
         */

        public:
        // Static Properties (Public) //
            static const    Vector3 Forward;  ///< Shorthand writing for Vector3(0.0f, 0.0f, 1.0f)
            static const    Vector3 Backward; ///< Shorthand writing for Vector3(0.0f, 0.0f, -1.0f)

            static const    Vector3 Up;       ///< Shorthand writing for Vector3(0.0f, 1.0f, 0.0f)
            static const    Vector3 Down;     ///< Shorthand writing for Vector3(0.0f, -1.0f, 0.0f)

            static const    Vector3 Right;    ///< Shorthand writing for Vector3(1.0f, 0.0f, 0.0f)
            static const    Vector3 Left;     ///< Shorthand writing for Vector3(-1.0f, 0.0f, 0.0f)

            static const    Vector3 One;      ///< Shorthand writing for Vector3(1.0f, 1.0f, 1.0f)
            static const    Vector3 Zero;     ///< Shorthand writing for Vector3(0.0f, 0.0f, 0.0f)

        // Static Methods (Public) //
            constexpr static    float   AngleDegree             (const Vector3& p_from, const Vector3& p_to);
            constexpr static    float   AngleRadian             (const Vector3& p_from, const Vector3& p_to);

            constexpr static    Vector3 ClampMagnitude		    (const Vector3& p_vector, const float p_maxLength)          noexcept;

            constexpr static    Vector3 Cross				    (const Vector3& p_a, const Vector3& p_b)                    noexcept;
            constexpr static    float   Distance                (const Vector3& p_a, const Vector3& p_b)                    noexcept;
            constexpr static    float   DistanceSqr             (const Vector3& p_a, const Vector3& p_b)                    noexcept;
            constexpr static    float   Dot                     (const Vector3& p_a, const Vector3& p_b)                    noexcept;
            constexpr static    Vector3 EulerAngleDegree        (const Vector3& p_a, const Vector3& p_b);
            constexpr static    Vector3 EulerAngleRadian        (const Vector3& p_a, const Vector3& p_b);
            constexpr static    bool    IsColinear              (const Vector3& p_a, const Vector3& p_b)                    noexcept;

            constexpr static    Vector3 Lerp                    (const Vector3& p_a, const Vector3& p_b, const float p_t)   noexcept;
            constexpr static    Vector3 LerpUnclamped           (const Vector3& p_a, const Vector3& p_b, const float p_t)   noexcept;

            constexpr static    Vector3 Max                     (const Vector3& p_a, const Vector3& p_b)                    noexcept;
            constexpr static    Vector3 Min                     (const Vector3& p_a, const Vector3& p_b)                    noexcept;

            constexpr static    Vector3 MoveTowards             (const Vector3& p_current, 
                                                                 const Vector3& p_target, 
                                                                 const float    p_maxDistanceDelta)                         noexcept;

            constexpr static    Vector3 Project                 (const Vector3& p_vector,    const Vector3& p_onNormal)      noexcept;
            constexpr static    Vector3 ProjectOnPlane          (const Vector3& p_vector,    const Vector3& p_planeNormal)   noexcept;
            constexpr static    Vector3 Reflect                 (const Vector3& p_direction, const Vector3& p_normal);
            constexpr static    Vector3 ReflectInvert           (const Vector3& p_direction, const Vector3& p_normal);

			constexpr static    Vector3 RotateTowards           (const Vector3& p_current, 
                                                                 const Vector3& p_target, 
												                 const float    p_maxRadiansDelta, 
                                                                 const float    p_maxMagnitudeDelta)                        noexcept;

            constexpr static    Vector3 Scale                   (const Vector3& p_a, const Vector3& p_b)                    noexcept;

            constexpr static    float   SignedAngleDegree       (const Vector3& p_from, 
                                                                 const Vector3& p_to, 
                                                                 const Vector3& p_axis);
            constexpr static    float   SignedAngleRadian       (const Vector3& p_from, 
                                                                 const Vector3& p_to, 
                                                                 const Vector3& p_axis);

            constexpr static    Vector3 SignedEulerAngleDegree  (const Vector3& p_a, const Vector3& p_b);
            constexpr static    Vector3 SignedEulerAngleRadian  (const Vector3& p_a, const Vector3& p_b);
                                                 
            constexpr static    Vector3 Slerp                   (const Vector3& p_a, const Vector3& p_b, const float p_t)   noexcept;
            constexpr static    Vector3 SlerpUnclamped          (const Vector3& p_a, const Vector3& p_b, const float p_t)   noexcept;

        // Local Variables (Public) //
            float   m_x; ///< The x value
            float   m_y; ///< The y value
            float   m_z; ///< The z value

        // Constructors + Destructor //
            constexpr   Vector3 	()                                                  noexcept;
            constexpr   Vector3 	(const float p_x, 
                                     const float p_y, 
                                     const float p_z)                                   noexcept;
            constexpr   Vector3 	(const float p_value)                               noexcept;
            constexpr   Vector3 	(const Vector3& p_from, const Vector3& p_to)        noexcept;
            constexpr   Vector3 	(const Vector2& p_vector2, const float p_z = 0.0f)  noexcept;
            constexpr   Vector3     (const Vector3& p_copy)                             noexcept;
            constexpr   Vector3     (const Vector4& p_copy)                             noexcept;
            constexpr   Vector3     (Vector3&& p_move)                                  noexcept;

            ~Vector3() noexcept = default;

        // Local Methods (Public) //
            constexpr   float       GetMagnitude    ()		            const noexcept;
            constexpr   Vector3     GetNormalize    ()		            const noexcept;
            constexpr   float       GetSqrMagnitude ()	                const noexcept;
            constexpr   Vector3 	Normalize       ()                        noexcept;
            constexpr   Vector3     Set		        (const float p_x, 
                                                     const float p_y, 
                                                     const float p_z)         noexcept;
            
            inline      std::string ToString	    ()                  const noexcept;

        // Local Operators (Public) //
            constexpr   Vector3&    operator=   (Vector3&& p_move)          noexcept;

            constexpr   Vector3&    operator=   (const Vector2& p_copy)     noexcept;
            constexpr   Vector3&    operator=   (const Vector3& p_copy)     noexcept;
            constexpr   Vector3&    operator=   (const Vector4& p_copy)     noexcept;
            
            constexpr   float       operator[]	(const int p_index)         const;
            constexpr   float& 	    operator[]	(const int p_index);
    };
    
        // General Operators //
            constexpr   bool            operator==  (const Vector3& p_a, const Vector3& p_b)    noexcept;
            constexpr   bool            operator!=  (const Vector3& p_a, const Vector3& p_b)    noexcept;

            constexpr   Vector3&        operator++  (Vector3& p_a)                              noexcept;
            constexpr   Vector3&        operator--  (Vector3& p_a)                              noexcept;

            constexpr   Vector3         operator+   (const Vector3& p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3         operator+   (const Vector3& p_a, const float    p_k)    noexcept;
            constexpr   Vector3         operator+   (const float    p_k, const Vector3& p_a)    noexcept;
            constexpr   Vector3&        operator+=  (Vector3&       p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3&        operator+=  (Vector3&       p_a, const float    p_k)    noexcept;

            constexpr   Vector3         operator-   (const Vector3& p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3         operator-   (const Vector3& p_a, const float    p_k)    noexcept;
            constexpr   Vector3         operator-   (const Vector3& p_a)                        noexcept;
            constexpr   Vector3&        operator-=  (Vector3&       p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3&        operator-=  (Vector3&       p_a, const float    p_k)    noexcept;

            constexpr   Vector3         operator*   (const Vector3& p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3         operator*   (const float    p_k, const Vector3& p_a)    noexcept;
            constexpr   Vector3         operator*   (const Vector3& p_a, const float    p_k)    noexcept;
            constexpr   Vector3&        operator*=  (Vector3&       p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3&        operator*=  (Vector3&       p_a, const float    p_k)    noexcept;

            constexpr   Vector3         operator/   (const Vector3& p_a, const Vector3& p_b);            
            constexpr   Vector3         operator/   (const Vector3& p_a, const float    p_k);
            constexpr   Vector3&        operator/=  (Vector3&       p_a, const Vector3& p_b);
            constexpr   Vector3&        operator/=  (Vector3&       p_a, const float    p_k);  

            constexpr   Vector3         operator%   (const Vector3& p_a, const Vector3& p_b)    noexcept;            
            constexpr   Vector3         operator%   (const Vector3& p_a, const float    p_k)    noexcept;
            constexpr   Vector3&        operator%=  (Vector3&       p_a, const Vector3& p_b)    noexcept;
            constexpr   Vector3&        operator%=  (Vector3&       p_a, const float    p_k)    noexcept;

            constexpr   Vector3         operator^   (const Vector3& p_a, const Vector3& p_b)    noexcept;

            inline      std::ostream&   operator<<  (std::ostream& p_flux, const Vector3& p_a)  noexcept;
}

#include "../Inlines/Vector3.inl"

#endif // !__VECTOR_3_HPP__