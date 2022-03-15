#ifndef _colored_output_strings_h_
#define _colored_output_strings_h_

#define ASCI_ESCAPE    "\033["
#define ASCI_TERMINATE "m"
/* Reset color back to normal with ANSI color codes */
#define RESET_COLOR "0"    ASCI_TERMINATE
#define END_COLOR   ASCI_ESCAPE RESET_COLOR

/* Define ANSI color codes for strings */
#define COLOR_RED                  "31" ASCI_TERMINATE
#define COLOR_RED_BOLD             "1;" COLOR_RED
#define COLOR_GREEN                "32" ASCI_TERMINATE
#define COLOR_GREEN_BOLD           "1;" COLOR_GREEN
#define COLOR_YELLOW               "33" ASCI_TERMINATE
#define COLOR_YELLOW_BOLD          "1;" COLOR_YELLOW
#define COLOR_BLUE                 "34" ASCI_TERMINATE
#define COLOR_BLUE_BOLD            "1;" COLOR_BLUE
#define COLOR_MAGENTA              "35" ASCI_TERMINATE
#define COLOR_MAGENTA_BOLD         "1;" COLOR_MAGENTA
#define COLOR_CYAN                 "36" ASCI_TERMINATE
#define COLOR_CYAN_BOLD            "1;" COLOR_CYAN


/* Define macros to process different color strings */
#define RED_STRING(string)          ASCI_ESCAPE COLOR_RED                string END_COLOR
#define RED_BOLD_STRING(string)     ASCI_ESCAPE COLOR_RED_BOLD           string END_COLOR
#define GREEN_STRING(string)        ASCI_ESCAPE COLOR_GREEN              string END_COLOR
#define GREEN_BOLD_STRING(string)   ASCI_ESCAPE COLOR_GREEN_BOLD         string END_COLOR
#define YELLOW_STRING(string)       ASCI_ESCAPE COLOR_YELLOW             string END_COLOR
#define YELLOW_BOLD_STRING(string)  ASCI_ESCAPE COLOR_YELLOW_BOLD        string END_COLOR
#define BLUE_STRING(string)         ASCI_ESCAPE COLOR_BLUE               string END_COLOR
#define BLUE_BOLD_STRING(string)    ASCI_ESCAPE COLOR_BLUE_BOLD          string END_COLOR
#define MAGENTA_STRING(string)      ASCI_ESCAPE COLOR_MAGENTA            string END_COLOR
#define MAGENTA_BOLD_STRING(string) ASCI_ESCAPE COLOR_MAGENTA_BOLD       string END_COLOR
#define CYAN_STRING(string)         ASCI_ESCAPE COLOR_CYAN               string END_COLOR
#define CYAN_BOLD_STRING(string)    ASCI_ESCAPE COLOR_CYAN_BOLD          string END_COLOR

#endif //_colored_output_strings_h_ header