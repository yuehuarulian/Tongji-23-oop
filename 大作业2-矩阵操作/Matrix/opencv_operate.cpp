#include <conio.h>
#include <iostream>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;
const int image_size = 256 * 256;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;

Mat applyConvolution(const Mat& input, const Mat& kernel, Mat& output) {
    filter2D(input, output, input.depth(), kernel);
    return output;
}
//7.���Ӧ��
bool demo()
{
    /* ��vs2019+opencv��ȷ���ú󷽿�ʹ�ã��˴�ֻ����һ�ζ�ȡ����ʾͼ��Ĳο����룬���๦������������ƺͲ������� */
    Mat image = imread("images/demolena.jpg", IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    if (image.empty()) {
        cerr << "Error: Could not read the image." << endl;
        return ERROR;
    }
    imshow("Image-original", image);
 
    for (int i = 0; i < 6; i++) {
        Mat image_copy = image.clone();  //��¡ԭͼ����ֵ
        int *image_matrix;
        image_matrix = (int*)malloc(sizeof(int) * image_size);
        for (int y = 0; y < image.rows; ++y) {
            for (int x = 0; x < image.cols; ++x)
                image_matrix[y * image.cols + x] = (int)image.at<uchar>(y, x);
        }
 
        conv_eg(image_matrix, i);
        for (int y = 0; y < image.rows; ++y) {
            for (int x = 0; x < image.cols; ++x) {
                image_copy.at<uchar>(y, x) = image_matrix[y * image.cols + x];
            }
        }  
        switch (i + 1)
        {
            case 1:
                imshow("Convolution B1", image_copy);
                break;
            case 2:
                imshow("Convolution B2", image_copy);
                break;
            case 3:
                imshow("Convolution B3", image_copy);
                break;
            case 4:
                imshow("Convolution B4", image_copy);
                break;
            case 5:
                imshow("Convolution B5", image_copy);
                break;
            case 6:
                imshow("Convolution B6", image_copy);
                break;
            default:
                break;
        }        
    }
    if (waitKey(20000)==' ')
        destroyAllWindows();
    return true;
}
//8.OTSU �㷨 
bool OTSU()
{
    Mat gray_img = imread("images/demolena.jpg", IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    if (gray_img.empty()) {
        cerr << "Error: Could not read the image." << endl;
        return ERROR;
    }
    imshow("Image-original", gray_img);
    // ���ж�ֵ��
    Mat binary_img;
    threshold(gray_img, binary_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary_img);
    if (waitKey(20000)==' ')
        destroyAllWindows();
    return true;
}
//9.�����ӷ��� 
Mat morph_close_open(const Mat& input, int closed_size = 5, int open_size = 3)
{
    Mat kernel = getStructuringElement(MORPH_RECT, Size(closed_size, closed_size));
    Mat closed;
    morphologyEx(input, closed, MORPH_CLOSE, kernel);

    Mat open;
    kernel = getStructuringElement(MORPH_RECT, Size(open_size, open_size));
    morphologyEx(closed, open, MORPH_OPEN, kernel);

    return open;
}
bool plus_code(const char* str, int closed_size, int open_size)
{
    Mat gray_img = imread(str, IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    if (gray_img.empty()) {
        cerr << "Error: Could not read the image." << endl;
        return ERROR;
    }
    Mat binary_img;
    threshold(gray_img, binary_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
    //threshold(gray_img, binary_img, 100, 255, THRESH_TOZERO );

    // ʹ����̬ѧ�����������binary_img�ڲ��Ŀն�
    binary_img = morph_close_open(binary_img, closed_size, open_size);

    //// �������֣�mask��������������Ϊ��ɫ
    //Mat mask = Mat::zeros(binary_img.size(), CV_8U);
    //mask.setTo(255, binary_img);  // ����ֵ����binary_imgΪ255��������Ϊ255����ɫ��

    // ����һ���µ�ͼ�񣬽���������Ϊ��ɫ
    Mat result = gray_img.clone();
    result.setTo(0, ~binary_img);  // ��~binary_img��Ϊ0����������Ϊvalue��0��

    // ��ʾԭͼ�ʹ�����ͼ
    imshow("Original Image", gray_img);
    imshow("Processed Image", result);
    if (waitKey(20000)==' ')
        destroyAllWindows();
    return true;
}

//a.���ɷ���

static void CannyThreshold(int, void* userdata)
{
    Mat src_gray;
    Mat dst, detected_edges;
    Mat Myimage = *(Mat*)userdata;
    cvtColor(Myimage, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ::ratio, kernel_size);
    dst = Scalar::all(0);
    Myimage.copyTo(dst, detected_edges);
    imshow("Your picture", dst);
}
bool free_act()
{
    Mat Myimage;
    namedWindow("Display window(�밴�¿ո�ѡ����)");
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "cannot open camera";
        system("pause");
        return ERROR;
    }
    cout << "���¿ո�ѡ����Ƭ" << endl;
    while (true)
    {
        cap >> Myimage; 
        imshow("Display window(�밴�¿ո�ѡ����)", Myimage);
        if (Myimage.empty())
            return 1;
        resize(Myimage, Myimage, Size(1280, 720));
        // cv::resize(img, img, cv::Size(600, 720));  // ����һ�£��Ա��ܿ���ͼ��ȫ��
        if (waitKey(25) == ' ')
            break;
    }
    cap >> Myimage;
    //dst.create(Myimage.size(), Myimage.type());
    namedWindow("Your picture", WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", "Your picture", &lowThreshold, max_lowThreshold, CannyThreshold,&Myimage);
    CannyThreshold(lowThreshold, &Myimage);
    waitKey(0);
    cap.release(); // �ͷŶ���
    destroyAllWindows();
    return true;
}