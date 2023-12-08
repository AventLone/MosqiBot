/**********************************************************
 * @author AventLone
 * @version 0.2
 * @date 2023-09-16
 * @copyright Copyright (AventLone) 2023
 **********************************************************/
#pragma once
#include <opencv2/core.hpp>
#include <iostream>
#include <variant>

namespace avent
{
inline void exitWithInfo(const std::string& error_info)
{
    std::cerr << "\033[1;31mError: " + error_info + "\033[0m" << std::endl;
    exit(EXIT_FAILURE);
}

inline void throwError(const std::string& error_info)
{
    throw std::runtime_error("\033[1;31mError: " + error_info + "\033[0m");
}

/********************************************************************************
 * @brief Parse a setting file, yaml, to get value of the parameter.
 * @param setting_file Path to the setting file.
 * @param param Name of your parameter.
 * @return Value of your parameter.
 ********************************************************************************/
template<typename T>
T parseSettings(const std::string& setting_file, const std::string& param);

/********************************************************************************
 * @brief Parse a setting file, yaml, to get values of the parameters.
 * @param setting_file Path to the setting file.
 * @param params Names of your parameters.
 * @return Values of your parameters.
 ********************************************************************************/
template<std::size_t N>
std::array<std::variant<int, double, std::string, cv::Mat>, N> parseSettings(const std::string& setting_file,
                                                                             const std::array<std::string, N>& params)
{
    cv::FileStorage fs_ettings(setting_file, cv::FileStorage::READ);
    if (!fs_ettings.isOpened())
    {
        exitWithInfo("Failed to open settings file at: " + setting_file);
    }

    std::array<std::variant<int, double, std::string, cv::Mat>, N> outcomes;

    for (int i = 0; i < N; ++i)
    {
        cv::FileNode node = fs_ettings[params[i]];

        if (node.isReal())
        {
            // outcomes[i] = node.real();
            outcomes[i] = double(node);
        }
        else if (node.isInt())
        {
            outcomes[i] = int(node);
        }
        else if (node.isString())
        {
            outcomes[i] = std::string(node);
        }
        else if (node.isMap())
        {
            outcomes[i] = node.mat();
        }
        else
        {
            exitWithInfo("\"" + params[i] + "\"" + " parameter doesn't exist");
        }
    }
    fs_ettings.release();
    return outcomes;
}
}   // namespace avent
