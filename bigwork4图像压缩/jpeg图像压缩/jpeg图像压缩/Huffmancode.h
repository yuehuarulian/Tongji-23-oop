#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include <string>
#include <iostream>
#include <stdio.h>
#include "const.h"
struct BitString
{
	int length;
	int value;
	BitString(int l = 0, int v = 0) :length(l), value(v) {}
};
class HuffmanCode{
public:
	HuffmanCode();
	void encode(const int* DU, int& prevDC, const BitString* HTDC, const BitString* HTAC,BitString* outputBitString, int& bitStringCounts);
	BitString m_Y_DC_Huffman_Table[12];
	BitString m_Y_AC_Huffman_Table[256];
	BitString m_CbCr_DC_Huffman_Table[12];
	BitString m_CbCr_AC_Huffman_Table[256];
private:
	BitString getBitCode(int value);
	void initHuffmanTables(const char* nr_codes, const unsigned char* std_table, BitString* huffman_table);
};

#endif
