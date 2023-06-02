
// c++ 2017

template <class T>
class Singleton 
{

public:

    Singleton& operator = (const Singleton&) = delete;
    Singleton& operator = (Singleton&&) = delete;

    static T& get_instance() {
        if (!instance)
            instance = new T_Instance;
        return *instance;
    }

protected:

    Singleton() {}

private:

    struct T_Instance : public T 
    {
        T_Instance() : T() {}
    };

    static inline T* instance = nullptr;
};

class A : public Singleton<A> 
{
protected:
    A() {}
};

int main()
{
    auto& x = A::get_instance();    

}