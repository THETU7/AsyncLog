/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-29 20:56                                           *
 * @ File: buffer.h                                                   *
 *                                                                    *
 * @ Description: head for buffer                                     *
 **********************************************************************/
#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <vector>

namespace Buffer {

using namespace std;

class buffer {
  const static int initsalSize = 1024;
  const static int preSize = 8;

public:
  buffer(int64_t size);
  buffer();
  buffer(const buffer &) = default;
  buffer(buffer &&rhs) = default;
  buffer &operator=(buffer &&rhs) = default;
  buffer &operator=(const buffer &) = default;
  void swap(buffer &);
  void append(const string &);
  void append(const char *, size_t len);
  void output(int fd);
  const string outputToString();
  inline bool isEmpty() { return readIndex == writeIndex; }
  string retrieveAsString(size_t len);
  string retrieveAllString();
  const char *findEOF();
  const char *findEOF(const char *begin);

private:
  inline int readableSize() const { return writeIndex - readIndex; }
  inline int writeableSize() const { return buf.size() - writeIndex; }
  inline int preableSize() const { return readIndex; }
  inline char *begintoWrite() { return buf.begin().base() + writeIndex; }
  void ensureWriteAbleSizes(size_t size);
  const char *peek() const { return buf.begin().base() + readIndex; }
  void retrieve(size_t len);

private:
  vector<char> buf{};
  size_t readIndex{preSize};
  size_t writeIndex{preSize};
};
} // namespace Buffer

#endif
