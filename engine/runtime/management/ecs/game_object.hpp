#ifndef TAIXUENGINE_GAME_OBJECT
#define TAIXUENGINE_GAME_OBJECT
#include <filesystem>

#include "guid_genenrator.hpp"

namespace taixu
{
class GameObject
{
    public:
    std::filesystem::path configure_path= "INVALID";
    std::uint32_t get_id(){return unique_id;};
    void set_id(std::uint32_t id_from_generator){unique_id=id_from_generator;};

    private:
    std::uint32_t unique_id;
    
};

}
#endif /* TAIXUENGINE_GAME_OBJECT */
