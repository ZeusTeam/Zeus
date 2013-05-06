#ifndef SCENE
#define SCENE


class Scene
{
public:
    Scene() {}
    ///> todo: 这个类和它的子类都要用虚析构函数，否则delete指向子类的父类指针时会内存泄漏
    ~Scene() {}

    virtual void Update() = 0;
    virtual void Output() = 0;
    virtual void Reset()  = 0;

private:

};

#endif