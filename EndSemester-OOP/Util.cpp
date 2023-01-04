#include "Util.h"
#include <string>


tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();


bool Util::state = true;
CNIC Util::cnic;

Mat Util::image = imread("D:\\Visual Studio\\EndSemester-OOP\\EndSemester-OOP\\Resources\\paper.jpg");
Mat Util::temp = imread("D:\\Visual Studio\\EndSemester-OOP\\EndSemester-OOP\\Resources\\paper.jpg");


void Util::init() {
    if (api->Init("C:\\Program Files\\Tesseract\\tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    api->SetPageSegMode(tesseract::PSM_AUTO);

}







bool Util::readText(Mat image) {

    state = false;

    char* outText;
    Mat blur, yuv, fin;

    GaussianBlur(image, blur, Size(3, 3), 1, 1);
    api->SetImage(image.data, image.cols, image.rows, 3, image.step);
    outText = api->GetUTF8Text();
    cout << outText;


    if (!cnic.isCNIC(outText)) {
        cvtColor(blur, blur, COLOR_BGR2YUV);
        api->SetImage(image.data, image.cols, image.rows, 3, image.step);
        outText = api->GetUTF8Text();
        cout << outText;


        if (!cnic.isCNIC(outText)) {
            fin = image - 255;
            cout << outText;


            if (!cnic.isCNIC(outText)) { state = true;  return false; }
        }
    }
    cout << outText;
   
    //createStudent(outText);

    state = true;

    return true;
}


Mat Util::addContour(Mat temp) {

    if (temp.empty()) { return Util::temp; }

    

    Mat image, blur, gray, canny, dial;

    resize(temp, image, Size(1280, 720), INTER_AREA);

    vector<vector<Point>> contours;

    cvtColor(image, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blur, Size(1,1), 1);
    Canny(gray, canny, 60, 255);
    dilate(canny, dial, getStructuringElement(MORPH_RECT, Size(3, 3)));

    findContours(dial,
        contours,
        RETR_TREE,
        CHAIN_APPROX_SIMPLE
    );


    bool chip = false, card = false;



    for (vector<Point> c : contours) {
        //double area = contourArea(c, false);
        Rect a = boundingRect(c);
        

        if (!chip)
        {
            if ((a.area() > 5000 && a.area() < 15000)) {
                if (a.x > 400 && a.x < 600 && a.y > 200 && a.y < 520) {
                    if (((a.width / a.height) < 1.08 && (a.width / a.height) > 0.95)) {

                        int t = a.height * 1.55+12;
                        int r = a.width * 0.7+12;
                        int l = a.width * 5.92+12;
                        int b = a.height * 3+12;
                        //rectangle(image, Point(a.x, a.y), Point(a.x + a.width, a.y + a.height), Scalar(0, 0, 255), 3);
                        //rectangle(image, Point(a.x- r, a.y-t), Point(a.x +l, a.y +b), Scalar(0, 0, 255), 3);

                        line(image, Point(a.x, a.y-t), Point(a.x, a.y+b), Scalar(0, 0, 255), 3);
                        line(image, Point(a.x+a.width, a.y - t), Point(a.x + a.width, a.y + b), Scalar(0, 0, 255), 3);
                        //putText(image, to_string(a.area()), Point(60, 60), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
                        chip = true;

                        cnic.chip_h = a.height;
                        cnic.chip_w = a.width;
                        cnic.chip_x = a.x;
                        cnic.chip_y = a.y;
                    }
                }
            }
        }

        if (!card)
        {
            if ((a.area() > 150000 && a.area() < 275000)) {
                if (a.x > 300 && a.x < 1000 && a.y > 150 && a.y < 570) {
                    if ((a.width / a.height) < 1.8 ) {

                        rectangle(image, Point(a.x, a.y), Point(a.x + a.width, a.y + a.height), Scalar(0, 0, 255), 3);
                        /*rectangle(image, Point(a.x- r, a.y-t), Point(a.x +l, a.y +b), Scalar(0, 0, 255), 3);

                        line(image, Point(a.x, a.y - t), Point(a.x, a.y + b), Scalar(0, 0, 255), 3);
                        line(image, Point(a.x + a.width, a.y - t), Point(a.x + a.width, a.y + b), Scalar(0, 0, 255), 3);*/
                        //putText(image, to_string(a.area()), Point(80, 80), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
                        card = true;

                        cnic.card_h = a.height;
                        cnic.card_w = a.width;
                        cnic.card_x = a.x;
                        cnic.card_y = a.y;
                    }
                }
            }
        }

        if (chip && card) {
            if (cnic.isValid()) {
                putText(image, "Is Valid!!!", Point(100,100), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 5);
                break;
            }
        }

    }
    /*Mat bg = imread("D:\\Visual Studio\\EndSemester-OOP\\EndSemester-OOP\\Resources\\bg.png");
    Mat final;
    addWeighted(bg, 1, image, 1, 0, final);*/


    rectangle(image, Point(250, 100), Point(1050, 630), Scalar(50, 50, 50), 11);
    return image;


}



Mat Util::detectCircle(Mat frame) {


    Mat gray, blur, canny, dial;

    cvtColor(frame, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blur, Size(1, 1), 1);
    Canny(gray, canny, 60, 255);
    dilate(canny, dial, getStructuringElement(MORPH_RECT, Size(3, 3)));

    vector<Vec3f> circles;
    HoughCircles(dial, circles, HOUGH_GRADIENT, 1,
        100,  // change this value to detect circles with different distances to each other
        100, 30, 40, 75 // change the last two parameters
        // (min_radius & max_radius) to detect larger circles
    );


    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(frame, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(frame, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
    }


    return frame;

}




