//
// Created by cx9ps3 on 09.05.2023.
//

#ifndef BATTLEBLAZE_TYPES_H
#define BATTLEBLAZE_TYPES_H

#include <cstdint>
#include <vector>
#include <functional>
#include <type_traits>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <string>

#if defined(__GNUC__) || defined(__GNUG__)
    #define HEXEN_INLINE                                  inline __attribute__((always_inline))
#elif defined(_MSC_VER)
    #define HEXEN_INLINE                                  inline __forceinline
#else
    #define HEXEN_INLINE                                  inline
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

                    template<class T>
                    bool equals(T &&key) const
                    {
                        assert(isUsed);
                        return Equal{}(keyValue.key,std::forward<T>(key));
                    }
                };

                std::vector<Slot> slots;
                u32 count;
                u32 maxHashOffset;

                auto cthis() const { return this; }

                template<class T>
                u32 keyIndex(T &&key) const
                {
                    return Hash{}(std::forward<T>(key)) & mask();
                }

                u32 mask() const noexcept
                {
                    assert(slots.size() && !(slots.size() & (slots.size() -1)) && "table size must be a power of two");
                    return slots.size() - 1;
                }

                bool isShouldRehash() const noexcept
                {
                    // keep load factor below 0.75
                    // this ratio is chosen carefully so that it can be optimized well:
                    // it is equivalent with ((size << 1) + size) >> 2.
                    return slots.empty() || count >= slots.size() * 3 /4;
                }
                template<class T>
                const Slot *getSlot(T &&key) const noexcept
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

                template<class T>
                Slot *getSlot(T &&key)
                {
                    return const_cast<Slot*>(cthis()->getSlot(std::forward<T>(key)));
                }

                template<class T, class V>
                KeyValue *insertNonexistentNoRehash(T &&key , V &&value)
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
                            insertNonexistentNoRehash(slot.keyValue.key, slot.keyValue.value);
                        }
                    }

                }

            public:
                HashTable() noexcept : slots(),count(0) , maxHashOffset(0){}

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

                const Value *get(Key &&key) const
                {
                    if(auto slot = getSlot(std::move(key)))
                    {
                        return &slot->keyValue.value;
                    }
                    return nullptr;
                }
                const Value *get(const Key &key) const
                {
                    if(auto slot = getSlot(key))
                    {
                        return &slot->keyValue.value;
                    }
                    return nullptr;
                }

                Value *get(Key &&key)
                {
                    if(auto slot = getSlot(std::move(key)))
                    {
                        return &slot->keyValue.value;
                    }
                    return nullptr;
                }

                Value *get(const Key &key)
                {
                    if(auto slot = getSlot(key))
                    {
                        return &slot->keyValue.value;
                    }
                    return nullptr;
                }


                Value *set(Key &&key,Value &&value)
                {
                    // if the key is already in the table, just replace it and move on
                    if(auto candidate = get(std::forward<Key>(key)))
                    {
                        *candidate = std::forward<Value>(value);
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

                Value *set(const Key &key,Value &&value)
                {
                    // if the key is already in the table, just replace it and move on
                    if(auto candidate = get(key))
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

                Value *set(const Key &key,const Value &value)
                {
                    // if the key is already in the table, just replace it and move on
                    if(auto candidate = get(key))
                    {
                        *candidate = value;
                        return candidate;
                    }

                    // else we need to insert it. First, check if we need to expand.
                    if(isShouldRehash())
                    {
                        rehash();
                    }

                    //insert the key
                    auto keyValue = insertNonexistentNoRehash(key,value);
                    return &keyValue->value;
                }


                void clear() noexcept
                {
                    slots.clear();
                    count = 0;
                    maxHashOffset = 0;
                }

                void remove(Key &&key)
                {
                    if(auto slot = getSlot(std::move(key)))
                    {
                        *slot = {};
                        assert(slot->isUsed == false);
                        count--;
                    }
                }
                void remove(const Key &key)
                {
                    if(auto slot = getSlot(std::forward<Key>(key)))
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

                template<class T>
                Value &operator[](T &&key)
                {
                    if(auto value = get(std::forward<T>(key)))
                    {
                        return  *value;
                    }
                    return *set(std::forward<T>(key),{});
                }
                template<class T>
                const Value& operator[](T &&key) const
                {
                    if(const auto value = get(std::forward<T>(key)))
                    {
                        return *value;
                    }
                }

                class ConstIterator
                {
                protected:
                    friend class HashTable;

                    const HashTable *owner;
                    u32 slotIndex;

                    ConstIterator(const HashTable *owner,u32 slotIndex) : owner(owner) , slotIndex(slotIndex) {}

                public:

                    ConstIterator(const ConstIterator &hashTable) = default;

                    const KeyValue *operator->() const
                    {
                        assert(slotIndex < owner->slots.size() && "cannot dereference end iterator");
                        return &owner->slots[slotIndex].keyValue;
                    }

                    const KeyValue &operator*() const
                    {
                        return *operator->();
                    }

                    ConstIterator &operator++()
                    {
                        assert(slotIndex < owner->slots.size() && "cannot increment end iterator");
                        do
                        {

                        } while (slotIndex < owner->slots.size() && !owner->slots[slotIndex].isUsed);
                        return *this;
                    }

                    ConstIterator operator++(int)
                    {
                        auto previous(*this);
                        ++*this;
                        return previous;
                    }

                    bool operator==(const ConstIterator &constIterator) const
                    {
                        return owner == constIterator.owner && slotIndex == constIterator.slotIndex;
                    }

                    bool operator!=(const ConstIterator &constIterator) const
                    {
                        return !operator==(constIterator);
                    }
                };

                class Iterator : public  ConstIterator
                {
                private:
                    friend class HashTable;

                    Iterator(const ConstIterator &constIterator) : ConstIterator(constIterator) {}

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
                        assert(this->slotIndex < this->owner->slots.size() && "cannot increment end iterator");
                        do
                        {
                            this->slotIndex++;
                        } while (this->slotIndex < this->owner->slots.size() && !this->owner->slots[this->slotIndex].isUsed);
                        return *this;
                    }

                    Iterator operator++(int)
                    {
                        auto previous(*this);
                        ++*this;
                        return previous;
                    }

                };

                ConstIterator begin() const
                {
                    auto iterator = ConstIterator(this,0);
                    while (iterator.slotIndex < slots.size() && !slots[iterator.slotIndex].isUsed)
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

            };

}

#endif //BATTLEBLAZE_TYPES_H
