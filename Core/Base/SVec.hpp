#ifndef SVEC_HPP
#define SVEC_HPP

#pragma once

#include<iostream>

namespace Abs
{
    template<typename T>
    class SVec
    {
        public:
        SVec()
        {
            mCap = 2;
            data = new T[this->mCap];
            count = 0;
        }

        SVec(uint sSize)
        {
            mCap = sSize;
            data = new T[this->mCap];
            count = 0;
        }

        SVec(SVec &svec)
        {
            this->mCap = svec.mCap;
            this->data = new T[this->mCap];
            copy(this->data, svec.data, svec.count);
            this->count = svec.count;
        }

        void Append(T *d, uint c)
        {
            while(this->count + c >= mCap)
            {
                expand();
            }
            copy((this->data+count), d, c);
            this->count+=c;
        }

        // the clear will start cleaning from the last decrementing the count;
        void Clear(uint c=0)
        {
            // for now the data itself is not clear rather the length is shifted to forward 
            if(c==0)
            {
                this->count = 0;
            }
            else
            {
                this->count -= c;
            }
        }

        inline uint GetCount() {   return this->count; }
        
        inline uint GetMCap()   {   return this->mCap;  }

        inline T* GetData() { return this->data;    }

        private:
        T *data;
        uint count;
        uint mCap;

        void expand(float factor = 1.5)
        {
            this->mCap *= 1.5;
            std::cout << "Expanding the array!!" << " || New Size : " << this->mCap << std::endl;
            T *temp = new T[this->mCap];
            copy(temp, this->data, this->count);
            delete[] this->data;
            this->data = temp;
        }

        void copy(T *des, T *src, uint count)
        {
            for(uint i=0;i<count;i++)
            {
                *(des+i) = *(src+i);
            }
        }
    };

    using SfVec = SVec<float>;
    using SiVec = SVec<int>;
    using SuiVec = SVec<unsigned int>;
}

#endif