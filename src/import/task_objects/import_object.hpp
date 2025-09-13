#pragma once

#include <string>
#include <fstream>
#include "i_import_object.hpp"
//#include "3d_party/json/include/nlohmann/json.hpp"

namespace import
{
using types::task::TaskObject;

class ImportObject : public IImportObject
{
   public:
    ImportObject(const std::string& filename);
    ~ImportObject() = default;

    // void setConfig(FileConfig config) override;
    void getTaskObject(std::list<TaskObject>& lst) override;

   private:
    std::ifstream input_file;
};
}  // namespace import