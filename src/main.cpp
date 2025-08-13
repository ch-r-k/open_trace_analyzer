#include <iostream>
#include "application/app.hpp"

using application::App;

int main(void)
{
    static App app;

    try
    {
        app.execute();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}