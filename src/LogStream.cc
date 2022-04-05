#include "src/LogStream.h"
#include <cstdio>
#include <iomanip>

namespace AsyncLog {
/*
 *LogStream &OUTPUTLOG(const char *filename, int lines) {
 *  string str = filename;
 *  str += "-";
 *  str += to_string(lines);
 *  return LOGSTREAM << str;
 *}
 *
 *void RUNLOGGING(Logging &ref) { ref.output(); }
 *
 */

void LogStream::format(const string &str) {
  auto now = chrono::system_clock::now();
  time_t nowTime = chrono::system_clock::to_time_t(now);
  auto time_us =
      chrono::duration_cast<chrono::microseconds>(now.time_since_epoch())
          .count() %
      100000;
  std::stringstream ss;
  ss << put_time(localtime(&nowTime), "%F %T") << "." << time_us << '\t';
  ss << getLevel();
  ss << '\t' << fid << '\t';
  ss << str << '\t' << filename_ << ':' << line_ << '\n';
  // buffer_.append(ss.str());
  string strs = ss.str();
  g_output(strs.c_str(), strs.length());
  // logging_.append(ss.str());
}

const string LogStream::getLevel() {
  switch (current_level) {
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::FATAL:
    return "FATAL";
  case LogLevel::TARCE:
    return "TARCE";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::NUM_LOG_LEVELS:
    return "OTHRE";
  default:
    return "";
  }
}

// Logging LogStream::logging_{};
LogLevel LogStream::level = LogLevel::INFO;
OUTPUTFUN LogStream::g_output = defalutOutPutFunction;
FLUSHFUN LogStream::g_flush = defalutFlushFunction;

void defalutOutPutFunction(const char *msg, size_t len) {
  size_t n = fwrite(msg, 1, len, stdout);
  (void)n;
}

void defalutFlushFunction() { fflush(stdout); }

} // namespace AsyncLog
