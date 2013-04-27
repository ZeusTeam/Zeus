#ifndef SCENE
#define SCENE


class Scene
{
public:
    Scene() {}
    ~Scene() {}

    virtual void Update() = 0;
    virtual void Output() = 0;
    virtual void Reset()  = 0;

private:

};

#endif