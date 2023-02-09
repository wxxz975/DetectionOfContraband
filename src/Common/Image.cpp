#include "Image.h"


/*
GLuint C_Image::CreateTexture(const cv::Mat& image) {
    GLuint textureID = 0;
    int width = image.cols;
    int height = image.rows;
    int channel = image.channels();

    //获取图像指针
    int pixellength = width * height * channel;
    GLubyte* pixels = new GLubyte[pixellength];
    memcpy(pixels, image.data, pixellength * sizeof(char));

    // 使用GL指令生成贴图，获取贴图ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //必须一个RGB  一个BGR（opencv的mat类的颜色通道是BGR） 否则会出现颜色偏差
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
    //纹理放大缩小使用线性插值
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(pixels);

    return textureID;
}*/