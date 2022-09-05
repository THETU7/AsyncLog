#include "src/AsyncLog.h"
#include <functional>
#include <unistd.h>

#define OUTPUTNUMS 100000

void backend(AsyncLog::Logging &log) { log.output(); }

void frontend(AsyncLog::Logging &log) {
  log.append("\nstart\n");
  sleep(4);
  log.append("end");
  sleep(3);
}

void backend2() { LOGINFO << "test Logging"; }

void thr1() {
  for (int i = 0; i < OUTPUTNUMS; ++i) {
    LOGINFO << "test " << std::to_string(i);
  }
}

void thr2() {
  for (int i = 0; i < OUTPUTNUMS; ++i) {
    LOGWARN << "Warning" << std::to_string(i);
  }
}

void thr3() {
  for (int i = 0; i < OUTPUTNUMS; ++i) {
    LOGERROR << "Error" << std::to_string(i);
  }
}

void thr4() {
  for (int i = 0; i < OUTPUTNUMS; ++i) {
    LOGFATAL << "FATAL" << std::to_string(i);
  }
}

int main() {
  /*
   *AsyncLog::Logging lg;
   *std::thread t1(backend, std::ref(lg));
   *std::thread t2(frontend, std::ref(lg));
   *t1.join();
   *t2.join();
   */
  std::ios::sync_with_stdio(false);
  AsyncLog::LogStream::setOutput(AsyncLog::ASYNCLOGOUT);
  auto start = std::chrono::high_resolution_clock::now();
  std::thread t1(thr3);
  std::thread t2(thr2);
  std::thread t3(thr1);
  std::thread t4(thr3);
  std::thread t5(thr2);
  std::thread t6(thr1);
  std::thread t7(thr3);
  std::thread t8(thr2);
  std::thread t9(thr1);
  std::thread t10(thr1);
  // std::thread t4(thr4);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << '\n';
  // t4.join();

  // exit(0);
  //
  return 0;
}
