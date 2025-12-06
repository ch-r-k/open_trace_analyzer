#pragma once

#include <stdexcept>
#include <string>

namespace import::txt_config
{

class TxtImportException : public std::runtime_error
{
   public:
    explicit TxtImportException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

}  // namespace import::txt_config