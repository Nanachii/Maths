#ifndef __PLANE_HPP__
#define __PLANE_HPP__

/**
 * @file     Plane.hpp
 * @brief    Include file for Plane
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GPlane Plane
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class Line;

    class Plane 
    {
        /**
         * @class Maths::Plane Plane.hpp Plane.cpp Plane.inl
         * @brief Used for planes
         * 
         * @ingroup GPlane
         * 
         */

        public:
        // Static Methods (Public) // 
            static  bool    Crossing2Plane      	(const Plane& p_plane1, const Plane& p_plane2)                          noexcept;
            static  bool    Crossing3Plane      	(const Plane& p_plane1, const Plane& p_plane2, const Plane& p_plane3)   noexcept;
    
            static  Line	GetLineWith2Plane		(const Plane& p_plane1, const Plane& p_plane2)                          noexcept;
            static  Vector3 GetPointWith3Plane  	(const Plane& p_plane1, const Plane& p_plane2, const Plane& p_plane3)   noexcept;

        // Local Variables (Public) //
            Vector3	    m_normal;   ///< The normal of the plane
            float		m_distance; ///< The distance from world's origin

        // Constructors + Destructor //
            constexpr   Plane   ()                                                                  noexcept;
            constexpr   Plane	(const Vector3& p_normal, const float p_distance)                   noexcept;
            constexpr   Plane	(const Vector3& p_normal, const Vector3& p_point)                   noexcept;
            constexpr   Plane	(const Vector3& p_pt1, const Vector3& p_pt2, const Vector3& p_pt3)  noexcept;
            constexpr   Plane	(const Plane& p_copy)                                               noexcept;
            constexpr   Plane	(Plane&& p_move)                                                    noexcept;
            
            ~Plane() noexcept = default;

        // Local Methods (Public) //
            Vector3 		        ClosestPointOnPlane 	(const Vector3& p_pt)							const noexcept;
            float			        DistanceToPoint			(const Vector3& p_pt)							const noexcept;
            Plane			        Flip               		()                                                    noexcept;
            float			        SignedDistanceToPoint	(const Vector3& p_pt)							const noexcept;
            float 			        GetSide             	(const Vector3& p_pt)							const noexcept;
            bool			        SameSide            	(const Vector3& p_pt1, const Vector3& p_pt2)    const noexcept;
            void			        Translate				(const float p_tranlation)                            noexcept;
            
            inline  std::string     ToString                ()                                              const noexcept;

        // Local Operators (Public) //
            constexpr   Plane&  operator=   (Plane&& p_move)        noexcept;

            constexpr   Plane&  operator=   (const Plane& p_copy)   noexcept;
    };

        // General Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Plane& p_plane) noexcept;
}

#include "../Inlines/Plane.inl"

#endif // !__PLANE_HPP__