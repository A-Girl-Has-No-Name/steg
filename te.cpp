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
#include "steg.h"

#include <sstream>


using namespace std;
using namespace cv;


int main(int argc, char** argv) {

        Mat src;
        int s, i;
        vector <double> q;
        double alpha; int beta;

        int check;
        cout << "input method number: \n 0 - fridrich \n 1- cox \n 2 - CUJB \n 3 - KJ\n";
        cin >> check;

        double gt;
        cout << "round parameter:  \n";
        cin >> gt;

        int copy;
        cout << "save or clone?:  \n 0 - save, 1 - clone matrix\n";
        cin >> copy;

 for (i=1; i<=100; i++)   {
     string ss;
     ss += to_string(i);
     ss.append (".bmp");
     cout <<ss<<"\n";
     src = imread (ss,1);

     if (check == 0) Testing (src, "fridrich.txt",  copy, gt);
     if (check == 1)  Testing1 (src, "cox.txt", copy, gt);
     if (check == 2) Testing2 (src, "CUJB.txt", copy, gt);
     if (check == 3) Testing3 (src, "KJ.txt", copy, gt);
     ss.clear();

 }

                return 0;
}





