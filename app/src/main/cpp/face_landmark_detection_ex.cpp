

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace dlib;
using namespace std;

#include <android/log.h>

#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

uchar * test_faced() {

    string path = "/storage/emulated/0/Pictures/dlibfolder/";

    try {

        frontal_face_detector detector = get_frontal_face_detector();

        shape_predictor sp;
        deserialize(path + "shape_predictor_68_face_landmarks.dat") >> sp;

        array2d<rgb_pixel> img;
        load_image(img,path + "header.png");
        const rectangle &rectOri = get_rect(img);
        pyramid_up(img);
        const rectangle &rectUp = get_rect(img);
        float scalY = rectUp.bottom() / rectOri.bottom();
        float scalX = rectUp.right() / rectOri.right();
        //LOGD("%f == %f",scalY, scalX);

        cv::Mat temp;
        temp=cv::imread(path + "header.png",cv::IMREAD_UNCHANGED);
        std::vector<rectangle> dets = detector(img);

        std::vector<full_object_detection> shapes;
        for (unsigned long j = 0; j < dets.size(); ++j) {
            full_object_detection shape = sp(img, dets[j]);
            shapes.push_back(shape);
        }

        //int checks = 5;
        int checks = 68;
        if (!shapes.empty()) {
            for (int i = 0; i < checks; i++) {
                //LOGD("%d %d == %d",i, shapes[0].part(i).x(), shapes[0].part(i).y());
                //bgr
                circle(temp, cvPoint(static_cast<int>(shapes[0].part(i).x() / scalX), static_cast<int>(shapes[0].part(i).y() / scalY)), 1, cv::Scalar(0, 0, 255, 255), 1, cv::LINE_AA, 0);
            }
        }

        return temp.data;
    }
    catch (exception &e) {
        LOGD("\nexception thrown!");
        LOGD("%s", e.what());
    }
}
// ----------------------------------------------------------------------------------------

