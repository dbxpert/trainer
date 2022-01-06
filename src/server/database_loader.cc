#include "database_loader.h"

Table DatabaseLoader::Load(const SQLHDBC connection) {
  Table table;

  adapter_.Execute(sql_.c_str(), connection);

  while (true) {
    auto row_array = adapter_.Fetch();
    if (row_array.size() == 0) break;

    for(auto row = row_array.begin(); row != row_array.end(); ++row) {
      table.push_back(*row);
    }
  }

  return table;

}
