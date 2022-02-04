#ifndef THREAD_H
#define THREAD_H

#include <ros/ros.h>

#include <thread>


template <class T>
class Thread
{
public:
    ~Thread();
    
    bool start();
    bool stop();
    
    virtual T runOnce() = 0;
    bool isRunning() const { return (this->Thread_ != nullptr); };
    
protected:
    void setRunning(bool running) { this->Running_ = running; };
    bool getNext() const { return this->Running_; };
    static void run(Thread<T> *Instance);
	
private:
    std::thread *Thread_ = nullptr;
    bool Running_;
};



template<class T>
Thread<T>::~Thread()
{
	this->stop();
}


template <class T>
bool Thread<T>::start()
{
    if (this->Thread_ == nullptr)
    {
        this->setRunning(true);

        this->Thread_ = new std::thread(Thread::run, this);
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


// static
template <class T>
void Thread<T>::run(Thread<T>* Instance)
{
    if (Instance != nullptr)
    {
        while (Instance->getNext())
        {
            Instance->runOnce();
        }
    }
}

#endif // THREAD_H


