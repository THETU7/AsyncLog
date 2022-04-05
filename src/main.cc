#include "src/AsyncLog.h"
#include <functional>
#include <unistd.h>

void backend(AsyncLog::Logging &log) { log.output(); }

void frontend(AsyncLog::Logging &log) {
  log.append("\nstart\n");
  sleep(4);
  log.append("end");
  sleep(3);
}

void backend2() { LOGINFO << "test Logging"; }

void thr1() {
  for (int i = 0; i < 100; ++i) {
    LOGINFO << "test " << std::to_string(i);
  }
}

void thr2() {
  for (int i = 0; i < 100; ++i) {
    LOGWARN << "Warning" << std::to_string(i);
  }
}

void thr3() {
  for (int i = 0; i < 100; ++i) {
    LOGERROR << "Error" << std::to_string(i);
  }
}

void thr4() {
  for (int i = 0; i < 100; ++i) {
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

  std::thread t1(thr1);
  std::thread t2(thr2);
  std::thread t3(thr3);
  /*std::thread t4(thr4);*/

  t1.join();
  t2.join();
  t3.join();
  /*t4.join();*/

  exit(0);
  // return 0;
}
