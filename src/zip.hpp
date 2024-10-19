#ifndef ZIP_EXTRACTOR_H
#define ZIP_EXTRACTOR_H

#include <string>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#define UNZIP_COMMAND "powershell -command \"Expand-Archive -Path"
#else
#define UNZIP_COMMAND "unzip"
#endif

class ZipExtractor {
public:
    // Constructor
    ZipExtractor(const std::string& zipPath, const std::string& outputPath)
        : zipPath(zipPath), outputPath(outputPath) {}

    // Method to extract the ZIP file
    void extract() {
        std::string command = buildCommand();
        int result = system(command.c_str());

        if (result != 0) {
            throw std::runtime_error("Failed to extract ZIP file.");
        }
    }

private:
    std::string zipPath;
    std::string outputPath;

    // Build the command for extracting the ZIP file
    std::string buildCommand() {
        std::string command;

#ifdef _WIN32
        command = UNZIP_COMMAND;
        command += " '" + zipPath + "' -DestinationPath '" + outputPath + "'";
#else
        command = UNZIP_COMMAND;
        command += " '" + zipPath + "' -d '" + outputPath + "'";
#endif

        return command;
    }
};

#endif // ZIP_EXTRACTOR_H
