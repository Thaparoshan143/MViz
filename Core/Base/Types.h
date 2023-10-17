// This file contains all the typedef required for this applications for basic workload 
#pragma once

#include<iostream>

#include"../../includes/GLM/glm/glm.hpp"

typedef std::string String;
typedef glm::ivec2 iVec2;
typedef glm::dvec2 dVec2;
typedef unsigned int uint;

struct Point2 {
    double x;
    double y;
};

struct Size2 {
    double width;
    double height;
};