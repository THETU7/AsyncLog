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

#include "src/FixedBuffer.h"
#include "src/Logging.h"
#include <thread>

//#define LOGINFO OUTPUTLOG(__FILE__, __LINE__)

namespace AsyncLog {

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
      : filename_(filename), line_(lines), current_level(levels){};

  self &operator<<(const string &str) {
    buffer_.append(str);
    return *this;
  }

  ~LogStream() { format(buffer_.outputToString()); }

  self &operator<<(const char *str) {
    buffer_.append(str);
    return *this;
  }

  self &stream() { return *this; }

  void format(const string &str);

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
  FixedBuffer<SMALLBUFFERSIZE> buffer_;
  static Logging logging_;
};

// static LogStream LOGSTREAM;

// LogStream &OUTPUTLOG(const char *filename, int lines);
} // namespace AsyncLog

#endif
