#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


Mat DCT_bw(Mat img);

Mat IDCT_bw(Mat img);

Mat code_CUJB(Mat src, int &s, vector<int> message);

double med(Mat img, int i, int j);

Mat Cox (Mat img, int &s, int way, vector<double> message);

vector<double> decode_Cox (Mat src, Mat was,  int s, int way);

Mat Fridrich (Mat src, int &s,  vector<int> message, vector <double> &q);

vector<int> decode_Fridrich (Mat dci, int s, vector<double> q);

Mat code_KJ_bw (Mat src, int &s, vector<int> message);

vector <int> decode_KJ_bw (Mat dci, int s);

Mat round (Mat src, int gt) { };

Mat round (Mat src, double gt) { };

string compare ( const vector<int> a, const vector<int> b)   { };

string compare ( const vector<double> a, const vector<double> b)   { };

void Testing (Mat src, string filename, int i, double gt)  { };

void Testing1 (Mat src, string filename, int i, double gt)  { };

void Testing2 (Mat src, string filename, int i, double gt)  { };

void Testing3 (Mat src, string filename, int i, double gt)  { };



