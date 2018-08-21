#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

/**
 * @file     Utilities.hpp
 * @brief    General include file for Maths
 * @author   Alexis Beracochea, Philippe Yi
 * 
 * @defgroup GUtilities Utilities
 * 
 */

namespace Maths
{
    /**
     * @brief Constexpr declaration of PI as long double for constexpr operations
     * 
     * @ingroup GUtilities
     * 
     */
    constexpr long double PI = 3.141592653589793238462643383279502884l;

    /**
     * @brief From degrees to radians conversion operator at variable definition
     * 
     * @ingroup GUtilities
     * 
     */
    constexpr long double operator"" _Radians(long double p_num) noexcept
    {
        return (p_num * PI) / 180.0l;
    }

    /**
     * @brief From radians to degrees conversion operator at variable definition
     * 
     * @ingroup GUtilities
     * 
     */
    constexpr long double operator"" _Degrees(long double p_num) noexcept
    {
        return (p_num * 180.0l) / PI;       
    }

    /**
     * @brief Raises a float value to the power exponent
     * 
     * @ingroup GUtilities  
     * 
     * @param p_num            Base value
     * @param p_exp            Exponent value
     * @return constexpr float The resulting value of raising base to the power exponent
     */
    constexpr float pow(const float p_num, const unsigned int p_exp) noexcept
    {
        return p_exp > 0 ? p_num * pow(p_num, p_exp - 1u) : 1.0f;
    }

    /**
     * @brief Converts a value to degrees
     * 
     * @ingroup GUtilities
     * 
     * @param p_num            Base value
     * @return constexpr float The resulting value the conversion
     */
    constexpr float ToDegrees(const float p_num) noexcept
    {
        return (p_num * 180.0f) / (float)PI;
    }

    /**
     * @brief Converts a value to radians
     * 
     * @ingroup GUtilities
     * 
     * @param p_num            Base value
     * @return constexpr float The resulting value of the conversion
     */
    constexpr float ToRadians(const float p_num) noexcept
    {
        return (p_num * (float)PI) / 180.0f;
    }

    /**
     * @brief Compares the base value with the minimum value and returns the smaller one
     * 
     * @ingroup GUtilities
     * 
     * @tparam T           Integer type
     * @param p_num        Base value
     * @param p_min        Minimum value
     * @return constexpr T The resulting value of the comparison
     */
    template <typename T>
    constexpr T Min(T p_num, T p_min) noexcept
    {
        return (p_num < p_min) ? p_num : p_min;
    }

    /**
     * @brief Compares the base value with the maximum value and returns the greater one
     * 
     * @ingroup GUtilities
     * 
     * @tparam T           Integer type
     * @param p_num        Base value
     * @param p_max        Maximum value
     * @return constexpr T The resulting value of the comparison
     */
    template <typename T>
    constexpr T Max(T p_num, T p_max) noexcept
    {
        return (p_num > p_max) ? p_num : p_max;
    }

    /**
     * @brief Clamps the base value with the minimum and the maximum value
     * 
     * @ingroup GUtilities
     * 
     * @tparam T           Integer type
     * @param p_num        Base value
     * @param p_min        Minimum value
     * @param p_max        Maximum value
     * @return constexpr T The resulting value of the clamping
     */
    template <typename T>
    constexpr T Clamp(T p_num, T p_min, T p_max) noexcept
    {
        return (p_num < p_min) ? p_min : (p_num > p_max) ? p_max : p_num;
    }

    /**
     * @brief Clamps the base value with 0 and 1
     * 
     * @ingroup GUtilities
     * 
     * @tparam T           Integer type
     * @param p_num        Base value
     * @return constexpr T The resulting value of the clamping
     */
    template <typename T>
    constexpr T Clamp01(T p_num) noexcept
    {
        return (p_num < (T)0) ? (T)0 : (p_num > T(1)) ? (T)1 : p_num;
    }

    /**
     * @brief Lerp between 2 values with a clamp for the result
     * 
     * @tparam T            Interger type
     * @param p_a           Start value
     * @param p_b           End value
     * @param p_t           Speed value
     * @return constexpr T  The resulting value of the lerping
     */
    template <typename T>
    constexpr T Lerp(T p_a, T p_b, const float p_t)
    {
        float value ((p_t <= 0.0f) ? 0.0f : (p_t >= 1.0f) ?  1.0f : p_t);

        return (1.0f - value) * p_a + value * p_b;
    }

    /**
     * @brief Lerp between 2 values with a clamp for the result
     * 
     * @tparam T            Interger type
     * @param p_a           Start value
     * @param p_b           End value
     * @param p_t           Speed value
     * @return constexpr T  The resulting value of the lerping
     */
    template <typename T>
    constexpr T LerpUnclamped(T p_a, T p_b, const float p_t)
    {
        return (1.0f - p_t) * p_a + p_t * p_b;
    }
}

#endif // !__UTILITIES_HPP__