#include <stdio.h>
#include <stdlib.h>

#include "NET.hpp"
#include "CAMERA.hpp"

#define MAX_SIZE 4096

void enable_camera(int sock_fd, sockaddr_in* client, socklen_t* client_size)
{
    cv::VideoCapture camera(0);
    
    if(!camera.isOpened())
    {
        error("Unable to access camera");
    }

    cv::Mat frame;
    camera.read(frame);
    int dim[2] = { frame.cols, frame.rows };

    sendto(sock_fd, dim, sizeof(int) * 2, 0, (sockaddr*)client, *client_size);
    int size = dim[0] * dim[1] * 3;
    fprintf(stdout, "[INFO-SERVER] size:%dx%d\n",dim[0], dim[1]);
    while(true)
    {
        camera.read(frame);

        if(frame.empty())
        {
            error("Unable to read the frame");
        }

        uchar* data = frame.data;
        int sum = 0;
        int c = 0;
        while(sum < size)
        {
            c = sendto(sock_fd, data + sum, MAX_SIZE, 0, (sockaddr*)client, *client_size);
            sum = sum + c;
        }
        
        
        cv::imshow("Camera SERVER", frame);

        if(cv::waitKey(1) == 'q')
        {
            close(sock_fd);
                break;
        }
    }


    camera.release();
    cv::destroyAllWindows();
    
    return;
}


void recive_frame(int sock_fd, sockaddr_in* client, socklen_t* client_size)
{
    int dim[2];
    recvfrom(sock_fd, dim, sizeof(int) * 2, 0, (sockaddr*)client, client_size);
    cv::Mat frame(dim[1], dim[0], CV_8UC3);
    uchar* data = frame.data;

    int size = dim[1] * dim[0] * 3;
    fprintf(stdout, "[INFO-CLIENT] size:%dx%d\n",dim[0], dim[1]);
    while(true)
    {   
        int sum = 0;
        int c = 0;
        while(sum < size)
        {
            c = recvfrom(sock_fd, data + sum, MAX_SIZE, 0, (sockaddr*)client, client_size);
            sum = sum + c;
        }

        imshow("CAMERA CLIENT", frame);
        if(cv::waitKey(1) == 'q')
        {
            close(sock_fd);
            break;
        }
    }
}