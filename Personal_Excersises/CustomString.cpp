#include <iostream>
#include <cstring>
#include <string>

class String
{
private:
    unsigned int m_Size; //Size not including '\0'
    char* m_Buffer; //String including '\0'
public:

    String()
    :m_Size(0),m_Buffer(nullptr) {}

    String(const char* _String) //Constructor
    :m_Size(strlen(_String))
    {  
       m_Buffer = new char[m_Size+1];
       for(unsigned int i =0; i<m_Size;i++)
       {
           m_Buffer[i] = _String[i];
       }
        m_Buffer[m_Size]='\0';
    }   

    void operator= ( const char* _String  ) //Assignement Operator
    {
        if( this->m_Buffer!=nullptr) delete  this->m_Buffer;
        
        this->m_Size = strlen(_String);
         this->m_Buffer = new char[m_Size+1];
        for(unsigned int i = 0;i< this->m_Size;i++)
        {
             this->m_Buffer[i] = _String[i];
        }
         this->m_Buffer[m_Size]='\0';
    }	    
    char* c_str() //C string method
    {
        return m_Buffer;
    }

    ~String() //Destructor
    {
        delete m_Buffer;
    }

    String(const String& other) //Copy Constructor
    :m_Size(other.m_Size)
    {
        m_Buffer = new char[m_Size+1];
        for(unsigned int i =0; i<m_Size+1;i++)
        {
           m_Buffer[i] = other.m_Buffer[i];
        }        
    }
    void operator= ( const String& other  ) //Assignement Operator
    {
        if( this->m_Buffer!=nullptr) delete  this->m_Buffer;
        
        m_Size = other.Size();
        m_Buffer = new char[m_Size+1];
        for(unsigned int i = 0;i< this->m_Size;i++)
        {
             this->m_Buffer[i] = other[i];
        }
         this->m_Buffer[m_Size]='\0';
    }

    char operator[](unsigned int pos) const //Array Access operator
    {
        return m_Buffer[pos];
    }
    bool operator==(const String& other) //Boolean Equals operator
    {
        return m_Buffer==other.m_Buffer;
    }
    bool operator!=(const String& other) //Boolean !Equals operator
    {
        return !(*this == other);
    }
    int Size() const //Return Size
    {
        return m_Size;
    }
    
    friend std::istream& operator >> (std::istream & input, String& o);
   
};

std::istream& operator >> (std::istream& stream, String& other)
{
    char* in = new char[20];
    stream>>in;    
    other = in;   
    return stream;
}

int main(int,const char*[]) 
{
    String first="First";
    String second;
    second = first;    
    printf("%s\n",second.c_str());
    printf("%i %i\n",first.Size(),second.Size());
    second = "yaaas";
    printf("%s -----------------------\n",first.c_str());
    printf("%s\n",second.c_str());
    printf("%i\n",second.Size());
    String input;
    std::cin>>input;
    printf("%s\n",input.c_str());
    printf("%i\n",input.Size());
    printf("---------------------------\n");
    String* ptr;
    ptr = new String(first);
    printf("%s\n",first.c_str());
    printf("%s\n",second.c_str());
    printf("%s\n",ptr->c_str());
    printf("%s\n",input.c_str());

    return 0;
}

