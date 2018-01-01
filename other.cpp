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

      cout  <<" (write) fin  (100,  100):    "<< (int)fin.at<Vec3b>(100, 100)[0] <<"   " << (int) fin.at<Vec3b>(100, 100)[1] << "   "  <<(int) fin.at<Vec3b>(100, 100)[2] <<"\n";
      cout  <<"  fin1:    "<<  fin1.at<float>(100, 100) <<"\n";

      cout << "  fin size  "  << fin.rows <<"     " << fin.cols;  cout << "    ;     fin depth  " <<fin.depth() << ";   cha   "<<  fin.channels() << "  \n";
      cout << "  fin1 size  "  << fin1.rows <<"     " << fin1.cols;  cout << "   ;      fin1 depth  " <<fin1.depth() << ";   cha1   "<<  fin1.channels() << "  \n";

      cout  <<"  fin: CV_8U   "<< CV_8U <<"\n";
      cout  <<"  fin1: CV_32F   "<<  CV_32F  << "\n";

     /*  cout  <<" (write) fin  (50,  50):    "<< (int)fin.at<Vec3b>(50,  50)[0] <<"   " << (int) fin.at<Vec3b>(50,  50)[1] << "   "  <<(int) fin.at<Vec3b>(50,  50)[2] <<"\n";
       cout  <<"  fin1:    "<<  fin1.at<float>(50,  50) <<"\n";

       cout  <<" (write) fin  (20,  20):    "<< (int)fin.at<Vec3b>(20,  20)[0] <<"   " << (int) fin.at<Vec3b>(20,  20)[1] << "   "  <<(int) fin.at<Vec3b>(20,  20)[2] <<"\n";
       cout  <<"  fin1:    "<<  fin1.at<float>(20,  20) <<"\n";

       cout  <<" (write) fin  (1,  10):    "<< (int)fin.at<Vec3b>(1,  10)[0] <<"   " << (int) fin.at<Vec3b>(1,  10)[1] << "   "  <<(int) fin.at<Vec3b>(1,  10)[2] <<"\n";
       cout  <<"  fin1:    "<<  fin1.at<float>(1,  10) <<"\n";
*/



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


/*

      answer = decode_Fridrich (fin1, s, q);
      ss = compare(  answer,  message);
      h.clear();
      h += to_string(i);
      h.append("bmp :  ");

 h.append(ss);
      h.append("\n\n");
     // ofstream File;
     // File.open ( filename, ofstream::app);
      File << h;
       cout<<"writing:  "<<h;
      File.close();

*/

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

      /*cout  <<" (write) fin  (100,  100):    "<< (int)fin.at<Vec3b>(100, 100)[0] <<"   " << (int) fin.at<Vec3b>(100, 100)[1] << "   "  <<(int) fin.at<Vec3b>(100, 100)[2] <<"\n";
      cout  <<"  fin1:    "<<  fin1.at<float>(100, 100) <<"\n";

      cout << "  fin size  "  << fin.rows <<"     " << fin.cols;  cout << "    ;     fin depth  " <<fin.depth() << ";   cha   "<<  fin.channels() << "  \n";
       cout << "  fin1 size  "  << fin1.rows <<"     " << fin1.cols;  cout << "   ;      fin1 depth  " <<fin1.depth() << ";   cha1   "<<  fin1.channels() << "  \n";

       cout  <<"  fin: CV_8U   "<< CV_8U <<"\n";
       cout  <<"  fin1: CV_32F   "<<  CV_32F  << "\n";

      */
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


   /* cout  <<" (write) fin  (100,  100):    "<< (int)fin.at<Vec3b>(100, 100)[0] <<"   " << (int) fin.at<Vec3b>(100, 100)[1] << "   "  <<(int) fin.at<Vec3b>(100, 100)[2] <<"\n";
    cout  <<"  fin1:    "<<  fin1.at<float>(100, 100) <<"\n";

    cout << "  fin size  "  << fin.rows <<"     " << fin.cols;  cout << "    ;     fin depth  " <<fin.depth() << ";   cha   "<<  fin.channels() << "  \n";
    сout << "  fin1 size  "  << fin1.rows <<"     " << fin1.cols;  cout << "   ;      fin1 depth  " <<fin1.depth() << ";   cha1   "<<  fin1.channels() << "  \n";

    cout  <<"  fin: CV_8U   "<< CV_8U <<"\n";
    cout  <<"  fin1: CV_32F   "<<  CV_32F  << "\n";


    cout  <<" (write) fin  (50,  50):    "<< (int)fin.at<Vec3b>(50,  50)[0] <<"   " << (int) fin.at<Vec3b>(50,  50)[1] << "   "  <<(int) fin.at<Vec3b>(50,  50)[2] <<"\n";
    cout  <<"  fin1:    "<<  fin1.at<float>(50,  50) <<"\n";
    cout  <<" (write) fin  (20,  20):    "<< (int)fin.at<Vec3b>(20,  20)[0] <<"   " << (int) fin.at<Vec3b>(20,  20)[1] << "   "  <<(int) fin.at<Vec3b>(20,  20)[2] <<"\n";
    cout  <<"  fin1:    "<<  fin1.at<float>(20,  20) <<"\n";

    cout  <<" (write) fin  (1,  10):    "<< (int)fin.at<Vec3b>(1,  10)[0] <<"   " << (int) fin.at<Vec3b>(1,  10)[1] << "   "  <<(int) fin.at<Vec3b>(1,  10)[2] <<"\n";
    cout  <<"  fin1:    "<<  fin1.at<float>(1,  10) <<"\n";

*/
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



   /* cout  <<" (write) fin  (100,  100):    "<< (int)fin.at<Vec3b>(100, 100)[0] <<"   " << (int) fin.at<Vec3b>(100, 100)[1] << "   "  <<(int) fin.at<Vec3b>(100, 100)[2] <<"\n";
    cout  <<"  fin1:    "<<  fin1.at<float>(100, 100) <<"\n";

    cout << "  fin size  "  << fin.rows <<"     " << fin.cols;  cout << "    ;     fin depth  " <<fin.depth() << ";   cha   "<<  fin.channels() << "  \n";
     cout << "  fin1 size  "  << fin1.rows <<"     " << fin1.cols;  cout << "   ;      fin1 depth  " <<fin1.depth() << ";   cha1   "<<  fin1.channels() << "  \n";

     cout  <<"  fin: CV_8U   "<< CV_8U <<"\n";
     cout  <<"  fin1: CV_32F   "<<  CV_32F  << "\n";
*/
      answer = decode_KJ_bw (fin1, s);
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