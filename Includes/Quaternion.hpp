#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include <string>
#include <iostream>

/**
 * @file     Quaternion.hpp
 * @brief    Include file for GQuaternion
 * @author   Alexis Beracochea
 * 
 * @defgroup GQuaternion Quaternion
 * 
 */

namespace Maths
{
    class Vector3;
    class Vector4;

    class Quaternion
    {
         /**
         * @class Maths::Quaternion Quaternion.hpp Quaternion.cpp Quaternion.inl
         * @brief Quaternions are used to represent rotations
         * 
         * @ingroup GQuaternion
         * 
         */

        public:
        // Static Variables (Public) //
            static	const	Quaternion Identity; ///< The identity quaternion

        // Static Methods (Public) //
            constexpr   static  Quaternion  Angle           (const Quaternion& p_a, const Quaternion& p_b)                  noexcept;
            constexpr   static  float       AngleDeg        (const Quaternion& p_a, const Quaternion& p_b)                  noexcept;
            constexpr   static  float       AngleRad        (const Quaternion& p_a, const Quaternion& p_b)                  noexcept;
            constexpr   static  Quaternion  AngleAxis       (const Vector3& p_axis, const float p_angle)                    noexcept;       
            constexpr   static	float       Dot             (const Quaternion& p_a, const Quaternion& p_b)                  noexcept;
            constexpr   static  Quaternion  Euler           (const Vector3& p_eulerRotation)                                noexcept; 
            constexpr   static  Quaternion  Euler           (const float p_xRot, const float p_yRot, const float p_zRot)    noexcept; 
            constexpr   static	Quaternion  FromToRotation  (const Vector3& p_fromDirection, const Vector3& p_toDirection)  noexcept;
            constexpr   static 	Quaternion  Lerp            (const Quaternion& p_a, const Quaternion& p_b, const float p_t) noexcept;
            constexpr   static  Quaternion  LerpUnclamped   (const Quaternion &p_a, const Quaternion &p_b, const float p_t) noexcept;
            // static 	Quaternion      LookRotation    (const Vector3& p_forward, const Vector3& p_upwards = Vector3::Up);    
            // static 	Quaternion      RotateTowards   (const Quaternion& p_from, Quaternion p_to, const float p_maxDegreesDelta);   
            // constexpr   static 	Quaternion  Slerp           (const Quaternion& p_a, const Quaternion& p_b, const float p_t) noexcept;
            // constexpr   static 	Quaternion  SlerpUnclamped  (const Quaternion& p_a, const Quaternion& p_b, const float p_t) noexcept;

        // Variables (Public) //
            float m_x; ///< The x value
            float m_y; ///< The y value
            float m_z; ///< The z value
            float m_w; ///< The w value

        // Constructor + Destructor //
            constexpr   Quaternion	()                                                                          noexcept;
            constexpr   Quaternion	(const float p_x, const float p_y, const float p_z, const float p_scalar)   noexcept;
            constexpr   Quaternion	(const Vector3& p_vector3, const float p_scalar)                            noexcept;
            constexpr   Quaternion	(const Vector4& p_vector4)                                                  noexcept;
            constexpr   Quaternion	(const Quaternion& p_copy)                                                  noexcept;
            constexpr   Quaternion	(const Quaternion&& p_copy)                                                 noexcept;
                        ~Quaternion	() noexcept = default;

        // Methods	(Public) //

            constexpr   void        Conjugate           ()                                      noexcept;
            constexpr   Quaternion  GetConjugate        ()                              const   noexcept;
            constexpr   Vector3     GetEulerAngles      ()                              const   noexcept;
            constexpr   Quaternion  GetInverse          ()                              const   noexcept;
            constexpr   float       GetMagnitude        ()                              const   noexcept;
            constexpr   Quaternion  GetNormalize        ()                              const   noexcept;
            constexpr   float       GetSqrMagnitude     ()                              const   noexcept;
            constexpr   void        Inverse             ()                                      noexcept;
            constexpr   void        Normalize           ()                                      noexcept;
            constexpr   void	    Set				    (const float p_x, 
                                                         const float p_y, 
                                                         const float p_z, 
                                                         const float p_w)                       noexcept;
            constexpr    void	    SetEulersAngles	    (const Vector3& p_euler)                noexcept;
            constexpr    void	    SetEulersAngles	    (const float p_xRot,
                                                         const float p_yRot, 
                                                         const float p_zRot)                    noexcept;
            // constexpr    void 	    SetFromToRotation   (const Vector3& p_fromDirection, const Vector3& p_toDirection);
            // constexpr    void 	    SetLookRotation	    (const Vector3& p_view, const Vector3& p_up = Vector3::Up);
            // constexpr    void 	    ToAngleAxis		    (const float p_angle, const Vector3& p_axis);
            
            // inline  std::string ToString		    ();

        // Operator (Public) //
            constexpr   Quaternion& operator=   (const Quaternion& p_copy)          noexcept;
            constexpr   Quaternion& operator=   (const Quaternion&& p_move)         noexcept;

            constexpr   float 		operator[]	(const int p_index)         const;
            constexpr   float& 		operator[]	(const int p_index);
    };

        // General Operators //
            constexpr   bool            operator==  (const Quaternion& p_a, const Quaternion& p_b)  noexcept;
            constexpr   bool            operator!=  (const Quaternion& p_a, const Quaternion& p_b)  noexcept;

            constexpr   Quaternion      operator+   (const Quaternion& p_a, const Quaternion& p_b)  noexcept;
            constexpr   Quaternion&     operator+=  (Quaternion& p_a, const Quaternion& p_b)        noexcept;

            constexpr   Quaternion      operator-   (const Quaternion& p_a)                         noexcept;
            constexpr   Quaternion      operator-   (const Quaternion& p_a, const Quaternion& p_b)  noexcept;
            constexpr   Quaternion&     operator-=  (Quaternion& p_a, const Quaternion& p_b)        noexcept;

            constexpr   Quaternion      operator*   (const Quaternion& p_a, const Quaternion& p_b)  noexcept;
            constexpr   Quaternion      operator*   (const Quaternion& p_a, const float p_k)        noexcept;
            constexpr   Quaternion      operator*   (const float p_k, const Quaternion& p_a)        noexcept;
            constexpr   Quaternion&     operator*=  (Quaternion& p_a, const Quaternion& p_b)        noexcept;
            constexpr   Quaternion&     operator*=  (Quaternion& p_a, const float p_k)              noexcept;

            constexpr   Quaternion      operator/   (const Quaternion& p_a, const float p_k)        noexcept;
            constexpr   Quaternion&     operator/=  (Quaternion& p_a, const float p_k)              noexcept;

            inline      std::ostream&   operator<<  (std::ostream& p_flux, const Quaternion& p_a)   noexcept;

}

#include "../Inlines/Quaternion.inl"

#endif