#ifndef CIRCINALQUEUE_H
#define CIRCINALQUEUE_H

template <typename T>
class CircinalQueue
{
public:
    CircinalQueue(int queueCapacity);
    virtual ~CircinalQueue();

    int GetHead(){ return m_iHead; }
    int GetLenth();

    bool EnQueue(T element);        //元素入队
    bool DeQueue(T &element);       //元素出队
    bool QueueEmpty();              //队列判空
    bool QueueFull();               //队列判满
    void ClearQueue();              //清空队列
    bool IsValidIndex(int InIndex);
    void Insert(int InIndex, T Element);

    T &IndexAt(int InIndex);
    int GetRealIndex(int InIndex);
    int GetVirtualIndex(int InIndex);

private:
    T *m_pQueue;                    //队列指针
    int m_iHead;                    //队列头
    int m_iTail;                    //队列尾
    int m_iQueueLenth;              //队列长度
    int m_iQueueCapacity;           //队列容量
};

template<typename T>
CircinalQueue<T>::CircinalQueue(int queueCapacity)
{
    m_iQueueCapacity = queueCapacity;
    m_iHead = 0;
    m_iTail = 0;
    m_iQueueLenth = 0;

    m_pQueue = new T[queueCapacity];
}

template<typename T>
CircinalQueue<T>::~CircinalQueue()
{
    delete[]m_pQueue;
    m_pQueue = nullptr;
}

template<typename T>
int CircinalQueue<T>::GetLenth()
{
    return m_iQueueLenth;
}

template<typename T>
bool CircinalQueue<T>::EnQueue(T element)
{
    if (QueueFull())
    {
        return false;
    }
    else
    {
        m_pQueue[m_iTail] = element;
        m_iTail++;
        m_iTail = m_iTail % m_iQueueCapacity;
        m_iQueueLenth++;
        qDebug()<<"m_iTail:"<<m_iTail;
        return true;
    }
}

template<typename T>
bool CircinalQueue<T>::DeQueue(T &element)
{
    if (QueueEmpty())
    {
        return false;
    }
    else
    {
        element = m_pQueue[m_iHead];
        m_iHead++;
        m_iHead = m_iHead % m_iQueueCapacity;
        m_iQueueLenth--;
        return true;
    }
}

template<typename T>
bool CircinalQueue<T>::QueueEmpty()
{
    return m_iQueueLenth == 0;
}

template<typename T>
bool CircinalQueue<T>::QueueFull()
{
    return m_iQueueLenth == m_iQueueCapacity;
}

template<typename T>
void CircinalQueue<T>::ClearQueue()
{
    m_iHead = 0;
    m_iTail = 0;
    m_iQueueLenth = 0;
}

template<typename T>
bool CircinalQueue<T>::IsValidIndex(int InIndex)
{
    return GetVirtualIndex(m_iHead) <= InIndex && InIndex <= GetVirtualIndex(m_iTail) - 1;
}

template<typename T>
void CircinalQueue<T>::Insert(int InIndex, T Element)
{
    if(QueueFull())
        return;

    if(!IsValidIndex(InIndex) && InIndex != GetVirtualIndex(m_iTail))
        return;

    m_iTail++;
    m_iTail = m_iTail % m_iQueueCapacity;
    m_iQueueLenth++;

    int TargetIndex = GetVirtualIndex(m_iTail - 1) - 1;

    while(TargetIndex >= InIndex)
    {
        m_pQueue[GetRealIndex(TargetIndex + 1)] = m_pQueue[GetRealIndex(TargetIndex)];
        TargetIndex--;
    }

    m_pQueue[GetRealIndex(TargetIndex + 1)] = Element;
}

template<typename T>
T & CircinalQueue<T>::IndexAt(int InIndex)
{
    return m_pQueue[GetRealIndex(InIndex)];
}

template<typename T>
int CircinalQueue<T>::GetRealIndex(int InIndex)
{
    return ((m_iHead + InIndex) % m_iQueueCapacity + m_iQueueCapacity) % m_iQueueCapacity;
}

template<typename T>
int CircinalQueue<T>::GetVirtualIndex(int InIndex)
{
    return (InIndex - m_iHead + m_iQueueCapacity) % m_iQueueCapacity;
}

#endif // CIRCINALQUEUE_H
