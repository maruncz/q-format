#include <iostream>

int main()
{
    for(int i=1;i<8;++i)
    {
        for(int j=1;j<(8-i);++j)
        {
            std::cout << "(" << i << " ," << j << ")\n";
        }
    }
    return 0;
}
