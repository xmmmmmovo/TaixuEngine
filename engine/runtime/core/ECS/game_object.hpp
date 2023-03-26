#ifndef GAME_OBJECT
#define GAME_OBJECT

namespace taixu
{
class GameObject
{
    public:
    std::uint32_t get_id(){return unique_id;};
    std::uint32_t set_id(std::uint32_t id_from_generator){unique_id=id_from_generator;};

    private:
    std::uint32_t unique_id;
    
};

}
#endif /* GAME_OBJECT */
