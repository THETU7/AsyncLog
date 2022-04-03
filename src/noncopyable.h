/**********************************************************************
 * @ Copyright (C) 2022 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2022-03-31 17:52                                           *
 * @ File: noncopyable.h                                              *
 *                                                                    *
 * @ Description: a base class for nocopy, reference from chen shuo   *
 **********************************************************************/
#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class noncopyable {
public:
  noncopyable(const noncopyable &) = delete;
  void operator=(const noncopyable &) = delete;

protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

#endif
