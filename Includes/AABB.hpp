#ifndef __AABB_HPP__
#define __AABB_HPP__

/**
 * @file     AABB.hpp
 * @brief    Include file for AABB
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GAABB AABB
 * 
 */

#include <string>
#include <iostream>
#include <vector>

namespace Maths
{
    class Vector3;
    class OBB;
    class Sphere;
    class Cylinder;
    class InfiniteCylinder;
    class Capsule;

    class AABB
    {
        /**
         * @class Maths::AABB AABB.hpp AABB.cpp AABB.inl
         * @brief Used for 3D aabbs
         * 
         * @ingroup GAABB
         * 
         */

        private:
        // Local Variables (Private) //
            Vector3 m_extents; ///< The half-length of the box's extents
            Vector3 m_max;     ///< The top-right corner
            Vector3 m_min;     ///< The bottom-left corner
            Vector3	m_size;    ///< The lengths of the box's extents

        public:
        // Local Variables (Public) //
            Vector3 m_origin; ///< The position of the origin

        // Constructors + Destructor //
            constexpr 	AABB    ()                                                  noexcept;
            constexpr 	AABB	(const Vector3& p_origin, const Vector3& p_size)    noexcept;
            constexpr 	AABB	(const AABB& p_copy)                                noexcept;
            constexpr   AABB    (AABB&& p_move)                                     noexcept;

            ~AABB() noexcept = default;
            
        // Local Methods (Public) //
            Vector3		            ClosestPoint			(const Vector3& p_point)	            const noexcept;
            bool		            Contains				(const Vector3& p_point)	            const noexcept;

            Vector3	                Corner                  (const int p_n)                         const noexcept;

            float		            Distance				(const Vector3& p_point)	            const noexcept;
            float		            DistanceSqr				(const Vector3& p_point)	            const noexcept;

    		void		            Encapsulate				(const Vector3& p_point)	            const noexcept;
    		void		            Encapsulate				(const AABB&    p_aabb)		            const noexcept;

    		void		            Expand					(const float    p_amount)		              noexcept;
    		void		            Expand					(const Vector3& p_amount)	                  noexcept;

            Vector3 	            GetExtents				()							            const noexcept;
            Vector3 	            GetMax					()							            const noexcept;
            Vector3 	            GetMin					()							            const noexcept;
            Vector3 	            GetSize					()							            const noexcept;
            std::vector<Vector3> 	GetVertices			    ()							            const noexcept;

            bool		            IsColliding				(const AABB&             p_other)       const noexcept;
            bool		            IsColliding				(const OBB&              p_obb)         const noexcept;
            bool		            IsColliding				(const Sphere&           p_sphere)      const noexcept;
            bool		            IsColliding				(const Cylinder&         p_cylinder)    const noexcept;
            bool		            IsColliding				(const InfiniteCylinder& p_cylinder)    const noexcept;
            bool		            IsColliding				(const Capsule&          p_capsule)     const noexcept;

            Vector3		            Normal					(const Vector3& p_point)	            const noexcept;

            inline  std::string     ToString                ()                                      const noexcept;

        // Local Operators (Public) //
            constexpr   AABB&   operator=   (AABB&& p_move)         noexcept;

            constexpr   AABB&   operator=   (const AABB& p_copy)    noexcept;
    };

        // General Operators //
            inline  std::ostream&    operator<<  (std::ostream& p_flux, const AABB& p_aabb) noexcept;
}

#include "../Inlines/AABB.inl"

#endif // !__AABB_HPP__