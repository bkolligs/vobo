/**
 * This header file contains common declerations that are used across multiple
 * files
 */
#ifndef _vobo_common_h_
#define _vobo_common_h_
#include "vobo_pch.h"

namespace vobo {
namespace fs = std::filesystem;
// This is a const string to the path of the `vobo/` directory
const std::string filePath = __FILE__;
const std::string VOBO_SRC_DIR =
    filePath.substr(0, filePath.find("common.h")) + "../";
}  // namespace vobo

#endif  //_vobo_common_h_ header