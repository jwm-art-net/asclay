#ifndef STRINGS_H
#define STRINGS_H

char* get_line(const char* src, char* dest, int length, const char** src_remaining, bool skip_leading, int* did_break);

// justify: 'l', 'r', 'c', 'j'
int justify(char* str, int justify);

char* file_to_string(const char* path);

#endif
