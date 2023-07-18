//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <type_traits>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <iterator>

#if defined(__GNUC__) || defined(__GNUG__)
    #define HEXEN_INLINE                                  inline __attribute__((always_inline))
#elif defined(_MSC_VER)
    #define HEXEN_INLINE                                  inline __forceinline
#else
    #define HEXEN_INLINE                                  inline
#endif

#if defined(_WIN32)
#define WINDOWS_API
#elif defined(unix) || defined(__ANDROID__) || defined(__APLE__)
#define POSIX_API
#endif

namespace core
{
    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using vptr = void*;
    using size = size_t;

    const std::string ENGINE_VERSION = std::string("0.0.0.1");

#define HEXEN_EXPAND(s) s
#define HEXEN_STR_IMPL(s) #s
#define HEXEN_STR(s) HEXEN_EXPAND(HEXEN_STR_IMPL(s))
#ifndef NDEBUG
#define HEXEN_ASSERT(expression,message)                                                         \
    if(!(expression))                                                                            \
    {                                                                                            \
        std::fputs("Assertion Failure: " HEXEN_STR(msg) ". Expr: " HEXEN_STR(expr) "\n", stderr); \
        std::fputs("Source File: " __FILE__ ":" HEXEN_STR(__LINE__) "\n", stderr);                  \
        std::abort();                                                                              \
    }                                                                                            \


#else
#define HEXEN_ASSERT(msg, expr)
#endif
#if defined(__unix__)
    const std::string PATH_SLASH("/");
#elif defined(WIN32)
    const std::string PATH_SLASH("\\");
#endif

    struct Color
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

    constexpr core::u32 polynomial = 0xEDB88320;
    constexpr core::u32 HASHING_ROUNDS  = 32;

    HEXEN_INLINE core::u32 crc32(const core::u8 *data,core::u32 lenght,core::u32 previousCRC = 0)
    {
        core::u32 crc = ~previousCRC;
        while(lenght-- != 0)
        {
            crc ^= *data++;
            for(int i = 0;i<8;i++)
            {
                crc = (crc >> 1)  ^ (-core::u32(crc & 1) & polynomial);
            }
        }
        return ~crc;
    }

    HEXEN_INLINE core::u32 hashString(const std::string &s)
    {
        core::u32 hash{0};
        for(core::i32 i{0}; i < HASHING_ROUNDS; i++)
        {
            hash = crc32((core::u8*)s.c_str(),s.size(),hash);
        }
        return hash;
    }

    template<typename Key ,typename Value,typename Hash = std::hash<Key> ,typename Equal = std::equal_to<Key>>
    class HashTable
    {
    public:
        struct KeyValue
        {
                    Key key;
                    Value value;
        };

        using keyType        = Key;
        using mappedType     = Value;
        using valueType      = KeyValue;
        using sizeType       = std::size_t;
        using differenceType = std::ptrdiff_t;
        using hasher          = Hash;
        using keyEqual       = Equal;
        using reference       = valueType&;
        using constReference = const valueType &;
        using pointer         = valueType *;
        using constPointer   = const valueType *;

        private:
        struct Slot
        {
            KeyValue keyValue;
            bool isUsed;
            Slot() noexcept : keyValue(),isUsed(false){}

            Slot(Key key,Value value) : keyValue{std::move(key),std::move(value)}, isUsed(true) {}

            Slot(const Slot &other) = default;

            Slot(Slot &&slot) noexcept: keyValue(std::move(slot.keyValue)),isUsed(slot.isUsed)
            {
                slot.isUsed = false;
            }

            friend void swap(Slot &lhs,Slot &rhs) noexcept
            {
                using std::swap;
                swap(lhs.keyValue,rhs.keyValue);
                swap(lhs.isUsed,rhs.isUsed);
            }

            Slot &operator=(Slot slot)
            {
                if(&slot == this)
                {
                            return *this;
                }

                swap(*this,slot);
                return *this;
            }

            template<class T>bool equals(T &&key) const
            {
                assert(isUsed);
                return Equal{}(keyValue.key,std::forward<T>(key));
            }
        };
        std::vector<Slot> slots;
        u32 count;
        u32 maxHashOffset;

        auto cthis() const { return this; }

        template<class T>u32 keyIndex(T &&key) const
        {
            return Hash{}(std::forward<T>(key)) & mask();
        }

        u32 mask() const noexcept
        {
            HEXEN_ASSERT(slots.size() && !(slots.size() & (slots.size() -1)) , "table size must be a power of two");
            return slots.size() - 1;
        }
        bool isShouldRehash() const
        {
            // keep load factor below 0.75
            // this ratio is chosen carefully so that it can be optimized well:
            // it is equivalent with ((size << 1) + size) >> 2.
            return slots.empty() || count >= slots.size() * 3 /4;
        }

        template<class T> const Slot *getSlot(T &&key) const
        {
            if(slots.empty())
            {
                return nullptr;
            }

            u32 i = keyIndex(std::forward<T>(key));
            u32 hashOffset = 0;

            // linear probing using a cached maximal probe sequence length.
            // This avoids the need to mark deleted slots as special and
            // fixes the performance problem whereby searching for a key after
            // having performed lots of deletions results in O(n) running time.
            // (maxHashOffset is one less than the length of the longest sequence.)
            do
            {
                if (slots[i].isUsed && slots[i].equals(std::forward<T>(key)))
                {
                    return &slots[i];
                }

                i = (i + 1) & mask();
                hashOffset++;
            } while (hashOffset <= maxHashOffset);

            return nullptr;
        }

        template<class T>Slot *getSlot(T &&key)
        {
            return const_cast<Slot*>(cthis()->getSlot(std::forward<T>(key)));
        }

        template<class T, class V> KeyValue *insertNonexistentNoRehash(T &&key , V &&value)
        {
            assert(isShouldRehash() == false);
            assert(size() < slots.size());
            assert(cthis()->getSlot(std::forward<T>(key)) == nullptr);

            u32 i = keyIndex(std::forward<T>(key));
            u32 hashOffset = 0;

            //find unused slot
            while(slots[i].isUsed)
            {
                i = (i + 1) & mask();
                hashOffset++;
            }

            //insert and mark used slot
            slots[i] = {std::forward<T>(key),std::forward<V>(value)};

            assert(slots[i].isUsed);

            count++;

            //update maximal length of probe sequences
            if(hashOffset > maxHashOffset)
            {
                maxHashOffset = hashOffset;
            }
            return &slots[i].keyValue;

        }

        void rehash()
        {
            const u32 newSize = slots.empty() ?  8 : slots.size() * 2;

            auto oldSlots = std::move(slots);


            // language lawyer: move() need not clear std::vector.
            // this->clear() takes care of that, however
            // (as well as zeroing out count and maxHashOffset.)

            clear();

            // make room for new slots (need to default-construct
            // in order for them to be in an 'unused'/free state)
            slots.resize(newSize);

            for (auto &slot : oldSlots)
            {
                if (slot.isUsed)
                {
                    insertNonexistentNoRehash(std::forward<Key>(slot.keyValue.key), std::forward<Value>(slot.keyValue.value));
                }
            }


        }
    public:
        HashTable() noexcept : slots{},count{0} , maxHashOffset{0}{}

        HashTable(u32 capacity) noexcept : HashTable()
        {
            // Make sure the real capacity is a power of two >= 8.
            // We should also keep in mind that the number of elements
            // is at most 3/4 of the number of slots!
            u32 minimalNumberSlots = (capacity * 4 + 2) / 3;
            u32 realCapacity = 8;
            while(realCapacity < minimalNumberSlots)
            {
                realCapacity *= 2;
            }
            slots.resize(realCapacity);
        }

        HashTable(const HashTable &hashTable) = default;


        HashTable(HashTable &&hashTable)noexcept: slots{ std::move(hashTable.slots)} , count {hashTable.count} , maxHashOffset { hashTable.maxHashOffset}
        {
            hashTable.clear();
        }

        HashTable(std::initializer_list<KeyValue> elements) : HashTable(elements.size())
        {
            for(auto &element : elements)
            {
                set(element.key,element.value);
            }
        }

        friend void swap(HashTable &lhs,HashTable &rhs) noexcept
        {
            using std::swap;
            swap(lhs.slots,rhs.slots);
            swap(lhs.count, rhs.count);
            swap(lhs.maxHashOffset,rhs.maxHashOffset);
        }

        HashTable &operator=(HashTable hashTable)
        {
            if(&hashTable == this)
            {
                return *this;
            }

            swap(*this,hashTable);
            return *this;
        }

        void clear() noexcept
        {
            slots.clear();
            count = 0;
            maxHashOffset = 0;
        }

        const Value *get(const Key &key) const
        {
            if(const Slot *slot = getSlot(key))
            {
                return &slot->keyValue.value;
            }

            return nullptr;
        }

        Value *get(const Key &key)
        {
            if(Slot *slot = getSlot(key))
            {
                return &slot->keyValue.value;
            }

            return nullptr;
        }

        Value *set(const Key &key, Value value)
        {
            // if the key is already in the table, just replace it and move on
            if(Value  *candidate = get(key))
            {
                *candidate = std::move(value);
                return candidate;
            }

            // else we need to insert it. First, check if we need to expand.
            if(isShouldRehash())
            {
                rehash();
            }

            //insert the key
            auto keyValue = insertNonexistentNoRehash(key,std::forward<Value>(value));
            return &keyValue->value;
        }

        Value *set(Key &&key, Value value)
        {
            // if the key is already in the table, just replace it and move on
            if(Value *candidate = get(key))
            {
                *candidate = std::move(value);
                return candidate;
            }

            // else we need to insert it. First, check if we need to expand.
            if(isShouldRehash())
            {
                rehash();
            }

            //insert the key
            auto keyValue = insertNonexistentNoRehash(std::move(key), std::move(value));
            return &keyValue->value;
        }
        void remove(const Key &key)
        {
            if(Slot *slot = getSlot(key))
            {
                *slot = {};
                assert(slot->isUsed == false);
                count--;
            }
        }

        u32 size() const noexcept
        {
            return count;
        }

        bool empty() const
        {
            return size() == 0;
        };

        double loadFactor() const
        {
            return double(size() / slots.size());
        }

        Value &operator[](const Key &key)
        {
            if(Value *value = get(key))
            {
                return  *value;
            }
            return *set(key,{});
        }
        Value& operator[](Key &&key)
        {
            if(Value *value = get(key))
            {
                return *value;
            }
            return *set(std::move(key), {});
        }

        const Value &operator[](const Key &key) const
        {
            if (const Value *value = get(key))
            {
                return *value;
            }

            std::fprintf(stderr, "hash_table::operator[] failed: key does not exist\n");
            std::fflush(stderr);
            abort();
        }

        struct ConstIterator
        {
        protected:
            friend class HashTable;

            const HashTable *owner{nullptr};
            u32 slotIndex{0};
            ConstIterator(const HashTable *owner,u32 slotIndex) : owner(owner) , slotIndex(slotIndex) {}

        public:

            using iterator_category = std::forward_iterator_tag;
            using value_type = HashTable::KeyValue;
            using difference_type = ptrdiff_t;
            using pointer = const value_type*;
            using reference = const value_type&;

            ConstIterator(const ConstIterator &hashTable) = default;

            const KeyValue *operator->() const
            {
                HEXEN_ASSERT(slotIndex < owner->slots.size() , "cannot dereference end iterator");
                return &owner->slots[slotIndex].keyValue;
            }

            const KeyValue &operator*() const
            {
                return *operator->();
            }

            ConstIterator &operator++()
            {
                HEXEN_ASSERT(slotIndex < owner->slots.size() , "cannot increment end iterator");
                do
                {
                    slotIndex++;
                } while (slotIndex < owner->slots.size() && not owner->slots[slotIndex].isUsed);

                return *this;
            }

            ConstIterator operator++(core::i32)
            {
                auto previous(*this);
                ++*this;
                return previous;
            }

            bool operator==(const ConstIterator &constIterator) const
            {
                HEXEN_ASSERT(owner == constIterator.owner , "different iterators owners!");
                return owner == constIterator.owner && slotIndex == constIterator.slotIndex;
            }

            bool operator!=(const ConstIterator &constIterator) const
            {
                return !operator==(constIterator);
            }
        };

        struct Iterator : public  ConstIterator
        {

        private:
            friend class HashTable;
            explicit Iterator(const ConstIterator &constIterator) : ConstIterator(constIterator) {}

        public:
            Iterator(const Iterator &iterator) : ConstIterator(iterator)  {}

            KeyValue &operator*() const
            {
                return *operator->();
            }

            KeyValue *operator->() const
            {
                return const_cast<KeyValue *>(static_cast<const ConstIterator *>(this)->operator->());
            }

            Iterator &operator++()
            {
                HEXEN_ASSERT(this->slotIndex < this->owner->slots.size() , "cannot increment end iterator");
                do
                {
                    this->slotIndex++;
                } while (this->slotIndex < this->owner->slots.size() && not this->owner->slots[this->slotIndex].isUsed);
                return *this;
            }

            Iterator operator++(core::i32)
            {
                auto previous(*this);
                ++*this;
                return previous;
            }

        };

        ConstIterator begin() const
        {
            auto iterator = ConstIterator(this,0);
            while (iterator.slotIndex < slots.size() && not slots[iterator.slotIndex].isUsed)
            {
                iterator.slotIndex++;
            }
            return iterator;
        }

        ConstIterator end() const
        {
            return ConstIterator(this,slots.size());
        }

        Iterator begin()
        {
            return Iterator(cthis()->begin());
        }

        Iterator end()
        {
            return Iterator(cthis()->end());
        }

        ConstIterator cbegin() const
        {
            return begin();
        }

        ConstIterator cend() const
        {
            return end();
        }
        ConstIterator findConst(const Key &key) const
        {
            if (const Slot *slot = getSlot(key))
            {
                return ConstIterator(this, slot - slots.data());
            }
            return end();
        }

        Iterator find(const Key &key)
        {
            return Iterator(cthis()->findConst(key));
        }

        void erase(const ConstIterator &it)
        {
            HEXEN_ASSERT(it.owner == this , "cannot erase an element of another instance");
            remove(it->key);
        }
    };
}

