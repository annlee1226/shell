#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";
  
  std::string input;

  while (std::getline(std::cin, input) && input != "exit 0")
  {
      
    if (input.find("echo") != std::string::npos){
        std::cout << input.substr(5, input.size() - 1) << std::endl;
        std::cout << "$ ";
    }
    
    else{
        std::cout << input << ": command not found\n";
        std::cout << "$ ";
    }
    
  }

}