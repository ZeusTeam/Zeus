#ifndef SINGLETON
#define SINGLETON

template<typename T>
class Singleton
{
protected:
    static T* m_pInst;

    Singleton() {}
    virtual ~Singleton() {}

public:
    static T* Instance()
    {
        if (m_pInst == NULL)
        {
            m_pInst = new T();
        }
        return m_pInst;
    }

    static void Destroy()
    {
        if (m_pInst != NULL)
        {
            delete m_pInst;
        }
        m_pInst = NULL;
    }

    virtual bool Initialize() = 0;

private:
    Singleton(const Singleton &s);
    Singleton& operator=(const Singleton &s);
};


#endif