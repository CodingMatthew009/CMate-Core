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

    Image Imager::LoadImage(const char* image_path, int width)
    {
        std::ifstream image_stream;

        image_stream.open(image_path, std::ios::binary);

        if (!image_stream) {LOG("Failed to load Image", LFlags::FAILED);}
        else 
        {   
            char temp[4];
            char temp2[2];
            int size_bytes;
            int data_offset;
            int info_header_size;
            int image_width;
            int image_height;
            int color_accuracy;

            std::vector<Color> pixels;

            image_stream.ignore(1);
            image_stream.ignore(1);
            image_stream.read((char*)&size_bytes, 4);
            image_stream.ignore(2);
            image_stream.ignore(2);
            image_stream.read((char*)&data_offset, 4);

            image_stream.read((char*)&info_header_size, 4);
            image_stream.read((char*)&image_width, 4);
            image_stream.read((char*)&image_height, 4);
            image_stream.ignore(2);
            image_stream.read((char*)&color_accuracy, 2);

            // Load optional data
            image_stream.ignore(4);
            image_stream.ignore(4);
            image_stream.ignore(4);
            image_stream.ignore(4);
            image_stream.ignore(4);
            image_stream.ignore(4);

            LOG(std::format("Loaded image data width:{}", image_width), LFlags::INFO);

            int row_size = (image_width* 3 + 3) & ~3;
            for (int x = 0; x < image_width; x++)
            {
                for (int y = 0; y < image_height; y++)
                {
                    int B, G, R;
                    image_stream.read((char*)&B, 1);
                    image_stream.read((char*)&G, 1);
                    image_stream.read((char*)&R, 1);

                    pixels.push_back(Color(R, G, B));
                }

                for (int p = image_width * 3; p < row_size; p++)
                {
                    image_stream.ignore(row_size - image_width * 3);
                }
            }

            return Image(pixels, image_width);
        }

    }

    Image Imager::LayerImages(Image& image1, Image& image2, BlendMode mode, float alpha)
    {
        // TODO: Convert to RGB format if different format
        std::vector<Color> new_pixels;
        for (int i = 0; i < image1.pixel_map.size(); i++)
        {
            Color new_pixel;

            switch (mode)
            {
                case BlendMode::Alpha:
                {
                    Color first_pixel = image1.pixel_map[i] * alpha;
                    Color second_pixel = image2.pixel_map[i] * (1 - alpha);
                    new_pixel = first_pixel + second_pixel;
                    break;
                }
                case BlendMode::Additive:
                {
                    new_pixel = image1.pixel_map[i] + image2.pixel_map[i];
                    break;
                }
                case BlendMode::Subtractive:
                {
                    new_pixel = image1.pixel_map[i] - image2.pixel_map[i];
                    break;
                }
                case BlendMode::Multiply:
                {
                    new_pixel = image1.pixel_map[i] * image2.pixel_map[i];
                    break;
                }
                case BlendMode::Min:
                {
                    new_pixel = min(image1.pixel_map[i], image2.pixel_map[i]);
                    break;
                }
                case BlendMode::Max:
                {
                    new_pixel = max(image1.pixel_map[i], image2.pixel_map[i]);
                    break;
                }
            }
            new_pixels.push_back(new_pixel);
        }

        return Image(new_pixels, image1.width);
    }

    Image Imager::Filter(Image& image, ColorRange range)
    {
        std::vector<Color> new_pixels;
        for (int i = 0; i < image.pixel_map.size(); i++)
        {
            Color pixel = image.pixel_map[i];
            if (pixel.R >= range.lowColor.R && pixel.R <= range.highColor.R &&
                pixel.G >= range.lowColor.G && pixel.G <= range.highColor.G &&
                pixel.B >= range.lowColor.B && pixel.B <= range.highColor.B)
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
    // TODO
    Image Imager::Colorize(Image &image, ColorRange from, ColorRange to)
    {
        std::vector<Color> new_pixels;
        for (int i = 0; i < image.pixel_map.size(); i++)
        {
            Color pixel = image.pixel_map[i];
            //double t = Color::SmoothStep(from.lowColor, from.highColor, pixel);
        }

        return Image(new_pixels, image.width);
    }
}