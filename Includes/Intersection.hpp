#ifndef __INTERSECTION_HPP__
#define __INTERSECTION_HPP__

/**
 * @file     Intersection.hpp
 * @brief    Include file for Intersection
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GIntersection Intersection
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;

    class Intersection
    {
        /**
         * @class Maths::Intersection Intersection.hpp Intersection.cpp Intersection.inl
         * @brief Used for intersections
         * 
         * @ingroup GIntersection
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_impact; ///< The position of the intersection
            Vector3	m_normal; ///< The normal of the intersection
        
        // Constructors + Destructor //
            constexpr   Intersection    ()                                                  noexcept;
            constexpr   Intersection    (const Vector3& p_impact, const Vector3& p_normal)  noexcept;
            constexpr   Intersection    (const Intersection& p_copy)                        noexcept;
            constexpr   Intersection    (Intersection&& p_move)                             noexcept;
            
            ~Intersection() noexcept = default;

        // Local Methods (Public)//
            Intersection        Set		    (const Vector3& p_impact, const Vector3& p_normal)        noexcept;
            void	            Reset	    ()                                                        noexcept;

            inline  std::string ToString    ()                                                  const noexcept;

        // Local Operators (Public)//
            constexpr   Intersection&   operator=   (Intersection&& p_move)         noexcept;

            constexpr	Intersection&	operator=	(const Intersection& p_copy)    noexcept;
    };

        // General Operators //
            constexpr   bool			operator==  (const Intersection& p_a, const Intersection& p_b)	        noexcept;
            constexpr   bool			operator!=	(const Intersection& p_a, const Intersection& p_b)	        noexcept;

            inline	    std::ostream&   operator<<  (std::ostream& p_flux, const Intersection& p_intersection)  noexcept;
}

#include "../Inlines/Intersection.inl"

#endif // !__INTERSECTION_HPP__