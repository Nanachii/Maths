#ifndef __LINE_HPP__
#define __LINE_HPP__

/**
 * @file     Line.hpp
 * @brief    Include file for Line
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GLine Line
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class Plane;
    class Quad;
    class OBB;
    class AABB;
    class Sphere;
    class Cylinder;
    class InfiniteCylinder;
    class Capsule;
    class Intersection;

    class Line
    {
        /**
         * @class Maths::Line Line.hpp Line.cpp Line.inl
         * @brief Used for 3D lines
         * 
         * @ingroup GLine
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin;    ///< The position of the origin
            Vector3	m_direction; ///< The direction of the line

        // Constructors + Destructor //
            constexpr   Line    ()                                                      noexcept;
            constexpr   Line    (const Vector3& p_origin, const Vector3& p_direction)   noexcept;
            constexpr   Line    (const Line& p_copy)                                    noexcept;
            constexpr   Line    (Line&& p_move)                                         noexcept;
            
            ~Line() noexcept = default;

        // Local Methods (Public) //
            constexpr   Vector3 ClosestPointOnLine	(const Vector3& p_pt)	                const noexcept;
            constexpr   float   DistancePoint		(const Vector3& p_pt)	                const noexcept;
            constexpr   float   DistancePointSqr	(const Vector3& p_pt)	                const noexcept;

            bool	            IsIntersecting		(const Plane&            p_plane,    Intersection& p_hit)	const noexcept;
            bool	            IsIntersecting		(const Quad&             p_quad,     Intersection& p_hit)	const noexcept;
            bool                IsIntersecting      (const OBB&              p_obb,      Intersection& p_hit)   const noexcept;
            bool                IsIntersecting      (const AABB&             p_aabb,     Intersection& p_hit)   const noexcept;
            bool                IsIntersecting      (const Sphere&           p_sphere,   Intersection& p_hit)   const noexcept;
            bool                IsIntersecting      (const Cylinder&         p_cylinder, Intersection& p_hit)   const noexcept;
            bool                IsIntersecting      (const InfiniteCylinder& p_cylinder, Intersection& p_hit)   const noexcept;
            bool                IsIntersecting      (const Capsule&          p_capsule,  Intersection& p_hit)   const noexcept;

            inline  std::string ToString            ()                                                          const noexcept;

        // Local Operators (Public) //
            constexpr	Line&	operator=	(Line&& p_move)         noexcept;

            constexpr 	Line&	operator=	(const Line& p_other)   noexcept;
    };
    
        // General Operators //
            constexpr   bool		    operator==	(const Line& p_a, const Line& p_b) 			noexcept;
            constexpr   bool		    operator!=	(const Line& p_a, const Line& p_b) 			noexcept;

            inline 	    std::ostream&   operator<<  (std::ostream& p_flux, const Line& p_line) 	noexcept;
}

#include "../Inlines/Line.inl"

#endif // !__LINE_HPP__