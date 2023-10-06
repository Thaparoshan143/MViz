#include<iostream>

typedef std::string String;

namespace Abs
{
    class Application
    {
        public:
        Application() {}

        virtual void Initialize() = 0;
        virtual void Loop() = 0;

        protected:
        String m_name;
    };
}