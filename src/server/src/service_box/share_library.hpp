#ifndef SHARE_LIBRARY_H_
#define SHARE_LIBRARY_H_

#include <common.h>
#include <boost/noncopyable.hpp>

typedef void ShareObject;

class ShareLibrary : public boost::noncopyable
{
public:
    ShareLibrary() 
        : _shareObject(NULL)
    {
    }

    ShareLibrary(const std::string& filename) 
        : _filename(filename), _shareObject(NULL)
    {
    }

    ~ShareLibrary()
    {
        dlclose();
    }

public:
    void setFileName(const std::string& filename)
    {
        _filename = filename;
    }

    ShareObject* dlopen()
    {
        return dlopen(_filename);
    }

    ShareObject* dlopen(const std::string& filename)
    {
        setFileName(filename);
#ifdef _WIN32
        _shareObject = (HMODULE)LoadLibraryA(_filename.c_str());
#else
        _shareObject = dlopen(_filename.c_str());
#endif
        return _shareObject;
    }

    void* getSymbol(const std::string& symbol)
    {
        if (_shareObject == NULL)
            return NULL;

#ifdef _WIN32
        return (void *)GetProcAddress((HMODULE)_shareObject, symbol.c_str());  
#else
        return dlsym(_shareObject, symbol.c_str());
#endif
    }

    void dlclose()
    {
        if (_shareObject == NULL)
            return;

#ifdef _WIN32
        FreeLibrary((HMODULE)_shareObject);
#else
        dlclose(_shareObject);
#endif
    }

private:
    ShareObject* _shareObject;
    std::string _filename;
};

#endif