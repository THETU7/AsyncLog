#include "Logging.h"
#include <iomanip>

namespace AsyncLog {

void OUTPUTLOG(Logging &log) { log.output(); }
Logging::Logging()
    : current_(make_unique<Buffer>()), nextBuffer(make_unique<Buffer>()),
      buffers_(make_unique<BufferVector>()) {
  thread_ = thread(OUTPUTLOG, std::ref(*this));
}

/*
 *void Logging::getTimeStr() {
 *  char timebuf[32];
 *  if (strftime(timebuf, 32, "%F %T", localtime(&lastModTime)) == 0) {
 *    cerr << "time buffer size 16 is too small\n" << endl;
 *  }
 *  date = timebuf;
 *}
 */

void Logging::append(const string &str) {
  // lock_guard<mutex> lock(mutex_);

  lock_guard<mutex> lcok(mutex_);
  if (str.length() <= current_->availbe())
    current_->append(str);
  else {
    buffers_->push_back(std::move(current_));

    if (nextBuffer.get()) {
      current_ = std::move(nextBuffer);
    } else {
      current_.reset(new Buffer);
    }
    current_->append(str);
    // cout << str << endl;
    // lcok.unlock();
    cond.notify_one();
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

      if (current_->writedSize() == 0) {
        continue;
      }

      buffers_->push_back(std::move(current_));
      current_ = std::move(bufferA);
      buffersToWirte.swap(buffers_);
      if (!nextBuffer)
        nextBuffer = std::move(bufferB);
      lock.unlock();
    }
    //移出缓冲区
    for (auto it = buffersToWirte->begin(); it != buffersToWirte->end(); ++it) {
      if (*it) {
        (*it)->outputByFile(file);
      }
    }
    // cout << "size:" << buffersToWirte->size() << endl;

    /*
     *while (buffersToWirte->empty()) {
     *  buffersToWirte->back()->outputByFile(file);
     *  buffersToWirte->pop_back();
     *}
     */

    // buffersToWirte->clear();

    bufferA = std::move(buffersToWirte->back());
    buffersToWirte->pop_back();
    bufferA->reset();
    if (!bufferB) {
      bufferB = std::move(buffersToWirte->back());
      buffersToWirte->pop_back();
      bufferB->reset();
    }
    buffersToWirte->clear();
    file.flush();
  }
  file.flush();
}

} // namespace AsyncLog
