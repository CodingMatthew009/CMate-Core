#include "../Include/Imager.hpp"

namespace utils
{
    void Imager::ValuesToBitmap(std::vector<std::vector<double>> value_array, std::string image_path)
    {
        std::vector<Color> pixels = ValuesToColors(std::vector<double> values)

        std::ofstream image_stream;
        int size_bytes = 

        image_stream.open(image_path, std::ios::binary);
        if (!image_stream) {LOG("Failed to create image file!", LFlags::ERROR);}
        else
        {
            image_stream << "BM";
            image_stream << "\n";
            image_stream << size_bytes;
        }

    }

}