#ifndef CONFIG_H
#define CONFIG_H
#include <map>
#include <string>

class GameConfig {
    public:
        std::map<std::string,std::string> Textures;
        static GameConfig LoadConfig(std::string path) {
            GameConfig config;
            config.Textures.insert(std::pair<std::string, std::string>("tileset","assets/tiny_galaxy_world.png"));
            config.Textures.insert(std::pair<std::string, std::string>("characters","assets/tiny_galaxy_monsters.png"));

            return config;
        };
};

#endif