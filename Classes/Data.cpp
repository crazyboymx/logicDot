/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Data.cpp
 * $Id: Data.cpp v 1.0 2015-03-09 17:40:56 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-10 23:12:42 $
 * @brief
 *
 ******************************************************************/

#include "Data.h"
#include <cocos2d.h>

USING_NS_CC;

std::string puzzles1[] = {
    "4,4,1010000000011000",
    "4,4,0000101100000100",
    "4,4,0001110100010100",
    "4,4,1010000000011100",
    "4,4,1011100010100010",
    "4,4,1101000100001110",
    "4,4,0000110000000100",
    "4,4,0000100110001010",
    "4,4,0000010001010100",
    "4,4,0000010001010100",
    "4,4,0101010100000110",
    "4,4,1101000111010000",
};

std::string puzzles2[] = {
    "5,5,1000000001010010000111000",
    "5,5,0000001011000000111000000",
    "5,5,0000000010100101000010110",
    "5,5,1110100001100010010100100",
    "5,5,0000100000011010000000100",
    "5,5,1100000011110000001101000",
    "5,5,1110100001010010000100000",
    "5,5,1100100001100011010100100",
    "5,5,0000011110000000000011110",
    "5,5,0000010100000001010000100",
    "5,5,1110000000110100001010010",
    "5,5,1010110000101101000000000",
    "5,5,0001100000010000100000010",
    "5,5,0101000000001011000010000",
    "5,5,1001010010100100000001100",
    "5,5,0100000010010100101001010",
    "5,5,0000000000100100001011000",
    "5,5,1100100001100001010100000",
    "5,5,1110000001001010000101100",
    "5,5,0001001000010000000100100",
    "5,5,0111100000000101101000010",
    "5,5,0011100000100011010010100",
    "5,5,0001001010000101000000110",
    "5,5,1001000010100101000010000",
};

std::string puzzles3[] = {
    "6,6,110110000000100111100000000011000000",
    "6,6,101001000000000010000010000010100010",
    "6,6,100001000100000101010001000000111000",
    "6,6,010000000001111100000000101111100000",
    "6,6,000011110000000000011001000000010000",
    "6,6,010100010101000000110101000101010100",
    "6,6,100000000100010100010000000001110000",
    "6,6,001010001000001010101010000000010000",
    "6,6,000000000101000101100101000000001000",
    "6,6,010111000000000100100000001011001000",
    "6,6,000101010100000101100000100110100000",
    "6,6,101000101011000000101011001000101010",
    "6,6,000000110001000101000000011111000000",
    "6,6,000001111100000000000010000000011110",
    "6,6,000001011000000000101111000000111110",
    "6,6,100110000000111101000000011010000010",
    "6,6,101000000010011010000000111010000010",
    "6,6,010101000101100101000000001010001010",
    "6,6,000100010001000100000001100100100100",
    "6,6,000010111010000010101000100011101000",
    "6,6,100001101001000000110110000000101010",
    "6,6,111000000001001101100000000001110000",
    "6,6,000000011010000000100001100000101000",
    "6,6,110100000000100100100001000001111100",
    "6,6,100100000001100000101111000000111110",
    "6,6,010100000100000001001001100000001110",
    "6,6,101001000001000001001101000000100010",
    "6,6,101110000000101100100001100100100100",
    "6,6,101010000000100100000100000101010000",
    "6,6,111000000010000010000010001010100000",
};

std::string puzzles4[] = {
    "7,7,0010100001000000100100000010011000000001100100000",
    "7,7,0101110010000000010000001010110100000000101011010",
    "7,7,0010101101000000100100000000111010000001010110100",
    "7,7,0011100100000100101010010001000010100001011010000",
    "7,7,0001001000000001001010000001101010000101010000100",
    "7,7,0000000001111100000001001000000000010011111000000",
    "7,7,0100100010010100000000101100000000010000001011010",
    "7,7,0101100010000000000000000011100100010000000000110",
    "7,7,0101000010101000000000100100010010101000000101010",
    "7,7,0101100010000100000001011110000000011010010001000",
    "7,7,0000111101000010101001010101000000010010101000010",
    "7,7,0111001000000100001011010101100000000101110010000",
    "7,7,1001000000101011010100000000111000000000010010100",
    "7,7,0000000111111000000000000011101000010101010010100",
    "7,7,0001000010100001010000001010100100000000011100100",
    "7,7,1000110001000000001110000000101010100000011101000",
    "7,7,0000001001010010000000000101110000000010100100000",
    "7,7,0101010010101001010000000011101000010101101010000",
    "7,7,0000110010000001000010000100110010000001000010000",
    "7,7,0001010110000000010011101001000000000000101011000",
    "7,7,1001111100000000000101111010000000010001011010100",
    "7,7,1011000100000110101000000001100100110010000001000",
    "7,7,0010100001010000000001010010001000000001011000000",
    "7,7,0110001000010011101000000000001111100000000110000",
    "7,7,0000000111110000000000101000000100000000101100000",
    "7,7,0111110000000010100001010000000010000000000011010",
    "7,7,1010101100000000000100000010100000000001011100100",
    "7,7,0101011010100000000010111101000000100010011101000",
    "7,7,0110000000000100010001100001000110100000000110100",
    "7,7,0111000000001100110000000011010000000000001100000",
};

std::string puzzles5[] = {
    "8,8,1000000000111010000000101011101000000010010100000001001010000010",
    "8,8,0001000000000101110101010000000001010100010100000000000010000000",
    "8,8,1000101000000010101100000000010111010100000000011001010110010000",
    "8,8,1000000110000001000100001000010010010100100000010010000100100100",
    "8,8,0010010100100001000010000110101100001000100000001010100000101000",
    "8,8,1001010110000101100000010000100111000001000010010100000001011010",
    "8,8,0000001111001000000000010111110000000000111000000000111001000000",
    "8,8,0100011101000000000000110010100010000000000000000111110000000000",
    "8,8,0000011000110000100001100001000000000011110000000000101111100000",
    "8,8,0000001000000000111010100000100000000011000110001000000010100110",
    "8,8,0101001100000000100000001000010000110100000000010101000000000010",
    "8,8,0110000000001000100000111010000000001001011010000000101011000010",
    "8,8,1111110100000001101101010000010000010001100000000000101110101000",
    "8,8,1000000010011101000000010001100011000010000000100001001011010010",
    "8,8,0100011101010000010100000001011000000000001110101000001000100000",
    "8,8,1000111100100000100000100010101000101000000010100010101000000010",
    "8,8,0000100011101010000000001100111100000000101001110000000001010100",
    "8,8,0000010010100100100001010000010000100100000000000110000100001100",
    "8,8,0000010001100101000001001100000100011101010000000000110000000000",
    "8,8,0000100101101001000010011110000100001001101010011000000110011000",
    "8,8,0001010011010000000101010001010001010101000000010001000111000000",
    "8,8,1111001000000010010110000100001101000000010000010001110111000000",
    "8,8,1010001000000000100100001001010000000100000000000000111011100000",
    "8,8,1011000110000100001101000000010111100000000001111001000010010110",
    "8,8,1000000000111001000000010101100001000011010110000000000001111110",
    "8,8,1111010100000101010101000101000000010010100000101011101000000000",
    "8,8,0011011010000000100000100000001000010010010000000000011010000000",
    "8,8,1110000000000001010011010000000111100000000010101000101000001000",
    "8,8,1111000000000011111110000000001010000000000001011111000100000100",
    "8,8,0001100011000000000110000000000000110011000000000100011100010000",
};

std::string puzzles6[] = {
    "9,9,000101001100101001100001001000100000110001101000000001101101001100001000001001010",
    "9,9,000010101001010101000000000010111011010000000000111000000000011000000000110011100",
    "9,9,010011000010000011010001000010000001000110101100000100101000100101000000101011110",
    "9,9,100110110100000000000100000010100111010000000000000100100000100000100000010000110",
    "9,9,000100100110100001000101101000000000111011011000000000100000010100000000101101110",
    "9,9,100000011100100000100101100000100001100100001000101100110100001000001100011100000",
    "9,9,100000100000010000001000100000010001101010000000000000101111100000000000000000110",
    "9,9,101010010100000000100111000100000010001011000100000001001000101001000100001010000",
    "9,9,010110100010000000000100001100100101000100101110100001000001001010000000010111110",
    "9,9,101001101000000001101100101000000101110110000000000110111110000000000000100101100",
    "9,9,011110000000000111000000000100001000000000001011001001000001000000001000100100010",
    "9,9,110110100000000000000010001000000100001000000000011101101000000000000100001010100",
    "9,9,010000100010110100000000100011010001000000101001100101000000000111101111000000000",
    "9,9,001101110000000000000011000100000010000001000110100000000000000000000111011010000",
    "9,9,101100001000000100100100100000100000100100101000000000001101000100000000100000110",
    "9,9,111101001000001001010100001000001001011000000000011001000000001000001001011101000",
    "9,9,110010010000010000000000001000001001100101000000000000111000000000010010110000000",
    "9,9,110010101000010000010000010010111010000000000000001111011100000000001010111101010",
    "9,9,101100010100001010101001000101001000000000001010001000010000001000001001110001000",
    "9,9,100100100100000000100000000001111101000000001100001100101100000000000011100010000",
    "9,9,101010010101010010000000010100001010100001000001101000000001010011100010000001010",
    "9,9,000010100110000100000000000100011010101000010000010000101000011100000000100011000",
    "9,9,011100110000000000000010000100000100100010001000010100011000101000010000010000010",
    "9,9,111110000000000111000010000011000111000010000101010101000000001011111000000000010",
    "9,9,001010111001010000000010000010000010000011000101000001101011101001000000101001110",
    "9,9,000100000000001000100101010100000000100110101100000101100110000100000010100001010",
    "9,9,111000000000000001000101001010101000010101010010101010000101010000000000111011010",
    "9,9,111010101000010100000010000111000000000000001110101000000000011101111000100000000",
    "9,9,100100100100000101101010101000000001011110001000000000001000001101010001000010100",
    "9,9,000000101000100000110001011000100000000000110100010000100000011000101000110100010",
};

std::string puzzles7[] = {
    "10,10,0000000000101111011010000000000001010100010001010101010000010101011101000100000101010100000001010010",
    "10,10,0011001000100000000110001111011010000001100001110100010000000001010110110000000000000000011100111100",
    "10,10,1110100010000000001001010000000001000011100000100010100010111010101000100000001110110010000000000010",
    "10,10,1110000000000011101000000000101100101010000010100010001000011000101101101010000010000000111011001000",
    "10,10,1110010001000000010100100000011000011000100100000100000010010110000000000001000110110000001000000000",
    "10,10,1100011100000100000010010011101001000000000100101111010010000001001011000000000001110111110000000000",
    "10,10,1001101010000000100010110000010000000000011001101100000000000110001110000000000010000000100000111010",
    "10,10,1100000001000001000100000101000100000001000111100000000000001010011010101000001000101100001010000100",
    "10,10,0100100101010010010100000001010010000101001001010010100101001010010100000000010101011000000100001010",
    "10,10,0100101000010010001100001010001110001000000000101000110010001000001001101100000110000110010010000000",
    "10,10,1001001000100000100010100000011010101001100000100000001010000000000010011010100000001000010010100000",
    "10,10,0101110101000000000110111000010000001001011110100000000000100101011000010100001000010000001001011100",
    "10,10,0100000100000110010101000000010100111001010000000000000100000000010111010000000001000110000101000010",
    "10,10,0000001011110110000000000000101111010000000000000011000000000000011111000100000000000010000110001000",
    "10,10,0101010011010101000000010100000100000100010110000000000011111011100000100000100000011000001100001110",
    "10,10,1000101000100010101000000000101111111000000000000100101110000010000001001000100010101000110010100000",
    "10,10,0010001111000000000000000010001111101001000000000110000011011011000000000000110110000000001011111000",
    "10,10,0010001010101000100010100000001000000011000000100011010000000001010100010100000001000000100000011000",
    "10,10,0110000000000000111011010000000000011101000000000001100010000000101011101010000000100000001010111000",
    "10,10,0000000101010111000000000001100101100000000000000000001000111110001000000000100100000000000111011100",
    "10,10,0001111011010000000001011110000100000010000000001011111000000000000100101110000000000010101001001010",
    "10,10,0001100001100000010110010001010001000001100100110100000000011000001000100000001110110100000000010000",
    "10,10,0100101000010010000100000001000001110101000000000010110001111000000000000110101101000010000100001000",
    "10,10,0101010001000000010010110100001000000110101011000010000001001011100101000000000001000101000000000100",
    "10,10,0101011101000100000101000000010100111100000000000010011110101000000000000001000100010001001001000100",
    "10,10,1010001000000000100001110010010000000001100011010100100001010000000001000110110011000000010001111100",
    "10,10,0100001110010010000001000010100101101010010000101001011010100100000010010011000001000001110001010000",
    "10,10,0101000111010100000000000110001010000010101000000010001000100000100010001000001000001000101110001010",
    "10,10,1101101000000000100111101010000000101011001010000010101010000000000000110010100100000000001110011010",
    "10,10,1010000001000001000000010100011101010001000000000111001000010000100000110010001000000000101101011000",
};

std::string puzzles8[] = {
    "11,11,0101010010101010100101010000000000000110100001100001011000000000001000001010110001000100101010000000000001001011111010010",
    "11,11,1000010000100000100001001000011001000100000010000000010100110100101000001000000100000000101011101010000000000111000110100",
    "11,11,1001000111100010100000100000011100000100000010101011001000010000001100000011000010110000000100001110000000000011000011000",
    "11,11,1101010000100010101001100000010011000000000010001000000000010110101100000001000000000000001011100011010000000000001000100",
    "11,11,0010010101010000100010001101010000000000100000110000010000001010100010000100000101000000000000100000110000000000000011110",
    "11,11,1111000000000000011100000100000000101001001001000010010000010000000000001001011010010010000000000100111100000000000010110",
    "11,11,0100000010101001110100010000000000100101011100001010000111010100100000000001000011110000100000001010010101000010100000110",
    "11,11,0110001010100001010101110010001010000101000001000000000010000110000000000000010000101101100101000010000010000000100001010",
    "11,11,0000000000010101101101000000000011000010010100000000000000011100001000000011110100110000000000000010110000010100001100100",
    "11,11,1010101101110100000000101000101011000000000100010010000000100001010100011010000000000000101111010111000000100010001000000",
    "11,11,0001001111110000000000100000010010011100100010000001011100101010001001010000000010000111110001000000000000000101111000000",
    "11,11,0010011111100100000000100001010100011000101010000001010001111000000000000010101101010001000010101000000001000011101000110",
    "11,11,0101000100000000000001101010111000010100000000000000010111111010100000000101000010101010110101000000000000111001101100000",
    "11,11,0010110100010000000010000101000101101010000000010001011010000000000101011110101010000000000100110100100000001000011010000",
    "11,11,0010100000000100010000001010000010010000010100000010000010100000100101011100000000000000101001000010010010110000100100000",
    "11,11,0101110000100000000001011101010000000010000000000001111100110000000000001101110101000000101000001010010010000000000000010",
    "11,11,1010000000010100101011000000000000010010000110000100101101000001000000101000011100000000000001001000001000000011010011010",
    "11,11,0110100110100000000001111111100000000000011010010000000000000100110001101000011000000111000000000001010110000000100001110",
    "11,11,0000101100100001000001110010000010000101000000100010111001010000001010100100000100000000001000100010010101000010001010000",
    "11,11,1111100000000000001001001100000000000001011101011010000000000001101010001000010100000011000001010000000000101010010000010",
    "11,11,0010001110100000000001000000011010000000000001000001011000101010000101010000001010001000000000010000001000100011000101010",
    "11,11,0010100000110101011001100000000010011101000010000000111000101000000100010010000000000101011000101000000001010011010010100",
    "11,11,0010001010000101010101000000100010010000000010000000010001010010100000100100010101000010101000100100000001001010010000010",
    "11,11,0101000000001010001111000000000001000100100000100001010101001000101000000000000101000101001000101010000000010001001100000",
    "11,11,1001010001000010101000100000000011000100010010100010000100000001011000100000100001011101010000000010100100000101000001000",
    "11,11,1011000000110000011100000000000011011000000010000101011100101010000001000000101010110101000000001011111010000100000000100",
    "11,11,0001110110110000000000001011101101010000000000001100001101000010000000100001010100001010101001000001010010011000100100000",
    "11,11,0010000110010001000000100000111010010100000100100010000100010101000000000000001100010100000010001000000001000010110000000",
    "11,11,1000000000100110010001000000100000100001011101001010000010010101010100100000101000001100000110000001000001111010111000000",
    "11,11,0001100000110000010101100000101011001000000100010100001000000001010110000010100001110001100000000000001101001011000010000",
};

std::string puzzles9[] = {
    "12,12,001000010000100001000100100100000001000100001000010100000011010001001000000101000000000000011100101011000000101000000101000000110100101000000000",
    "12,12,101110000101000000110000010010000000010000010111010101000000010000000000000100101110010000100000010100000010010001111010000100000000100101111110",
    "12,12,100110000101000000010101000111010101010000000000000000100000001010101110000010100000111010100100000000100000000100001000000000001011111100100000",
    "12,12,010000000000000111111101110000000000000101010001010101000101000001000101111001000000000000001101101111100000000000001010011110000000000000110000",
    "12,12,100111111000000000000011110000000000000010111111101000000000101001001001101000000001000001110000111000000110000000010000000011000111111000010000",
    "12,12,100100111111000000000000011110001001000000000001010001110000010100000111000000000000000010110100101000000100100001010000100100000101000000000100",
    "12,12,000100100010110000000010000000010000101111000100000000010000101001010111100001010000100101000100000101000101110001000000000000000000111111110010",
    "12,12,110000000000000011111110111000000000000000000000100100110011000100000000010000000000010111101000000000001011101010101000100000001010000111000010",
    "12,12,000000010001011000000001000010011100000000000000100010101110000000100000000110100110000000000000100000011011000100000000010000011011010001000000",
    "12,12,000000000100110010010000000000000100100010000100001010100001000010100101000010000000001010101100100000000001000101011001110000000001000001100000",
    "12,12,000111010101010000010001010101010000000000010110010011000000010000011101010000000001010110100000010000101111010000100000000110100010110000101010",
    "12,12,100100011100100101000001100001000000100000000111000110110000110000000100000011010101101000010000100010000000001010111011000000000000001100101010",
    "12,12,110001100001000100001001000000101001010000101001010110001001000000000001001011110000100000000111101011000000001000010010001011000010101000011010",
    "12,12,010101011110010001000000000000001011100000001000101110101000000000101000010100001001010101001000010000000001000010101101101000000001100001001000",
    "12,12,101110010110100000010000000000000000000001100010100100001000000001100010100000000010001100100000100000000100000100100000110100101010000100000000",
    "12,12,100001010000000001010110000101010000010100000000000001000011101000001000000000000000111001000001000000001100001000000001000000000001110010010100",
    "12,12,000000000001111100000100000000100001100100001000100101101000100100001011100000000000001001110111000000000000101000100001000010000001001000011100",
    "12,12,111001101010000000001000010101000001000100000001110100101101000000000001011001010000000000000100010001000001000101000101000000010100110010010100",
    "12,12,010001101110000100000000010001111010000000000010000010111010011000000000000001111001101100000000000001101110111000000000000010101000101000001010",
    "12,12,111100100000000000001101110101000001000101011000010101000010000101000000110000000100000101010000000101000010000100010000110100000101000100110100",
    "12,12,110110000011000000101000010000101010000000001000000001000001000000000000101010101100101000000000000001100010100000000000000100001000000001101010",
    "12,12,101001010000101000000000000011000100101000010001001001000100000001010101100101000000100000001010001011100000000000001110010101000000010001011000",
    "12,12,000100010001110100000001000000101000100000100000101000100101001010000100001000000000001000101010101000100000000000101000110100100010000100101010",
    "12,12,000000100100011010100101000000100001010100000001010100010000010100010111000000000000100001110000100000000100101010100101001010100001000000000000",
    "12,12,110100001101000101000000110000000111000001000000000000011111111101000000000001001000011101000011000001000000001100001000000001000011111000000000",
    "12,12,110100011000000001000000000001010100000101000000010000000000000010000011100000110000100100000000000101000011100000010000101010000101000000100100",
    "12,12,010001100101010000000000000001011010111000000000000011110001000000000100001110000000000000010000011000010101000001000000100000000001000101001000",
    "12,12,000000000000011010100110000000000000010101000111010101010000000001000000100000001110000011100000000000000010011001101010000000001010000001000000",
    "12,12,110101100100000100000000100000001001000110000000010000001010010111101010000000000000000000010111011010010000000010000100000000000100011110000000",
    "12,12,001001011110101001000000000001011010011101000010000000010000000010000100011010000101000010100001010000001000010100101001010000100001010000000100",
};

StageData stages[] = {
    {1, 4,  12, 62,  puzzles1},
    {2, 5,  24, 178,  puzzles2},
    {3, 6,  30, 320,  puzzles3},
    {4, 7,  30, 423,  puzzles4},
    {5, 8,  30, 548,  puzzles5},
    {6, 9,  30, 706,  puzzles6},
    {7, 10, 30, 881,  puzzles7},
    {8, 11, 30, 1023,  puzzles8},
    {9, 12, 30, 1187,  puzzles9},
};

PuzzleData puzzleData = {9, 5328, stages};

PlayerData playerData = {
    0, 0, 0, 0, 0,
};

#define DATA_KEY_HASPLAYED      "hp"
#define DATA_KEY_CURRSTAGE      "cs"
#define DATA_KEY_LASTSTAGE      "ls"
#define DATA_KEY_CURRLEVEL      "cl"
#define DATA_KEY_LASTLEVEL      "ll"

void loadPlayerData() {
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    playerData.hasPlayed = ud->getBoolForKey(DATA_KEY_HASPLAYED);
    if (playerData.hasPlayed == false) {
        playerData.hasPlayed = true;
        savePlayerData();
        return;
    }
    playerData.currentStage = ud->getIntegerForKey(DATA_KEY_CURRSTAGE);
    playerData.lastStage = ud->getIntegerForKey(DATA_KEY_LASTSTAGE);
    playerData.currentLevel = ud->getIntegerForKey(DATA_KEY_CURRLEVEL);
    playerData.lastLevel = ud->getIntegerForKey(DATA_KEY_LASTLEVEL);
}

void savePlayerData() {
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    ud->setBoolForKey(DATA_KEY_HASPLAYED, playerData.hasPlayed);
    ud->setIntegerForKey(DATA_KEY_CURRSTAGE, playerData.currentStage);
    ud->setIntegerForKey(DATA_KEY_LASTSTAGE, playerData.lastStage);
    ud->setIntegerForKey(DATA_KEY_CURRLEVEL, playerData.currentLevel);
    ud->setIntegerForKey(DATA_KEY_LASTLEVEL, playerData.lastLevel);
    ud->flush();
}

void nextLevel() {
    playerData.currentLevel ++;
    if (playerData.currentLevel >= puzzleData.stages[playerData.currentStage].count) {
        playerData.currentLevel = 0;
        playerData.currentStage ++;
        if (playerData.currentStage >= puzzleData.count) {
            playerData.currentStage --;
            playerData.currentLevel = puzzleData.stages[playerData.currentStage].count - 1;
        }
    }
    if (playerData.currentStage > playerData.lastStage) {
        playerData.lastStage = playerData.currentStage;
        playerData.lastLevel = playerData.currentLevel;
    }
    if (playerData.currentLevel > playerData.lastLevel) {
        playerData.lastLevel = playerData.currentLevel;
    }
    savePlayerData();
}

bool endLevelOfStage() {
    return playerData.currentLevel + 1 >= puzzleData.stages[playerData.currentStage].count;
}

bool endStage() {
    return playerData.currentStage + 1 >= puzzleData.count;
}
