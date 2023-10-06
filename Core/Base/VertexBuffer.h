#pragma once

#include<iostream>

#include"../../includes/GLM/glm/glm.hpp"
#include"./SVec.hpp"

namespace Abs
{
    class VertexBuffer
    {
        public:
        VertexBuffer(uint size = 2) : m_data(size) {}

        virtual void LoadBuffer(uint loadMode) = 0;
        virtual void Append(float *data, uint count) = 0;
        virtual void Clear() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        protected:
        SfVec m_data;
    };
}