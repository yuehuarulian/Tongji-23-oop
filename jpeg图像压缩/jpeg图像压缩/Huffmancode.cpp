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
            huffmantable[Values[position]].length = i;//���볤��
            huffmantable[Values[position]].value = codevalue;//��Ӧ��ֵ
            position++;
            codevalue++;
        }
        codevalue <<= 1;
    }
}
// ����������������֣����ֵ�ȡֵ��Χ��-2047~2047֮�䣬JPEG�ṩ��һ�ű�׼��������ڶ���Щ���ֱ���
BitString HuffmanCode::getBitCode(int value)
{
    BitString ret(0, 0);
    int t = std::abs(value);
    //bit �ĳ���
    for (ret.length = 0; t; t >>= 1)
        ret.length++;
    if (value > 0)
        ret.value = value;
    else
        ret.value = ((1 << ret.length) - 1) ^ ( - value);//ȡ������-5 ��> 5:101 ��> 010
    return ret;
};
//DU���ҵ�64���� 
//preDC��ǰһ�����ݵ�DC 
//HRDC��HTAC��Huffman���������
//outputBitString�Ǵ���õ�
void HuffmanCode::encode(const int* DU, int& prevDC, const BitString* HTDC, const BitString* HTAC,BitString* outputBitString, int& bitStringCounts)
{
    // ���������־��16���������
    BitString EOB = HTAC[0x00];
    BitString SIXTEEN_ZEROS = HTAC[0xF0];

    int index = 0;

    // ���� DC ϵ��
    int dcDiff = (int)(DU[0] - prevDC);// ��εļ�ȥ֮ǰ��
    prevDC = DU[0];//����һ��DU
    if (dcDiff == 0)
        outputBitString[index++] = HTDC[0]; // DC û�б仯��ʹ�� Huffman ���е� 0 ����
    else {
        BitString bs = getBitCode(dcDiff);
        //JPEG�ṩ��һ�ű�׼��������ڶ���Щ���ֱ���
        // ʹ�� Huffman DC���ж�Ӧ���ȵ�����
        outputBitString[index++] = HTDC[bs.length];
        outputBitString[index++] = bs; // ��Ӳ���Ķ����Ʊ�ʾ
    }

    // ���� AC 
    // ���涼��0��EOB
    int endPos;
    for (endPos = 63; (endPos > 0) && (DU[endPos] == 0); endPos--)
        continue;
    // RLE����eg��(12,2):12��0��Ȼ��һ��2
    for (int i = 1; i <= endPos; ){
        int startPos = i;
        while (DU[i] == 0) 
            i++;
        int zeroCou = i - startPos;
        // �������� 16 ����ı���
        if (zeroCou >= 16){
            for (int j = 1; j <= zeroCou / 16; j++)
                outputBitString[index++] = SIXTEEN_ZEROS;
            zeroCou = zeroCou % 16;
        }
        // �������
        BitString bs = getBitCode(DU[i]);
        // ʹ�� Huffman ���ж�Ӧ���ȵ�����
        outputBitString[index++] = HTAC[(zeroCou << 4) | bs.length];//zero��Ŀǰ��λ�����㳣������λ
        outputBitString[index++] = bs; // ��ӷ���ϵ���Ķ����Ʊ�ʾ
        i++;
    }

    // ���ͼ����е� AC ϵ��û�е������һ��λ�ã���ӽ�����־
    if (endPos != 63)
        outputBitString[index++] = EOB;

    bitStringCounts = index; // �洢����ı������ĳ���
}