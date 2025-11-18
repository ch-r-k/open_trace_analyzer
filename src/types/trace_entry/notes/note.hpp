#pragma once

#include <bits/c++config.h>
#include <cstdint>
#include <string>
#include "../trace_entry.hpp"

namespace types::trace
{

class Note : public TraceEntry
{
   public:
    Note(const std::size_t line_number,  //
         const std::uint64_t timestamp,  //
         std::string text);
    ~Note() = default;

    std::string getText();
    friend std::ostream& operator<<(std::ostream& os, const Note& p);

   private:
    std::string text;
};

}  // namespace types::trace