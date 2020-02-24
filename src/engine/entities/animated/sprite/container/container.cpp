#include "container.hpp"

Container::Container() : Entity() {
    this->type = container;
}
Container::Container(std::string id, std::string file_path) : Entity(id, file_path) {
    this->type = container;
}
Container::Container(std::string id, uint8_t red, uint8_t green, uint8_t blue) : Entity(id, red, green, blue) {
    this->type = container;
}
Container::~Container() {
    for(auto child : _children) delete child;
}

void Container::add_child(Entity* child) {
    _children.insert(child);
}
void Container::remove_child(Entity* child) {
    /** TO DO **/
}
void Container::remove_child_by_id(std::string id) {
    /** TO DO **/
}
void Container::remove_children_by_type(entity_type type) {
    /** TO DO **/
}
void Container::remove_most_recent_child(Entity* child) {
    /** TO DO **/
}

int Container::dependencies() {
    return _children.size();
}
Entity* Container::most_recent_child() {
    /** TO DO **/
    return nullptr;
}
Entity* Container::child_by_id(std::string id) {
    /** TO DO **/
    return nullptr;
}

void Container::update() {
    Entity::update();
    for(auto child : _children) child->update();
}
void Container::render(Transform & transform) {
    Entity::render(transform);
    apply_transform(transform);
    for(auto child : _children) child->render(transform);
    deapply_transform(transform);
}
