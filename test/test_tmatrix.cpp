#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> v1(3);
	v1[0] = 3;
	TMatrix<int> v(v1);
	EXPECT_EQ(v, v1);

}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> v(3), v1(4);
	v = v1;
	EXPECT_EQ(v, v1);
	EXPECT_EQ(4, v1.GetSize());
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(m.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[0][1] = 4;
	int a = m[0][1];
	EXPECT_EQ(m[0][1], a);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[0][-3] = 4);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[0][6] = 4);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> A(5);
	ASSERT_NO_THROW(A = A);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> v(3), v1(3);
	v[0][1] = 777;
	v1 = v;
	EXPECT_EQ(v1, v);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> v(3), v1(4);
	v = v1;
	EXPECT_EQ(4, v.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> v(3), v1(4);
	v1[0][1] = 5;
	v = v1;
	EXPECT_EQ(5, v[0][1]);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> v(3), v1(3);
	v[1][1] = 1337;
	v1[1][1] = 1337;
	EXPECT_TRUE(v == v1);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> v(3);
	v[0][1] = 1337;
	EXPECT_TRUE(v == v);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> v(3), v1(4);
	EXPECT_TRUE(v != v1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> v(3), v1(3);
	v[0][1] = 3;
	v1 = v1 + v;
	EXPECT_EQ(v1[0][1], 3);

}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> v(3), v1(4);
	v[0][1] = 3;
	ASSERT_ANY_THROW(v1 = v1 + v);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> v(3), v1(3);
	v[0][1] = 3;
	v1 = v1 - v;
	EXPECT_EQ(v1[0][1], -3);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> v(3), v1(4);
	v[0][1] = 3;
	ASSERT_ANY_THROW(v1 = v1 - v);
}

