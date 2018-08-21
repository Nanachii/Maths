#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

/**
 * @file     Sphere.hpp
 * @brief    Include file for Sphere
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GSphere Sphere
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class OBB;
    class AABB;
    class Cylinder;
    class InfiniteCylinder;
    class Capsule;
    class Intersection;

    class Sphere
    {
        /**
         * @class Maths::Sphere Sphere.hpp Sphere.cpp Sphere.inl
         * @brief Used for spheres
         * 
         * @ingroup GSphere
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin; ///< The position of the origin
            float	m_radius; ///< The sphere's radius

        // Constructors + Destructor //
            constexpr   Sphere	()                                              noexcept;
            constexpr   Sphere	(const Vector3& p_origin, const float p_radius) noexcept;
            constexpr   Sphere	(const Sphere& p_copy)                          noexcept;
            constexpr   Sphere  (Sphere&& p_move)                               noexcept;
            
            ~Sphere() noexcept = default;
        
        // Local Methods (Public) //
            AABB                GetAABB                     ()                                      const noexcept;

            bool                IsColliding                 (const Sphere&           p_other)       const noexcept;
            bool                IsColliding                 (const OBB&              p_obb)         const noexcept;
            bool                IsColliding                 (const AABB&             p_aabb)        const noexcept;
            bool                IsColliding                 (const Cylinder&         p_cylinder)    const noexcept;
            bool                IsColliding                 (const InfiniteCylinder& p_cylinder)    const noexcept;
            bool                IsColliding                 (const Capsule&          p_capsule)     const noexcept;

            bool                IsMovingSphereColliding     (const Sphere&           p_sphere, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            bool                IsMovingSphereColliding     (const OBB&              p_obb, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            bool                IsMovingSphereColliding     (const AABB&             p_aabb, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            bool                IsMovingSphereColliding     (const Cylinder&         p_cylinder, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            bool                IsMovingSphereColliding     (const InfiniteCylinder& p_cylinder, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            bool                IsMovingSphereColliding     (const Capsule&          p_capsule, 
                                                             const Vector3&          p_speed, 
                                                             Intersection&           p_hit)         const noexcept;
            inline  std::string ToString                    ()                                      const noexcept;

        // Local Operators (Public) //
            constexpr   Sphere&     operator=   (Sphere&& p_move)       noexcept;

            constexpr   Sphere&     operator=   (const Sphere& p_copy)  noexcept;
    };

        // General Operators //
            inline std::ostream&    operator<<  (std::ostream& p_flux, const Sphere& p_sphere) noexcept;
}

#include "../Inlines/Sphere.inl"

#endif // !__SPHERE_HPP__