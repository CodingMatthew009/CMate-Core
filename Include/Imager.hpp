#pragma once

#include "MLogger.hpp"
#include "Color.hpp"

#include <fstream>
#include <vector>
#include <string>

namespace cmate::core
{
    //Constant data for bmp files
    const int data_offset = 54;
    const int info_header_size = 40;
    const int planes = 1;
    const int color_accuracy = 24;

    enum BlendMode
    {
        Additive,
        Alpha,
        Subtractive,
        Multiply,
        Min,
        Max
    };

    struct Image
    {
        std::vector<Color> pixel_map;
        unsigned int width;
        // Color Space


        Image(std::vector<Color> pixels, int im_width);
        Image(Image& other);
        Image(std::vector<std::vector<Color>> array_2d);
        Image() {}

        static Image ValueMapToImage(std::vector<double> values, int width);
    
        static std::vector<double> ImageToValueMap(Image& image);
    };

    class Imager
    {
        public:

        static void SaveImage(Image& image, const char* image_path);

        static Image LoadImage(const char* image_path, int width);

        static Image LayerImages(Image& image1, Image& image2, BlendMode mode, float alpha=0.5);

        static Image Filter(Image& image, ColorRange range);

        static Image Colorize(Image& image, ColorRange from, ColorRange to);
    };
}