#ifdef TESTING_MODE

#ifndef VERTGENERATOR_HPP
#define VERTGENERATOR_HPP

#pragma once

#include<iostream>

#include"./Types.h"
#include "../../includes/GLM/glm/glm.hpp"

#define VERT2_SIZE 8
#define VERT3_SIZE 12
#define VERT3_RGB_SIZE 18

#define PI 3.1415926535

namespace Util
{
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

	float* _get_sine_ver2(int freq, int res, double amp)
	{
		float *temp = new float[res*(freq*2+2)];
		float startPoint = -1.0f;
		float cycleOff = 2.0/freq;
		float xOff = cycleOff/res;

		std::cout << "Cycle Offset " << cycleOff << " and XOffs is : " << xOff << std::endl;

		for(int i=0;i<freq;i++)
		{
			std::cout << "Starting Point is : " << startPoint << std::endl;
			for(int j=0;j<=res;j++)
			{
				*(temp+2*i*res+2*j) = startPoint+xOff*j;
				*(temp+2*i*res+2*j+1) = abs(sin(2*PI*xOff*j/cycleOff) * amp)<0.0001f?0.0:(sin(2*PI*xOff*j/cycleOff) * amp);
			}
			startPoint+=cycleOff;
 		}

		return temp;
	}

	template<typename T>
	T _random_num(T start = 0, T end = 1)
	{
		T random = ((T) rand()) / (T) RAND_MAX;
		return start + (end - start) * random;
	}

	template<typename T>
	T _print_ptr(T *data, uint c)
	{
		for(uint i=0;i<c;i++)
		{
			std::cout << i+1 << " - " << *(data+c) << std::endl;
		}
	}

	template<typename T>
	T* _allocate_block(uint s)
	{
		return new T[s];
	}

	template<typename T>
	void _copy_block(T *des, T *src, uint s)
	{
		if(des == nullptr || src == nullptr)
		{
			std::cout << "Either pointer is NULL" << std::endl;
			exit(0);
		}
		for(uint i=0;i<s;i++)
		{
			*(des+i) = *(src+i);
		}
	}

	template<typename T>
	void _copy_block_offset(T *des, T* src, uint s, uint eoff)
	{
		if(des==nullptr || src==nullptr)
		{
			std::cout << "Pointer is NULL" << std::endl;
			exit(0);
		}
		for(uint i=0;i<s;i++)
		{
			*(des+i*(eoff+1))=*(src+i);
		}
	}

	template<typename T>
	void _copy_block_f(T *des, T* src, uint s, uint *ods, bool (*fptr)(int))
	{
		if(des==nullptr || src==nullptr)
		{
			std::cout << "Pointer is NULL" << std::endl;
			exit(0);
		}
		int desCount=0;
		for(uint i=0;i<s;i++)
		{
			if(fptr(*(src+i)))
			{
				*(des+desCount)=*(src+i);
				desCount++;
			}
		}
		*(ods)=desCount;
	}

	void _print_string(const char *s)
	{
		std::cout << s << std::endl;
 	}

	template<typename T>
	void _print_tval(const char *s, T n)
	{
		std::cout << s << n << std::endl;
	}
}
#endif

#endif