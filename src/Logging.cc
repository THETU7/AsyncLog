#include "Logging.h"
#include <iomanip>

namespace AsyncLog {
void OUTPUTLOG(Logging &log) { log.output(); }

Logging::Logging()
    : current_(make_unique<Buffer>()), nextBuffer(make_unique<Buffer>()),
      buffers_(make_unique<BufferVector>()) {
  lastModTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
  getTimeStr();
  thread t1(OUTPUTLOG, std::ref(*this));
  t1.detach();
}

void Logging::getTimeStr() {
  char timebuf[32];
  if (strftime(timebuf, 32, "%F %T", localtime(&lastModTime)) == 0) {
    cerr << "time buffer size 16 is too small\n" << endl;
  }
  date = timebuf;
}

void Logging::append(const string &str) {
  // lock_guard<mutex> lock(mutex_);
  unique_lock<mutex> lcok(mutex_);
  if (str.length() <= current_->availbe())
    current_->append(str.c_str(), str.length());
  else {
    buffers_->push_back(std::move(current_));

    if (nextBuffer) {
      current_ = std::move(nextBuffer);
    } else {
      current_ = make_unique<Buffer>();
    }
    current_->append(str.c_str(), str.length());
    cond.notify_all();
  }
  /*
   *  else if (str.length() <= nextBuffer->availbe()) {
   *    buffers_->push_back(std::move(current_));
   *    current_ = std::move(nextBuffer);
   *    current_->append(str.c_str(), str.length());
   *  } else {
   *    buffers_->push_back(std::move(current_));
   *    current_ = make_unique<Buffer>();
   *
   *    // warning: 如果strlen 大于 一个 buffer 可容纳量，则无法处理
   *    current_->append(str.c_str(), str.length());
   *  }
   */
}

void Logging::output() {
  BufferPtr bufferA = make_unique<Buffer>();
  BufferPtr bufferB = make_unique<Buffer>();
  vectorPtr buffersToWirte = make_unique<BufferVector>();

  while (running_) {
    {
      unique_lock<mutex> lock(mutex_);
      if (buffers_->empty()) {
        cond.wait_for(lock, FLUSHINTERVAL);
      }
      buffers_->push_back(std::move(current_));
      buffersToWirte.swap(buffers_);
      current_ = std::move(bufferA);
      if (!nextBuffer)
        nextBuffer = std::move(bufferB);
    }
    //移出缓冲区
    for (auto it = buffersToWirte->begin(); it != buffersToWirte->end(); ++it) {
      (*it)->outputByFile(file);
    }

    /*
     *while (buffersToWirte->empty()) {
     *  buffersToWirte->back()->outputByFile(file);
     *  buffersToWirte->pop_back();
     *}
     */

    file.flush();
    buffersToWirte = make_unique<BufferVector>();

    bufferA = make_unique<Buffer>();
    if (!bufferB)
      bufferB = make_unique<Buffer>();
  }
}

} // namespace AsyncLog
