#include <bits/c++config.h>
#include <cstdint>
#include <iostream>
#include "note.hpp"

namespace types::trace
{
Note::Note(const std::size_t line_number,  //
           const std::uint64_t timestamp,  //
           std::string text)
    : TraceEntry{line_number, timestamp, TraceEntry::TraceType::STATE_MACHINE},
      text{text}
{
}

std::string Note::getText() { return text; }

std::ostream& operator<<(std::ostream& os, const Note& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", Text: " << p.text;         //
    return os;
}
}  // namespace types::trace