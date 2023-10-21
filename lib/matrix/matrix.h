#pragma once

#include <iostream>
#include <unordered_map>
#include <array>
#include <memory>
#include "helper.h"


template<typename T, size_t SIZE = 2, T DEFAULT_VALUE = 0>
class Matrix {
public:
    using Key = std::array<size_t, SIZE>;
    
    struct MyHash {
        std::size_t operator()(const Key& key) const noexcept
        {
            return MurmurHash2((char *)key.data(), key.size() * sizeof(size_t));
        }
    };
 
    using Storage = std::unordered_map<Key, T, MyHash>;

    /**
     * @brief Модель представления данных
     * @tparam CUR_SIZE текущий уровень вложенности
     * @tparam Dummy    пустышка
     */
    template<size_t CUR_SIZE, typename Dummy = void>
    struct Model {
        Model(size_t index, Key&& key, std::shared_ptr<Storage> storage) 
            : key_(std::move(key)), storage_(storage)
        {
            key_[CUR_SIZE] = index;
        }

        Model<CUR_SIZE+1> operator[](size_t index) 
        { 
            return Model<CUR_SIZE+1>(index, std::move(key_), storage_); 
        }
    private:
        Key key_;  
        std::shared_ptr<Storage> storage_;
    };

    template<typename Dummy> 
    struct Model<SIZE-1, Dummy> {
        Model(size_t index, Key&& key, std::shared_ptr<Storage> storage) 
            : key_(std::move(key)), storage_(storage)
        {
            key_[SIZE-1] = index;
        }

        operator T() 
        { 
            if (auto search = storage_->find(key_); search != storage_->end())
                return search->second;
            return DEFAULT_VALUE;
        }

        Model<SIZE-1, Dummy>& operator =(const T& el) 
        {
            if (el != DEFAULT_VALUE) 
                (*storage_)[key_] = el;
            else if (auto search = storage_->find(key_); search != storage_->end())
                storage_->erase(search);
            return *this;
        }
    private:
        Key key_;    
        std::shared_ptr<Storage> storage_;      
    };

    /**
     * @brief Итератор
     */
    struct iterator {
        typename Storage::iterator  it_;    

        iterator& operator ++() { it_++; return *this; }
        iterator& operator --() { it_--; return *this; }
        auto operator*() { return std::tuple_cat(it_->first, std::tie(it_->second)); }
        bool operator == (const iterator& other) { return it_==other.it_; }
        bool operator != (const iterator& other) { return it_!=other.it_; }
    };

public:
    Matrix() { storage_ = std::shared_ptr<Storage>(new Storage()); }

    Model<0> operator[](int index) { return Model<0>(index, {}, storage_); };

    size_t size() { return storage_->size(); }

    iterator begin() { return iterator({storage_->begin()}); }
    iterator end() { return iterator({storage_->end()}); }

private:
    std::shared_ptr<Storage> storage_;
};