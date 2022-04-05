/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-31 19:42                                           *
 * @ File: LogFile.cc                                                 *
 *                                                                    *
 * @ Description: for LogFile                                         *
 **********************************************************************/

#include "LogFile.h"
#include <iomanip>

namespace AsyncLog {

LogFile::LogFile() : path("./"), basename("LOG") { initFile(); }

LogFile::LogFile(const string &basename) : path("./"), basename("LOG") {
  initFile();
}

void LogFile::initFile() {
  auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());

  // 获取0点0时的time_t
  lastTime = now - now % (24 * 3600);
  setDate();
  char hostbuf[_SC_HOST_NAME_MAX];
  if (gethostname(hostbuf, _SC_HOST_NAME_MAX) < 0) {
    cerr << "gethostname error" << endl;
  }
  mechan = hostbuf;
  os = ofstream();
  os.open(getfilename(), ios::out | ios::app);
}

void LogFile::append(const string &con) {
  rollfile();
  os << con;
  bytes += con.length();
}

void LogFile::flush() { os.flush(); }

size_t LogFile::wirtedBytes() const { return bytes; }

void LogFile::rollfile() {
  time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
  if (now - lastTime >= 24 * 3600) {
    lastTime = now - now % (24 * 3600);
    setDate();
    os.close();
    os.open(getfilename(), ios::out | ios::app);
  }
}

void LogFile::append(const char *buf, size_t len) {
  if (len == 0)
    return;
  rollfile();
  os << setw(len) << buf;
  bytes += len;
}

} // namespace AsyncLog
