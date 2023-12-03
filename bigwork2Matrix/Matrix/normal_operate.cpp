#include <conio.h>
#include <iostream>
#include <numeric>
#include "Matrix.h"
#define overflow 0
#define SQUARE_MATRIC 1
using namespace std;
const int prime_size = 90000;
const int increase_size = 1000;
const int kernel_size = 3;
const int padding = 1;
const int stride = 1;
const int dilation = 1;

/*
    int size;

    // 动态分配内存
    int *arr = new int[size];

    // 检查内存是否分配成功
    if (!arr) {
        cout << "Memory allocation failed." << endl;
        return 1;
    }

    // 输入数组元素
    cout << "Enter " << size << " elements for the array:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // 在使用完后释放内存
    delete[] arr;*/

struct MATRIX {
private:
    int size;
    //int MALLOC(){
    //    Matrix = (int*)malloc(size * sizeof(int));
    //    if (!Matrix)
    //        return overflow;
    //    for (int i = 0; i < size; i++)
    //        Matrix[i] = 0;
    //    return true;
    //}
public:
    int row;//行
    int col;//列
    int* Matrix;

    bool Matrix_in(bool square_matric = 0);
    void Matrix_out();
    //void Matrix_free();
    MATRIX(int r = 0, int c = 0, int* matrix = NULL) 
    {
        row = r;
        col = c;
        size = r * c;
        Matrix = new(nothrow) int[size]();
        if (Matrix == NULL && !size)
        {
            cout << "申请内存失败" << endl;
            exit;
        }
        if (matrix)
        {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    Matrix[i * col + j] = matrix[i * col + j];
                }
            }
        }
            //MALLOC();
    }
    ~MATRIX()
    {
        delete[]Matrix;
    }
};
bool MATRIX::Matrix_in(bool square_matric)
{
    if (square_matric) {   //方阵
        if (!row) {
            cout << "请输入方阵的阶数：" << endl;
            cin >> row;
            if (!cin.good() || row <= 0) {
                cout << "输入错误,返回菜单" << endl;
                cin.ignore(100000, '\n');
                cin.clear();
                return ERROR;
            }
            col = row;
        }
        else
            cout << "kernel矩阵的阶数为：" << kernel_size << endl;
    }
    else {
        cout << "请输入矩阵的行和列，中间用空格隔开：" << endl;
        cin >> row;
        cin >> col;
        if (!cin.good() || col <= 0 || row <= 0) {
            cout << "输入错误,返回菜单" << endl;
            cin.ignore(100000, '\n');
            cin.clear();
            return ERROR;
        }
        //动态申请内存
        size = row * col;
        Matrix = new(nothrow) int[size]();
        if (Matrix == NULL && !size)
        {
            cout << "申请内存失败" << endl;
            exit;
        }
    }

    //if (MALLOC() == overflow)
    //    return ERROR;
    //输入项数
    cout << "请输入矩阵的项，中间用空格隔开：" << endl;//优化一下输入，做个表格试试???
    for (int i = 0; i < row ; i++) {
        for (int j = 0; j < col; j++){
            cin >> Matrix[i * col + j];
            if (!cin.good()) {
                cout << "输入错误,返回菜单" << endl;
                cin.ignore(100000, '\n');
                cin.clear();
                return ERROR;
            }
        }
    }
    return true;
}
void MATRIX::Matrix_out()
{
    cout << "运算结果是：" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << Matrix[i * col + j] << ' ';
        cout << endl;
    }
}
//void MATRIX::Matrix_free(){
//    free(Matrix);
//}
//1.矩阵加法
bool matriplus()
{
    MATRIX matrix1, matrix2;
    if (!matrix1.Matrix_in())
        return ERROR;
    if (!matrix2.Matrix_in())
        return ERROR;
    if (matrix1.row != matrix2.row || matrix1.col != matrix2.col){
        cout << "两个矩阵行和列不相等，无法进行加法运算" << endl;
        return ERROR;
    }
    int row = matrix1.row;
    int col = matrix1.col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            matrix1.Matrix[i * col + j] += matrix2.Matrix[i * col + j];
    }
    matrix1.Matrix_out();
    //matrix1.Matrix_free();
    //matrix2.Matrix_free();
    return true;
}
//2.矩阵数乘
bool nummulti()
{
    MATRIX matrix;
    int a;
    if (!matrix.Matrix_in())
        return ERROR;
    cout << "请输入一个整数:" << endl;
    cin >> a;
    if (!cin.good()) {
        cout << "输入错误,返回菜单" << endl;
        cin.ignore(100000, '\n');
        cin.clear();
        return ERROR;
    }
    int row = matrix.row;
    int col = matrix.col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            matrix.Matrix[i * col + j] *= a;
    }
    matrix.Matrix_out();
    //matrix.Matrix_free();
    return true;
}
//3.矩阵转置
bool matritrans()
{
    MATRIX matrix;
    if (!matrix.Matrix_in())
        return ERROR;
    MATRIX matrix_trans(matrix.col, matrix.row);

    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++)
            matrix_trans.Matrix[j * matrix_trans.col + i] = matrix.Matrix[i * matrix.col + j];
    }
    matrix_trans.Matrix_out();
    //matrix.Matrix_free();
    //matrix_trans.Matrix_free();
    return true;
}
//4.矩阵乘法
bool matrimulti() 
{
    MATRIX matrix1, matrix2;
    if (!matrix1.Matrix_in())
        return ERROR;
    if (!matrix2.Matrix_in())
        return ERROR;
    if (matrix1.col != matrix2.row) {
        cout << "矩阵 A 的列数和矩阵 B 的行数相等，运算才有意义！" << endl;
        return ERROR;
    }
    MATRIX matrix_multi(matrix1.row, matrix2.col);

    for (int i = 0; i < matrix_multi.row; i++) {
        for (int j = 0; j < matrix_multi.col; j++) {
            for (int k = 0; k < matrix1.col; k++)
                matrix_multi.Matrix[i * matrix_multi.col + j] += matrix1.Matrix[i * matrix1.col + k] * matrix2.Matrix[k * matrix2.col + j];
        }
    }
    matrix_multi.Matrix_out();
    //matrix1.Matrix_free();
    //matrix2.Matrix_free();
    //matrix_multi.Matrix_free();
    return true;
}
//5.Hadamard乘积
bool hadamulti()
{
    MATRIX matrix1, matrix2;
    if (!matrix1.Matrix_in())
        return ERROR;
    if (!matrix2.Matrix_in())
        return ERROR;
    if (matrix1.row != matrix2.row || matrix1.col != matrix2.col) {
        cout << "两个矩阵行和列不相等，无法进行Hadamard乘积运算" << endl;
        return ERROR;
    }
    int row = matrix1.row;
    int col = matrix1.col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            matrix1.Matrix[i * col + j] *= matrix2.Matrix[i * col + j];
    }
    matrix1.Matrix_out();
    //matrix1.Matrix_free();
    //matrix2.Matrix_free();
    return true;
}
//6.矩阵卷积
int hadamulti(const MATRIX &kernel, const MATRIX &matrix_padding,const int i,const int j)//Hadamard乘积
{
    int a = 0;
    for (int m = 0; m < kernel_size; m++) {
        for (int n = 0; n < kernel_size; n++)
            a += kernel.Matrix[m * kernel_size + n] * matrix_padding.Matrix[(m + i) * matrix_padding.col + (n + j)];
    }
    return a;
}
bool conv()//矩阵卷积
{
    MATRIX matrix, kernel(kernel_size, kernel_size);
    if (!matrix.Matrix_in())
        return ERROR;
    if (!kernel.Matrix_in(SQUARE_MATRIC))
        return ERROR;
    int N_padding_row = matrix.row + 2 * padding;
    int N_padding_col = matrix.col + 2 * padding;
    if (N_padding_row < kernel_size || N_padding_col < kernel_size) {
        cout << "行列太小，无法做卷积" << endl;
        return ERROR;
    }
    //建造扩展后的矩阵
    MATRIX matrix_padding(N_padding_row, N_padding_col);
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            matrix_padding.Matrix[(i + padding) * N_padding_col + (j + padding)] = matrix.Matrix[i * matrix.col + j];
        }
    }

    //卷积后的矩阵
    int N_conv_row = (N_padding_row - kernel_size + 1) / dilation;
    int N_conv_col = (N_padding_col - kernel_size + 1) / dilation;

    MATRIX matrix_conv(N_conv_row, N_conv_col);
    for (int i = 0; i < N_conv_row; i++) {
        for (int j = 0; j < N_conv_col; j++) {
            matrix_conv.Matrix[i * N_conv_col + j] = hadamulti(kernel, matrix_padding, i, j);
        }
    }
    matrix_conv.Matrix_out();
    //kernel.Matrix_free();
    //matrix.Matrix_free();
    //matrix_padding.Matrix_free();
    //matrix_conv.Matrix_free();
    return true;
}
//7.矩阵应用_求卷积
bool conv_eg(int*& image_matrix, int choice)
{
    //卷积核
    int B[6][9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    -1, -2, -1, 0, 0, 0, 1, 2, 1,
                    -1, 0, 1, -2, 0, 2, -1, 0, 1,
                    -1, -1, -1, -1, 9, -1, -1, -1, -1,
                    -1, -1, 0, -1, 0, 1, 0, 1, 1,
                     1, 2, 1, 2, 4, 2, 1, 2, 1 };
    int sum = accumulate(B[choice], B[choice] + 9, 0);
    MATRIX matrix(256, 256, image_matrix);
    MATRIX kernel(kernel_size, kernel_size, B[choice]);
    //建造扩展后的矩阵
    int N_padding = matrix.row + 2 * padding;
    MATRIX matrix_padding(N_padding, N_padding);
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.row; j++) {
            matrix_padding.Matrix[(i + padding) * N_padding + (j + padding)] = matrix.Matrix[i * matrix.row + j];
        }
    }
   
    //卷积后的矩阵
    int N_conv = (N_padding - kernel_size + 1) / dilation;
    static MATRIX matrix_conv(N_conv, N_conv);
    for (int i = 0; i < N_conv; i++) {
        for (int j = 0; j < N_conv; j++) {
            matrix_conv.Matrix[i * N_conv + j] = hadamulti(kernel, matrix_padding, i, j);
            //超出0-255的处理以及加128的修正
            if (sum)
                matrix_conv.Matrix[i * N_conv + j] /= sum;
            else
                matrix_conv.Matrix[i * N_conv + j] += 128;
            if (matrix_conv.Matrix[i * N_conv + j] < 0)
                matrix_conv.Matrix[i * N_conv + j] = 0;
            else if (matrix_conv.Matrix[i * N_conv + j] > 255)
                matrix_conv.Matrix[i * N_conv + j] = 255;
        }
    }
    image_matrix = matrix_conv.Matrix;         
    //matrix.Matrix_free();
    //matrix_padding.Matrix_free();
    return true;
}
 