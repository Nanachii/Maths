#ifndef __RANGE_HPP__
#define __RANGE_HPP__

/**
 * @file     Range.hpp
 * @brief    Include file for range
 * @author   Philippe Yi
 * 
 * @defgroup GRange Range
 * 
 */

#include <string>
#include <iostream>

namespace Maths
{
    class Vector3;
    class OBB;

    class Range
    {   
        /**
         * @class Maths::Range Range.hpp Range.cpp Range.inl
         * @brief Used for ranges
         * 
         * @ingroup GRange
         * 
         */

        public:
        // Static Methods (Public) //
            static  Range   SAT (const Vector3& p_vector, const OBB& p_obb) noexcept;

        // Local Variables (Public) //
            float  m_min; ///< The minimum value
            float  m_max; ///< The maximum value

        // Constructors + Destructor //
            Range() = delete;

            constexpr   Range   (float p_min, float p_max)  noexcept;
            constexpr   Range   (const Range& p_copy)       noexcept;
            constexpr   Range   (Range&& p_move)            noexcept;

            ~Range() noexcept = default;

        // Local Methods (Public) //
            constexpr   bool        IsOverlapping   (const Range& p_other)  const noexcept;

            inline      std::string ToString        ()                      const noexcept;

        // Local Operators (Public) //
            constexpr   Range&  operator=   (Range&& p_move)        noexcept;
            
            constexpr   Range&  operator=   (const Range& p_copy)   noexcept;
    };

        // General Operators //
            inline  std::ostream&   operator<<  (std::ostream& p_flux, const Range& p_range) noexcept;
}

#include "../Inlines/Range.inl"

#endif // !__RANGE_HPP__