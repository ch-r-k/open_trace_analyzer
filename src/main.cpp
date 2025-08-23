#include <iostream>
#include "application/manager.hpp"

using application::ApplicationManager;

int main(int argc, char* argv[])
{
    try
    {
        static ApplicationManager app_manager{argc, argv};
        return app_manager.execute();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}