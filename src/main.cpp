#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <cstdio>
#include <filesystem>
#include <iostream>

// Handles echo command
void get_Echo(const std::string& input) {
    if (input.length() == 4) {
        std::cout << std::endl;
    } else {
        std::cout << input.substr(5, input.size()) << std::endl;
    }
    std::cout << "$ ";
}

bool isexecutable(const char* p) {
    if (!access(p, X_OK)) {
        return true;
    }

    else { 
        return false;
    }
}

// Command is a shell builtin
bool shellbuiltin(const std::string& command) {
    return (command == "echo" || command == "type" || command == "exit" || command == "pwd");
}

std::vector<std::string> seperateDirectories(const char* p){
    std::stringstream pathvar(p);
    std::string split;
    std::vector<std::string> lst;

    while(std::getline(pathvar, split, ':')) {
        lst.push_back(split);
    }

    return lst;

}

std::string findexecutable(const std::string& input) {
    char* path = getenv("PATH");
    std::vector<std::string> directories; 
    std::string filepath;
    directories = seperateDirectories(path);
    for (int i = 0; i < directories.size(); ++i) {
        filepath = directories.at(i) + "/" + input;
        if (isexecutable(filepath.c_str())) {
            return filepath;
        }
    }

    return "";
}




// Handles type command
void get_Type(const std::string& input) {
    std::string command = input.substr(5);

    if (shellbuiltin(command)) {
        std::cout << command << " is a shell builtin";
    }
    else {
        std::string path = findexecutable(command);
        if (!path.empty()) {
            std::cout << command << " is " << path;
        } else {
            std::cout << command << ": not found";
        }
    }

    std::cout << std::endl << "$ ";
}

// Handles unknown commands
void UnknownCommand(const std::string& input) {
    char buffer[1024];
    std::string newinput = input.substr(0, input.find(' '));
    std::string path = findexecutable(newinput);
    if (!path.empty()) {
        FILE* pipe = popen((path + input.substr(newinput.length())).c_str(), "r");
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::cout << buffer;
        }

        pclose(pipe);
    } 
    else {
        std::cout << input << ": command not found\n";
    }
    std::cout << "$ ";
    
}

void get_cd(const std::string& input) {
    std::string command = input.substr(3);
    std::filesystem::path newpath = command;
        if (std::filesystem::exists(newpath) && std::filesystem::is_directory(newpath) ) {  
            //sets path
            std::filesystem::current_path(newpath);
        } 
        else if (command == "~") {
            char* home = getenv("HOME");
            std::filesystem::path homepath = std::string(home);
            std::filesystem::current_path(homepath);
        }
        else {
            std::cout << "cd: "<< command << ": No such file or directory" << std::endl;
    }
    std::cout << "$ ";
}

void get_pwd() {
    std::filesystem::path curpath = std::filesystem::current_path();
    std::cout << curpath.string() << std::endl << "$ ";
}

// Main function
int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";
    std::string input;


    while (std::getline(std::cin, input) && input != "exit 0") {
        if (input.substr(0, 4) == "echo") {
            get_Echo(input);
        } else if (input.substr(0, 4) == "type") {
            get_Type(input);
        } else if (input.substr(0, 3) == "pwd") {
            get_pwd();
        } else if (input.substr(0, 2) == "cd") {
            get_cd(input);
        }
        else {
            UnknownCommand(input);
        }
    }

    return 0;
}

