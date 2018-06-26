//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_SINGLETON_H
#define VM2_0_SINGLETON_H

namespace vm2{
    template <class T>
    class Singleton {
    public:
        Singleton() {
            refCount++;
        }

        virtual ~Singleton(){
            refCount--;
            if(refCount == 0){
                if(ptr)
                    delete ptr;
            }
        }

    private:
        static T* ptr;
        static int refCount;

    public:
        static T& get(){
            if(ptr == nullptr)
                ptr = new T();
            return *ptr;
        }
    };
}

template <class T>
T* vm2::Singleton<T>::ptr = nullptr;

template <class T>
int vm2::Singleton<T>::refCount = 0;

#endif //VM2_0_SINGLETON_H
