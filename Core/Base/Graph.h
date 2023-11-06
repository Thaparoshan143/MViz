#pragma once

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

    enum NumberingInfo
    {
        CONCISE = 1,
        NORMAL = 2,
        EXTEND = 4                
    };

    #define DEFAULT_DIM iVec2(600, 400)

    struct GraphInfo
    {
        public:
        GraphInfo() : title("-Graph-"), dim(DEFAULT_DIM), screenpos(ScreenPosition::TOP_RIGHT), numinfo(NORMAL) {}
        GraphInfo(String t, iVec2 d, ScreenPosition sp, NumberingInfo ni)
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
        // Numering info will hold the resolution of the vertical/horizontal line for the graph
        NumberingInfo numinfo;
    };

    class Graph
    {
        public:
        Graph();
        Graph(GraphInfo &gi) {  m_gi = gi;  }

        protected:
        GraphInfo m_gi;        
    };
}