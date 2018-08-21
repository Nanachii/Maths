#ifndef __SEGMENT_HPP__
#define __SEGMENT_HPP__

/**
 * @file     Segment.hpp
 * @brief    Include file for Segment
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GSegment Segment
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class Line;
    class Plane;
    class Quad;
    class OBB;
    class AABB;
    class Sphere;
    class Cylinder;
    class InfiniteCylinder;
    class Capsule;
    class Intersection;

    class Segment
    {
        /**
         * @class Maths::Segment Segment.hpp Segment.cpp Segment.inl
         * @brief Used for segments
         * 
         * @ingroup GSegment
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_ptA; ///< The position of the first point
            Vector3	m_ptB; ///< The position of the second point
        
        // Constructors + Destructor //
            constexpr   Segment ()                                              noexcept;
            constexpr   Segment (const Vector3& p_ptA, const Vector3& p_ptB)    noexcept;
            constexpr   Segment (const Segment& p_copy)                         noexcept;
            constexpr   Segment (Segment&& p_move)                              noexcept;
            
            ~Segment() noexcept = default;
    
        // Local Methods (Public) //
            float	                DistancePoint 		(const Vector3& p_pt)									    const noexcept;
            float	                DistancePointSqr    (const Vector3& p_pt)									    const noexcept;

            Vector3	                GetAB 				()														    const noexcept;
            Vector3	                GetBA 				()														    const noexcept;
            Line 	                GetLine 			()	 													    const noexcept;
    
            bool	                IsIntersecting		(const Plane&            p_plane,    Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const Quad&             p_quad,     Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const OBB&              p_obb,      Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const AABB&             p_aabb,     Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const Sphere&           p_sphere,   Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const Cylinder&         p_cylinder, Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting	    (const InfiniteCylinder& p_cylinder, Intersection& p_hit)	const noexcept;
            bool	                IsIntersecting		(const Capsule&          p_capsule,  Intersection& p_hit)	const noexcept;

            float	                Length 				()														    const noexcept;
            float	                LengthSqr 			()														    const noexcept;

            inline  std::string     ToString            ()                                                          const noexcept;

        // Local Operators (Public) //
            constexpr   Segment&    operator=   (Segment&& p_move)      noexcept;

            constexpr   Segment&    operator=	(const Segment& p_copy) noexcept;
    };

        // General Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Segment& p_segment) noexcept;
}

#include "../Inlines/Segment.inl"

#endif // !__SEGMENT_HPP__