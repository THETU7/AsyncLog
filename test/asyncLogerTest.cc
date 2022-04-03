#include "src/LogFile.h"
#include "src/Logging.h"
#include <fstream>
#include <gtest/gtest.h>

/*
 *TEST(TESTLogFile, TESTWRITE) {
 *  AsyncLog::LogFile lf;
 *  lf.append("just test");
 *  lf.flush();
 *  EXPECT_EQ(9, lf.wirtedBytes());
 *}
 */

TEST(TESTLogging, TESTAPPEND) {
  AsyncLog::Logging lg;
  lg.append("logging test");
  lg.output();
}
