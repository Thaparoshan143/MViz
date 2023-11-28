#pragma once

#include<vector>

#include"./Types.h"

namespace Abs
{
    enum NumberingScale
    {
        CONCISE = 11,
        NORMAL = 21,
        EXTEND = 41                
    };

    class Graph
    {
        public:
        Graph(NumberingScale numScale): m_numScale(numScale) {}

        protected:
        std::vector<String> m_numberLabel;
        NumberingScale m_numScale;
    };
}