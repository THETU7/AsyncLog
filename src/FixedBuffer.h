/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-04-01 15:02                                           *
 * @ File: FixedBuffer.h                                              *
 *                                                                    *
 * @ Description: fixed Buffer                                        *
 **********************************************************************/
#ifndef FIXEDBUFFER_H
#define FIXEDBUFFER_H

#include "src/LogFile.h"
#include "src/noncopyable.h"
#include <cstring>
#include <iostream>

namespace AsyncLog {

template <int SIZE> class FixedBuffer : noncopyable {
public:
  FixedBuffer() : cur(buf_), len_(0) {}
  ~FixedBuffer() {}
  void append(const char *buf, size_t len) {
    if (len == 0)
      return;
    if (availbe() >= len) {
      memcpy(cur, buf, len);
      cur += len;
      len_ += len;
    }
  };

  void append(const string &str) { append(str.c_str(), str.length()); }

  size_t availbe() const { return SIZE - len_; }

  void output(char *buf, size_t len) {
    if (len < len_) {
      memcpy(buf, buf_, len);
      cur -= len;
      len_ -= len;
    } else {
      memcpy(buf, buf_, len_);
      cur = buf_;
      len_ = 0;
    }
  }

  void reset() {
    memset(buf_, 0, SIZE);
    cur = buf_;
    len_ = 0;
  }

  void outputByFile(LogFile &file) {
    file.append(buf_, len_);
    len_ = 0;
    cur = buf_;
  }
  const string outputToString() {
    len_ = 0;
    cur = buf_;
    return string(buf_, len_);
  }

  inline size_t writedSize() { return len_; }

private:
  char buf_[SIZE];
  char *cur;
  size_t len_;
};
} // namespace AsyncLog

#endif
