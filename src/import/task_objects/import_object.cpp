
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

#include "types/task_object/task_object.hpp"
#include "import_object.hpp"

using Json = nlohmann::json;
using types::task::TaskObject;

namespace import
{
ImportObject::ImportObject(const std::string& filename) : input_file(filename)
{
    if (!input_file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

void ImportObject::getTaskObject(std::list<TaskObject>& lst)
{
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    Json json_data;
    input_file >> json_data;

    for (const auto& item : json_data)
    {
        TaskObject task_object{item.at("priority").get<std::uint32_t>(),
                               item.at("id").get<std::string>(),
                               item.at("name").get<std::string>()};

        lst.emplace_back(task_object);
    }
}

}  // namespace import