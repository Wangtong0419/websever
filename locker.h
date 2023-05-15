#ifndef LOCKER_H
#define LOCKER_H
//线程同步类
#include"pthread.h"
#include<exception>
#include<semaphore.h>

//互斥锁类
class mutex
{
private:
    pthread_mutex_t *m_mutex;
public:
    mutex();
    ~mutex();
    bool lock();
    bool unlock();
    pthread_mutex_t getlocker();
};

mutex::mutex()
{
    if(pthread_mutex_init(m_mutex,NULL)!=0)
        throw std::exception();
}

mutex::~mutex()
{
    pthread_mutex_destroy(m_mutex);
}

bool mutex::lock()
{
    return pthread_mutex_lock(m_mutex)==0;
}

bool mutex::unlock()
{
    return pthread_mutex_unlock(m_mutex)==0;
}

pthread_mutex_t mutex::getlocker()
{
    return *m_mutex;
}

//条件变量类
class cond
{
private:
    pthread_cond_t *m_cond;
public:
    cond();
    ~cond();
    bool wait(pthread_mutex_t *mutex);
    bool timewait(pthread_mutex_t *mutex,timespec *t);
    bool signal();
    bool broadcast();
    pthread_cond_t getcond();
};

cond::cond()
{
    if (pthread_cond_init(m_cond,NULL)!=0)
    {
        throw std::exception();
    }
    
}

cond::~cond()
{
    pthread_cond_destroy(m_cond);
}

bool cond::wait(pthread_mutex_t *mutex)
{
    return pthread_cond_wait(m_cond,mutex)==0;
}
bool cond::timewait(pthread_mutex_t *mutex,timespec *t)
{
    return pthread_cond_timedwait(m_cond,mutex,t)==0;
}
bool cond::signal()
{
    return pthread_cond_signal(m_cond)==0;
}
bool cond::broadcast()
{
    return pthread_cond_broadcast(m_cond)==0;
}
pthread_cond_t cond::getcond()
{
    return *m_cond;
}

//信号量类
class sem
{
private:
    sem_t *m_sem;
public:
    sem();
    ~sem();
    bool wait();
    bool post();
};

sem::sem()
{
    if(sem_init(m_sem,0,0)!=0)
    {
        throw std::exception();
    }
}

sem::~sem()
{
    sem_destroy(m_sem);
}
bool sem::wait()
{
    return sem_wait(m_sem)==0;
}
bool sem::post()
{
    return sem_post(m_sem)==0;
}




#endif