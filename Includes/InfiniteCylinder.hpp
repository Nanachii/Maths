#ifndef __INFINITE_CYLINDER_HPP__
#define __INFINITE_CYLINDER_HPP__

/**
 * @file     InfiniteCylinder.hpp
 * @brief    Include file for InfiniteCylinder
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GInfiniteCylinder InfiniteCylinder
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;

    class InfiniteCylinder
    {
        /**
         * @class Maths::InfiniteCylinder InfiniteCylinder.hpp InfiniteCylinder.cpp InfiniteCylinder.inl
         * @brief Used for infinite cylinders
         * 
         * @ingroup GInfiniteCylinder
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin;    ///< The position of the origin
            Vector3 m_direction; ///< The direction of the axis
            float	m_radius;    ///< The cylinder's radius

        // Constructors + Destructor //
            constexpr   InfiniteCylinder    ()                                  noexcept;
            constexpr   InfiniteCylinder    (const Vector3& p_origin, 
                                             const Vector3& p_direction, 
                                             const float    p_radius)           noexcept;
            constexpr   InfiniteCylinder    (const InfiniteCylinder& p_copy)    noexcept;
            constexpr   InfiniteCylinder    (InfiniteCylinder&& p_move)         noexcept;

            ~InfiniteCylinder() noexcept = default;
        
        // Local Methods (Public) //
            inline  std::string     ToString() const noexcept;

        // Local Operators (Public) //
            constexpr   InfiniteCylinder&   operator=   (InfiniteCylinder&& p_move)         noexcept;

            constexpr   InfiniteCylinder&   operator=   (const InfiniteCylinder& p_copy)    noexcept;
    };

        // General  Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const InfiniteCylinder& p_cylinder) noexcept;
}

#include "../Inlines/InfiniteCylinder.inl"

#endif // !__INFINITE_CYLINDER_HPP__