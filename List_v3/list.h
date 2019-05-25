//#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class TList
{
protected:
public:
    class TItem
    {
    public:
        T value;
        TItem* Next;
        TItem(const T &val, TItem* _next) : value(val), Next(_next) {}
    };

    class Iterator
    {
        public:
            Iterator()
            {
                CurItem = nullptr;
            }
            Iterator(TItem* Cur) : CurItem(Cur) {}

            T operator*()
            {
                if (CurItem == nullptr)
                {
                    throw "Invalid pointer";
                }
                else
                {
                    return CurItem->value;
                }
            }
			
            Iterator operator++()
            {
                CurItem = CurItem->Next;
                return (CurItem == nullptr ? nullptr : *this);
            }

            bool operator== (const Iterator &other)
            {
                return (CurItem == other.CurItem);
            }

            bool operator!= (const Iterator &other)
            {
                return (CurItem != other.CurItem);
            }

            TItem* Current()
            {
                return CurItem;
            }

        private:
            TItem* CurItem;
    };


    Iterator begin()
    {
        return Iterator(Head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    Iterator next(Iterator &It)
    {
        if (It != nullptr)
        {
            return It.Current()->Next;
        }
        else
        {
            return It;
        }
    }

    TList()
    {
        Head = nullptr;
        Count = 0;
    }

    ~TList()
    {
        Destroy();
    }

    bool IsEmpty()
    {
        return (Size() == 0);
    }

    int Size()
    {
        return Count;
    }
	
    void EraseValue(const T &value)
    {
        Iterator It, PrevIt;
        It = begin();

        while (It != end())
        {
            if (*It == value)
            {
                if (PrevIt != nullptr)
                {
                    PrevIt.Current()->Next = It.Current()->Next;
                }
                else
                {
                    Head = It.Current()->Next;
                }

                delete It.Current();
                Count--;
            }
            else
            {
                PrevIt = It;
            }

            ++It;
        }

        if (Count == 0)
        {
            Head = nullptr;
        }
    }
	
    void ErasePos(const int pos)
    {
        int cur_pos = 0;
        Iterator It, PrevIt;
        It = begin();

        while (It != end())
        {
            if (cur_pos == pos)
            {
                if (PrevIt != nullptr)
                {
                    PrevIt.Current()->Next = It.Current()->Next;
                }
                else
                {
                    Head = It.Current()->Next;
                }

                delete It.Current();
                Count--;
                return;
            }

            PrevIt = It;
            ++It;
            cur_pos++;
        }
    }
	
    void InsertAt(const T &value, const T &value_at)
    {
        int PrevCount = Count;
        Iterator It, PrevIt;
        It = begin();

        while (It != end())
        {
            if (*It == value_at)
            {
                TItem* NewItem = new TItem(value, It.Current());

                if (PrevIt != nullptr)
                {
                    PrevIt.Current()->Next = NewItem;
                }

                if (It.Current() == Head)
                {
                    Head = NewItem;
                }

                Count++;
                break;
            }
            else
            {
                PrevIt = It;
                ++It;
            }
        }

        if (PrevCount == Count)
        {
            Head = new TItem(value, (Count == 0 ? nullptr : Head));
            Count++;
        }
    }

    void Insert(const T &value, const int pos = 0)
    {
        if (pos > (Count - 1))
        {
            Add(value);
            return;
        }

        else if (Count == 0)
        {
            Head = new TItem(value, nullptr);
            Count++;
            return;
        }

        int cur_pos = 0;
        Iterator It, PrevIt;
        It = begin();

        while (It != end())
        {
            if (cur_pos == pos)
            {
                TItem* NewItem = new TItem(value, It.Current());

                if (PrevIt != nullptr)
                {
                    PrevIt.Current()->Next = NewItem;
                }

                if (It.Current() == Head)
                {
                    Head = NewItem;
                }

                return;
            }

            PrevIt = It;
            ++It;
            cur_pos++;
        }
    }

    void Print()
    {
        Iterator It;
        It = begin();

        while (It != end())
        {
            std::cout << *It << std::endl;
            ++It;
        }
    }

    void Clear()
    {
        TItem* Item;
        Iterator It;
        It = begin();

        while (It != end())
        {
            Item = It.Current();
            delete Item;
            Count--;
            ++It;
        }

        Head = nullptr;
    }

    void Add(const T &value)
    {
        if (Count == 0)
        {
            Head = new TItem(value, nullptr);
            Count++;
        }
        else
        {
            Iterator It, PrevIt;
            It = begin();

            while (It != end())
            {
                PrevIt = It;
                ++It;
            }

            if (PrevIt != nullptr)
            {
                TItem* LastItem = PrevIt.Current();
                LastItem->Next = new TItem(value, nullptr);
                Count++;
            }
        }
    }

    bool Exist(const T &value)
    {
        Iterator It;
        It = begin();

        while (It != end())
        {
            if (*It == value)
            {
                return true;
            }

            ++It;
        }

        return false;
    }
	
private:
    void Destroy()
    {
        TItem* Item = Head;
        while (Item)
        {
            Head = Item;
            Item = Item->Next;
            delete Head;
        }
    }

    TItem* Head;
    int Count;

};

#endif // LIST_H




