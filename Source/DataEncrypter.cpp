#include "../Include/DataEncrypter.hpp"

namespace cmate::core
{
    Encrypter::Encrypter(std::string encryption_token)
    {
        SetToken(encryption_token);
    }

    Encrypter::Encrypter(const Encrypter& other)
    {
        SetToken(other.GetToken());
    }

    std::string Encrypter::Encrypt(std::string Data)
    {
        std::string encrypted_string;
        encrypted_string.resize(Data.size());

        for (int i = 0; i < Data.size(); i++)
        {
            encrypted_string[i] = Data[i] ^ token[i % token.size()];
        }

        return encrypted_string;
    }

    std::string Encrypter::Decrypt(std::string encrypted_data)
    {
        std::string decrypted_string;
        decrypted_string.resize(encrypted_data.size());

        for (int i = 0; i < encrypted_data.size(); i++)
        {
            decrypted_string[i] = encrypted_data[i] ^ token[i % token.size()];
        }

        return decrypted_string;
    }

    std::string Encrypter::GetToken() const
    {
        return token;
    }

    void Encrypter::SetToken(std::string new_token)
    {
        token = new_token;
    }
}