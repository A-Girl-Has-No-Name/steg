#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "steg1.h"

#include <sstream>


using namespace std;
using namespace cv;


int main(int argc, char** argv) {

        Mat src;
        int s, i;
        vector <double> q;
        double alpha; int beta;

        int check;
        cout << "input method number: \n";
        cin >> check;

        int gt;
        cout << "round parameter:  \n";
        cin >> gt;

 for (i=1; i<=100; i++)   {
     string ss;
     ss += to_string(i);
     ss.append (".bmp");
     cout <<ss<<"\n";
     src = imread (ss,1);

     if (check == 0) Testing (src, "fridrich.txt", i, gt);
     if (check == 1)  Testing1 (src, "cox.txt", i, gt);
     if (check == 2) Testing2 (src, "CUJB.txt", i, gt);
     if (check == 3) Testing3 (src, "KJ.txt", i, gt);
     ss.clear();

 }

                return 0;
}





