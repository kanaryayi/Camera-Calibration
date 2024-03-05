#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main()
{
    // Set up parameters for the Charuco board
    // Number of squares along the X and Y axis
    int squaresX = 15;
    int squaresY = 11;
    // Square and marker length in meters or any other unit of measure
    float squareLength = 0.04f; // e.g., 4cm
    float markerLength = 0.02f; // e.g., 2cm
    // Dictionary of markers
    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    // Create Charuco board
    cv::aruco::CharucoBoard board(cv::Size(squaresX, squaresY), squareLength, markerLength, dictionary);

    // Create an image to display or save the board
    cv::Mat boardImage;
    board.generateImage(cv::Size(2440, 1440), boardImage, 10, 1);

    // Save the board to a file
    bool saved = cv::imwrite("charuco_board.png", boardImage);
    if (saved)
    {
        std::cout << "Charuco board image saved successfully!" << std::endl;
    }
    else
    {
        std::cout << "Failed to save the Charuco board image." << std::endl;
    }

    return 0;
}
