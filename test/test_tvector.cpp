#include "tmatrix.h"

#include <gtest.h>


TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(7);
    for (int i = 0; i < 7; i++)
        v[i] = i;

    TDynamicVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(7);
    for (int i = 0; i < 7; i++)
        v[i] = i;

    TDynamicVector<int> v1(v);
    v1[0] = 100;

    EXPECT_NE(v[0], v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(10);

    ASSERT_ANY_THROW(v.at(-2) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(10);

    ASSERT_ANY_THROW(v.at(11) = 11);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(10);
    v.at(5) = 5;
    v.at(7) = 7;

    v = v;

    EXPECT_EQ(5, v.at(5));
    EXPECT_EQ(7, v.at(7));
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    const size_t size = 4;
    TDynamicVector<int> v1(size), v2(size);

    for (int i = 0; i < size; i++) v2[i] = i;

    v1 = v2;

    EXPECT_EQ(3, v1[3]);
    EXPECT_EQ(0, v1[0]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(4), v2(15);

    for (int i = 0; i < 4; i++) v1[i] = i;
    v2 = v1;
    EXPECT_EQ(4, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(4), v2(15);

    for (int i = 0; i < 4; i++) v1[i] = i;
    v2 = v1;

    EXPECT_EQ(0, v1[0]);
    EXPECT_EQ(1, v1[1]);
    EXPECT_EQ(2, v1[2]);
    EXPECT_EQ(3, v1[3]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(7), v2(7);

    for (int i = 0; i < 7; i++) v1[i] = i;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(15);
    for (int i = 0; i < 15; i++) v[i] = 11;
    EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(4), v2(5);

    for (int i = 0; i < 4; i++) v1[i] = v2[i] = i;

    EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3);
    for (int i = 0; i < 3; i++) v[i] = i;
    v = v + 1;
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3);
    for (int i = 0; i < 3; i++) v[i] = i;
    v = v - 1;

    EXPECT_EQ(-1, v[0]);
    EXPECT_EQ(0, v[1]);
    EXPECT_EQ(1, v[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++) v[i] = i;
    v = v * 10;

    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(40, v[4]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(2), v2(2), v3;
    for (int i = 0; i < 2; i++) v1[i] = v2[i] = i;
    v3 = v1 + v2;

    EXPECT_EQ(0, v3[0]);
    EXPECT_EQ(2, v3[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(7);
    for (int i = 0; i < 3; i++) v1[i] = v2[i] = i;
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)  // нет необходимости отдельно делать тест на отстутствие исключений при вычитании?
{
    TDynamicVector<int> v1(5), v2(5), v;
    for (int i = 0; i < 5; i++) v1[i] = v2[i] = i;
    v = v1 - v2;

    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(0, v[4]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(5);
    for (int i = 0; i < 3; i++) v1[i] = v2[i] = i;
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3), v2(3);
    for (int i = 0; i < 3; i++) v1[i] = v2[i] = i;
    int res = v1 * v2;

    EXPECT_EQ(5, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(17), v2(25);
    for (int i = 0; i < 17; i++) v1[i] = v2[i] = 7;
    ASSERT_ANY_THROW(v1 * v2);
}

