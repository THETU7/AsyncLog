/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-04-02 17:10                                           *
 * @ File: LogStream.h                                                *
 *                                                                    *
 * @ Description: expose logging stream                               *
 **********************************************************************/
#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include "src/Logging.h"
#include "src/buffer.h"
#include <cstdlib>
#include <thread>

//#define LOGINFO OUTPUTLOG(__FILE__, __LINE__)

namespace AsyncLog {

using OUTPUTFUN = void (*)(const char *msg, size_t len);
using FLUSHFUN = void (*)();

void defalutOutPutFunction(const char *msg, size_t len);
void defalutFlushFunction();
// void RUNLOGGING(Logging &ref);
class LogStream {
  using self = LogStream;

public:
  LogStream(const char *filename, int lines)
      : filename_(filename), line_(lines), current_level(LogLevel::INFO) {
    // fid = this_thread::get_id();
    fid = pthread_self();
  }
  LogStream(const char *filename, int lines, LogLevel levels)
      : filename_(filename), line_(lines), current_level(levels) {
    fid = pthread_self();
  };

  self &operator<<(const string &str) {
    buffer_.append(str);
    return *this;
  }

  ~LogStream() {
    format(buffer_.outputToString());
    if (current_level == LogLevel::FATAL) {
      abort();
    }
  }

  self &operator<<(const char *str) {
    buffer_.append(str);
    return *this;
  }

  self &stream() { return *this; }

  void format(const string &str);
  static void setOutput(OUTPUTFUN func) { g_output = func; }
  static void setFlush(FLUSHFUN func) { g_flush = func; }
  static void setLogLevel(LogLevel le) { level = le; }

  static LogLevel level;
  /*
   *private:
   *  class format {
   *  public:
   *    format() { fid = this_thread::get_id(); }
   *    const string append(const char *filename, int lines, const string
   *&content);
   *
   *  private:
   *    // LogLevel level{LogLevel::INFO};
   *    thread::id fid;
   *    static Logging logging_;
   *  };
   *
   */
private:
  const string getLevel();
  const static int SMALLBUFFERSIZE = 1024;

private:
  // format format;
  // thread::id fid;
  pthread_t fid;
  int times{0};
  string filename_{};
  int line_{0};
  LogLevel current_level;
  Buffer::buffer buffer_{SMALLBUFFERSIZE};
  // static Logging logging_;
  static OUTPUTFUN g_output;
  static FLUSHFUN g_flush;
};

// static LogStream LOGSTREAM;

// LogStream &OUTPUTLOG(const char *filename, int lines);
} // namespace AsyncLog

#endif
