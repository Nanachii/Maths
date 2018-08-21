/**
 * @file    OBB.cpp
 * @brief   Source file for OBB
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GOBB
 * 
 */

#include "../Includes/Vector3.hpp"
#include "../Includes/Matrix4x4.hpp"
#include "../Includes/Range.hpp"
#include "../Includes/AABB.hpp"
#include "../Includes/Sphere.hpp"
#include "../Includes/Cylinder.hpp"
#include "../Includes/InfiniteCylinder.hpp"
#include "../Includes/Capsule.hpp"

#include "../Includes/OBB.hpp"

using namespace Maths;

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Creates an AABB for the current oriented box
 * 
 * @return AABB The new AABB
 */
AABB					OBB::GetAABB		() const noexcept
{
	float x (__FLT_MIN__);
	float y (__FLT_MIN__);
	float z (__FLT_MIN__);

	std::vector<Vector3> vertices = GetVertices();

	for (unsigned int i = 0u; i < vertices.size(); ++i)
	{
		x = Max(x, vertices[i].m_x);
		y = Max(y, vertices[i].m_y);
		z = Max(z, vertices[i].m_z);
	}

	return AABB(m_origin, Vector3(x, y, z));
}

/**
 * @brief Computes the vertices of the current oriented box
 * 
 * @return std::vector<Vector3> The array of vertices
 */
std::vector<Vector3> 	OBB::GetVertices	() const noexcept
{
	std::vector<Vector3> 	vertices;
		
	Matrix4x4 				rotation(Matrix4x4::Rotate(Quaternion::Euler(m_angle)));

	// Front
    vertices.push_back(m_origin + rotation * Vector3(-m_extents.m_x,  m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3( m_extents.m_x,  m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3(-m_extents.m_x, -m_extents.m_y,  m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3( m_extents.m_x, -m_extents.m_y,  m_extents.m_z));

    // Back
    vertices.push_back(m_origin + rotation * Vector3( m_extents.m_x,  m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3(-m_extents.m_x,  m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3( m_extents.m_x, -m_extents.m_y, -m_extents.m_z));
    vertices.push_back(m_origin + rotation * Vector3(-m_extents.m_x, -m_extents.m_y, -m_extents.m_z));

	return vertices;
}

/**
 * @brief Checks if there is collision with another oriented box
 * 
 * @param p_other The target box
 * @return true   There is collision with the other box
 * @return false  There is no collision with the other box
 */
bool 	OBB::IsColliding	(const OBB& p_other) const noexcept
{
	// Check AABBs
	if (GetAABB().IsColliding(p_other.GetAABB()))
	{
		Matrix4x4 currentRotation	(Matrix4x4::Rotate(Quaternion::Euler(m_angle)));
		Matrix4x4 otherRotation		(Matrix4x4::Rotate(Quaternion::Euler(p_other.m_angle)));

		// Compute unit vectors for the current box
		Vector3 lhsVectors[3] = {
			currentRotation * Vector3::Right, 
			currentRotation * Vector3::Up, 
			currentRotation * Vector3::Forward
		};

		// Compute unit vectors for the other box
		Vector3 rhsVectors[3] = {
			otherRotation * Vector3::Right, 
			otherRotation * Vector3::Up, 
			otherRotation * Vector3::Forward
		};

		// Compute cross products between the unit vectors
		Vector3 crossProducts[9] = {
			lhsVectors[0] ^ rhsVectors[0], 
			lhsVectors[0] ^ rhsVectors[1],
			lhsVectors[0] ^ rhsVectors[2],

			lhsVectors[1] ^ rhsVectors[0],
			lhsVectors[1] ^ rhsVectors[1],
			lhsVectors[1] ^ rhsVectors[2],

			lhsVectors[2] ^ rhsVectors[0],
			lhsVectors[2] ^ rhsVectors[1],
			lhsVectors[2] ^ rhsVectors[2]
		};

		// Check SATs for all unit vectors
		for (int i = 0; i < 3; ++i)
		{
			if (!Range::SAT(lhsVectors[i], *this).IsOverlapping(Range::SAT(lhsVectors[i], p_other)))
				return false;
			
			if (!Range::SAT(rhsVectors[i], *this).IsOverlapping(Range::SAT(rhsVectors[i], p_other)))
				return false;
		}

		// Check SATs for all cross products
		for (int i = 0; i < 9; ++i)
			if (!Range::SAT(crossProducts[i], *this).IsOverlapping(Range::SAT(crossProducts[i], p_other)))
				return false;

		return true;
	}

	return false;
}

/**
 * @brief Checks if there is collision with an AABB
 * 
 * @param p_aabb The target AABB
 * @return true  There is collision with the AABB
 * @return false There is no collision with the AABB
 */
[[deprecated("This method is not implemented yet!")]]
bool	OBB::IsColliding	(const AABB& p_aabb) const noexcept
{
	(void)p_aabb;

	return false;
}

/**
 * @brief Checks if there is collision with a sphere
 * 
 * @param p_sphere The target sphere
 * @return true    There is collision with the sphere
 * @return false   There is no collision with the sphere
 */
[[deprecated("This method is not implemented yet!")]]
bool	OBB::IsColliding	(const Sphere& p_sphere) const noexcept
{
	(void)p_sphere;

	return false;
}

/**
 * @brief Checks if there is collision with a cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the cylinder
 * @return false     There is no collision with the cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool	OBB::IsColliding	(const Cylinder& p_cylinder) const noexcept
{
	(void)p_cylinder;

	return false;
}

/**
 * @brief Checks if there is collision with an infinite cylinder
 * 
 * @param p_cylinder The target cylinder
 * @return true      There is collision with the infinite cylinder
 * @return false     There is no collision with the infinite cylinder
 */
[[deprecated("This method is not implemented yet!")]]
bool	OBB::IsColliding	(const InfiniteCylinder& p_cylinder) const noexcept
{
	(void)p_cylinder;

	return false;
}

/**
 * @brief Checks if there is collision with a capsule
 * 
 * @param p_capsule The target capsule
 * @return true     There is collision with the capsule
 * @return false    There is no collision with the capsule
 */
[[deprecated("This method is not implemented yet!")]]
bool	OBB::IsColliding	(const Capsule& p_capsule) const noexcept
{
	(void)p_capsule;

	return false;
}