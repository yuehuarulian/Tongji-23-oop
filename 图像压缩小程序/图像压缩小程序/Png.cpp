#include"Png.h"
#include <iostream>
#include <cmath>
#include <iostream>
#include <cmath>


// 定义 JPEG 标准的亮度和色度量化表
const int luminanceQuantizationTable[blockSize][blockSize] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99}
};

const int chrominanceQuantizationTable[blockSize][blockSize] = {
    {17, 18, 24, 47, 99, 99, 99, 99},
    {18, 21, 26, 66, 99, 99, 99, 99},
    {24, 26, 56, 99, 99, 99, 99, 99},
    {47, 66, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99}
};

// 量化步骤
void quantizeDCT(double block[blockSize][blockSize], const int quantizationTable[blockSize][blockSize]) {
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            block[i][j] = std::round(block[i][j] / quantizationTable[i][j]);
        }
    }
}

// 螺旋扫描顺序
const int zigzagOrder[blockSize * blockSize] = {
    0, 1, 8, 16, 9, 2, 3, 10,
    17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
};

// 将量化后的 DCT 系数按照螺旋扫描顺序转换为一维数组
void zigzagScan(double block[blockSize][blockSize], double zigzagArray[blockSize * blockSize]) {
    for (int i = 0; i < blockSize * blockSize; ++i) {
        int index = zigzagOrder[i];
        zigzagArray[i] = block[index / blockSize][index % blockSize];
    }
}

// 定义 DCT 转换矩阵
const double alpha_u(int u) {
    return (u == 0) ? 1.0 / std::sqrt(2) : 1.0;
}

const double alpha_v(int v) {
    return (v == 0) ? 1.0 / std::sqrt(2) : 1.0;
}

// 执行离散余弦变换 (DCT)
void performDCT(double block[blockSize][blockSize]) {
    double result[blockSize][blockSize] = { 0.0 };

    for (int u = 0; u < blockSize; ++u) {
        for (int v = 0; v < blockSize; ++v) {
            double sum = 0.0;

            for (int x = 0; x < blockSize; ++x) {
                for (int y = 0; y < blockSize; ++y) {
                    sum += block[x][y] * std::cos((2.0 * x + 1.0) * u * M_PI / 16.0) *
                        std::cos((2.0 * y + 1.0) * v * M_PI / 16.0);
                }
            }

            result[u][v] = 0.25 * alpha_u(u) * alpha_v(v) * sum;
        }
    }

    // 将结果复制回原始图像块
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            block[i][j] = result[i][j];
        }
    }
}

void RGBtoYCbCr(const Pixel& rgbPixel, double& Y, double& Cb, double& Cr) {
    Y = 0.29871 * rgbPixel.R + 0.58661 * rgbPixel.G + 0.11448 * rgbPixel.B;
    Cb = -0.168736 * rgbPixel.R - 0.331264 * rgbPixel.G + 0.5 * rgbPixel.B + 128;
    Cr = 0.5 * rgbPixel.R - 0.418688 * rgbPixel.G - 0.081312 * rgbPixel.B + 128;
}
void Jpeg::Zip()
{
    // JPEG 图像分割
    x_ycbcr = x / 8;
    y_ycbcr = y / 8;
    for (int row = 0; row < x; row += 8) {
        for (int col = 0; col < y; col += 8) {
            // 对 8x8 的图像块进行处理
            for (int blockY = 0; blockY < 8; ++blockY) {
                for (int blockX = 0; blockX < 8; ++blockX) {
                    int currentX = row + blockX;
                    int currentY = col + blockY;

                    // 处理当前像素
                    if (currentX < x && currentY < y) {
                        Pixel currentPixel(data[currentY * y * 4 + currentX],
                            data[currentY * y * 4 + currentX + 1],
                            data[currentY * y * 4 + currentX + 2],
                            data[currentY * y * 4 + currentX + 3]);
                        // 进行颜色空间转换
                        RGBtoYCbCr(currentPixel, ycbcr[row * x_ycbcr + col].Y[blockX][blockY],
                            ycbcr[row * x_ycbcr + col].Cb[blockX][blockY],
                            ycbcr[row * x_ycbcr + col].Cr[blockX][blockY]);

                    }
                }
            }
            // DCT 
            performDCT(ycbcr[row * x_ycbcr + col].Y);
            performDCT(ycbcr[row * x_ycbcr + col].Cb);
            performDCT(ycbcr[row * x_ycbcr + col].Cr);
            // 量化
            quantizeDCT(ycbcr[row * x_ycbcr + col].Y, luminanceQuantizationTable);
            quantizeDCT(ycbcr[row * x_ycbcr + col].Cb, chrominanceQuantizationTable);
            quantizeDCT(ycbcr[row * x_ycbcr + col].Cr, chrominanceQuantizationTable);
            // 使用螺旋扫描将二维数组转换为一维数组
            double zigzagArray[blockSize * blockSize];
            zigzagScan(ycbcr[row * x_ycbcr + col].Y, zigzag[row * x_ycbcr + col].Y);
            zigzagScan(ycbcr[row * x_ycbcr + col].Cb, zigzag[row * x_ycbcr + col].Cb);
            zigzagScan(ycbcr[row * x_ycbcr + col].Cr, zigzag[row * x_ycbcr + col].Cr);
        }
    }
}