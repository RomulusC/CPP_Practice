#include <iostream>
#define REGULAR_SINGLETON
#ifdef REGULAR_SINGLETON

class Singleton
{
protected:
    Singleton() {} 
    
    //No Object Instantiation means the Destructor is never called. 
public:
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&)  = delete;   
    ~Singleton() {} 
    static Singleton& Instance()
    {
        //#define here for platform dependant operations
        #ifdef REGULAR_SINGLETON
            static Singleton* s_Instance = new Singleton();        
        #endif
        return  *s_Instance;
    }
};

class ConcreteClass : public Singleton
{
    public:
    static  Singleton& DeInit() //does nothing
    {
        static Singleton* s_Instance = nullptr; //these static variables are attatched to the funciton. 
        return *s_Instance;
    }
    static Singleton& Instance()
    {
        //#define here for platform dependant operations
        #ifdef REGULAR_SINGLETON
        static Singleton* s_Instance = new ConcreteClass(); //these static variables are attatched to the funciton. 
        #endif
        return  *s_Instance;
    }
};

int main()
{
    Singleton::Instance();
    std::cout<<"I1: "<<&Singleton::Instance()<<"\n";
    std::cout<<"I1: "<<&Singleton::Instance()<<"\n";
    std::cout<<"I2: "<<&ConcreteClass::DeInit()<<"\n";
    std::cout<<"I2: "<<&ConcreteClass::Instance()<<"\n";
    std::cout<<"I2: "<<&ConcreteClass::DeInit()<<"\n";
    std::cout<<"I2: "<<&ConcreteClass::Instance()<<"\n";

    return 0;
}
#else

class Singleton
{
private:
    static Singleton* s_Instance;
protected:
    Singleton() {} 
    
    
    //No Object Instantiation means the Destructor is never called. 
public:
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&)  = delete;   
    ~Singleton() {} 
    static Singleton& Instance()
    {
        //#define here for platform dependant operations
        
        static Singleton* s_Instance = new Singleton();        
        //#endif
        return  *s_Instance;
    }
};

class ConcreteClass : public Singleton
{
    public:
    static Singleton& Instance()
    {
        //#define here for platform dependant operations
        //#define here for platform dependant operations
        static Singleton* s_Instance = new ConcreteClass();        
        
        return  *s_Instance;
    }
};
//#define here, platform dependant defines
Singleton* Singleton::s_Instance = new ConcreteClass(); //Globally created. 
//#endif

int main()
{
    std::cout<<&ConcreteClass::Instance()<<"\n";  
    std::cout<<&ConcreteClass::Instance()<<"\n";  
    return 0;
} 
#endif