#include "server/database_connector.h"
#include "gtest/gtest.h"

TEST(DatabaseConnectorTest, get_connection) {
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");
  EXPECT_TRUE(connector.IsConnected());
  EXPECT_NO_THROW(
    connector.GetConnection();
  );
}
