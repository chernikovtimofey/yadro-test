#include<string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

int detect_faces(const std::string& image_path, const std::string& save_path) {
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << image_path << "\n";
        return 1;
    }
    
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    // cv::imwrite("gray_photo.jpg", gray_image);

    cv::Mat eq_hist_image;
    cv::equalizeHist(gray_image, eq_hist_image);
    // cv::imwrite("eq_hist_photo.jpg", eq_hist_image);

    cv::Mat result_image = image.clone();
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(cv::samples::findFile("../haarcascades/haarcascade_frontalface_default.xml"))) {
        std::cerr << "Error loading Haar cascade\n";
        return 1;
    }

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(eq_hist_image, faces);
    for (const auto& face : faces) {
        cv::rectangle(result_image, face, cv::Scalar(191, 255, 0), 5);
    }

    cv::imwrite(save_path, result_image);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image_path> <save_path>\n";
        return 1;
    }

    std::string image_path = argv[1];
    std::string save_path = argv[2];
    
    return detect_faces(image_path, save_path);
}