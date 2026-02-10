#pragma once

#include "MLogger.hpp"
#include "General/Helpers.hpp"
#include "General/Enums.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

namespace cmate::core
{
    class Encrypter
    {
        public:
            Encrypter(std::string encryption_token);
            Encrypter(const Encrypter& other);

            std::string Encrypt(std::string Data);

            std::string Decrypt(std::string encrypted_data);

            std::string GetToken() const;

            void SetToken(std::string new_token);

        private:
            std::string token;
    };
}