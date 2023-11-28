// This file contains all the typedef required for this applications for basic workload 
#pragma once

#include<iostream>

#include"../../includes/GLM/glm/glm.hpp"

typedef std::string String;
typedef glm::ivec2 iVec2;
typedef glm::dvec2 dVec2;
typedef glm::fvec2 fVec2;
typedef glm::ivec3 iVec3;
typedef glm::dvec3 dVec3;
typedef glm::fvec3 fVec3;
typedef glm::dvec4 dVec4;
typedef glm::fvec4 fVec4;
typedef dVec3 Color;

typedef glm::mat4 Mat4;
typedef glm::fmat4 fMat4;

typedef unsigned int uint;

typedef dVec2 Point2;
typedef dVec2 Size2;

typedef void (*ClickEventCallback)();
