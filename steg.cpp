#include <iostream>
#include <opencv2/opencv.hpp>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


Mat DCT_bw(Mat img) {

int rows = img.rows;
        int cols = img.cols;

        Mat dst = img.clone();
        //cout << img.type() << "           here i am       \n";

        if (img.type() == 16) {
                cvtColor(dst, dst, CV_BGR2GRAY);
        }
        //if (img.type()) {
                dst.convertTo(dst, CV_32FC1);
        //}
        Mat prom;

        int p, q, i, j; int s = 0;
        int m = cols ; int n = rows; //int di = cols % 8; int dj = rows % 8;

        for (p = 0; p < n; p += 8) {
                for (q = 0; q < m; q += 8) {
                Rect region_of_interest = Rect(p, q, 8, 8);
                Mat pr = dst(region_of_interest);
                //pr.convertTo(pr, CV_32FC1);
                dct(pr, pr);
                //pr.convertTo(pr, CV_8UC1);

                }
        }
        
        //imshow("in_dct", dst);
        //imshow("in_dct_convert", dst);
        //waitKey(10000);
        imwrite ("./dct.jpg",dst );
        return dst;
}

Mat IDCT_bw(Mat img) {
        int rows = img.rows;
        int cols = img.cols;

        Mat dst = img.clone();
        dst.convertTo(dst, CV_32FC1);
        Mat prom;

        int p, q, i, j; int s = 0;
        int m = cols; int n = rows;

        for (p = 0; p < n; p += 8) {
                for (q = 0; q < m; q += 8) {
                        Rect region_of_interest = Rect(p, q, 8, 8);
                        Mat pr = dst(region_of_interest);
                        //pr.convertTo(pr, CV_32FC1);
                        idct(pr, pr);
                        //pr.convertTo(pr, CV_8UC1);

                }
        }
        //dst.convertTo(dst, CV_8UC1);
        //imshow("inverse_dct", dst);
        //waitKey(10000);
        //cout << "im dying"<<endl;

        return dst;
}




Mat code_CUJB(Mat src, int &s, vector<int> message)
{
        Mat img = src.clone();
        int rows = img.rows;
        int cols = img.cols;
        s = 0;
        int m, g;

        double co = 0.1;
        int i = 10;
        int j = 10;
        double sum;

           for (g = 0; g < message.size(); g++) {m = message.at(g);

                if (m == 0) {
                        sum = 0.299*img.at<Vec3b>(i, j)[2] + 0.587*img.at<Vec3b>(i, j)[1] + 0.114*img.at<Vec3b>(i, j)[0];
                        if (img.at<Vec3b>(i, j)[0] - co*sum > 0) { img.at<Vec3b>(i, j)[0] -= co*sum; } //bgr
                        else { img.at<Vec3b>(i, j)[0] = 0; }
                        s++;
                }
                if (m == 1) {
                        sum = 0.299*img.at<Vec3b>(i, j)[2] + 0.587*img.at<Vec3b>(i, j)[1] + 0.114*img.at<Vec3b>(i, j)[0];
                        if (img.at<Vec3b>(i, j)[0] + co*sum < 255) img.at<Vec3b>(i, j)[0] += co*sum; //bgr
                        else  img.at<Vec3b>(i, j)[0] = 255;
                        s++;
                }
                if (j + 10 < cols) j += 10;      
                else {
                        if (i + 10 < rows) {                
                                i += 10;
                                j = 1;
                        }
                        else break;
                }


        }

        img.convertTo(img, CV_8UC1);
        return img;

}

double med(Mat img, int i, int j) {
return (img.at<Vec3b>(i + 1, j)[0] + img.at<Vec3b>(i, j + 1)[0] + img.at<Vec3b>(i - 1, j)[0] + img.at<Vec3b>(i, j - 1)[0]) / 4;
//	return (img.at<Vec3b>(i + 1, j)[0] + img.at<Vec3b>(i, j + 1)[0] + img.at<Vec3b>(i - 1, j)[0] + img.at<Vec3b>(i, j - 1)[0] + img.at<Vec3b>(i + 2, j)[0] + img.at<Vec3b>(i, j + 2)[0] + img.at<Vec3b>(i - 2, j)[0] + img.at<Vec3b>(i, j - 2)[0]) / 8;
}

vector<int> decode_CUJB(Mat img, int s) {
        vector<int> message;
        //double eps = 2;
        int rows = img.rows;
        int cols = img.cols;

                for (int i = 10; i < rows; i+=10) {
                        for (int j = 10; j < cols; j +=10) {

                                if (s == 0) break;
                                if (img.at<Vec3b>(i, j)[0] < med(img, i, j) ) {
                                        message.push_back(0);
                                        s--;

                                }
                                if (img.at<Vec3b>(i, j)[0] > med(img, i, j) ) {
                                        message.push_back(1);
                                        s--;
                                }
                        }
                }

        return message;

}



Mat Cox (Mat img, int &s, int way, vector<double> message) {
                int rows = img.rows;
                int cols = img.cols;
                double co = 0.1;
                Mat dci = DCT_bw (img);
                s = 0;

                double m = 0;
                int i = 0;
                int j = 0;
                int g;

if (way == 2)  {
                for (g = 0; g<message.size(); g++ ) {

                                s++;
                                dci.at<float>(i, j) += co*message.at(g);
                        if (j + 9 < cols) j += 8;
                        else {
                                if (i + 9 < rows) {
                                        i += 8;
                                        j = 1;
                                }
                        }
                } }

if (way == 1)  {
                for (g = 0; g < message.size(); g++ ) {
                                s++;
                                dci.at<float>(i, j) *=( 1 + co*message.at(g));

                        if (j + 9 < cols) j += 8;
                        else {
                                if (i + 9 < rows) {
                                        i += 8;
                                        j = 1;
                                }
                        }
                }  }

if (way == 3)  {
                for (g = 0; g<message.size(); g++ ) {
                                s++;
                                dci.at<float>(i, j) *= exp(co*message.at(g));

                        if (j + 9 < cols) j += 8;
                        else {
                                if (i + 9 < rows) {
                                        i += 8;
                                        j = 1;
                                }

                }
}  }

                Mat coding = IDCT_bw (dci);
                return coding;
}


vector<double> decode_Cox (Mat src, Mat was,  int s, int way) {
        vector<double> message;
        int rows = src.rows;
        int cols = src.cols;
        double co = 0.1;
        Mat dci = DCT_bw (was);
        Mat img = DCT_bw (src);
        double m;
        int i;
        if (way == 1) {
         i = 0;
                for (int j = 0; j < cols; j += 8) {
                if (s == 0) break;
                        m = (dci.at<float>(i, j) - img.at<float>(i , j))/ co * img.at<float>(i , j) ;
                                message.push_back(m);
                                s--;
                        }

                }

        if (way == 2) {
                 i = 0;
                        for (int j = 0; j < cols; j += 8) {
                        if (s == 0) break;
                                m = (dci.at<float>(i, j) - img.at<float>(i , j))/ co ;
                                        message.push_back(m);
                                        s--;
                                }

                        }


        if (way == 3) {
                 i = 0;
                        for (int j = 0; j < cols; j += 8) {
                        if (s == 0) break;
                                m = log((dci.at<float>(i, j) - img.at<float>(i , j)))/ co ;
                                        message.push_back(m);
                                        s--;
                                }

                        }


        return message;
}

Mat Fridrich (Mat src, int &s,  vector<int> message, vector <double> &q)
                {
                        Mat img = src.clone();
                        int rows = img.rows;
                        int cols = img.cols;
                        double a = 0.5;
                        double c = (1+a)/(1-a);
                        s = 0;
                        int m;
                        int k=0;


                        int y;
                        int i = 10;
                        int j = 10;
                        int g;
                        double sum;
                        int h;
                        q.push_back(1);
                        while (q.back() <600)
                          {
                            q.push_back ( q.back()*c );
                          }

                        Mat dci = DCT_bw (src);

                                for (g=0; g < message.size(); g++) { m = message.at(g);
                                while (dci.at<float> (i,j) > q[k])  {
                                k++;}

                                y = pow (-1, k);
                                if (m!=y) {dci.at<float>(i,j) = q.at(k)+0.5;}
                                k = 0;
                                s++;

                                if (j + 11 < cols) j += 10;
                                else {
                                        if (i + 11 < rows) {
                                                i += 10;
                                                j = 1;
                                        }
                                        else break;
                                }


                        }


                                Mat coding = IDCT_bw (dci);
                                return coding;


                }

vector<int> decode_Fridrich (Mat dci, int s, vector<double> q)  {
        vector<int> message;
                int rows = dci.rows;
                int cols = dci.cols;
                int k = 0;

                Mat src = DCT_bw (dci);

                for (int i = 10; i < rows; i += 10) {
                        for (int j = 10; j < cols; j += 10) {
                    //  for (int j = 0; j < 120; j += 8) {
                                if (s == 0) break;
                                while (src.at<float> (i,j) > q[k])  {
                                                                k++;}
                                        message.push_back(pow(-1,k) );
                                        k = 0;
                                        s--;
                                }

                        }
                //}

                return message;

}




Mat code_KJ_bw (Mat src, int &s, vector<int> message) { //â êàêîì èçîáðàæåíèè ïðàâêè?
        int rows = src.rows;
        int cols = src.cols;

        //vector<int> message;
        Mat dci = DCT_bw (src);
        s = 0;

        //cout << "input binary message:\n";
        int m = 0;
        int i = 0;
        int j = 0;
        int k = 30;
        double x;
        int g;

        int a, b, c, d;
        a = 0;
        b = 0;
        c = 2;
        d = 1;

           for (g=0; g < message.size(); g++) { m = message.at(g);
                if (m == 0) {
                        s++;
                       // cout << "it was"   << "  pixel 1:   " << dci.at<float>(i + a, j + b) << "     pixel 2 : " << dci.at<float>(i + c, j + d) << "\n";
                        if (abs(dci.at<float>(i + a, j + b)) - abs(dci.at<float>(i + c, j + d)) < k) {
                                x = k - abs(dci.at<float>(i + a, j + b )) + abs(dci.at<float>(i + c, j + d));

                                if (dci.at<float>(i + a, j + b) > 0) dci.at<float>(i + a, j + b) += x / 2 + 1;
                                else if (dci.at<float>(i + a, j + b) < 0) 	dci.at<float>(i + a, j + b) -= x / 2 - 1;
                                if (dci.at<float>(i + c, j + d) > 0) dci.at<float>(i + c, j + d) -= x / 2 - 1;
                                else if (dci.at<float>(i + c, j + d) < 0) 	dci.at<float>(i + c, j + d) += x / 2 + 1;

                        }
                        //cout <<" i:  " << i+a << "    j: " << j+b <<  "   pixel 1:"    << dci.at<float>(i + a, j + b) << "   pixel 2:" << dci.at<float>(i + c, j + d) <<"  m:" <<m <<"\n"<<endl;
                }


                if (m == 1) {
                        s++;
                        //cout << "it was"   << "  pixel 1:   " << dci.at<float>(i + a, j + b) << "     pixel 2 : " << dci.at<float>(i + c, j + d) << "\n";
                        if (abs(dci.at<float>(i + a, j + b)) - abs(dci.at<float>(i + c, j + d)) > -k) {
                                x = k + abs(dci.at<float>(i + a, j + b)) - abs(dci.at<float>(i + c, j + d));

                                if (dci.at<float>(i + a, j + b) > 0) dci.at<float>(i + a, j +b) -= (x / 2 + 1);
                                else if (dci.at<float>(i + a, j + b) < 0) 	dci.at<float>(i + a, j + b) += (x / 2 + 1);
                                if (dci.at<float>(i + c, j + d) > 0) dci.at<float>(i + c, j + d) += x / 2 + 1;
                                else if (dci.at<float>(i + 5, j + 4) < 0) 	dci.at<float>(i + c, j + d) -= x / 2 - 1;

                        }
                        //cout <<" i:  " << i+a << "    j: " << j+b <<  "   pixel 1:"    << dci.at<float>(i + a, j + b) << "   pixel 2:" << dci.at<float>(i + c, j + d) <<"  m:" <<m <<"\n"<<endl;
                }


                if (j + 24 < cols) j += 24;                     //?
                else {
                        if (i + 30 < rows) {                   
                                i += 30;
                                j = 1;
                        }
                        else break;
                }



        }

        Mat coding = IDCT_bw (dci);
        return coding;

}

vector <int> decode_KJ_bw (Mat dci, int s) {
        vector<int> message;
        int rows = dci.rows;
        int cols = dci.cols;
        int k = 8;
        //cout << "we got picture -  "  << (int)dci.at<float>(0, 0) << "\n";
        //cout << "we got picture -  " << (int)dci.at<float>(2, 1) << "\n";
        Mat src = DCT_bw (dci);
        //cout << "   first dci element (0,0) :   " << src.at<float>(0, 0) << "   pixel 2   " << src.at<float>(2, 1) << "\n";
        int a, b, c, d;
        a =0 ;
        b =0;
        c =2;
        d =1;



        for (int i = 0; i < rows; i += 30) {
//	int i = 0;
                for (int j = 0; j < cols; j += 24) {
            //  for (int j = 0; j < 120; j += 8) {
                        if (s == 0) break;
                        if (abs(src.at<float>(i + a, j + b)) - abs(src.at<float>(i + c, j + d)) > k) {
                                message.push_back(0);
                              //  cout << " i: " << i + a << "   j: " << j + b << "    pixel 1: " << src.at<float>(i + a, j + b) << "     pixel 2: " << src.at<float>(i + c, j + d) <<  "   inserted: 0  " "\n";
                                s--;
                        }
                        if (abs(src.at<float>(i + a, j + b)) - abs(src.at<float>(i + c, j + d)) < -k) {
                                message.push_back(1);
                             //   cout << "   now i   " << i + a << "   now j   " << j + b << "    pixel 1:    " << src.at<float>(i + a, j + b) << "     pixel 2:      " << src.at<float>(i + c, j + d) << "   inserted: 1  " "\n";
                                s--;
                        }
                }
        }
        //cout << "cycle ended.\n";
        //for (int i = 0; i < message.size(); i++) cout << message.at(i);
        //cout << "\n";

        return message;
}
