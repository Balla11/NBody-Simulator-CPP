#include <gtest/gtest.h>
#include "Vector2.hpp"
#include "Body.hpp"


// --- VECTOR2 TESTS ---
TEST(VectorMath, Addition) {
  Vector2 v1(10.0, -5.0);
  Vector2 v2(5.0, 5.0);
  Vector2 result = v1 + v2;

  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
}


TEST(VectorMath, NormCalculation) {
  Vector2 v(3.0, 4.0);
  EXPECT_DOUBLE_EQ(v.norm(), 5.0);
}


TEST(VectorMath, CompoundAddition) {
  Vector2 v1(1.0, 1.0);
  v1 += Vector2(2.0, 3.0);

  EXPECT_DOUBLE_EQ(v1.x, 3.0);
  EXPECT_DOUBLE_EQ(v1.y, 4.0);
}

// --- PHYSICS TESTS ---
TEST(BodyTest, PhysicsMovement) {
  Body b ({0, 0}, {0, 0}, 2.0);
  b.applyForce({10.0, 0.0});
  EXPECT_DOUBLE_EQ(b.acceleration.x, 5.0);

  // Update system after 1 second
  b.update(1.0);
  EXPECT_DOUBLE_EQ(b.velocity.x, 5.0);
  EXPECT_DOUBLE_EQ(b.velocity.y, 0.0);
  EXPECT_DOUBLE_EQ(b.position.x, 5.0);
  EXPECT_DOUBLE_EQ(b.position.y, 0.0);
  EXPECT_DOUBLE_EQ(b.acceleration.x, 0.0);

}