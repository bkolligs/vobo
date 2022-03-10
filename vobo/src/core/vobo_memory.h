#ifndef _vobo_memory_h_
#define _vobo_memory_h_
#include "vobo_pch.h"

namespace vobo {

template <class T>
using Ref = std::shared_ptr<T>;

template <class T>
using Unique = std::unique_ptr<T>;

/* Can overload new to track memory usage */

}  // namespace vobo
#endif  //_vobo_memory_h_ header