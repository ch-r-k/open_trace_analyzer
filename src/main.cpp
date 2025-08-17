#include <iostream>
#include "application/manager.hpp"

using application::ApplicationManager;

int main(void)
{
    static ApplicationManager app_manager{};

    return app_manager.execute();
}