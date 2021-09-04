#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <homography_transformer.h>

int main(int argc, char **argv)
{
    // Setting the random seed to get random results in each run.
    srand(time(NULL));

    if (argc < 8)
    {
        std::cout << "some arguments are missing" << std::endl;
        return -1;
    }
    std::string homography_matrix_file = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];

    int output_width = std::stoi(argv[4]);
    int output_height = std::stoi(argv[5]);
    double multiplication_ratio = std::stod(argv[6]);
    int starting_x = std::stoi(argv[7]);
    int starting_y = std::stoi(argv[8]);

    // Read homography matrix
    cv::Mat H;
    HomographyTransformer::readMatrix(homography_matrix_file, 3, 3, H);
    std::cout << H << std::endl;

    HomographyTransformer homographyTransformer(H, output_width, output_height, multiplication_ratio, starting_x, starting_y);

    cv::VideoCapture cap(input_file);

    int fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << "fps: " << fps << std::endl;

    cv::VideoWriter video(output_file, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(output_width, output_height));

    int i = 0;
    while (1)
    {
        cv::Mat frame;
        cap >> frame;


        if (frame.empty())
        {
            std::cout << "video is empty" << std::endl;
            break;
        }

        cv::Mat new_image = homographyTransformer.transformImage(frame);

        video << new_image;

        if (i % 100 == 0)
            std::cout << i << " frames are processed" << std::endl;
        i++;
    }

    video.release();
    cap.release();

    return 0;
}