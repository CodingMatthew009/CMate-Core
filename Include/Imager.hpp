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

    struct Image
    {
        std::vector<Color> pixel_map;
        unsigned int width;
        // Color Space


        Image(std::vector<Color> pixels, int im_width);
        Image(Image& other);
        Image(std::vector<std::vector<Color>> array_2d);

        Image ValueMapToImage(std::vector<double> values, int width);
    
        std::vector<double> ImageToValueMap(Image& image);
    };

    struct ColorRange
    {
        Color lowColor;
        Color highColor;

        ColorRange(unsigned int lowR,
                   unsigned int lowG,
                   unsigned int lowB,
                   unsigned int highR,
                   unsigned int highG,
                   unsigned int highB
                );

        ColorRange(Color& low, Color& high);
        ColorRange(ColorRange& other);
    };

    class Imager
    {
        public:

        static void SaveImage(Image& image, const char* image_path);

        static Image LayerImages(Image& image1, Image& image2);

        static Image Filter(Image& image, ColorRange range);
    };
}