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
#include "other.h"
#include <sstream>


using namespace std;
using namespace cv;

typedef Vec<float, 1> Vec1f;


void Testing (Mat src, string filename, int i, double gt)  {

      Mat img = src.clone();
      img = img (Rect( 0,0,240,240));
      vector<int> message;
      vector<int> answer;
      int l, s;
      int mis;


FILE * frid = fopen ("frid.txt", "r");
while (fscanf( frid, "%d", &l) == 1)
{
    message.push_back(l);
}

      vector<double> q;
      Mat code = Fridrich (img, s, message, q);
      Mat fin1 = round (code, gt);

      imwrite("./code.bmp",code);   Mat fin = imread ("code.bmp");

      answer = decode_Fridrich (fin1, s, q);
      ss = compare(  answer,  message);
      h.clear();

      h.append(ss);
      h.append("\n\n");
      ofstream File;
      File.open ( filename, ofstream::app);
      File << h;
       cout<<"writing:  "<<h;
      File.close();

  }

void Testing1 (Mat src, string filename, int i, double gt)  {

      Mat img = src.clone();
      img = img (Rect( 0,0,480,480));
      vector<double> message;
      vector<double> answer;
      int  s;
      int mis;
      double l;


FILE * frid = fopen ("coxi.txt", "r");
while (fscanf( frid, "%lf", &l) == 1)
{
    message.push_back(l);
}


      Mat code = Cox (img, s, 2, message);

      Mat fin = code.clone();

    imwrite("./code.bmp",fin);  fin = imread ("code.bmp");
      Mat fin1 = round (code, gt);

      answer = decode_Cox (fin1 ,img, s, 2);
      ss = compare(  answer,  message);
      h.clear();
      h.append(ss);
      h.append("\n\n");
      ofstream File;
      File.open ( filename, ofstream::app);

      File << h;
      File.close();



  }

void Testing2 (Mat src, string filename, int i, double gt)  {

      Mat img = src.clone();
      img = img (Rect( 0,0,240,240));
      vector<int> message;
      vector<int> answer;
      int s;
      int mis;
      double l;


FILE * frid = fopen ("CUJB1.txt", "r");
while (fscanf( frid, "%lf", &l) == 1)
{
    message.push_back(l);
}

      Mat code = code_CUJB(img, s, message);

      Mat fin = code.clone();

      imwrite("./code.bmp",fin);  fin = imread ("code.bmp");
      Mat fin1 = round (code, gt);
      
     answer = decode_CUJB (fin1, s);
     ss = compare(  answer,  message);

      h.clear();
      h.append(ss);
      h.append("\n\n");

      ofstream File;
      File.open ( filename, ofstream::app);
      File << h;
      File.close();

  }

void Testing3 (Mat src, string filename, int i, double gt)  {

      Mat img = src.clone();
      img = img (Rect( 0,0,240,240));
      vector<int> message;
      vector<int> answer;
      int s;
      int mis;
      double l;


FILE * frid = fopen ("KJ1.txt", "r");
while (fscanf( frid, "%lf", &l) == 1)
{
    message.push_back(l);
}

      Mat code = code_KJ_bw (img, s, message);

      Mat fin = code.clone();
      Mat fin1 = round (code, gt);
      imwrite("./code.bmp",fin);   fin = imread ("code.bmp");
      answer = decode_KJ_bw (fin1, s);
      ss = compare(  answer,  message);
      h.clear();

      h.append(ss);
      h.append("\n\n");
      ofstream File;
      File.open ( filename, ofstream::app);
      File << h;
      File.close();

  }

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





