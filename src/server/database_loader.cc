#include "database_loader.h"

Table DatabaseLoader::Load() {
  Table table;

  adapter_.Execute(sql_.c_str(), connector_.GetConnection());

  while (true) {
    auto row_array = adapter_.Fetch();
    if (row_array.size() == 0) break;

    for(auto row = row_array.begin(); row != row_array.end(); ++row) {
      table.push_back(*row);
    }
  }

  return table;

}
