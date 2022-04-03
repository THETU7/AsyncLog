/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-04-03 10:39                                           *
 * @ File: AsyncLog.h                                                 *
 *                                                                    *
 * @ Description: define for AsyncLog                                 *
 **********************************************************************/
#ifndef ASYNCLOG_H
#define ASYNCLOG_H

#include "src/LogStream.h"

#define LOGTARCE                                                               \
  if (AsyncLog::LogLevel::TARCE >= AsyncLog::LogStream::level)                 \
  AsyncLog::LogStream(__FILE__, __LINE__, AsyncLog::LogLevel::TARCE).stream()

#define LOGINFO                                                                \
  if (AsyncLog::LogLevel::INFO >= AsyncLog::LogStream::level)                  \
  AsyncLog::LogStream(__FILE__, __LINE__).stream()

#define LOGWARN                                                                \
  if (AsyncLog::LogLevel::WARN >= AsyncLog::LogStream::level)                  \
  AsyncLog::LogStream(__FILE__, __LINE__, AsyncLog::LogLevel::WARN).stream()

#define LOGDEBUG                                                               \
  if (AsyncLog::LogLevel::DEBUG >= AsyncLog::LogStream::level)                 \
  AsyncLog::LogStream(__FILE__, __LINE__, AsyncLog::LogLevel::DEBUG).stream()

#define LOGERROR                                                               \
  if (AsyncLog::LogLevel::ERROR >= AsyncLog::LogStream::level)                 \
  AsyncLog::LogStream(__FILE__, __LINE__, AsyncLog::LogLevel::DEBUG).stream()

#define LOGFATAL                                                               \
  AsyncLog::LogStream(__FILE__, __LINE__, AsyncLog::LogLevel::FATAL).stream()

#endif
