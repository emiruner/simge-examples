#include "MainWin.hpp"

#include <simge/glut/Application.hpp>

#include <cstdlib>
#include <vector>
#include <iostream>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    std::vector<int> x, y;
    int val;
    
    std::cout << "Please enter chart data by x, y value pairs.\n"
              << "Separate numbers only with whitespace.\n";
    
    while(std::cin >> val)
    {
        x.push_back(val);
        
        if(std::cin >> val)
        {
            y.push_back(val);
        }
        else
        {
            x.erase(x.end() - 1);
            break;
        }
    }
    
    MainWin sw(x, y);

    app.run();

    return 0;
}
