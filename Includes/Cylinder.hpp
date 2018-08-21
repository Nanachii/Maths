#ifndef __CYLINDER_HPP__
#define __CYLINDER_HPP__

/**
 * @file     Cylinder.hpp
 * @brief    Include file for Cylinder
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GCylinder Cylinder
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;

    class Cylinder
    {
        /**
         * @class Maths::Cylinder Cylinder.hpp Cylinder.cpp Cylinder.inl
         * @brief Used for cylinders
         * 
         * @ingroup GCylinder
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin;    ///< The position of the origin
            Vector3 m_direction; ///< The direction of the axis
            float   m_height;    ///< The axis's length
            float	m_radius;    ///< The cylinder's radius

        // Constructors + Destructor //
            constexpr   Cylinder    ()                          noexcept;
            constexpr   Cylinder    (const Vector3& p_origin, 
                                     const Vector3& p_direction, 
                                     const float    p_height, 
                                     const float    p_radius)   noexcept;
            constexpr   Cylinder    (const Cylinder& p_copy)    noexcept;
            constexpr   Cylinder    (Cylinder&& p_move)         noexcept;
            
            ~Cylinder() noexcept = default;

        // Local Methods (Public) //
            inline  std::string     ToString() const noexcept;
        
        // Local Operators (Public) //
            constexpr   Cylinder&   operator=   (Cylinder&& p_move)         noexcept;

            constexpr   Cylinder&   operator=   (const Cylinder& p_copy)    noexcept;
    };

        // General Operator //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Cylinder& p_cylinder) noexcept;
}

#include "../Inlines/Cylinder.inl"

#endif // !__CYLINDER_HPP__