#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>

void detectAndDisplayCharucoBoard(cv::VideoCapture &capture)
{
    // Set up parameters for the Charuco board
    // Number of squares along the X and Y axis
    int squaresX = 15;
    int squaresY = 11;
    // Square and marker length in meters or any other unit of measure
    float squareLength = 0.03f;  // e.g., 3cm
    float markerLength = 0.015f; // e.g., 1.5cm
    // Dictionary of markers
    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    cv::Ptr<cv::aruco::CharucoBoard> board = cv::makePtr<cv::aruco::CharucoBoard>(cv::Size(squaresX, squaresY), squareLength, markerLength, dictionary);

    cv::Mat frame, imageCopy;
    size_t i = 0;
    while (true)
    {
        std::cout << "Running ! .." << std::endl;
        capture >> frame;
        if (frame.empty())
            break;
        frame.copyTo(imageCopy);
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
        cv::aruco::ArucoDetector arucoDetector(dictionary);
        arucoDetector.detectMarkers(frame, markerCorners, markerIds, rejectedCandidates);

        if (!markerIds.empty())
        {
            cv::aruco::drawDetectedMarkers(imageCopy, markerCorners, markerIds);
            std::vector<cv::Point2f> charucoCorners;
            std::vector<int> charucoIds;
            cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, frame, board, charucoCorners, charucoIds);
            if (!charucoIds.empty())
                cv::aruco::drawDetectedCornersCharuco(imageCopy, charucoCorners, charucoIds);
        }
        cv::imshow("Live Charuco Detection", imageCopy);
        char key = (char)cv::waitKey(10);
        if (key == 27) // press ESC to quit
            break;
        else if (key == 'c' || key == 'C')
        { // press 'c' for capture image
            // Capture the current frame and save it with a timestamp
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << "frame_" << std::put_time(std::localtime(&in_time_t), "%F-%X-") << i++ << ".png";
            cv::imwrite(ss.str(), frame);
            std::cout << "Captured " << ss.str() << std::endl;
        }
    }
}

int main()
{
    cv::VideoCapture capture(0); // Open default camera
    if (!capture.isOpened())
    {
        std::cerr << "Failed to open video capture device." << std::endl;
        return -1;
    }
    detectAndDisplayCharucoBoard(capture);
    return 0;
}
