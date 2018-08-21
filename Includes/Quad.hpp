#ifndef	__QUAD_HPP__
#define __QUAD_HPP__

/**
 * @file     Quad.hpp
 * @brief    Include file for Quad
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GQuad Quad
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector2;
    class Vector3;

    class Quad
    {
        /**
         * @class Maths::Quad Quad.hpp Quad.cpp Quad.inl
         * @brief Used for quads
         * 
         * @ingroup GQuad
         * 
         */

        private:
        // Local Variables (Private) //
            Vector3	m_forward; ///< The direction of the quad
            Vector3	m_right;   ///<
            Vector3	m_up;      ///<

        public:
        // Local Variables (Public) //
            Vector3	m_origin; ///< The position of the origin
            Vector2	m_size;   ///< The lengths of the quad's extents
            
        // Constructors + Destructor //
            constexpr   Quad    ()                                                  noexcept;
            constexpr   Quad	(const Vector3& p_origin, const Vector2& p_size)    noexcept;
            constexpr   Quad	(const Vector3& p_origin, 
                                 const Vector2& p_size, 
                                 const Vector3&	p_up, 
                                 const Vector3& p_right,  
                                 const Vector3& p_forward)                          noexcept;
            constexpr   Quad	(const Vector3& p_origin, 
                                 const Vector2& p_size, 
                                 const Vector3& p_rotation)                         noexcept;
            constexpr   Quad	(const Quad& p_copy)                                noexcept;
            constexpr   Quad	(Quad&& p_move)                                     noexcept;
            
            ~Quad() noexcept = default;

        //	Local Methods (Public) //
            constexpr   Vector3 GetForward		()						    const noexcept;
            constexpr   Vector3	GetRight		()						    const noexcept;
            constexpr   Vector3 GetUp 			()						    const noexcept;

            bool	            IsPointInclude  (const Vector3& p_pt)	    const noexcept;

            void	            Rotate		    (const Vector3& p_rotation)       noexcept;
            void	            Rotate		    (const float p_xRot, 
                                                 const float p_yRot,
                                                 const float p_zRot)              noexcept;

            inline  std::string ToString        ()                          const noexcept;

        // Local Operators (Public) //
            constexpr   Quad&   operator=   (Quad&& p_move)         noexcept;

            constexpr   Quad&   operator=   (const Quad& p_copy)    noexcept;
    };

        // General Operators //
            inline  std::ostream&	operator<<	(std::ostream& p_flux, const Quad& p_quad) noexcept;
}

#include "../Inlines/Quad.inl"

#endif // !__QUAD_HPP__