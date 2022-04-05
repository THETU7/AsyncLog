/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-31 22:38                                           *
 * @ File: Logging.h                                                  *
 *                                                                    *
 * @ Description: reailze backend of AsyncLog                         *
 **********************************************************************/
#ifndef LOGGING_H
#define LOGGING_H

#include "FixedBuffer.h"
#include "LogFile.h"
#include "src/noncopyable.h"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#define FLUSHINTERVAL 3s

namespace AsyncLog {
enum class LogLevel { TARCE, DEBUG, INFO, WARN, ERROR, FATAL, NUM_LOG_LEVELS };

class Logging : noncopyable {
  const static int bufferSize = 1024 * 10;

  using Buffer = FixedBuffer<bufferSize>;
  using BufferPtr = unique_ptr<Buffer>;
  using BufferVector = vector<BufferPtr>;
  using vectorPtr = unique_ptr<BufferVector>;

public:
  Logging();
  ~Logging() {
    /*
     *    for (auto it = buffers_->begin(); it != buffers_->end(); ++it) {
     *      cout << "out put buffer,size:" << (*it)->writedSize() << endl;
     *      (*it)->outputByFile(file);
     *    }
     *
     */
    if (running_) {
      running_ = false;
      cond.notify_all();
      thread_.join();
    }
  }
  void append(const string &);
  // inline void changeLevel(const LogLevel &lev) { level = lev; }
  void closeRun() { running_ = false; }
  void output();
  void append(const char *msg, size_t len);

private:
  void getTimeStr();
  // void outputTofile(const vectorPtr &);

  //前端buffer
private:
  BufferPtr current_;
  BufferPtr nextBuffer;

private:
  //后端buffer
  vectorPtr buffers_;

private:
  LogFile file{};
  mutex mutex_{};
  condition_variable cond{};
  bool running_{true};
  thread thread_;

  //格式化数据
  /*
   *private:
   *  string date;
   *  time_t lastModTime;
   *  LogLevel level{LogLevel::INFO};
   */
};

extern unique_ptr<Logging> GLOABLASYNCLOG;

void ASYNCLOGOUT(const char *msg, size_t len);

} // namespace AsyncLog

#endif
