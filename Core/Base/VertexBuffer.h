#pragma once

#include<iostream>

#include"./Types.h"
#include"./SVec.hpp"

namespace Abs
{
    class VertexBuffer
    {
        public:
        VertexBuffer(uint size = 2) : m_data(size) {}

        virtual void LoadBuffer(uint loadMode) = 0;
        virtual void Append(float *data, uint count) {  m_data.Append(data, count); };
        void Clear() {  m_data.Clear(); };
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        protected:
        SfVec m_data;
    };
}