#pragma once

#include<vector>

#include"./Types.h"

namespace Abs
{
    // Later move to the UI part for now its ok
    enum ScreenPosition
    {   
        TOP_LEFT = 1,
        TOP_RIGHT = 2,
        BOTTOM_RIGHT = 3,
        BOTTOM_LEFT = 4
    };

    enum NumberingScale
    {
        CONCISE = 11,
        NORMAL = 21,
        EXTEND = 41                
    };

    #define DEFAULT_DIM iVec2(600, 400)

    struct GraphInfo
    {
        public:
        GraphInfo(String t, iVec2 d, ScreenPosition sp, NumberingScale ni)
        {
            title = t;
            dim = d;
            screenpos = sp;
            numinfo = ni;
        }

        String title;
        // Here dim is, width and height
        iVec2 dim;
        ScreenPosition screenpos;
        // Numering info will hold the resolution of the vertical/horizontal (used same for now..) line for the graph
        NumberingScale numinfo;
    };

    class Graph
    {
        public:
        Graph(GraphInfo &gi): m_gi(gi) {}

        protected:
        std::vector<String> m_numberLabel;
        GraphInfo m_gi;        
    };
}