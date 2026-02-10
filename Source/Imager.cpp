#include "../Include/Imager.hpp"

namespace cmate::core
{
    void Imager::ValuesToBitmap(std::vector<std::vector<double>> value_array, const char* image_path)
    {
        std::vector<std::vector<Color>> pixels = ValueMapToPixelMap(value_array);
        std::fstream image_stream;

        const int data_offset = 54;
        const int info_header_size = 40;
        const int planes = 1;
        const int color_accuracy = 24; //BGR = 24 bits

        int width = pixels.size();
        int height = pixels[0].size();
        int row_size = (width * 3 + 3) & ~3; // +3 always crosses the next number divisable by 4 || & ~3 Removes last two digits (aka 0-2 from the value)
        int size_bytes = 54 + row_size * height;

        image_stream.open(image_path, std::ios::out | std::ios::binary);
        if (!image_stream) {LOG("Failed to create image file!", LFlags::ERROR);}
        else
        {
            image_stream.put('B');
            image_stream.put('M');
            image_stream.write((char*)&size_bytes, 4);
            image_stream.write("\0\0", 2);
            image_stream.write("\0\0", 2);
            image_stream.write((char*)&data_offset, 4);

            image_stream.write((char*)&info_header_size, 4);
            image_stream.write((char*)&width, 4);
            image_stream.write((char*)&height, 4);
            image_stream.write((char*)&planes, 2);
            image_stream.write((char*)&color_accuracy, 2);

            //Optional Data in header
            image_stream.write("\0\0\0\0", 4);
            image_stream.write("\0\0\0\0", 4);
            image_stream.write("\0\0\0\0", 4);
            image_stream.write("\0\0\0\0", 4);
            image_stream.write("\0\0\0\0", 4);
            image_stream.write("\0\0\0\0", 4);


            for (int y = height - 1; y >= 0; y--)
            {
                for (int x = 0; x < width; x++)
                {
                    image_stream.put(pixels[x][y].B);
                    image_stream.put(pixels[x][y].G);
                    image_stream.put(pixels[x][y].R);

                }
            
                for (int p = width * 3; p < row_size; p++)
                {
                    image_stream.put(0);
                }
            }

            image_stream.close();
        }

    }

}