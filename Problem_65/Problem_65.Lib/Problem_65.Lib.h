#pragma once

#include <boost/multiprecision/cpp_int.hpp>

int coefficient(int n);
boost::multiprecision::cpp_int convergentNumerator(int n);
int digitSum(boost::multiprecision::cpp_int n);

