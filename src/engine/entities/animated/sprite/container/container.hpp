#ifndef CONTAINER_HPP_INCLUDED
#define CONTAINER_HPP_INCLUDED

#include "entity.hpp"

class Container : public Entity {
  public:
    Container();
    Container(std::string id, std::string file_path);
    Container(std::string id, uint8_t red, uint8_t green, uint8_t blue);
    virtual ~Container();

    void add_child(Entity* child);
    void remove_child(Entity* child);
    void remove_child_by_id(std::string id);
    void remove_children_by_type(entity_type type);
    void remove_most_recent_child(Entity* child);

    virtual int dependencies();
    virtual Entity* child_by_id(std::string id);
    virtual Entity* most_recent_child();

    virtual void update();
    virtual void render(Transform & transform);

  private:
    std::set<Entity*> _children;
};

#endif /* end of include guard: CONTAINER_HPP_INCLUDED */
