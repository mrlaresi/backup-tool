#ifndef FILEINOUT_H
#define FILEINOUT_H

#include <filesystem> // traversing files
#include <vector> // std::vector


class FileInOut {
    private:
        /** time of last backup */
        time_t last_backup = -1; 
        /** all the paths */
        std::vector<std::filesystem::path> backup_paths;
        /** backup file */
        std::filesystem::path backup_addr;
        /** destination of backups */ 
        std::filesystem::path backup_dest;

        /**
        * Recursively copies the contents of the source folder into the 
        * destination folder. 
        * @param path1 Folder to be copied
        * @param path2 Location where path1 will be copied to
        * @return std::error_code
        */
        std::error_code copy_folder (const std::filesystem::path&, const std::filesystem::path&);
        
        /**
        * Get current local time
        * @return local time in yyyymmdd_hhmm format
        */
        std::string get_time();


    public:
        /** Default constructor */
        FileInOut();

        /**
        * Reads backup paths from the file 'backup_addr'
        * @return 1 if reading file failed, otherwise 0.
        */
        int read_backup();

        /** Recursively copies folder and it's contents to 'backup_dest'. */
        void backup();

        /**
        * Adds new file path to the list of backups
        * @param string1 path to a folder or a file
        */
        void add_backup(const std::string);

        /**
        * Returns the date and time of the last modification done to a given file 
        * in time_t format.
        * @param string1 path to a folder or a file
        */
        time_t modify_time(const std::string&);
};

#endif