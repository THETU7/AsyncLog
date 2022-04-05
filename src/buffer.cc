/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-29 21:08                                           *
 * @ File: buffer.cc                                                  *
 *                                                                    *
 * @ Description: realize class buffer                                *
 **********************************************************************/

#include "buffer.h"
#include <algorithm>
#include <assert.h>
#include <cstring>

namespace Buffer {

buffer::buffer()
    : buf(initsalSize + preSize), readIndex(preSize), writeIndex(preSize) {
  assert(readableSize() == 0);
  assert(writeableSize() == initsalSize);
  assert(preableSize() == preSize);
}

buffer::buffer(int64_t size)
    : buf(size + preSize), readIndex(preSize), writeIndex(preSize) {
  assert(readableSize() == 0);
  assert(writeableSize() == initsalSize);
  assert(preableSize() == preSize);
}

void buffer::swap(buffer &rhs) {
  buf.swap(rhs.buf);
  std::swap(writeIndex, rhs.writeIndex);
  std::swap(readIndex, rhs.readIndex);
}

void buffer::append(const string &str) { append(str.data(), str.size()); }

void buffer::append(const char *str, size_t len) {
  ensureWriteAbleSizes(len);
  std::copy(str, len + str, begintoWrite());
  assert((int)len <= writeableSize());
  writeIndex += len;
}

void buffer::ensureWriteAbleSizes(size_t size) {
  size_t len = writeableSize();
  if (len >= size) {
    return;
  }

  buf.resize(buf.size() + size - len);
}

string buffer::retrieveAllString() { return retrieveAsString(readableSize()); }

string buffer::retrieveAsString(size_t len) {
  assert((int)len <= readableSize());
  string re(peek(), len);
  retrieve(len);
  return re;
}

void buffer::retrieve(size_t len) {
  assert((int)len <= readableSize());

  readIndex += len;

  if (readIndex == writeIndex) {
    readIndex = writeIndex = preSize;
  }
}

const char *buffer::findEOF() { return findEOF(peek()); }

const char *buffer::findEOF(const char *begin) {
  assert(peek() <= begin);
  assert(begin <= begintoWrite());
  return static_cast<const char *>(memchr(begin, '\n', begintoWrite() - begin));
}

const string buffer::outputToString() { return string(peek(), readableSize()); }

} // namespace Buffer
