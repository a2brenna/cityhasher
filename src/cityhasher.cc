#include <boost/program_options.hpp>
#include <iostream>
#include <city.h>
#include <unistd.h>

namespace po = boost::program_options;

std::string DATA;
uint64_t MOD = 0;

size_t BUFF_SIZE = 1000000;

int get_config(int argc, char *argv[]) {
  po::options_description desc("Options");
  desc.add_options()
      ("d", po::value<std::string>(&DATA), "Data to hash. If unspecified, read and hash all of stdin as one value")
      ("m", po::value<uint64_t>(&MOD), "Unsigned integer to mod resulting hash by. Allows you to map to an arbitrarily sized hash space")
      ;

  try {

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch (...) {
    std::cerr << desc << std::endl;
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[]){
    if(get_config(argc, argv) != 0){
        return -1;
    }

    if(DATA.empty()){
        char buffer[BUFF_SIZE];
        for(;;){
            const auto bytes_read = read(0, buffer, BUFF_SIZE);
            if(bytes_read <= 0){
                break;
            }
            else{
                DATA.append(buffer, bytes_read);
            }
        }
    }

    if(MOD == 0){
        std::cout << CityHash64(DATA.c_str(), DATA.size()) << std::endl;
    }
    else{
        std::cout << CityHash64(DATA.c_str(), DATA.size()) % MOD << std::endl;
    }

    return 0;
}
