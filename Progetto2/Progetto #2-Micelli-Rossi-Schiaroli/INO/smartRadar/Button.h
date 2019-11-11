#ifndef __BUTTON__
#define __BUTTON__

class ButtonListener {
  public:
    virtual void notifyButtonPressed() = 0;
};

class Button {
  public:
    virtual bool isPressed() = 0;
    virtual bool registerListener(ButtonListener* listener) = 0;
};

#endif
