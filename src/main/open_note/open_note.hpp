#ifndef OPEN_NOTE_HPP_INCLUDED
#define OPEN_NOTE_HPP_INCLUDED

#include "game.hpp"

class Open_Note : public Game {
  public:
    Open_Note();
    virtual ~Open_Note();

    virtual void update();
    virtual void render(Transform & transform);
  private:
    Container* scene;
};

#endif /* end of include guard: OPEN_NOTE_HPP_INCLUDED */
