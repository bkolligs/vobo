#ifndef _vobo_log_h_
#define _vobo_log_h_

#include "colored_output_strings.h"
#include "vobo_pch.h"

/* In case we don't want to output a string to the standard output */
#define VOBO_DEBUG_STRING(string) GREEN_STRING(string)
#define VOBO_WARNING_STRING(string) YELLOW_STRING(string)
#define VOBO_ERROR_STRING(string) RED_STRING(string)
#define VOBO_CRITICAL_STRING(string) RED_BOLD_STRING(string)

/* Macros for printing output to the screen in different colors */
#define VOBO_INFO_LOG(...)     std::cout << __VA_ARGS__ <<           std::endl
#define VOBO_DEBUG_LOG(...)    std::cerr << ASCI_ESCAPE COLOR_GREEN  << __VA_ARGS__  << END_COLOR << std::endl
#define VOBO_WARNING_LOG(...)  std::cerr << ASCI_ESCAPE COLOR_YELLOW << __VA_ARGS__  << END_COLOR << std::endl
#define VOBO_ERROR_LOG(...)    std::cerr << ASCI_ESCAPE COLOR_RED    << __VA_ARGS__  << END_COLOR << std::endl
#define VOBO_CRITICAL_LOG(...) std::cerr << ASCI_ESCAPE COLOR_RED_BOLD << __VA_ARGS__  END_COLOR << std::endl

enum class DebugLevel {
	INFO = 0,
	DEBUG,
	WARNING,
	ERROR,
	CRITICAL
};

/**
 * Future function for logging to a file for easier filtering of data and such
 */
template<typename ...Args>
void log(DebugLevel level, Args && ...args) {

	(std::cout << ... << args);
}

typedef unsigned int uint;


#endif //_vobo_log_h_ header