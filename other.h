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
//#include "steg.h"
#include <sstream>


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
  // ss.append ( "     mistakes from   ");
  // int tmp = (int) a.size();
  // ss += to_string(tmp);
  // ss.append ("  possible\n");
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
 //  ss.append ( "     mistakes from   ");
 //  int tmp = (int) a.size();
 //  ss += to_string(tmp);
 //  ss.append ("  possible\n");
}


if (a.size() > b.size())  ss.append ("14\n");                          //string& append (const char* s);
if (a.size() < b.size())  ss.append ("13\n");


return ss;

}


 //img = img (Rect( 0,0,240,240));

//	GaussianBlur (code, fin, Size(7,7), 0,0 );


 //     GaussianBlur(code, fin, Size(0, 0), 3);
//      addWeighted(code, 1.5, fin, -0.5, 0, fin);


/*
cout<< "in a, b\n";
cin >> alpha;
cin >> beta;
for (int y = 0; y < rows; y++ )
  { for( int x = 0; x < cols; x++ )
                     {
    fin.at<float>(y,x) =
        alpha*( fin.at<float>(y,x) ) + beta;
           }
  }


*/