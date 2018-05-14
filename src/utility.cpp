#ifndef __UTILITY
#define __UTILITY
#include <cstdio>
#include <string>

#define CARRY 0
#define ZERO 1
#define IRQ 2
#define DECIMAL 3
#define BRK 4
#define OVERFLOW 6
#define NEGATIVE 7

// From https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BIN_PATT "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BIN(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

std::string dec_hex_bin(uint8_t value) {
    char formated_str[26];
    snprintf(formated_str, sizeof(formated_str), "%3d  %02x  " BIN_PATT,
            value, value, BYTE_TO_BIN(value));
    return std::string(formated_str);
}

std::string dec_hex_bin_16(uint16_t value) {
    std::string ret = "Low:  " + dec_hex_bin(value) + "\n";
    value = value >> 8;
    ret += "High: " + dec_hex_bin(value) + "\n";
    return ret;
}

#endif
