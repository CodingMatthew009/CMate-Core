#include "../Include/CMate-Core.h"

namespace cmate::core
{
    Image::Image(std::vector<Color> pixels, int im_width)
    {
        pixel_map = pixels;
        width = im_width;
    }

    Image::Image(Image& other)
    {
        pixel_map = other.pixel_map;
        width = other.width;
    }

    Image::Image(std::vector<std::vector<Color>> array_2d)
    {
        width = array_2d[0].size();

        for (auto collumn : array_2d)
        {
            for (Color pixel : collumn)
            {
                pixel_map.push_back(pixel);
            }
        }
    }

    Image Image::ValueMapToImage(std::vector<double> values, int width)
    {
        std::vector<Color> pixels;
        for (int c = 0; c < values.size(); c++)
        {
            pixels.push_back(ValueToColor(values[c]));
        }
        
        Image result = Image(pixels, width);
        return result;
    } 

    std::vector<double> Image::ImageToValueMap(Image& image)
    {
        std::vector<double> values;
        for (int i = 0; i < image.pixel_map.size(); i++)
        {
            values.push_back(ColorToValue(image.pixel_map[i]));
        }
        return values;
    } 


    ColorRange::ColorRange(unsigned int lowR,
                            unsigned int lowG,
                            unsigned int lowB,
                            unsigned int highR,
                            unsigned int highG,
                            unsigned int highB)
    {
        lowColor = Color(lowR, lowG, lowB);
        highColor = Color(highR, highG, highB);
    }

    ColorRange::ColorRange(Color& low, Color& high)
    {
        lowColor = low;
        highColor = high;
    }

    ColorRange::ColorRange(ColorRange& other)
    {
        lowColor = other.lowColor;
        highColor = other.highColor;
    }

    void Imager::SaveImage(Image& image, const char* image_path)
    {
        std::fstream image_stream;

        int height = image.pixel_map.size() / image.width;
        int row_size = (image.width * 3 + 3) & ~3; // +3 always crosses the next number divisable by 4 || & ~3 Removes last two digits (aka 0-2 from the value)
        int size_bytes = data_offset + row_size * height;

        // Open in binary writing mode
        image_stream.open(image_path, std::ios::out | std::ios::binary);
        if (!image_stream) {LOG("Failed to create image file!", LFlags::ERROR);}
        else
        {

            // BMP File Header
            {
                image_stream.put('B');
                image_stream.put('M');
                image_stream.write((char*)&size_bytes, 4);
                image_stream.write("\0\0", 2);
                image_stream.write("\0\0", 2);
                image_stream.write((char*)&data_offset, 4);

                image_stream.write((char*)&info_header_size, 4);
                image_stream.write((char*)&image.width, 4);
                image_stream.write((char*)&height, 4);
                image_stream.write((char*)&planes, 2);
                image_stream.write((char*)&color_accuracy, 2);

                //Optional/Unneeded Data in header
                image_stream.write("\0\0\0\0", 4);
                image_stream.write("\0\0\0\0", 4);
                image_stream.write("\0\0\0\0", 4);
                image_stream.write("\0\0\0\0", 4);
                image_stream.write("\0\0\0\0", 4);
                image_stream.write("\0\0\0\0", 4);
            }


            for (int x = image.width - 1; x >= 0; x--)
            {
                for (int y = 0; y < height; y++)
                {
                    image_stream.put(image.pixel_map[x + image.width * y].B);
                    image_stream.put(image.pixel_map[x + image.width * y].G);
                    image_stream.put(image.pixel_map[x + image.width * y].R);
                }
            
                // Bit Fillings
                for (int p = image.width * 3; p < row_size; p++)
                {
                    image_stream.put(0);
                }
            }
            image_stream.close();
        }

    }

    Image Imager::LayerImages(Image& image1, Image& image2)
    {
        std::vector<Color> new_pixels;
        for (int i = 0; i < image1.pixel_map.size(); i++)
        {
            new_pixels.push_back(image1.pixel_map[i] + image2.pixel_map[i]);
        }

        return Image(new_pixels, image1.width);
    }

    Image Imager::Filter(Image& image, ColorRange range)
    {
        std::vector<Color> new_pixels;
        for (int i = 0; i < image.pixel_map.size(); i++)
        {
            Color pixel = image.pixel_map[i];
            if (pixel > range.lowColor && pixel < range.highColor)
            {
                new_pixels.push_back(Color(255, 255, 255));
            }
            else
            {
                new_pixels.push_back(Color(0, 0, 0));
            }
        }

        return Image(new_pixels, image.width);
    }
}