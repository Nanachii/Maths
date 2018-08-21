/**
 * @file    Vector2.cpp
 * @brief   Source file for Vector2
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GVector2
 * 
 */

#include "../Includes/Vector2.hpp"

using namespace Maths;

/*=========================[Static Properties (Public)]=========================*/

const Vector2 Vector2::Up    {Vector2( 0.0f,  1.0f)};
const Vector2 Vector2::Down  {Vector2( 0.0f, -1.0f)};

const Vector2 Vector2::Right {Vector2( 1.0f,  0.0f)};
const Vector2 Vector2::Left  {Vector2(-1.0f,  0.0f)};

const Vector2 Vector2::One   {Vector2( 1.0f,  1.0f)};
const Vector2 Vector2::Zero  {Vector2( 0.0f,  0.0f)};