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

    #define DEFAULT_DIM iVec2(600, 400)
    #define DEFAULT_RES iVec2(20, 20)

    struct GraphInfo
    {
        public:
        GraphInfo() : title("-Graph-"), dim(DEFAULT_DIM), resolution(DEFAULT_RES), screenpos(ScreenPosition::TOP_RIGHT) {}
        GraphInfo(String t, iVec2 d, iVec2 r, ScreenPosition sp)
        {
            title = t;
            dim = d;
            resolution = r;
            screenpos = sp;
        }

        protected:
        String title;
        // Here dim is, width and height
        // rersolution menas the total graoh line in each axis i.e total line in x, total line in y
        iVec2 dim, resolution;
        ScreenPosition screenpos;
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