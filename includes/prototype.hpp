/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** prototype
*/

#ifndef PROT_HPP_
    #define PROT_HPP_

    #include "my.hpp"

std::string get_input(const std::string& ask, const std::string& default_value);
int get_choice(const std::string& ask, const std::vector<std::string>& choices);
void get_files(global_t *global);
void cursor_fix(int *cursor, Index min_max);
void init_ncurses(void);
void print_warning(std::string str);
void processRegFile(const std::string file);
void open_file(global_t *global);
void print_files(struct Index pos, int cursor, std::filesystem::path path, std::vector<std::string> files);
void print_options(struct Index pos, int cursor);
void option_loop(std::filesystem::path path, std::vector<std::string> files, global_t *global, int cursorFile);
void stop(void);
void print_path(std::filesystem::path path, struct Index pos);
void print_text(struct Index pos, std::string text);
void print_colored_text(struct Index pos, std::string text, int color);
void print_vector(std::vector<std::string> vector, struct Index pos, ...);

void setKey(const std::string& action, int key);
int getKey(const std::string& action);
std::string getKey_byIndex(int index);
int getKey_second_byIndex(int index);
std::unordered_map<std::string, int> get_keys_Map(void);
int getNbKeys(void);
void setDefaultKeys(void);
std::string key_to_str(int key);
void setKeyFromFile(const std::string& filePath);
void saveKeyOnFile(const std::string& filePath);

void settings_loop(global_t *global);
void print_settings(Index pos, int cursor);

std::vector<std::string> split(std::string str, char delim);
int get_max_str_size_from_vector(std::vector<std::string> files);

int init_config_folder(void);

std::string searchInCurrentRep(const std::string& toSearch, std::filesystem::path currentPath);
std::string executeCommand(const std::string& command);

#endif /* !PROT_HPP_ */
