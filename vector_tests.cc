#include <gtest/gtest.h>

#include "vector.h"

TEST(VectorConstructorSuite, DefaultConstructor) {
  cpp::vector<int> my_vector;
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.begin() == nullptr);
  ASSERT_TRUE(my_vector.begin() == my_vector.end());
  ASSERT_TRUE(my_vector.empty());
}

TEST(VectorConstructorSuite, ParameterConstructor) {
  cpp::vector<int> my_vector(3);
  std::vector<int> std_vector(3);
  for (int i = 0; i < 3; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
  ASSERT_TRUE(my_vector.size() == 3);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 3);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorConstructorSuite, ZeroConstructor) {
  cpp::vector<int> my_vector(0);
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.begin() == my_vector.end());
  ASSERT_TRUE(my_vector.empty());
}

TEST(VectorConstructorSuite, NegativeConstrustor) {
  ASSERT_THROW(cpp::vector<int> my_vector(-3), std::bad_array_new_length);
}

TEST(VectorConstructorSuite, OneElementList) {
  cpp::vector<int> my_vector{3};
  std::vector<int> std_vector{3};
  ASSERT_TRUE(my_vector.size() == 1);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  ASSERT_TRUE(my_vector[0] == 3);
  ASSERT_TRUE(my_vector[0] == std_vector[0]);
}

TEST(VectorConstructorSuite, ThreeElementList) {
  cpp::vector<int> my_vector{3, 7, 4};
  std::vector<int> std_vector{3, 7, 4};
  ASSERT_TRUE(my_vector.size() == 3);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 3);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 3; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorConstructorSuite, InitializerListConstructor) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6};
  for (int i = 0; i < 6; i++) ASSERT_TRUE(my_vector[i] = std_vector[i]);
  ASSERT_TRUE(my_vector.size() == 6);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 6);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorConstructorSuite, InitializerListEmpty) {
  cpp::vector<int> my_vector = {};
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.begin() == my_vector.end());
  ASSERT_TRUE(my_vector.empty());
}

TEST(VectorConstructorSuite, InitializerListNew) {
  int *v1 = new int[5];
  cpp::vector<int *> my_vector{v1, v1, v1};
  std::vector<int *> std_vector{v1, v1, v1};
  ASSERT_TRUE(my_vector.size() == 3);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 3);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  delete[] v1;
}

TEST(VectorConstructorSuite, CopyConstructor) {
  cpp::vector<int> my_vector = {1, 2, 3};
  cpp::vector<int> my_vector_copy(my_vector);
  std::vector<int> std_vector = {1, 2, 3};
  std::vector<int> std_vector_copy(std_vector);
  for (int i = 0; i < 3; i++)
    ASSERT_TRUE(my_vector_copy[i] == std_vector_copy[i]);
  ASSERT_TRUE(my_vector_copy.size() == 3);
  ASSERT_TRUE(my_vector_copy.size() == my_vector.size());
  ASSERT_TRUE(my_vector_copy.size() == std_vector_copy.size());
  ASSERT_TRUE(my_vector_copy.capacity() == 3);
  ASSERT_TRUE(my_vector_copy.capacity() == my_vector.capacity());
  ASSERT_TRUE(my_vector_copy.capacity() == std_vector_copy.capacity());
}

TEST(VectorConstructorSuite, CopyConstructorCapacity) {
  cpp::vector<int> my_vector = {1, 2, 3};
  my_vector.push_back(9);
  cpp::vector<int> my_vector_copy(my_vector);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(9);
  std::vector<int> std_vector_copy(std_vector);
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(my_vector_copy[i] == std_vector_copy[i]);
  ASSERT_TRUE(my_vector_copy.size() == my_vector.size());
  ASSERT_TRUE(my_vector_copy.size() == std_vector_copy.size());
  // funky one: copied vectors's capacity ALWAYS equals its' size
  ASSERT_TRUE(my_vector_copy.capacity() == std_vector_copy.capacity());
}

TEST(VectorMoveConstructorSuite, SimpleMove) {
  cpp::vector<int> my_vector = {1, 2, 3};
  my_vector.push_back(9);
  cpp::vector<int> my_vector_move(std::move(my_vector));
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(9);
  std::vector<int> std_vector_move(std::move(std_vector));
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(my_vector_move[i] == std_vector_move[i]);
  ASSERT_TRUE(my_vector_move.size() == std_vector_move.size());
  // move constructor keeps capacity the same
  ASSERT_TRUE(my_vector_move.capacity() == std_vector_move.capacity());
}

TEST(VectorMoveAssigmentSuite, MoveAssign) {
  cpp::vector<int> my_vector = {1, 2, 3};
  my_vector.push_back(9);
  cpp::vector<int> my_vector_move = my_vector;
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(9);
  std::vector<int> std_vector_move = std_vector;
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(my_vector_move[i] == std_vector_move[i]);
  ASSERT_TRUE(my_vector_move.size() == std_vector_move.size());
  ASSERT_TRUE(my_vector_move.capacity() == std_vector_move.capacity());
}

TEST(VectorMoveAssigmentSuite, ClearPrevious) {
  cpp::vector<int> my_vector = {1, 2, 3};
  my_vector.push_back(9);
  cpp::vector<int> my_vector_move = {4, 5, 6, 7, 8};
  my_vector_move = std::move(my_vector);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(9);
  std::vector<int> std_vector_move = {4, 5, 6, 7, 8};
  std_vector_move = std::move(std_vector);
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(my_vector_move[i] == std_vector_move[i]);
  ASSERT_TRUE(my_vector_move.size() == std_vector_move.size());
  ASSERT_TRUE(my_vector_move.capacity() == std_vector_move.capacity());
}

TEST(VectorAtSuite, NormalAt) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  for (int i = 0; i < 7; i++) ASSERT_TRUE(my_vector.at(i) == std_vector.at(i));
}

TEST(VectorAtSuite, ExceptionAt) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_THROW(my_vector.at(my_vector.size()), std::out_of_range);
  ASSERT_THROW(std_vector.at(std_vector.size()), std::out_of_range);
}

TEST(VectorAtSuite, ExceptionAtCapacity) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  my_vector.push_back(9);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.push_back(9);
  ASSERT_THROW(my_vector.at(my_vector.size()), std::out_of_range);
  ASSERT_THROW(std_vector.at(std_vector.size()), std::out_of_range);
}

TEST(VectorOperatorAtSuite, NormalOperatorAt) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  for (int i = 0; i < 7; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

// Technically, we are testing that
// undefined behaviour will throw no exceptions
// Segmentation fault is possible on another OS
TEST(VectorOperatorAt, OutOfBorders) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_NO_THROW(my_vector[my_vector.size()]);
  ASSERT_NO_THROW(std_vector[std_vector.size()]);
}

TEST(VectorFrontBackSuite, Front) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(my_vector.front() == std_vector.front());
  ASSERT_TRUE(my_vector.front() == *my_vector.begin());
}

TEST(VectorFrontBackSuite, Back) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(my_vector.back() == std_vector.back());
  ASSERT_TRUE(my_vector.back() == *std::prev(my_vector.end()));
}

TEST(VectorFrontBackSuite, BackCapacity) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  my_vector.push_back(9);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.back() == std_vector.back());
  ASSERT_TRUE(my_vector.back() == *std::prev(my_vector.end()));
}

TEST(VectorFrontBackSuite, FrontAndBack) {
  cpp::vector<int> my_vector = {1};
  std::vector<int> std_vector = {1};
  ASSERT_TRUE(my_vector.front() == std_vector.front());
  ASSERT_TRUE(my_vector.front() == *my_vector.begin());
  ASSERT_TRUE(my_vector.back() == std_vector.back());
  ASSERT_TRUE(my_vector.back() == *std::prev(my_vector.end()));
  ASSERT_TRUE(my_vector.front() == my_vector.back());
}

TEST(VectorFrontBackSuite, FrontAndBackReserve) {
  cpp::vector<int> my_vector = {1};
  std::vector<int> std_vector = {1};
  my_vector.reserve(2);
  std_vector.reserve(2);
  ASSERT_TRUE(my_vector.front() == std_vector.front());
  ASSERT_TRUE(my_vector.front() == *my_vector.begin());
  ASSERT_TRUE(my_vector.back() == std_vector.back());
  ASSERT_TRUE(my_vector.back() == *std::prev(my_vector.end()));
  ASSERT_TRUE(my_vector.front() == my_vector.back());
}

TEST(VectorDataSuite, Data) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  int *my_vector_data = my_vector.data();
  int *std_vector_data = std_vector.data();
  for (int i = 0; i < 7; i++)
    ASSERT_TRUE(my_vector_data[i] == std_vector_data[i]);
}

// If size() is ​0​, data() may or may not return a null pointer
TEST(VectorDataSuite, EmptyVector) {
  cpp::vector<int> my_vector(0);
  std::vector<int> std_vector(0);
  ASSERT_NO_THROW(my_vector.data());
  ASSERT_NO_THROW(std_vector.data());
}

TEST(VectorDataSuite, EmptyVectorReserve) {
  cpp::vector<int> my_vector(0);
  std::vector<int> std_vector(0);
  my_vector.reserve(2);
  std_vector.reserve(2);
  ASSERT_NO_THROW(my_vector.data());
  ASSERT_NO_THROW(std_vector.data());
}

TEST(VectorBeginEndSuite, Begin) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(*my_vector.begin() == *std_vector.begin());
}

TEST(VectorBeginEndSuite, End) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(*std::prev(my_vector.end()) == *std::prev(std_vector.end()));
}

TEST(VectorBeginEndSuite, EndReserve) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  my_vector.reserve(9);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.reserve(9);
  ASSERT_TRUE(*std::prev(my_vector.end()) == *std::prev(std_vector.end()));
}

TEST(VectorBeginEndSuite, BeginEndSuite) {
  cpp::vector<int> my_vector(0);
  std::vector<int> std_vector(0);
  ASSERT_TRUE(my_vector.begin() == my_vector.end());
}

TEST(VectorBeginEndSuite, BeginEndReserveSuite) {
  cpp::vector<int> my_vector(0);
  my_vector.reserve(9);
  std::vector<int> std_vector(0);
  std_vector.reserve(9);
  ASSERT_TRUE(my_vector.begin() == my_vector.end());
  ASSERT_TRUE(std_vector.begin() == std_vector.end());
}

TEST(VectorEmptySuite, IsEmpty) {
  cpp::vector<int> my_vector(0);
  std::vector<int> std_vector(0);
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
}

TEST(VectorEmptySuite, IsEmptyReserve) {
  cpp::vector<int> my_vector(0);
  my_vector.reserve(9);
  std::vector<int> std_vector(0);
  std_vector.reserve(9);
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
}

TEST(VectorEmptySuite, NotEmpty) {
  cpp::vector<int> my_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  ASSERT_FALSE(my_vector.empty());
  ASSERT_FALSE(std_vector.empty());
}

TEST(VectorSizeSuite, SizeEmpty) {
  cpp::vector<int> my_vector;
  std::vector<int> std_vector;
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
}

TEST(VectorSizeSuite, SizeFixed) {
  cpp::vector<int> my_vector(9);
  std::vector<int> std_vector(9);
  ASSERT_TRUE(my_vector.size() == 9);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
}

TEST(VectorSizeSuite, SizeAuto) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  ASSERT_TRUE(my_vector.size() == 5);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
}

TEST(VectorSizeSuite, SizeReserved) {
  cpp::vector<int> my_vector(9);
  std::vector<int> std_vector(9);
  my_vector.reserve(12);
  std_vector.reserve(12);
  ASSERT_TRUE(my_vector.size() == 9);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
}

TEST(VectorReserveSuite, ReserveMore) {
  cpp::vector<int> my_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  my_vector.reserve(12);
  std_vector.reserve(12);
  ASSERT_TRUE(my_vector.capacity() == 12);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorReserveSuite, ReserveLess) {
  cpp::vector<int> my_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  my_vector.reserve(2);
  std_vector.reserve(2);
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorCapacitySuite, CapacityNotChanged) {
  cpp::vector<int> my_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  my_vector.reserve(4);
  std_vector.reserve(4);
  my_vector.push_back(9);
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorCapacitySuite, CapacityDoubled) {
  cpp::vector<int> my_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  my_vector.push_back(9);
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.capacity() == 6);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorCapacitySuite, CapacityDoubledAgain) {
  cpp::vector<int> my_vector = {1};
  std::vector<int> std_vector = {1};
  my_vector.push_back(9);
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.capacity() == 2);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  my_vector.push_back(3);
  std_vector.push_back(3);
  my_vector.push_back(7);
  std_vector.push_back(7);
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorShrinkToFitSuite, ShrinkToFitSimple) {
  cpp::vector<int> my_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  my_vector.reserve(4);
  std_vector.reserve(4);
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  ASSERT_TRUE(my_vector.capacity() == 3);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorShrinkToFitSuite, ShrinkToFitNew) {
  cpp::vector<int> my_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  my_vector.push_back(9);
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.capacity() == 6);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorShrinkToFitSuite, ShrinkToFitEmpty) {
  cpp::vector<int> my_vector = {1};
  std::vector<int> std_vector = {1};
  my_vector.pop_back();
  std_vector.pop_back();
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorShrinkToFitSuite, ShrinkToFitNothing) {
  cpp::vector<int> my_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  my_vector.reserve(4);
  std_vector.reserve(4);
  my_vector.push_back(9);
  std_vector.push_back(9);
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
}

TEST(VectorClearSuite, ClearSimple) {
  cpp::vector<int> my_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  my_vector.clear();
  std_vector.clear();
  ASSERT_TRUE(my_vector.capacity() == 4);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
}

TEST(VectorClearSuite, ClearEmpty) {
  cpp::vector<int> my_vector = {};
  std::vector<int> std_vector = {};
  my_vector.clear();
  std_vector.clear();
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
}

TEST(VectorClearSuite, ClearEmpty2) {
  cpp::vector<int> my_vector;
  std::vector<int> std_vector;
  my_vector.clear();
  std_vector.clear();
  ASSERT_TRUE(my_vector.capacity() == 0);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
}

TEST(VectorClearSuite, ClearNew) {
  int *filler = new int[5];
  cpp::vector<int *> my_vector{filler};
  std::vector<int *> std_vector{filler};
  my_vector.clear();
  std_vector.clear();
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.empty());
  ASSERT_TRUE(std_vector.empty());
  delete[] filler;
}

TEST(VectorInsertSuite, InsertSomewhere) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int>::iterator iterator_std =
      std_vector.insert(std_vector.begin(), 9);
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert(my_vector.begin(), 9);
  ASSERT_TRUE(*my_iterator == 9);
  ASSERT_TRUE(*my_iterator == *iterator_std);
  ASSERT_TRUE(my_vector.size() == 8);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 14);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 8; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorInsertSuite, InsertEmpty) {
  cpp::vector<int> my_vector;
  std::vector<int> std_vector;
  std::vector<int>::iterator iterator_std =
      std_vector.insert(std_vector.begin(), 9);
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert(my_vector.begin(), 9);
  ASSERT_TRUE(*my_iterator == 9);
  ASSERT_TRUE(*my_iterator == *iterator_std);
  ASSERT_TRUE(my_vector.size() == 1);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 1; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorInsertSuite, InsertSomewhereElse) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  my_vector.reserve(10);
  std_vector.reserve(10);
  std::vector<int>::iterator iterator_std =
      std_vector.insert(std_vector.begin() + 5, 9);
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert(my_vector.begin() + 5, 9);
  ASSERT_TRUE(*my_iterator == 9);
  ASSERT_TRUE(*my_iterator == *iterator_std);
  ASSERT_TRUE(my_vector.size() == 8);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 10);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 8; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorInsertSuite, InsertInTheEnd) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int>::iterator iterator_std =
      std_vector.insert(std_vector.begin() + 5, 9);
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert(my_vector.begin() + 5, 9);
  ASSERT_TRUE(*my_iterator == 9);
  ASSERT_TRUE(*my_iterator == *iterator_std);
  ASSERT_TRUE(my_vector.size() == 8);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 14);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 8; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorEraseSuite, SimpleErase) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.erase(std_vector.begin());
  my_vector.erase(my_vector.begin());
  ASSERT_TRUE(my_vector.size() == 6);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 7);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 6; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorEraseSuite, EraseNew) {
  int *filler = new int[5];
  cpp::vector<int *> my_vector{filler};
  std::vector<int *> std_vector{filler};
  std_vector.erase(std_vector.begin());
  my_vector.erase(my_vector.begin());
  ASSERT_TRUE(my_vector.size() == 0);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  delete[] filler;
}

TEST(VectorEraseSuite, EraseInTheCenter) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.erase(std_vector.begin() + 5);
  my_vector.erase(my_vector.begin() + 5);
  ASSERT_TRUE(my_vector.size() == 6);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 7);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 6; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorEraseSuite, EraseInTheEnd) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.erase(std::prev(std_vector.end()));
  my_vector.erase(std::prev(my_vector.end()));
  ASSERT_TRUE(my_vector.size() == 6);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 7);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 6; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorPushBackSuite, PushBackReserve) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.push_back(9);
  my_vector.push_back(9);
  ASSERT_TRUE(my_vector.size() == 8);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 14);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 8; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorPushBackSuite, PushBackEmpty) {
  cpp::vector<int> my_vector;
  std::vector<int> std_vector;
  std_vector.push_back(9);
  my_vector.push_back(9);
  ASSERT_TRUE(my_vector.size() == 1);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 1);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 1; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorPushBackSuite, PushBackNew) {
  int *filler = new int[7]{1, 2, 3, 4, 5, 6, 7};
  cpp::vector<int *> my_vector{filler};
  std::vector<int *> std_vector{filler};
  my_vector.push_back(filler);
  std_vector.push_back(filler);
  ASSERT_TRUE(my_vector.size() == 2);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 2);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 7; i++) ASSERT_TRUE(my_vector[0][i] == std_vector[0][i]);
  delete[] filler;
}

// Calling pop_back on an empty container results in undefined behavior.
TEST(VectorPopBackSuite, PopBack) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7};
  std_vector.pop_back();
  my_vector.pop_back();
  ASSERT_TRUE(my_vector.size() == 6);
  ASSERT_TRUE(my_vector.size() == std_vector.size());
  ASSERT_TRUE(my_vector.capacity() == 7);
  ASSERT_TRUE(my_vector.capacity() == std_vector.capacity());
  for (int i = 0; i < 6; i++) ASSERT_TRUE(my_vector[i] == std_vector[i]);
}

TEST(VectorSwapSuite, SimpleSwap) {
  cpp::vector<int> my_vector_1 = {1, 2, 3, 4};
  cpp::vector<int> my_vector_2 = {5, 6, 7};
  std::vector<int> std_vector_1 = {1, 2, 3, 4};
  std::vector<int> std_vector_2 = {5, 6, 7};
  cpp::vector<int>::iterator my_begin_1 = my_vector_1.begin();
  cpp::vector<int>::iterator my_begin_2 = my_vector_2.begin();
  cpp::vector<int>::iterator my_end_1 = std::prev(my_vector_1.end());
  cpp::vector<int>::iterator my_end_2 = std::prev(my_vector_2.end());
  std::vector<int>::iterator std_begin_1 = std_vector_1.begin();
  std::vector<int>::iterator std_begin_2 = std_vector_2.begin();
  std::vector<int>::iterator std_end_1 = std::prev(std_vector_1.end());
  std::vector<int>::iterator std_end_2 = std::prev(std_vector_2.end());
  my_vector_1.swap(my_vector_2);
  std_vector_1.swap(std_vector_2);
  ASSERT_TRUE(*my_begin_1 == *my_vector_2.begin());
  ASSERT_TRUE(*my_begin_2 == *my_vector_1.begin());
  ASSERT_TRUE(*std_begin_1 == *std_vector_2.begin());
  ASSERT_TRUE(*std_begin_2 == *std_vector_1.begin());
  ASSERT_TRUE(*my_end_1 == *std::prev(my_vector_2.end()));
  ASSERT_TRUE(*my_end_2 == *std::prev(my_vector_1.end()));
  ASSERT_TRUE(*std_end_1 == *std::prev(std_vector_2.end()));
  ASSERT_TRUE(*std_end_2 == *std::prev(std_vector_1.end()));
  ASSERT_TRUE(my_vector_1.size() == std_vector_1.size());
  ASSERT_TRUE(my_vector_2.capacity() == std_vector_2.capacity());
}

TEST(VectorSwapSuite, SwapWithItself) {
  cpp::vector<int> my_vector_1 = {1, 2, 3, 4};
  std::vector<int> std_vector_1 = {1, 2, 3, 4};
  cpp::vector<int>::iterator my_begin_1 = my_vector_1.begin();
  cpp::vector<int>::iterator my_end_1 = std::prev(my_vector_1.end());
  std::vector<int>::iterator std_begin_1 = std_vector_1.begin();
  std::vector<int>::iterator std_end_1 = std::prev(std_vector_1.end());
  my_vector_1.swap(my_vector_1);
  std_vector_1.swap(std_vector_1);
  for (int i = 0; i < 4; i++) ASSERT_TRUE(my_vector_1[i] == std_vector_1[i]);
  ASSERT_TRUE(*my_begin_1 == *my_vector_1.begin());
  ASSERT_TRUE(*std_begin_1 == *std_vector_1.begin());
  ASSERT_TRUE(*my_end_1 == *std::prev(my_vector_1.end()));
  ASSERT_TRUE(*std_end_1 == *std::prev(std_vector_1.end()));
}

TEST(VectorEmplaceSuite, EmplaceTest) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5};
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert_many(my_vector.begin(), 6, 7, 8, 9);
  std::vector<int> std_vector = {6, 7, 8, 9, 1, 2, 3, 4, 5};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(my_vector[i] == std_vector[i]);
  ASSERT_TRUE(*my_iterator == 6);
}

TEST(VectorEmplaceSuite, EmplaceNothingTest) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5};
  cpp::vector<int>::iterator my_iterator = my_vector.insert_many(my_vector.begin());
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(my_vector[i] == std_vector[i]);
  ASSERT_TRUE(*my_iterator == 1);
}

TEST(VectorEmplaceSuite, EmplaceEmptyTest) {
  cpp::vector<int> my_vector = {};
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert_many(my_vector.begin(), 1, 2, 3, 4, 5);
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(my_vector[i] == std_vector[i]);
  ASSERT_TRUE(*my_iterator == 1);
}

TEST(VectorEmplaceSuite, EmplaceEndTest) {
  cpp::vector<int> my_vector = {1, 2, 3, 4, 5};
  cpp::vector<int>::iterator my_iterator =
      my_vector.insert_many(my_vector.end(), 6, 7, 8, 9);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(my_vector[i] == std_vector[i]);
  ASSERT_TRUE(*my_iterator == 6);
}

TEST(VectorEmplaceSuite, EmplaceBackTest) {
  cpp::vector<int> my_vector = {1, 2, 4, 5};
  my_vector.insert_many_back(3, 7, 8, 9);
  std::vector<int> std_vector = {1, 2, 4, 5, 3, 7, 8, 9};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(std_vector[i] == my_vector[i]);
}

TEST(VectorEmplaceSuite, EmplaceBackNothing) {
  cpp::vector<int> my_vector = {1, 2, 4, 5};
  my_vector.insert_many_back();
  std::vector<int> std_vector = {1, 2, 4, 5};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(std_vector[i] == my_vector[i]);
}

TEST(VectorEmplaceSuite, EmplaceBackEmpty) {
  cpp::vector<int> my_vector = {};
  my_vector.insert_many_back(1, 2, 4, 5);
  std::vector<int> std_vector = {1, 2, 4, 5};
  for (size_t i = 0; i < std_vector.size(); i++)
    ASSERT_TRUE(std_vector[i] == my_vector[i]);
}