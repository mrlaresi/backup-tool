#ifndef BACKUP_FILEINOUT_H
#define BACKUP_FILEINOUT_H

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


    public:
        /** 
        * Default constructor 
        * @param addr filepath to file containing backups
        * @param dest filepath to folder where backups will be made
        */
        FileInOut(const std::string& addr="./back.txt", const std::string& dest="./backup");

        /** Recursively copies folder and it's contents to 'backup_dest'. */
        void backup();

        /**
        * Adds new file path to the list of backups
        * @param path path to a folder or a file
        * @return 1 if success, otherwise 0
        */
        int add_backup(const std::filesystem::path&);

        /**
        * Removes file path from the list of backups
        * @param path path to a folder or a file
        * @return 1 if success, otherwise 0
        */
        int remove_backup(const std::filesystem::path&);
        

        /**
        * Read lines from file into a vector
        * @param path filepath
        * @return lines from the file in inside a vector
        */
        std::vector<std::string> read_file(const std::filesystem::path&);

        
        /**
        * Sets backup location
        * @param path filepath
        */
        void set_backup_dest(const std::filesystem::path&);


        /**
        * Returns vector containing backups in string format
        * @return vector containing backups in string fomrat
        */ 
        std::vector<std::string> get_backups();


        /**
        * Returns backup destination in string format
        * @return backup destination in string format
        */
        std::string get_destination();


    private:
        /**
        * Reads backup paths from the file 'backup_addr'
        * @return 1 if reading file failed, otherwise 0.
        */
        void read_backup();

        /**
        * Writes filepaths currently in memory to the backup file
        */
        void update_file();
        
        /**
        * Returns the date and time of the last modification done to a given file 
        * in time_t format.
        * @param path path to a folder or a file
        */
        time_t modify_time(const std::string&);

        /**
        * Recursively copies the contents of the source folder or the target
        * file into the destination folder. 
        * @param source Folder to be copied
        * @param destination Location where path1 will be copied to
        * @return std::error_code
        */
        std::error_code copy(const std::filesystem::path&, const std::filesystem::path&);
        
        /**
        * Get current local time
        * @return local time in yyyymmdd_hhmm format
        */
        std::string get_time();

        /**
        * Check if given filepath already exists on the list of paths to 
        * be backed up.
        * @param path path to a folder or a file
        * @return Iterator pointing to found item or vector<T>.end()
        */
        std::vector<std::filesystem::path>::iterator exists(const std::filesystem::path&);
};

#endif