/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-31 16:51                                           *
 * @ File: LogFile.h                                                  *
 *                                                                    *
 * @ Description: log info to file                                    *
 **********************************************************************/
#ifndef LOGFILE_H
#define LOGFILE_H

#include "noncopyable.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

namespace AsyncLog {
using namespace std;
class LogFile : noncopyable {
public:
  LogFile();
  LogFile(const string &basename);
  ~LogFile() { os.close(); }
  void append(const string &);
  void append(const char *, size_t len);
  void flush();
  void rollfile();
  size_t wirtedBytes() const;
  string getfilename() {
    return string(path + basename + "-" + date + "-" + mechan + ".log");
  };

private:
  void initFile();
  void setDate() {
    char buf[16];
    if (strftime(buf, 16, "%F", localtime(&lastTime)) == 0) {
      cerr << "buffer size 16 is too small\n" << endl;
    }
    date = buf;
  };

private:
  ofstream os;
  string path;
  string basename;
  string date;
  time_t lastTime;
  string mechan;
  size_t bytes{0};
};
} // namespace AsyncLog

#endif
