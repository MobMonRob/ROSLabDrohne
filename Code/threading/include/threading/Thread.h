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
    
    virtual bool start();
    
    bool stop();
    
    virtual T runOnce() = 0;
    inline bool isThreaded() const { return (this->Thread_ != nullptr); };
    
protected:
    bool lock(int MaxLoop = 1000000);
    inline bool isLocked() { return this->Lock_; };
    inline void unlock() { this->Lock_ = false; };
    bool setRunning(bool running);
    inline bool isRunning() const { return this->Running_; };
    inline bool getNext() const { return (this->isRunning() && this->isThreaded()); };
    static void run(Thread<T>* Instance);
	
protected:
    std::thread *Thread_ = nullptr;

private:
    bool Running_ = false;

    bool Lock_ = false;
};


template<class T>
Thread<T>::Thread(std::string Descriptor)
{
#ifdef DEBUG
    std::cout << "New Thread \"" << Descriptor  << "\" at " << this << std::endl;
#endif
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

    return this->isThreaded();
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

    return !this->isThreaded();
}



template<class T>
inline bool Thread<T>::lock(int MaxLoop)
{
    bool ReturnBool = false;

    if (this->isLocked())
    {
        for (int i = 0; i < MaxLoop; i++)
        {
            if (!this->isLocked())
            {
                this->Lock_ = true;

                ReturnBool = true;

                break;
            }
        }
    }
    else
    {
        this->Lock_ = true;

        ReturnBool = true;
    }

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

    return this->isRunning() == running;
}


// static
template <class T>
void Thread<T>::run(Thread<T>* Instance)
{
    if (Instance != nullptr)
    {
        while (Instance->isRunning())
        {
            Instance->runOnce();
        }
    }
}

#endif // THREAD_H


