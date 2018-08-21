#ifndef __OBB_HPP__
#define __OBB_HPP__

/**
 * @file     OBB.hpp
 * @brief    Include file for OBB
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GOBB OBB
 * 
 */

#include <string>
#include <iostream>
#include <vector>

namespace Maths
{
    class Vector3;
    class AABB;
    class Sphere;
    class Cylinder;
    class InfiniteCylinder;
    class Capsule;

    class OBB
    {
        /**
         * @class Maths::OBB OBB.hpp OBB.cpp OBB.inl
         * @brief Used for 3D oriented boxes
         * 
         * @ingroup GOBB
         * 
         */

        public:
        // Local Variables (Public) //
            Vector3	m_origin;  ///< The position of the origin
            Vector3	m_extents; ///< The lengths of the box's extents
            Vector3	m_angle;   ///< The rotation of the box

        // Constructors + Destructor //
            constexpr 	OBB	() 							noexcept;
            constexpr 	OBB	(const Vector3& p_origin, 
                             const Vector3& p_extents, 
                             const Vector3& p_angle)    noexcept;
            constexpr 	OBB	(const OBB& p_copy) 		noexcept;
            constexpr 	OBB	(OBB&& p_move) 		        noexcept;

            ~OBB() noexcept = default;	

        // Local Methods (Public) //
            AABB                    GetAABB     ()                                      const noexcept;
            std::vector<Vector3>    GetVertices ()                                      const noexcept;

            bool  				    IsColliding	(const OBB&              p_other)       const noexcept;
            bool                    IsColliding (const AABB&             p_aabb)        const noexcept;
            bool                    IsColliding (const Sphere&           p_sphere)      const noexcept;
            bool                    IsColliding (const Cylinder&         p_cylinder)    const noexcept;
            bool                    IsColliding (const InfiniteCylinder& p_cylinder)    const noexcept;
            bool                    IsColliding (const Capsule&          p_capsule)     const noexcept;

            inline	std::string	    ToString	() 						                const noexcept;

        // Local Operators (Public) //
            constexpr 	OBB&    operator=	(OBB&& p_move) 		noexcept;

            constexpr	OBB&	operator=	(const OBB& p_copy) noexcept;
    };
    
        // General Operators //
            inline	std::ostream&   operator<<  (std::ostream& p_flux, const OBB& p_obb)  noexcept;
}

#include "../Inlines/OBB.inl"

#endif // !__OBB_HPP__