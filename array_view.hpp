#pragma once 

#include <cstdint>

template<typename t>
struct array_view 
{
private:
    t* _data = nullptr;
    std::size_t _count{};
public:
    using data_type = t;
    
    struct iterator 
    {
    private:
        t* array;
        std::size_t position{};
        friend struct array_view;
    public:
        iterator(const array_view<t>& v) noexcept : array { v._data }
        {};

        iterator operator++() noexcept
        {
            iterator it_cpy { *this };
            ++position;

            return it_cpy;
        } 

        iterator operator--() noexcept
        {
            iterator it_cpy { *this };
            --position;

            return it_cpy;
        } 

        iterator& operator++(int) noexcept
        {
            ++position;
            return *this;
        } 

        iterator& operator--(int) noexcept
        {
            --position;
            return *this;
        } 

        [[nodiscard]] t* operator->() const noexcept
        {
            return &array[position];
        }

        [[nodiscard]] t& operator*() noexcept
        {
            return array[position];
        }

        [[nodiscard]] const t& operator*() const noexcept
        {
            return array[position];
        }

        [[nodiscard]] bool operator<(const iterator& it)
        {
            return position < it.position;
        }

        [[nodiscard]] bool operator>(const iterator& it)
        {
            return position > it.position;
        }
        
        [[nodiscard]] bool operator>=(const iterator& it)
        {
            return !(*this < it);
        }

        [[nodiscard]] bool operator<=(const iterator& it)
        {
            return !(*this > it);
        }

        [[nodiscard]] bool operator==(const iterator& it) const noexcept
        {
            return position == it.position && array == it.array;
        }

        [[nodiscard]] bool operator!=(const iterator& it) const noexcept
        {
            return !operator==(it);
        }

        
    };

    array_view(t* data, std::size_t count) noexcept : _data { data }, _count { count }
    {};

    [[nodiscard]] std::size_t size() const noexcept
    {
        return _count;
    }

    [[nodiscard]] iterator begin() 
    {
        return iterator { *this };
    }

    [[nodiscard]] iterator end() 
    {
        iterator it { *this };
        it.position = size();
        return it;
    }

    [[nodiscard]] t& back()
    {
        return *(--end());
    }

    [[nodiscard]] t& front()
    {
        return *begin();
    }

    [[nodiscard]] auto* data()
    {
        return _data;
    }

    [[nodiscard]] t& operator[](std::size_t idx) noexcept
    {
        return _data[idx];
    }

};
