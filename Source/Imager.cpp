#include "../Include/CMate-Core.h"

namespace cmate::core
{
    void Imager::ValuesToBitmap(std::vector<double> value_array, int width, const char* image_path)
    {
        std::vector<Color> pixels = ValueMapToPixelMap(value_array);
        std::fstream image_stream;

        int height = pixels.size() / width;
        int row_size = (width * 3 + 3) & ~3; // +3 always crosses the next number divisable by 4 || & ~3 Removes last two digits (aka 0-2 from the value)
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
                image_stream.write((char*)&width, 4);
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


            for (int x = width - 1; x >= 0; x--)
            {
                for (int y = 0; y < height; y++)
                {
                    image_stream.put(pixels[x + width * y].B);
                    image_stream.put(pixels[x + width * y].G);
                    image_stream.put(pixels[x + width * y].R);
                }
            
                // Bit Fillings
                for (int p = width * 3; p < row_size; p++)
                {
                    image_stream.put(0);
                }
            }
            image_stream.close();
        }

    }

}