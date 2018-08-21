#ifndef __RAYCAST_HPP__
#define __RAYCAST_HPP__

/**
 * @file     Raycast.hpp
 * @brief    Include file for Raycast
 * @author   Philippe Yi
 * 
 * @defgroup GRaycast Raycast
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

    class Raycast
    {
        /**
         * @class Maths::Raycast Raycast.hpp Raycast.cpp Raycast.inl
         * @brief Used for raycasts
         * 
         * @ingroup GRaycast
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3 m_origin;      ///< The position of the origin
            Vector3 m_direction;   ///< The direction of the ray
            float   m_maxDistance; ///< The maximum distance the ray should check collisions

        // Constructors + Destructor //
            constexpr   Raycast ()                              noexcept;
            constexpr   Raycast (const Vector3& p_origin, 
                                 const Vector3& p_direction, 
                                 const float    p_maxDistance)  noexcept;
            constexpr   Raycast (const Raycast& p_copy)         noexcept;
            constexpr   Raycast (Raycast&& p_move)              noexcept;

            ~Raycast() noexcept = default;
        
        // Local Methods (Public) //
            bool	            IsIntersecting  (const Plane&            p_plane,    Intersection& p_hit)	const noexcept;
            bool	            IsIntersecting	(const Quad&             p_quad,     Intersection& p_hit)	const noexcept;
            bool                IsIntersecting  (const AABB&             p_aabb,     Intersection& p_hit)   const noexcept;
            bool                IsIntersecting  (const OBB&              p_obb,      Intersection& p_hit)   const noexcept;
            bool                IsIntersecting  (const Sphere&           p_sphere,   Intersection& p_hit)   const noexcept;
            bool                IsIntersecting  (const Cylinder&         p_cylinder, Intersection& p_hit)   const noexcept;
            bool                IsIntersecting  (const InfiniteCylinder& p_cylinder, Intersection& p_hit)   const noexcept;
            bool                IsIntersecting  (const Capsule&          p_capsule,  Intersection& p_hit)   const noexcept;

            inline  std::string ToString        ()                                                          const noexcept;

        // Local Operators (Public) //
            constexpr   Raycast&    operator=   (Raycast&& p_move)      noexcept;

            constexpr   Raycast&    operator=   (const Raycast& p_copy) noexcept;
    };

        // General Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Raycast& p_raycast) noexcept;
}

#include "../Inlines/Raycast.inl"

#endif // !__RAYCAST_HPP__