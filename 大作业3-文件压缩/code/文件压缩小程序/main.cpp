#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include "huffman.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    //������ʼ
    auto starttime = chrono::high_resolution_clock::now();
    cout << "Zipper 0.001! Author: root" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }
    if (strcmp(argv[3], "zip") && strcmp(argv[3], "uzip")) {
        cerr << "Unknown parameter!\nCommand list:\nzip" << endl;
        return -1;
    }
    ifstream fin(argv[1], ios::binary); // �Զ����Ʒ�ʽ���ļ�
    if (!fin) {
        cerr << "Can not open the input file!" << endl; // ���������Ϣ���˳�
        return -1;
    }
    istreambuf_iterator<char> beg(fin),end; // ���������ļ�ָ�룬ָ��ʼ�ͽ������� char(һ�ֽ�) Ϊ����
    string text(beg, end); // ���ļ�ȫ������ string �ַ���
    fin.close(); // �������ļ���ر��ļ������һ����ϰ��

    // ����HuffmanTree��������outputText
    HuffmanTree huffmanTree('\0', 0);
    string t_outputText, outputText;
    if (!strcmp(argv[3], "zip"))//zip
        huffmanTree.encodeText(text, outputText);
    else //uzip
        huffmanTree.decodeText(text, outputText);
    huffmanTree.Delete();//�ֶ�deletһ�·�ֹ������������������

    //�ļ����
    ofstream fout(argv[2]); // ������ļ�
    if (!fout) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    fout << outputText; // ֱ�ӽ������õ��ַ����������
    fout.close();
    cout << "Complete!" << endl;

    //��¼ʱ��
    auto endtime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(endtime - starttime);
    cout << "����ʱ��: " << double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den << " ��" << std::endl;
    return 0;
}