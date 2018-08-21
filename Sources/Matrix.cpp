/**
 * @file    Matrix.cpp
 * @brief   Source file for Matrix
 * @author  Alexis Beracochea, Philippe Yi
 * 
 * @ingroup GMatrix
 * 
 */

#include <stdexcept>

#include "../Includes/Utilities.hpp"
#include "../Includes/Vector2.hpp"
#include "../Includes/Vector3.hpp"
#include "../Includes/Vector4.hpp"
#include "../Includes/Matrix.hpp"

using namespace Maths;

/*=========================[Constructors + Destructor]=========================*/

/**
 * @brief Default constructor
 * 
 */
Matrix::Matrix	() noexcept
:   m_row     {1},
    m_column  {1},
    m_matrix  {new float}
{ 
    m_matrix[0] = 0.0f;
}

/**
 * @brief Constructor with specific number of rows and columns
 * 
 * @param p_row    The number of rows
 * @param p_column The number of columns
 */
Matrix::Matrix  (const int p_row, const int p_column) noexcept
:   m_row     {p_row},
    m_column  {p_column},
    m_matrix  {new float[p_row * p_column]}
{
    for (int i = 0; i < p_row * p_column; ++i)
        m_matrix[i] = 0.0f;
}

/**
 * @brief Constructor with the same number of rows and columns
 * 
 * @param p_squareSize The number of rows and columns
 */
Matrix::Matrix  (const int p_squareSize) noexcept
:   m_row     {p_squareSize},
    m_column  {p_squareSize},
    m_matrix  {new float[p_squareSize * p_squareSize]}
{
    for (int i = 0; i < p_squareSize * p_squareSize; ++i)
        m_matrix[i] = 0.0f;
}

/**
 * @brief Copy constructor with a 2D vector
 * 
 * @param p_vector2 The vector to copy
 */
Matrix::Matrix  (const Vector2& p_vector2) noexcept
:   m_row     {2},
    m_column  {1},
    m_matrix  {new float[2]}
{
        m_matrix[0] = p_vector2.m_x;
        m_matrix[1] = p_vector2.m_y;
}

/**
 * @brief Copy constructor with a 3D vector
 * 
 * @param p_vector3 The vector to copy
 */
Matrix::Matrix  (const Vector3& p_vector3) noexcept
:   m_row     {3},
    m_column  {1},
    m_matrix  {new float[3]}
{
        m_matrix[0] = p_vector3.m_x;
        m_matrix[1] = p_vector3.m_y;
        m_matrix[2] = p_vector3.m_z;
}

/**
 * @brief Copy constructor with a 4D vector
 * 
 * @param p_vector4 The vector to copy
 */
Matrix::Matrix  (const Vector4& p_vector4) noexcept
:   m_row     {4},
    m_column  {1},
    m_matrix  {new float[4]}
{
        m_matrix[0] = p_vector4.m_x;
        m_matrix[1] = p_vector4.m_y;
        m_matrix[2] = p_vector4.m_z;
        m_matrix[3] = p_vector4.m_w;
}

/**
 * @brief Copy constructor with another matrix
 * 
 * @param p_copy The matrix to copy
 */
Matrix::Matrix  (const Matrix& p_copy) noexcept
:   m_row     {p_copy.m_row},
    m_column  {p_copy.m_column},
    m_matrix  {new float[m_row * m_column]}
{
    for (int i = 0 ; i < m_row * m_column ; ++i)
        m_matrix[i] = p_copy.m_matrix[i];
}

/**
 * @brief Move constructor
 * 
 * @param p_move The matrix to move
 */
Matrix::Matrix  (Matrix&& p_move) noexcept
:   m_row    {std::move(p_move.m_row)   },
    m_column {std::move(p_move.m_column)},
    m_matrix {std::move(p_move.m_matrix)}
{}

/**
 * @brief Destructor
 * 
 */
Matrix::~Matrix  () noexcept
{
    delete[] m_matrix;
}

/*=========================[Local Methods (Public)]=========================*/

/**
 * @brief Returns the values of the current matrix as an array
 * 
 * @return float* The resulting array
 */
float*          Matrix::GetArray	    ()  const noexcept
{
    return m_matrix;
}

/**
 * @brief Creates the cofactor matrix of the current matrix
 * 
 * @return Matrix The resulting cofactor matrix
 */
Matrix 	        Matrix::GetCofactor	    () const noexcept
{
    Matrix 	cofactor (m_row, m_column);
    float 	sign     (1);

    for (int r = 0; r < m_row; ++r)
    {
        if (r % 2 == 0)
            sign = 1;
        else
            sign = -1;

        for (int c = 0; c < m_column; ++c)
        {
            cofactor(r,c) = (*this).GetSubMatrix(r,c).GetDeterminant() * sign;
            sign *= -1;
        }
    }

    return cofactor;
}

/**
 * @brief Returns the number of columns
 * 
 * @return int The number of columns
 */
int             Matrix::GetColumn	    ()	const noexcept
{
    return m_column;
}

/**
 * @brief Calculates the determinant of the current matrix
 * 
 * @return float The resulting determinant 
 */
float 	        Matrix::GetDeterminant	() const noexcept
{

    if (m_row == 1 && m_column == 1)
        return m_matrix[0];
    
    if (m_row * m_column == 4)
        return m_matrix[0] * m_matrix[3] - m_matrix[1] * m_matrix[2];

    float result (0);
    float sign   (1);

    for (int i = 0 ; i < m_column ; ++i)
    {
        result += (*this)(0, i) * (*this).GetSubMatrix(0, i).GetDeterminant() * sign;
        sign   *= -1;
    }
    return result;
}

/**
 * @brief Creates the inverse of the current matrix
 * 
 * @return Matrix The resulting inverted matrix
 */
Matrix 	        Matrix::GetInverse		() const noexcept
{
    float determinant = this->GetDeterminant();

    if (determinant == 0.0f)
        return *this;

    return (*this).GetCofactor().GetTranspose() / determinant;
}

/**
 * @brief Returns the number of rows
 * 
 * @return int The number of rows
 */
int             Matrix::GetRow		    ()  const noexcept
{
    return m_row;
}

/**
 * @brief Creates the submatrix of the current matrix ignoring a specific row and column
 * 
 * @param p_row    The row's index to ignore
 * @param p_column The column's index to ignore
 * @return Matrix  The resulting submatrix
 */
Matrix	        Matrix::GetSubMatrix	(const int p_row, const int p_column) const
{
    if (p_row >= m_row || p_column >= m_column)
        throw std::out_of_range("No value available!");

    Matrix  new_matrix  (p_row - 1, p_column - 1);
    int     k           (0);

    for (int i = 0; i < new_matrix.GetColumn(); ++i)
    {
        int l (0);

        if (i == p_row)
            k++;

        for (int j = 0; j < new_matrix.GetColumn(); ++j)
        {
            if (j == p_column)
                l++;

            new_matrix(i, j) = (*this)(i + k, j + l);
        }
    }

    return new_matrix;
}

/**
 * @brief Creates the transpose of the current matrix
 * 
 * @return Matrix The resulting transposed matrix
 */
Matrix	        Matrix::GetTranspose	() const noexcept
{
    Matrix new_matrix(m_column, m_row);

    for (int r = 0 ; r < m_row ; ++r)
        for (int c = 0 ; c < m_column ; ++c)
            new_matrix(r,c) = (*this)(c,r);

    return new_matrix;
}

/**
 * @brief Converts the current matrix to a string
 * 
 * @return std::string The resulting string of the conversion
 */
std::string     Matrix::ToString        () const noexcept
{
    std::string string;

    for (int row = 0; row < m_row; ++row)
        for (int column = 0; column < m_column; ++column)
        {
            string += std::to_string((*this)(row, column));

            if (column == m_column - 1)
                string += "\n";
            else
                string += "\t|\t";
        }

    return string;
}

/*=========================[Local Operators (Public)]=========================*/

/**
 * @brief Move operator
 * 
 * @param p_move   The matrix to move
 * @return Matrix& The moved matrix
 */
Matrix&     Matrix::operator=   (Matrix&& p_move)
{
    if (m_row != p_move.m_row || m_column != p_move.m_column)
        throw std::domain_error("Trying to use move operator on two matrices of different size!");

    m_matrix = std::move(p_move.m_matrix);

    return *this;
}

/**
 * @brief Copy operator
 * 
 * @param p_copy   The matrix to copy
 * @return Matrix& The copied matrix
 */
Matrix&		Matrix::operator=   (const Matrix& p_copy)
{
    if (m_row != p_copy.m_row || m_column != p_copy.m_column)
        throw std::domain_error("Trying to use copoy operator on two matrices of different size!");

    for (int index = 0; index < m_row * m_column; ++index)
        m_matrix[index] = p_copy[index];

    return *this;
}

/**
 * @brief Read only accessor
 * 
 * @param p_row    The row's index value
 * @param p_column The column's index value
 * @return float   The value to read
 */
float		Matrix::operator()  (const int p_row, const int p_column)	const
{
    return m_matrix[p_row + p_column * m_row];
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_row    The row's index value
 * @param p_column The column's index value
 * @return float&  The value to modify
 */
float&		Matrix::operator()  (const int p_row, const int p_column)
{
    return m_matrix[p_row + p_column * m_row];
}

/**
 * @brief Read only accessor
 * 
 * @param p_index The index value
 * @return float  The value to read
 */
float		Matrix::operator()  (const int p_index)	const
{
    return m_matrix[p_index];
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_index The index value
 * @return float& The value to modify
 */
float&		Matrix::operator()	(const int p_index)
{
    return m_matrix[p_index];
}

/**
 * @brief Read only accessor
 * 
 * @param p_index The index value
 * @return float  The value to read
 */
float		Matrix::operator[]	(const int p_index)	const
{
    return m_matrix[p_index];
}

/**
 * @brief Modifiable accessor
 * 
 * @param p_index The index value
 * @return float& The value to modify
 */
float&		Matrix::operator[]	(const int p_index)
{
    return m_matrix[p_index];
}

/*=========================[General Operators]=========================*/

/**
 * @brief Checks if two matrices are equal
 * 
 * @param p_a    The left handed matrix
 * @param p_b    The right handed matrix
 * @return true  The matrices are approximately equal
 * @return false The matrices are not equal
 */
bool 		    Maths::operator==   (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() != p_b.GetRow() || p_a.GetColumn() != p_b.GetColumn())
        throw std::domain_error("Trying to compare two matrices of different size!");
    
    double epsilon (__DBL_EPSILON__ * __DBL_EPSILON__);

    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
    {
        double value ((p_a[index] - p_b[index]) * (p_a[index] - p_b[index]));

        if (value > epsilon)
            return false;
    }
  
    return true;
}

/**
 * @brief Checks if two matrices are different
 * 
 * @param p_a    The left handed matrix
 * @param p_b    The right handed matrix
 * @return true  The matrices are not equal
 * @return false The matrices are approximately equal
 */
bool 		    Maths::operator!=   (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() == p_b.GetRow() || p_a.GetColumn() == p_b.GetColumn())
        throw std::domain_error("Trying to compare two matrices of different size!");
    
    double epsilon (__DBL_EPSILON__ * __DBL_EPSILON__);
    
    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
    {
        double value ((p_a[index] - p_b[index]) * (p_a[index] - p_b[index]));

        if (value > epsilon)
            return true;
    }

    return false;
}

/**
 * @brief Adds two matrices
 * 
 * @param p_a     The left handed matrix
 * @param p_b     The right handed matrix
 * @return Matrix The resulting matrix of the addition
 */
Matrix		    Maths::operator+    (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() != p_b.GetRow() || p_a.GetColumn() != p_b.GetColumn())
        throw std::domain_error("Trying to add two matrices of different size!");

    Matrix result(p_a.GetRow(), p_a.GetColumn());

    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
        result[index] = p_a[index] + p_b[index];

    return result;		
}

/**
 * @brief Adds a matrix to the current one
 * 
 * @param p_a      The target matrix
 * @param p_b      The matrix to add
 * @return Matrix& The resulting matrix of the addition 
 */
Matrix&		    Maths::operator+=   (Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() != p_b.GetRow() || p_a.GetColumn() != p_b.GetColumn())
        throw std::domain_error("Trying to add two matrices of different size!");

    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
        p_a[index] += p_b[index];
   
    return p_a;
}

/**
 * @brief Computes the opposite of this matrix
 * 
 * @param p_a      The target matrix
 * @return Matrix& The opposite matrix
 */
Matrix&		    Maths::operator-    (Matrix& p_a) noexcept
{
    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
        p_a[index] = -p_a[index];        

    return p_a;
}

/**
 * @brief Substracts a matrix from another one
 * 
 * @param p_a     The target matrix
 * @param p_b     The matrix to substract
 * @return Matrix The resulting matrix of the substraction
 */
Matrix		    Maths::operator-    (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() != p_b.GetRow() || p_a.GetColumn() != p_b.GetColumn())
        throw std::domain_error("Trying to substract two matrices of different size!");

    Matrix result(p_a.GetRow(), p_a.GetColumn());
    
    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
        result  = p_a(index) - p_b(index); 

    return result;			
}

/**
 * @brief Substracts a matrix from the current one
 * 
 * @param p_a      The target matrix
 * @param p_b      The matrix to substract
 * @return Matrix& The resulting matrix of the substraction
 */
Matrix&		    Maths::operator-=   (Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetRow() != p_b.GetRow() || p_a.GetColumn() != p_b.GetColumn())
        throw std::domain_error("Trying to substract two matrices of different size!");

    for (int index = 0; index < p_a.GetRow() * p_a.GetColumn(); ++index)
        p_a(index) -= p_b(index); 

    return p_a;
}

/**
 * @brief Multiplies two matrices
 * 
 * @param p_a     The left handed matrix
 * @param p_b     The right handed matrix
 * @return Matrix The resulting matrix of the multiplication
 */
Matrix  	    Maths::operator*    (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetColumn() != p_b.GetRow())
        throw std::domain_error("The left handed matrix's number of columns is different of the second one's number of rows");

    Matrix result(p_a.GetRow(), p_b.GetColumn());

    for (int row = 0; row < result.GetRow(); ++row)
        for (int column = 0; column < result.GetColumn(); ++column)
            for (int i = 0; i < result.GetColumn(); ++i)
                result(row, column) += p_a(row, i) * p_b(i, column);

    return result;
}

/**
 * @brief Multiplies the current matrix by another one
 * 
 * @param p_a      The target matrix
 * @param p_b      The matrix to multiply
 * @return Matrix& The resulting matrix of the multiplication
 */
Matrix&  	    Maths::operator*=   (Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetColumn() != p_b.GetRow())
        throw std::domain_error("The left handed matrix's number of columns is different of the second one's number of rows");

    Matrix result(p_a.GetRow(), p_b.GetColumn());

    for (int row = 0; row < result.GetRow(); ++row)
        for (int column = 0; column < result.GetColumn(); ++column)
            for (int i = 0; i < result.GetColumn(); ++i)
                result(row, column) += p_a(row, i) * p_b(i, column);
    
    return p_a = std::move(result);
}

/**
 * @brief Multiplies a matrix by a number
 * 
 * @param p_k     The value to multiply
 * @param p_a     The target matrix
 * @return Matrix The resulting matrix of the multiplication
 */
Matrix 		    Maths::operator*    (const float p_k, const Matrix& p_a) noexcept
{
    Matrix result;

    for (int index = 0; index < p_a.GetColumn() * p_a.GetRow(); ++index)
        result[index] = p_a[index] * p_k;

    return result;
}

/**
 * @brief Multiplies a matrix by a number
 * 
 * @param p_a     The target matrix
 * @param p_k     The value to multiply
 * @return Matrix The resulting matrix of the multiplication
 */
Matrix 		    Maths::operator*    (const Matrix& p_a, const float p_k) noexcept
{
    Matrix result;

    for (int index = 0; index < p_a.GetColumn() * p_a.GetRow(); ++index)
        result[index] = p_a[index] * p_k;

    return result;
}

/**
 * @brief Multiplies the current matrix by a number
 * 
 * @param p_a      The target matrix
 * @param p_k      The value to multiply with
 * @return Matrix& The resulting matrix of the multiplication
 */
Matrix& 	    Maths::operator*=   (Matrix& p_a, const float p_k) noexcept
{
    for (int index = 0; index < p_a.GetColumn() * p_a.GetRow(); ++index)
        p_a[index] *= p_k;

    return p_a;
}

/**
 * @brief Divides a matrix by another one
 * 
 * @param p_a     The target matrix
 * @param p_b     The matrix to divide
 * @return Matrix The resulting matrix of the division
 */
Matrix          Maths::operator/    (const Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetColumn() != p_b.GetRow())
        throw std::domain_error("The left handed matrix's number of columns is different of the second one's number of rows");

    Matrix result   (p_a.GetRow(), p_b.GetColumn());
    Matrix inverse  (p_b.GetInverse());
    
    for (int row = 0; row < result.GetRow(); ++row)
        for (int column = 0; column < result.GetColumn(); ++column)
            for (int i = 0; i < p_a.GetColumn(); ++i)
                result(row, column) += inverse(i, column) * p_a(row, i);

    return result;
}

/**
 * @brief Divides a matrix by a number
 * 
 * @param p_a     The target matrix
 * @param p_k     The value to divide
 * @return Matrix The resulting matrix of the division
 */
Matrix          Maths::operator/    (const Matrix& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    Matrix result;

    for (int index = 0; index < p_a.GetColumn() * p_a.GetRow(); ++index)
        result[index] = p_a[index] / p_k;

    return result;
}

/**
 * @brief Divides the current matrix by a number
 * 
 * @param p_a      The target matrix
 * @param p_k      The value to divide
 * @return Matrix& The resulting matrix of the division
 */
Matrix&         Maths::operator/=	(Matrix& p_a, const float p_k)
{
    if (p_k == 0.0f)
        throw std::domain_error("Division by 0 is impossible!");

    for (int index = 0; index < p_a.GetColumn() * p_a.GetRow(); ++index)
        p_a[index] /= p_k;

    return p_a;
}

/**
 * @brief Divides the current matrix by another matrix
 * 
 * @param p_a      The target matrix
 * @param p_b      The matrix to divide
 * @return Matrix& The resulting matrix of the division
 */
Matrix&         Maths::operator/=   (Matrix& p_a, const Matrix& p_b)
{
    if (p_a.GetColumn() != p_b.GetRow())
        throw std::domain_error("The left handed matrix's number of columns is different of the second one's number of rows");

    Matrix result   (p_a.GetRow(), p_b.GetColumn());
    Matrix inverse  (p_b.GetInverse());

    for (int row = 0; row < result.GetRow(); ++row)
        for (int column = 0; column < result.GetColumn(); ++column)
            for (int i = 0; i < p_a.GetColumn(); ++i)
                result(row, column) += inverse(i, column) * p_a(row, i);
    
    return p_a = std::move(result);
}

/**
 * @brief Converts a matrix to a stream in order to print it
 * 
 * @param p_flux         The target stream
 * @param p_a            The target matrix
 * @return std::ostream& The resulting stream of the conversion
 */
std::ostream&   Maths::operator<<  (std::ostream& p_flux, const Matrix& p_a) noexcept
{
    for (int row = 0; row < p_a.GetRow(); ++row)
        for (int column = 0; column < p_a.GetColumn(); ++column)
        {
            p_flux << p_a(row, column);

            if (column < p_a.GetColumn() - 1)
                p_flux << "\n";
            else
                p_flux << "\t|\t";
        }

    return p_flux;
}