#include <iostream>
#include <cassert>
struct Vector3
{
    int x,y,z;
    Vector3(int _x,int _y,int _z)
    :x(_x), y(_y), z(_z)
    {
    }
};
class GameActor
{
private:
    Vector3 v;
public:
    GameActor()
    :v(Vector3(0,0,0))
    {}
    void moveX(const int& i)
    {
        v.x+=i;
    }
    void moveY(const int& i)
    {
        v.y+=i;
    }
    void moveZ(const int& i)
    {
        v.z+=i;
    }
    void printPos() const
    {
        std::cout<<"x: "<<v.x<<" y: "<<v.y<<" z: "<<v.z<<"\n";
    }

};
class Command
{
public:
    virtual ~Command() {}
    virtual void Execute(GameActor& actor) = 0;

};

class JumpCommand : public Command
{
     const int m_moveAmmount;
public:
    JumpCommand(const int& _i)
    : m_moveAmmount(_i)
    {        
    }
    virtual void Execute(GameActor& actor) override
    {
        actor.moveY(m_moveAmmount);
    }
};
class MoveX : public Command
{
     const int m_moveAmmount;
public:
    MoveX(const int& _i)
    : m_moveAmmount(_i)
    {        
    }
    virtual void Execute(GameActor& actor) override 
    {
        actor.moveX(m_moveAmmount);       
    }
};

class MoveY : public Command
{
    const int m_moveAmmount;
public:
    MoveY(const int& _i)
    : m_moveAmmount(_i)
    {        
    }
    virtual void Execute(GameActor& actor) override 
    {        
        actor.moveZ(m_moveAmmount);        
    }
};

class InputHandler
{
private:
    static bool s_Instantiated;

    struct BooleanInputs
{
    bool w,a,s,d,space;
    BooleanInputs() : w(true)
    {}
};
public: 
    InputHandler()
    :inputObj(BooleanInputs()) 
    {
        assert(!s_Instantiated); //Asserts if more than one instance is present
        s_Instantiated = true;
    }
    Command* HandleInput()
    {
        if(inputObj.w == true)
        {
            std::cout<<"W\n";
            inputObj.w = false;
            inputObj.a = true; //checks
            return button_W;
        }             
        if(inputObj.a == true)
        {
            std::cout<<"A\n";

            inputObj.a = false;
            inputObj.s = true; //checks

            return button_A;
        }
        if(inputObj.s == true)
        {
            std::cout<<"S\n";
            inputObj.s = false;
            inputObj.d = true; //checks
            return button_S;
        }
        if(inputObj.d == true)
        {
            std::cout<<"D\n";
            inputObj.d = false;
            inputObj.space = true; //checks
            return button_D;
        }
        if(inputObj.space == true)
        {
            std::cout<<"SPACE\n";
            inputObj.space = false;
            inputObj.w = true; //checks
            return button_SPACE;
        }

        return nullptr;
    }    
    template <class T>
    void BindW(T* commnadObj) 
    {
        button_W = commnadObj;
    }
    template <class T>
    void BindA(T* commnadObj) 
    {
        button_A = commnadObj;
    }
    template <class T>
    void BindS(T* commnadObj) 
    {
        button_S = commnadObj;
    }
    template <class T>
    void BindD(T* commnadObj) 
    {
        button_D = commnadObj;
    }
    template <class T>
    void BindSPACE(T* commnadObj) 
    {
        button_SPACE = commnadObj;
    } 
   
private: 
    BooleanInputs inputObj;
    Command* button_W;
    Command* button_A;
    Command* button_S;
    Command* button_D;
    Command* button_SPACE;



};
bool InputHandler::s_Instantiated = false;

int main()
{
    std::cout<<"Using Left-Hand Rule for 3D space!\nPress Enter to obeserve coordinate changes to keyboard inputs.\n";
    InputHandler handler = InputHandler();    
    handler.BindW(new  MoveY(10));
    handler.BindA(new MoveX(-10));
    handler.BindS(new MoveY(-10));
    handler.BindD(new MoveX(10));
    handler.BindSPACE(new JumpCommand(10));
    GameActor actor = GameActor();

    while(true)
    {
        Command* command = handler.HandleInput();
        if(command!=nullptr)
        {
            command->Execute(actor);
            std::cin.get();
        }         
        actor.printPos();        
    }
    return 0;
}