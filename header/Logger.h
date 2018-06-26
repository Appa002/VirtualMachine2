//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_LOGGER_H
#define VM2_0_LOGGER_H

#include "Singleton.h"
#include <fstream>
#include <string>

#define LOG(msg) vm2::Singleton<vm2::Logger>::get().log(std::string((msg)) + std::string(" [Line: ") + std::to_string(__LINE__) + std::string("] [File: ") + std::string(__FILE__) + "]")

namespace vm2{
    class Logger : public Singleton<Logger>{
    public:
        Logger(){
            file.open("./logger.txt", std::ios::binary | std::ios::ate);
            if(!file.is_open())
                throw std::runtime_error("File could not be opened!");
        }

        ~Logger(){
            file.close();
        }

    private:
        std::ofstream file;

    public:
        void log(std::string msg){
            file << msg << std::endl;
        }
    };
}



#endif //VM2_0_LOGGER_H
