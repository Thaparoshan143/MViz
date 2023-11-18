#include "../calculator.cpp"
#include<vector>

int main() {
    std::string text = "e^x";
    float mresult[100];
    std::vector<int> indexList;

    for(int i=0;i<text.length();i++)
    {
        if(text[i]=='x')
        {
            indexList.push_back(i);
        }
    }
    std::cout << "Index list vector size : " << indexList.size() << std::endl;
    for(int i : indexList)
    {
        std::cout << "Index list in vector : " << i << std::endl;

    }
    for(int i=-10;i<10;i++)
    {
        for(int j=0;j<indexList.size();j++)
        {
            text[indexList[j]] = 48 + i % 10;
            std::cout << "text value : " << i << std::endl;

        }
        mresult[i] = Calculator(text);
    }

    for (int i = 0; i < 100; i++) {
        std::cout << mresult[i] << "   ";
    }
    return 0;
}