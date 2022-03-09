/**
 * This header file contains common declerations that are used across multiple
 * files
 */
#ifndef _vobo_common_h_
#define _vobo_common_h_
#include "vobo_pch.h"

namespace vobo {

/**
 * This string is set by vobo/CMakeLists.txt since CMake provides a nice interface for this.
 * Can set preprocessor definitions with `target_compile_definitions`
 */
const std::string VOBO_SRC_DIR = VOBO_SOURCE_DIR;

}  // namespace vobo

#endif  //_vobo_common_h_ header