#ifdef TESTING_MODE

#include<iostream>

#include "../../includes/GLM/glm/glm.hpp"

#define VERT2_SIZE 8
#define VERT3_SIZE 12
#define VERT3_RGB_SIZE 18

#define PI 3.1415926535
// it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
#define SINE_RES 20
#define AMP_Y 0.6

namespace Util
{
    typedef glm::ivec2 iVec2;
    typedef glm::fvec2 fVec2;
    typedef glm::ivec3 iVec3;
    typedef glm::fvec3 fVec3;

    //this generated vertex is for the index based draw call
    template<typename T>
    T* _get_rect_vert2(fVec2 pos, fVec2 dim)
    {
        T *temp = new T[VERT2_SIZE];

        float hw = dim.x/2;
		float hh = dim.y/2;

		temp[0] = pos.x - hw;
		temp[1] = pos.y + hh;
		temp[2] = pos.x + hw;
		temp[3] = pos.y + hh;
		temp[4] = pos.x + hw;
		temp[5] = pos.y - hh;
		temp[6] = pos.x - hw;
		temp[7] = pos.y - hh;

        return temp;
    }

    // three dimensional x, y, z
    template<typename T>
	T* _get_rect_ver3(fVec3 pos, fVec3 dim)
	{
		float *temp = new T[VERT3_SIZE];
		float hw = dim.x/2;
		float hh = dim.y/2;
        float hb = dim.z/2;

		temp[0] = pos.x - hw;
		temp[1] = pos.y + hh;
		temp[3] = pos.x + hw;
		temp[4] = pos.x + hh;
		temp[6] = pos.y + hw;
		temp[7] = pos.y - hh;
		temp[9] = pos.x - hw;
		temp[10] = pos.y - hh;

		temp[2] = pos.z - hb;
        temp[5] = pos.z + hb;
        temp[8] = pos.z - hb;
        temp[11] = pos.z + hb;

		return temp;
	}

	// temp generator for testing only
    template<typename T>
	T* _get_rect_ver3_col(fVec3 pos, fVec3 dim, fVec3 col)
    {
        T *temp = new T[VERT3_RGB_SIZE];

		for(int i=0; i<3;i++)
		{
			*(temp+6*i+3) = col.x;
			*(temp+6*i+4) = col.y;
			*(temp+6*i+5) = col.z;
		}

		// float hw = dim.x/2.0;
		// float hh = dim.y/2.0;

		// *(temp+0) = pos.x + hw;
		// *(temp+1) = pos.y + hh;

		// *(temp+6) = pos.x - hw;
		// *(temp+7) = pos.y - hh;

		// *(temp+12) = pos.x + hw;
		// *(temp+13) = pos.y - hh;

		float hw = dim.x/2;
		float hh = dim.y/2;

		temp[0] = pos.x - hw;
		temp[1] = pos.y + hh;

		temp[6] = pos.y + hw;
		temp[7] = pos.y - hh;

		temp[12] = pos.x - hw;
		temp[13] = pos.y - hh;

		return temp;
    }

	float* _get_sine_ver2(int freq)
	{
		float *temp = new float[SINE_RES*(freq*2+2)];
		float startPoint = -1.0f;
		float cycleOff = 2.0/freq;
		float xOff = cycleOff/SINE_RES;

		std::cout << "Cycle Offset " << cycleOff << " and XOffs is : " << xOff << std::endl;

		for(int i=0;i<freq;i++)
		{
			std::cout << "Starting Point is : " << startPoint << std::endl;
			for(int j=0;j<=SINE_RES;j++)
			{
				*(temp+2*i*SINE_RES+2*j) = startPoint+xOff*j;
				*(temp+2*i*SINE_RES+2*j+1) = abs(sin(2*PI*xOff*j/cycleOff) * AMP_Y)<0.0001f?0.0:(sin(2*PI*xOff*j/cycleOff) * AMP_Y);
			}
			startPoint+=cycleOff;
 		}

		return temp;
	}
}
#endif