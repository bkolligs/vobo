#ifndef _vobo_memory_h_
#define _vobo_memory_h_
#include "vobo_pch.h"

template<class T>
using Ref = std::shared_ptr<T>;

template<class T>
using Unique = std::unique_ptr<T>;

#endif //_vobo_memory_h_ header