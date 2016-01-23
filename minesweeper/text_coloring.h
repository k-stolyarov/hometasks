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

#else // linux, Mac

const char * NORMAL_TEXT = "\x1B[0m";
const char * BOLD_RED_TEXT = "\x1B[1;31m";
const char * BOLD_BRIGHT_RED_TEXT = "\x1B[38;5;09m";
const char * BOLD_GREEN_TEXT = "\x1B[1;32m";
const char * BOLD_BRIGHT_GREEN_TEXT = "\x1B[38;5;0Am";
const char * BOLD_YELLOW_TEXT = "\x1B[1;33m";
const char * BOLD_BRIGHT_YELLOW_TEXT = "\x1B[38;5;0Bm";
const char * BOLD_BLUE_TEXT = "\x1B[1;34m";
const char * BOLD_BRIGHT_BLUE_TEXT = "\x1B[38;5;0Cm";
const char * BOLD_MAGENTA_TEXT = "\x1B[1;35m";
const char * BOLD_BRIGHT_MAGENTA_TEXT = "\x1B[38;5;0Dm";
const char * BOLD_CYAN_TEXT = "\x1B[1;36m";
const char * BOLD_BRIGHT_CYAN_TEXT = "\x1B[38;5;0Em";
const char * BOLD_WHITE_TEXT = "\x1B[1;37m";
const char * BOLD_BRIGHT_WHITE_TEXT = "\x1B[38;5;0Fm";
#endif

#endif // #ifndef TEXT_COLORING_H
