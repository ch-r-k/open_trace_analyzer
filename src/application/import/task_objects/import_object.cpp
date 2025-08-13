
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

#include "application/task_object/task_object.hpp"
#include "import_object.hpp"

using Json = nlohmann::json;
using application::task_types::TaskObject;

namespace application::import
{
// void ImportObject::setConfig(FileConfig config) {}
void ImportObject::setFile(std::string file_name)
{
    this->file_name = file_name;
}

void ImportObject::getTaskObject(std::list<TaskObject>& lst)
{
    std::ifstream in(file_name);

    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_name);
    }

    Json json_data;
    in >> json_data;

    for (const auto& item : json_data)
    {
        TaskObject task_object{item.at("priority").get<std::uint32_t>(),
                               item.at("id").get<std::uint32_t>(),
                               item.at("name").get<std::string>()};

        lst.emplace_back(task_object);
    }
}

}  // namespace application::import