#pragma once

#include <string>
#include "i_import_object.hpp"
//#include "3d_party/json/include/nlohmann/json.hpp"

namespace application::import
{
using application::task_types::TaskObject;

class ImportObject  //: public IImportObject
{
   public:
    ImportObject() = default;
    ~ImportObject() = default;

    // void setConfig(FileConfig config) override;
    void setFile(std::string file_name);
    void getTaskObject(std::list<TaskObject>& lst);

   private:
    std::string file_name;
};
}  // namespace application::import