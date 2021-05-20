#ifndef BACKUP_CORE_H
#define BACKUP_CORE_H

#include <vector>
#include <filesystem>

class Core {
    private:        
        /** time of last backup */
        time_t last_backup = -1; 

        /** Vector containing the paths that will be backed up */
        std::vector<std::filesystem::path> backup_paths;

        /** File containing list of file locations that will be backed up */
        std::filesystem::path backup_addresses = "./back.txt";

        /** Destination of backups */ 
        std::filesystem::path backup_destination = "./backup";
        
        /** Settings file */
        std::filesystem::path settings = "./settigns.ini";

    public:
        /** Default constructor */
        Core();


        /** Loads the program settings from .ini file */
        int load_settings();


        /** 
        * Recursively backs up filepaths contained in backup_paths vector
        * that have not been modified since last backup. 
        */
        std::string backup();
        

        /** 
        * Adds filepath to files to be backed up 
        * @param input path to a directory or a file
        * @return status message
        */
        std::string add_backup(const std::string&);


        /** 
        * Removes filepath from the backup list 
        * @param input path to a directory or a file
        * @return status message
        */
        std::string remove_backup(const std::string&);


        /**
        * Gets list of filepaths that will be backed up as string
        * @return string containing backup paths
        */ 
        std::string get_backups();
        

        /**
        * Gets backup destination
        * @return backup destination
        */
        std::string get_destination();


        /**
        * Sets backup destination 
        * @param path to the backup destination
        * @return message
        */
        std::string set_destination(const std::filesystem::path&);


        //int backup_loop();

    private:
        /**
        * Sets class variables
        */
        void set_settings(const std::vector<std::string>&);


        /**
        * Reads back up paths from backup_paths file
        */
        void read_backup();


        /**
        * Forms filepath pointing to the backup location from backup_destination,
        * filepath and current_time causing the following folder structure to
        * form: backup_destination/filepath/time/<backup files>
        * @param filepath to the directory that will be backed up
        * @param time in yyyymmdd_hhmm format
        * @return std::filesystem::path 
        */
        std::filesystem::path form_backup_path(
            const std::filesystem::path&,
            const std::filesystem::path&);

        
        /**
        * Check if given filepath already exists on the list of paths to 
        * be backed up.
        * @param path path to a folder or a file
        * @return Iterator pointing to found item or vector<T>.end()
        */
        std::vector<std::filesystem::path>::iterator exists(const std::filesystem::path&);
};

#endif