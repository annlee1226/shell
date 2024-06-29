#include <iostream>
#include <string>
#include <vector>

int main() {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";
  std::string input;

  while (std::getline(std::cin, input) && input != "exit 0")
  {
      
    if (input.substr(0, 4) == "echo"){
        if (input.length() == 4) {
                std::cout << std::endl;
            } else {
                std::cout << input.substr(5) << std::endl; 
            }
            std::cout << "$ ";
    }
    
    else if (input.find("type") != std::string::npos) {
    
        if (input.find("echo", 4) != std::string::npos){
            std::cout << input.substr(5, input.size() - 1) << " is a shell builtin";
        }
        
        else if (input.find("type", 5) != std::string::npos){
            std::cout << input.substr(5, input.size() - 1) << " is a shell builtin";
        }
        
        else if (input.find("exit", 5) != std::string::npos){
            std::cout << input.substr(5, input.size() - 1) << " is a shell builtin";
        }
        
        
        else if (input.find("cat", 5) != std::string::npos){
            std::cout << input.substr(5, input.size() - 1) << " is /bin/cat";
        }
        
        else {
            std::cout << input.substr(5, input.size() - 1) << ": not found";
        }
        
        std::cout << std::endl << "$ ";
        
    }
    
    else{
        std::cout << input << ": command not found\n";
        std::cout << "$ ";
    }
    
    
    
  }

}