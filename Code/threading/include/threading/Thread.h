#ifndef THREAD_H
#define THREAD_H

#include <ros/ros.h>

#include <iostream>
#include <thread>


template <class T>
class Thread
{
public:
    Thread() {};
    Thread(std::string Descriptor);
    ~Thread();
    
    bool start();
    bool stop();
    
    virtual T runOnce() = 0;
    inline bool isRunning() const { return (this->Thread_ != nullptr); };
    
protected:
    bool lock(int MaxLoop = 1000000);
    inline void unlock() { this->Lock_ = false; };
    bool setRunning(bool running);
    inline bool getNext() const { return (this->Running_ && this->isRunning()); };
    static void run(Thread<T>* Instance);
	
private:
    std::thread *Thread_ = nullptr;
    bool Running_;

    bool Lock_ = false;
};


template<class T>
Thread<T>::Thread(std::string Descriptor)
{
    std::cout << "New Thread \"" << Descriptor  << "\" at " << this << std::endl;
}

template<class T>
Thread<T>::~Thread()
{
#ifdef DEBUG
    std::cout << "Terminating Thread " << this << "..." << std::endl;
#endif
	this->stop();

    std::cout << "Terminated Thread " << this << std::endl;
}


template <class T>
bool Thread<T>::start()
{
    if (this->Thread_ == nullptr)
    {
        this->setRunning(true);

        this->Thread_ = new std::thread(Thread::run, this);
#ifdef DEBUG
        std::cout << "Creating Thread " << this->Thread_ << std::endl;
#endif
    }

    return this->isRunning();
}

template <class T>
bool Thread<T>::stop()
{
    this->setRunning(false);
	
    if (this->Thread_ != nullptr)
    {
        if (this->Thread_->joinable())
        {
            this->Thread_->join();

            delete this->Thread_;
            this->Thread_ = nullptr;
        }
    }

    return !this->isRunning();
}



template<class T>
inline bool Thread<T>::lock(int MaxLoop)
{
    bool ReturnBool = false;

    for (int i = 0; i < MaxLoop; i++)
    {
        if (!this->Lock_)
        {
            ReturnBool = true;

            this->Lock_ = true;

            break;
        }
    }

    ReturnBool &= this->getNext();

    return ReturnBool;
}

template<class T>
inline bool Thread<T>::setRunning(bool running)
{
    if (this->lock())
    {
        this->Running_ = running;
    }
    this->unlock();

    return this->Running_ == running;
}


// static
template <class T>
void Thread<T>::run(Thread<T>* Instance)
{
    if (Instance != nullptr)
    {
        while (Instance->lock())
        {
            Instance->runOnce();
            Instance->unlock();
        }
    }
}

#endif // THREAD_H


