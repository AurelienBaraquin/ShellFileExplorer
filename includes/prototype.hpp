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
void init_ncurses(void);
void print_warning(std::string str);
void processRegFile(const std::string file);
void open_file(global_t *global);
void print_files(global_t *global, struct Index pos);
void print_options(global_t *global, struct Index pos, int cursor);
void option_loop(global_t *global);
void stop(void);
void print_path(global_t *global, struct Index pos);
void print_text(struct Index pos, std::string text);
void print_colored_text(struct Index pos, std::string text, int color);

void setKey(const std::string& action, int key);
int getKey(const std::string& action);
std::string getKey_byIndex(int index);
int getKey_second_byIndex(int index);
std::unordered_map<std::string, int> get_keys_Map(void);
int getNbKeys(void);
void setDefaultKeys(void);
std::string key_to_str(int key);

void settings_loop(global_t *global);
void print_settings(Index pos, int cursor);

std::vector<std::string> split(std::string str, char delim);

#endif /* !PROT_HPP_ */
