#include <iostream>
#include "application/manager.hpp"

using application::ApplicationManager;

int main(int argc, char* argv[])
{
    static ApplicationManager app_manager{argc, argv};

    return app_manager.execute();
}