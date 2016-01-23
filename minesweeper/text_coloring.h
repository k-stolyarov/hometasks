#ifndef TEXT_COLORING_H
#define TEXT_COLORING_H

#if defined(_WIN32) || defined(WIN32)
const char * NORMAL_TEXT = "";
const char * BOLD_RED_TEXT = "";
const char * BOLD_BRIGHT_RED_TEXT = "";
const char * BOLD_GREEN_TEXT = "";
const char * BOLD_BRIGHT_GREEN_TEXT = "";
const char * BOLD_YELLOW_TEXT = "";
const char * BOLD_BRIGHT_YELLOW_TEXT = "";
const char * BOLD_BLUE_TEXT = "";
const char * BOLD_BRIGHT_BLUE_TEXT = "";
const char * BOLD_MAGENTA_TEXT = "";
const char * BOLD_BRIGHT_MAGENTA_TEXT = "";
const char * BOLD_CYAN_TEXT = "";
const char * BOLD_BRIGHT_CYAN_TEXT = "";
const char * BOLD_WHITE_TEXT = "";
const char * BOLD_BRIGHT_WHITE_TEXT = "";
const char * YELLOW_BACKGROUND_TEXT = "";
#else // linux, Mac

const char * NORMAL_TEXT = "\x1B[0m";
const char * BOLD_RED_TEXT = "\x1B[1;31m";
const char * BOLD_BRIGHT_RED_TEXT = "\x1B[1;91m";
const char * BOLD_GREEN_TEXT = "\x1B[1;32m";
const char * BOLD_BRIGHT_GREEN_TEXT = "\x1B[1;92m";
const char * BOLD_YELLOW_TEXT = "\x1B[1;33m";
const char * BOLD_BRIGHT_YELLOW_TEXT = "\x1B[1;93m";
const char * BOLD_BLUE_TEXT = "\x1B[1;34m";
const char * BOLD_BRIGHT_BLUE_TEXT = "\x1B[1;94m";
const char * BOLD_MAGENTA_TEXT = "\x1B[1;35m";
const char * BOLD_BRIGHT_MAGENTA_TEXT = "\x1B[1;95m";
const char * BOLD_CYAN_TEXT = "\x1B[1;36m";
const char * BOLD_BRIGHT_CYAN_TEXT = "\x1B[1;96m";
const char * BOLD_WHITE_TEXT = "\x1B[1;37m";
const char * BOLD_BRIGHT_WHITE_TEXT = "\x1B[1;97m";
const char * YELLOW_BACKGROUND_TEXT = "\x1B[43m";
#endif

#endif // #ifndef TEXT_COLORING_H
