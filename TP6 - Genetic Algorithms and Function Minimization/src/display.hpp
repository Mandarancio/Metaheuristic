#ifndef DISPLAY_HPP
#define DISPLAY_HPP 
#include<string>
#include <iostream>

#define BFOR "\033[1m"
#define NOFOR "\033[0m"
#define BRED "\033[1;31m"
#define BGREEN "\033[1;32m"
#define BYELLOW "\033[1;33m"

namespace msg{

enum type {
  NORM,
  BOLD, 
  GREEN,
  RED,
  YELLOW
};

};

template<typename Type> void display(std::string label, Type value, std::string unit="",msg::type type=msg::BOLD){
  switch(type){
    case(msg::GREEN):
      std::cout<<BGREEN;
      break;
    case(msg::RED):
      std::cout<<BRED;
      break;
    case(msg::YELLOW):
      std::cout<<BYELLOW;
      break;
    case(msg::BOLD):
      std::cout<<BFOR;
      break;
    default:
      std::cout<<NOFOR;
      break;
  }
  std::cout<<label<<": "<<NOFOR<<value<<" "<<unit<<std::endl;
};

void warning(std::string label);
void alert(std::string label);
void ok(std::string label);
void progress(int n, int tot);
#endif
