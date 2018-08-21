#ifndef __CAPSULE_HPP__
#define __CAPSULE_HPP__

/**
 * @file     Capsule.hpp
 * @brief    Include file for Capsule
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GCapsule Capsule
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;

    class Capsule
    {
        /**
         * @class Maths::Capsule Capsule.hpp Capsule.cpp Capsule.inl
         * @brief Used for capsules
         * 
         * @ingroup GCapsule
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin;    ///< The position of the origin
            Vector3 m_direction; ///< The direction of the axis
            float	m_height;    ///< The axis's length
            float	m_radius;    ///< The capsule's radius

        // Constructors + Destructor //
            constexpr   Capsule ()                          noexcept;
            constexpr   Capsule	(const Vector3& p_origin, 
                                 const Vector3& p_direction, 
                                 const float    p_height, 
                                 const float    p_radius)   noexcept;
            constexpr   Capsule	(const Vector3& p_origin, 
                                 const Vector3& p_target, 
                                 const float    p_radius)   noexcept;
            constexpr   Capsule	(const Capsule& p_copy)     noexcept;
            constexpr   Capsule	(Capsule&& p_move)          noexcept;
            
            ~Capsule() noexcept = default;

        // Local Methods (Public) //
            inline  std::string     ToString() const noexcept;

        // Local Operators (Public) //
            constexpr   Capsule&    operator=   (Capsule&& p_move)      noexcept;

            constexpr   Capsule&    operator=   (const Capsule& p_copy) noexcept;
    };

        // General Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Capsule& p_capsule) noexcept;
}

#include "../Inlines/Capsule.inl"

#endif // !__CAPSULE_HPP__