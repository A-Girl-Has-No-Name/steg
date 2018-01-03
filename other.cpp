#define _USE_MATH_DEFINES

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "steg.h"



using namespace std;
using namespace cv;

double eps = 0.3;
string ss;
string h;

typedef Vec<float, 1> Vec1f;


Mat round (Mat src, int gt) {
    Mat copy = src.clone();

    int rows = copy.rows;
    int cols = copy.cols;
    int chan = copy.channels();
    int dep = copy.depth();

    if ((dep!= CV_8U)&&(dep!=CV_32F))  {cout << " "  << dep << "   ouch\n"; exit(-1);}

    for (int i = 0; i < rows; i+=1) {
            for (int j = 0; j < cols; j +=1) {
                if (dep==CV_32F)  {
                for (int ch = 0; ch < chan; ch++)
                    copy.at<Vec1f>(i, j)[ch] = (round (  gt * copy.at<Vec1f>(i, j)[ch] ) )/gt;
                              }

                else  for (int ch = 0; ch < chan; ch++)
                    copy.at<Vec3b>(i, j)[ch] = ( round ( gt* copy.at<Vec3b>(i, j)[ch] ))/gt ;

            }
    }

    return copy;
}



Mat round (Mat src, double gt) {
    Mat copy = src.clone();

    int rows = copy.rows;
    int cols = copy.cols;
    int chan = copy.channels();
    int dep = copy.depth();

    if ((dep!= CV_8U)&&(dep!=CV_32F))  {cout << " "  << dep << "   ouch\n"; exit(-1);}

    for (int i = 0; i < rows; i+=1) {
            for (int j = 0; j < cols; j +=1) {
                if (dep==CV_32F)  {
                for (int ch = 0; ch < chan; ch++)
                    copy.at<Vec1f>(i, j)[ch] = (round (  gt * copy.at<Vec1f>(i, j)[ch] ) )/gt;
                              }

                else  for (int ch = 0; ch < chan; ch++)
                    copy.at<Vec3b>(i, j)[ch] = ( round ( gt* copy.at<Vec3b>(i, j)[ch] ))/gt ;

            }
    }

    return copy;
}





string compare ( const vector<int> a, const vector<int> b)   {
     int h = 0;
     int i;
     string ss;


if ( a.size() == b.size() )   {
    for (i=0; i<a.size(); i++)  {
        if (a.at(i) != b.at(i) ) h++;
    }

   ss += to_string(h);

}


if (a.size() > b.size())  ss.append ("14\n");                          //string& append (const char* s);
if (a.size() < b.size())  ss.append ("13");


return ss;

}

string compare ( const vector<double> a, const vector<double> b)   {
     int h = 0;
     int i;
     string ss;


if ( a.size() == b.size() )   {
    for (i=0; i<a.size(); i++)  {
        if (  abs(a.at(i) - b.at(i))>eps ) h++;
    }

   ss += to_string(h);

}


if (a.size() > b.size())  ss.append ("14\n");                          
if (a.size() < b.size())  ss.append ("13\n");


return ss;

}


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
      //int gt=5;
      //cin >> gt;
      Mat fin1 = round (code, gt);


     // Mat fin = code.clone();

      imwrite("./code.bmp",code);   Mat fin = imread ("code.bmp");

       
      answer = decode_Fridrich (fin1, s, q);
      ss = compare(  answer,  message);
      h.clear();
     // h += to_string(i);
     // h.append("bmp :  ");

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
  //    h += to_string(i);
  //    h.append("bmp :  ");
      h.append(ss);
      h.append("\n\n");
      ofstream File;
      File.open ( filename, ofstream::app);

      File << h;
      // cout<<"writing:  "<<h;
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
    //  h += to_string(i);
    //  h.append("bmp :  ");
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
    //  Mat fin = round (code);
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
