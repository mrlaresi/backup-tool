#ifndef BACKUP_FILEINOUT_H
#define BACKUP_FILEINOUT_H

#include <filesystem> // traversing files
#include <vector> // std::vector

/** 
* Handles the filesystem operations.
*/
class FileInOut {
    public:
        /**
        * Writes a line of text to the end of a file
        * @param file_path to the file that will be written to
        * @param text that will be written to the file
        * @return empty string or an error message
        */
        static std::string write_to_file(const std::filesystem::path&, const std::string&);


        /**
        * Creates new file at filepath
        * @param file_path to the file that will be created
        * @return status message from the operation
        */
        static std::string create_file(const std::filesystem::path&);


        /**
        * Creates new folder at filepath
        * @param file_path to the folder that will be created
        * @return status message from the operation
        */
        static std::string create_folder(const std::filesystem::path&);


        /**
        * Removes line of text from a file
        * @param file_path path to the file
        * @param text that will be removed from the file
        * @return empty string or an error message
        */
        static std::string remove_line(const std::filesystem::path&, const std::string&);
        

        /**
        * Read lines from file into a vector
        * @param path filepath
        * @return lines from the file in inside a vector
        */
        static std::vector<std::string> read_file(const std::filesystem::path&);


        /**
        * Parses the stem of a filename from given filename
        * @param path filepath
        * @return the stem of path
        */
        static std::filesystem::path fetch_filename_stem(const std::filesystem::path&);

        
        /**
        * Returns the date and time of the last modification done to a given file 
        * in time_t format.
        * @param path path to a folder or a file
        */
        static time_t modify_time(const std::string&);


        /**
        * Recursively copies the contents of the source folder or file
        * into the destination folder. 
        * @param source Folder or a file to be copied
        * @param destination Location where source will be copied to
        * @return std::error_code if an error happened
        */
        static std::error_code copy(const std::filesystem::path&, const std::filesystem::path&);
        

        /**
        * Get current local time
        * @return local time in yyyymmdd_hhmm format
        */
        static std::string get_time();
};

#endif