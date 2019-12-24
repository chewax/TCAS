#define BOOST_TEST_MODULE TCASSolutionTest
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "../core/Vector3.h"
#include "../core/Matrix.h"
#include "../core/Course.h"

using namespace std;
using namespace core;

BOOST_AUTO_TEST_CASE(Test_Vector3)
{
  //Test equality comparator
  Vector3 v0(1.0, 2.0, 3.0);
  Vector3 v1(1.0, 2.0, 3.0);
  BOOST_CHECK(v0 == v1);

  //Test not equal comparator
  Vector3 v2(4.0, 5.0, 6.0);
  BOOST_CHECK(v0 != v2);

  //Test add operator
  Vector3 r0(5.0, 7.0, 9.0);
  BOOST_CHECK(v0 + v2 == r0);

  //Test subtract operator
  Vector3 r1(3.0, 3.0, 3.0);
  BOOST_CHECK(v2 - v1 == r1);

  Vector3 r3 = Vector3(2*1.0, 2*2.0, 2*3.0);
  BOOST_CHECK(v0 * 2 == r3);

  //Test cross product1
  Vector3 x_prod = Vector3::cross(v0, v2);
  Vector3 res(-3.0, 6.0, -3.0);
  BOOST_CHECK(x_prod == res);

  //Test cross product2
  Vector3 v3(27.0, 103.0, 44.0);
  Vector3 x_prod2 = Vector3::cross(v0, v3);
  Vector3 res2(-221.0, 37.0, 49.0);
  BOOST_CHECK(x_prod2 == res2);

  //Test normalization
  v3.normalize();
  Vector3 res3(0.234349, 0.893998, 0.381902);
  BOOST_CHECK(v3 == res3);

  //Test magnitude
  double mag = v3.magnitude();
  BOOST_CHECK(mag == 1.0);
}

BOOST_AUTO_TEST_CASE(Test_Matrix)
{
  double mat[3][4] = {{3.0, 2.0, -4.0, 3.0},
                      {2.0, 3.0, 3.0, 15.0},
                      {5.0, -3, 1.0, 14.0}};

                
  Matrix m(mat);
  Vector3 calc_solution = m.gaussian_elimination();
  Vector3 res_solution(3.0, 1.0, 2.0);

  BOOST_CHECK(calc_solution == res_solution);
}

BOOST_AUTO_TEST_CASE(Test_Course1)
{
  Vector3 pos_a1(2.0, 2.0, 1.0);
  Vector3 dir_a1(0.0, 4.0, 0.0);
  Course a1(pos_a1, dir_a1);

  Vector3 pos_a2(4.0, 4.0, 0.0);
  Vector3 dir_a2(-4.0, 0.0, 0.0);
  Course a2(pos_a2, dir_a2);

  Course coll = Course::shortest_distance(a1, a2);
  coll.print("COLLISION");

  BOOST_CHECK(coll.position == Vector3(2.0, 4.0, 1.0));
  BOOST_CHECK(coll.direction == Vector3(0.0, 0.0, -1.0));
  BOOST_CHECK_EQUAL(coll.direction.magnitude(), 1.0);
  
};

BOOST_AUTO_TEST_CASE(Test_Course2)
{
  Course a1(2.0, 2.0, 6000.0, 360, 800.0);
  a1.print("AIRCRAFT 1");

  Course a2(4.0, 4.0, 6000.0, 270, 800.0);
  a2.print("AIRCRAFT 2");
  
  Course coll = Course::shortest_distance(a1, a2);
  coll.print("COLLISION");

  // BOOST_CHECK(coll.position == Vector3(2.0, 4.0, 1.0));
  // BOOST_CHECK(coll.direction == Vector3(0.0, 0.0, -1.0));
  // BOOST_CHECK_EQUAL(coll.direction.magnitude(), 1.0);
  
};