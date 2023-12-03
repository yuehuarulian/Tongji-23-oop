#include "Huffmancode.h"
HuffmanCode::HuffmanCode()
{
    initHuffmanTables(Standard_DC_Luminance_NRCodes, Standard_DC_Luminance_Values, m_Y_DC_Huffman_Table);
    initHuffmanTables(Standard_AC_Luminance_NRCodes, Standard_AC_Luminance_Values, m_Y_AC_Huffman_Table);
    initHuffmanTables(Standard_DC_Chrominance_NRCodes, Standard_DC_Chrominance_Values, m_CbCr_DC_Huffman_Table);
    initHuffmanTables(Standard_AC_Chrominance_NRCodes, Standard_AC_Chrominance_Values, m_CbCr_AC_Huffman_Table);
}
void HuffmanCode::initHuffmanTables(const char* nr_codes, const unsigned char* Values, BitString* huffmantable)
{
    int position = 0;
    unsigned short codevalue = 0;
    for (int i = 1; i <= 16; i++){
        for (int j = 1; j <= nr_codes[i - 1]; j++){
            huffmantable[Values[position]].length = i;//编码长度
            huffmantable[Values[position]].value = codevalue;//对应的值
            position++;
            codevalue++;
        }
        codevalue <<= 1;
    }
}
// 处理括号右面的数字，数字的取值范围在-2047~2047之间，JPEG提供了一张标准的码表用于对这些数字编码
BitString HuffmanCode::getBitCode(int value)
{
    BitString ret(0, 0);
    int t = std::abs(value);
    //bit 的长度
    for (ret.length = 0; t; t >>= 1)
        ret.length++;
    if (value > 0)
        ret.value = value;
    else
        ret.value = ((1 << ret.length) - 1) ^ ( - value);//取反：如-5 —> 5:101 —> 010
    return ret;
};
//DU是我的64数据 
//preDC是前一个数据的DC 
//HRDC和HTAC是Huffman编码的数组
//outputBitString是处理好的
void HuffmanCode::encode(const int* DU, int& prevDC, const BitString* HTDC, const BitString* HTAC,BitString* outputBitString, int& bitStringCounts)
{
    // 定义结束标志和16个零的码字
    BitString EOB = HTAC[0x00];
    BitString SIXTEEN_ZEROS = HTAC[0xF0];

    int index = 0;

    // 编码 DC 系数
    int dcDiff = (int)(DU[0] - prevDC);// 这次的减去之前的
    prevDC = DU[0];//更新一下DU
    if (dcDiff == 0)
        outputBitString[index++] = HTDC[0]; // DC 没有变化，使用 Huffman 表中的 0 码字
    else {
        BitString bs = getBitCode(dcDiff);
        //JPEG提供了一张标准的码表用于对这些数字编码
        // 使用 Huffman DC表中对应长度的码字
        outputBitString[index++] = HTDC[bs.length];
        outputBitString[index++] = bs; // 添加差异的二进制表示
    }

    // 编码 AC 
    // 后面都是0，EOB
    int endPos;
    for (endPos = 63; (endPos > 0) && (DU[endPos] == 0); endPos--)
        continue;
    // RLE编码eg：(12,2):12个0，然后一个2
    for (int i = 1; i <= endPos; ){
        int startPos = i;
        while (DU[i] == 0) 
            i++;
        int zeroCou = i - startPos;
        // 处理连续 16 个零的编码
        if (zeroCou >= 16){
            for (int j = 1; j <= zeroCou / 16; j++)
                outputBitString[index++] = SIXTEEN_ZEROS;
            zeroCou = zeroCou % 16;
        }
        // 处理非零
        BitString bs = getBitCode(DU[i]);
        // 使用 Huffman 表中对应长度的码字
        outputBitString[index++] = HTAC[(zeroCou << 4) | bs.length];//zero数目前四位，非零常数后四位
        outputBitString[index++] = bs; // 添加非零系数的二进制表示
        i++;
    }

    // 如果图像块中的 AC 系数没有到达最后一个位置，添加结束标志
    if (endPos != 63)
        outputBitString[index++] = EOB;

    bitStringCounts = index; // 存储输出的比特流的长度
}