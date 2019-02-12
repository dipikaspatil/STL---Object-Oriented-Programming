#ifndef WORKSPACE_DEQUE_DP_H
#define WORKSPACE_DEQUE_DP_H

#include <cstring>
#include <algorithm>

#define Deque_Custom(x)                                                                                             \
using namespace std;                                                                                                \
struct Deque_##x##_Iterator {                                                                                       \
    x *id;                                                                                                          \
    int current_ind;                                                                                                \
    int front_ind;                                                                                                  \
    int back_ind;                                                                                                   \
    size_t deque_size;                                                                                              \
    size_t deque_cnt;                                                                                               \
    void (*inc)(Deque_##x##_Iterator *);                                                                            \
    x &(*deref)(Deque_##x##_Iterator *);                                                                            \
    void (*dec)(Deque_##x##_Iterator *);                                                                            \
};                                                                                                                  \
                                                                                                                    \
struct Deque_##x {                                                                                                  \
    char type_name[sizeof("Deque_" #x)];                                                                            \
    x *id;                                                                                                          \
    int front_ind;                                                                                                  \
    int back_ind;                                                                                                   \
    size_t deque_size;                                                                                              \
    size_t deque_cnt;                                                                                               \
    size_t (*size)(Deque_##x *);                                                                                    \
    bool (*empty)(Deque_##x *);                                                                                     \
    void (*push_back)(Deque_##x *, x);                                                                              \
    void (*push_front)(Deque_##x *, x);                                                                             \
    void (*pop_back)(Deque_##x *);                                                                                  \
    void (*pop_front)(Deque_##x *);                                                                                 \
    x &(*front)(Deque_##x *);                                                                                       \
    x &(*back)(Deque_##x *);                                                                                        \
    Deque_##x##_Iterator (*begin)(Deque_##x *);                                                                     \
    Deque_##x##_Iterator (*end)(Deque_##x *);                                                                       \
    void (*clear)(Deque_##x *);                                                                                     \
    void (*dtor)(Deque_##x *);                                                                                      \
    void (*sort)(Deque_##x *, Deque_##x##_Iterator, Deque_##x##_Iterator);                                          \
    x &(*at)(Deque_##x *, size_t);                                                                                  \
    bool (*pf)(const x &, const x &);                                                                               \
};                                                                                                                  \
                                                                                                                    \
void increase_deque_space(Deque_##x *deque_obj) {                                                                   \
                                                                                                                    \
    x *local_deque_id = new x[deque_obj->deque_size * 2];                                                           \
    int old_deque_size = deque_obj->deque_size;                                                                     \
    int old_front_index = deque_obj->front_ind;                                                                     \
    int old_back_index = deque_obj->back_ind;                                                                       \
    int new_deque_index = old_front_index;                                                                          \
    bool check_indx = false;                                                                                        \
                                                                                                                    \
    while (old_front_index != old_back_index) {                                                                     \
        local_deque_id[new_deque_index] = deque_obj->id[old_front_index];                                           \
        old_front_index -= 1;                                                                                       \
        if (old_front_index < 0) {                                                                                  \
            old_front_index = old_deque_size + old_front_index;                                                     \
            check_indx = true;                                                                                      \
        }                                                                                                           \
        new_deque_index = old_front_index;                                                                          \
        if (check_indx) {                                                                                           \
            new_deque_index = old_front_index + old_deque_size;                                                     \
        }                                                                                                           \
    }                                                                                                               \
                                                                                                                    \
    local_deque_id[new_deque_index] = deque_obj->id[deque_obj->back_ind];                                           \
    delete[] deque_obj->id;                                                                                         \
    deque_obj->id = NULL;                                                                                           \
    deque_obj->id = local_deque_id;                                                                                 \
    deque_obj->back_ind = new_deque_index;                                                                          \
    deque_obj->deque_size = old_deque_size * 2;                                                                     \
}                                                                                                                   \
                                                                                                                    \
void fn_inc(Deque_##x##_Iterator *deque_itr) {                                                                      \
    int deque_index = deque_itr->current_ind - 1;                                                                   \
    if (deque_index < 0) {                                                                                          \
        deque_index = deque_itr->deque_size - deque_itr->current_ind - 1;                                           \
    }                                                                                                               \
    deque_itr->current_ind = deque_index;                                                                           \
}                                                                                                                   \
                                                                                                                    \
x &fn_deref(Deque_##x##_Iterator *deque_itr) {                                                                      \
    return deque_itr->id[deque_itr->current_ind];                                                                   \
}                                                                                                                   \
                                                                                                                    \
void fn_dec(Deque_##x##_Iterator *deque_itr) {                                                                      \
    size_t deque_index = deque_itr->current_ind + 1;                                                                \
    if (deque_index == deque_itr->deque_size) {                                                                     \
        deque_index = deque_itr->deque_size - deque_itr->current_ind - 1;                                           \
    }                                                                                                               \
                                                                                                                    \
    deque_itr->current_ind = deque_index;                                                                           \
}                                                                                                                   \
                                                                                                                    \
size_t fn_size(Deque_##x *deque_obj) {                                                                              \
    return deque_obj->deque_cnt;                                                                                    \
}                                                                                                                   \
                                                                                                                    \
bool fn_empty(Deque_##x *deque_obj) {                                                                               \
    int size = fn_size(deque_obj);                                                                                  \
    if (size == 0)                                                                                                  \
        return true;                                                                                                \
    return false;                                                                                                   \
}                                                                                                                   \
                                                                                                                    \
void fn_push_back(Deque_##x *deque_obj, x num) {                                                                    \
    int deque_index;                                                                                                \
    if (fn_empty(deque_obj)) {                                                                                      \
                                                                                                                    \
        deque_index = deque_obj->back_ind;                                                                          \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
                                                                                                                    \
    } else if (deque_obj->deque_cnt + 1 != deque_obj->deque_size) {                                                 \
                                                                                                                    \
        deque_index = deque_obj->back_ind - 1;                                                                      \
        /*when back_ind is on 0 need to move to end of queue*/                                                      \
        /* when back_ind = 0 and deque_size = 10 and dqueue is not full*/                                           \
        if (deque_index < 0) {                                                                                      \
            deque_index = deque_obj->deque_size - deque_obj->back_ind - 1;                                          \
        }                                                                                                           \
                                                                                                                    \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
        deque_obj->back_ind = deque_index;                                                                          \
                                                                                                                    \
    } else {                                                                                                        \
        /*allocate more space*/                                                                                     \
        increase_deque_space(deque_obj);                                                                            \
        deque_index = deque_obj->back_ind - 1;                                                                      \
        if (deque_index < 0) {                                                                                      \
            deque_index = deque_obj->deque_size - deque_obj->back_ind - 1;                                          \
        }                                                                                                           \
                                                                                                                    \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
        deque_obj->back_ind = deque_index;                                                                          \
    }                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
void fn_push_front(Deque_##x *deque_obj, x num) {                                                                   \
    size_t deque_index;                                                                                             \
    if (fn_empty(deque_obj)) {                                                                                      \
        /*adding first element*/                                                                                    \
        deque_index = deque_obj->front_ind;                                                                         \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
                                                                                                                    \
    } else if (deque_obj->deque_cnt + 1 != deque_obj->deque_size) {                                                 \
        /*deque has capacity i.e. it will not full after addition of element*/                                      \
        /*deque_index = (deque_obj->front_ind+1)%deque_obj->deque_size;*/                                           \
        deque_index = deque_obj->front_ind + 1;                                                                     \
        /*when front_ind = 9 and deque_size = 10 and dqueue is not full*/                                           \
        if (deque_index == deque_obj->deque_size) {                                                                 \
            deque_index = deque_obj->deque_size - deque_obj->front_ind - 1;                                         \
        }                                                                                                           \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
        deque_obj->front_ind = deque_index;                                                                         \
                                                                                                                    \
    } else {                                                                                                        \
        /*allocate more space*/                                                                                     \
        increase_deque_space(deque_obj);                                                                            \
        deque_index = deque_obj->front_ind + 1;                                                                     \
        /*when front_ind = 9 and deque_size = 10 and dqueue is not full*/                                           \
        if (deque_index == deque_obj->deque_size) {                                                                 \
            deque_index = deque_obj->deque_size - deque_obj->front_ind - 1;                                         \
        }                                                                                                           \
        deque_obj->id[deque_index] = num;                                                                           \
        deque_obj->deque_cnt++;                                                                                     \
        deque_obj->front_ind = deque_index;                                                                         \
    }                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
void fn_pop_back(Deque_##x *deque_obj) {                                                                            \
    if (fn_empty(deque_obj)) {                                                                                      \
        /*no action - as queue is empty*/                                                                           \
    } else {                                                                                                        \
        size_t deque_index = deque_obj->back_ind + 1;                                                               \
        /*when back_ind = 9 and deque_size = 10*/                                                                   \
        if (deque_index == deque_obj->deque_size) {                                                                 \
            deque_index = deque_obj->deque_size - deque_obj->back_ind - 1;                                          \
        }                                                                                                           \
        deque_obj->back_ind = deque_index;                                                                          \
        deque_obj->deque_cnt--;                                                                                     \
    }                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
void fn_pop_front(Deque_##x *deque_obj) {                                                                           \
    if (fn_empty(deque_obj)) {                                                                                      \
        /*no action - as queue is empty*/                                                                           \
    } else {                                                                                                        \
        int deque_index = deque_obj->front_ind - 1;                                                                 \
        /*when back_ind = 0 and deque_size = 10*/                                                                   \
        if (deque_index < 0) {                                                                                      \
            deque_index = deque_obj->deque_size - deque_obj->front_ind - 1;                                         \
        }                                                                                                           \
        deque_obj->front_ind = deque_index;                                                                         \
        deque_obj->deque_cnt--;                                                                                     \
    }                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
x &fn_front(Deque_##x *deque_obj) {                                                                                 \
    return deque_obj->id[deque_obj->front_ind];                                                                     \
}                                                                                                                   \
                                                                                                                    \
x &fn_back(Deque_##x *deque_obj) {                                                                                  \
    return deque_obj->id[deque_obj->back_ind];                                                                      \
}                                                                                                                   \
                                                                                                                    \
Deque_##x##_Iterator fn_begin(Deque_##x *deque_obj) {                                                               \
    Deque_##x##_Iterator local_itr_obj;                                                                             \
    local_itr_obj.dec = fn_dec;                                                                                     \
    local_itr_obj.deref = fn_deref;                                                                                 \
    local_itr_obj.inc = fn_inc;                                                                                     \
    local_itr_obj.front_ind = deque_obj->front_ind;                                                                 \
    local_itr_obj.back_ind = deque_obj->back_ind;                                                                   \
    local_itr_obj.deque_cnt = deque_obj->deque_cnt;                                                                 \
    local_itr_obj.deque_size = deque_obj->deque_size;                                                               \
    local_itr_obj.id = deque_obj->id;                                                                               \
    local_itr_obj.current_ind = deque_obj->front_ind;                                                               \
    return local_itr_obj;                                                                                           \
}                                                                                                                   \
                                                                                                                    \
Deque_##x##_Iterator fn_end(Deque_##x *deq_obj) {                                                                   \
    Deque_##x##_Iterator local_itr_obj;                                                                             \
    local_itr_obj.dec = fn_dec;                                                                                     \
    local_itr_obj.deref = fn_deref;                                                                                 \
    local_itr_obj.inc = fn_inc;                                                                                     \
    local_itr_obj.front_ind = deq_obj->front_ind;                                                                   \
    local_itr_obj.back_ind = deq_obj->back_ind;                                                                     \
    local_itr_obj.deque_cnt = deq_obj->deque_cnt;                                                                   \
    local_itr_obj.deque_size = deq_obj->deque_size;                                                                 \
    local_itr_obj.id = deq_obj->id;                                                                                 \
                                                                                                                    \
    int deq_indx = deq_obj->back_ind - 1;                                                                           \
    if (deq_indx < 0) {                                                                                             \
        deq_indx = deq_obj->deque_size - deq_obj->back_ind - 1;                                                     \
    }                                                                                                               \
    local_itr_obj.current_ind = deq_indx;                                                                           \
    return local_itr_obj;                                                                                           \
}                                                                                                                   \
                                                                                                                    \
void fn_clear(Deque_##x *deq_obj) {                                                                                 \
    deq_obj->deque_size = 0;                                                                                        \
    deq_obj->front_ind = 0;                                                                                         \
    deq_obj->back_ind = 0;                                                                                          \
    deq_obj->deque_cnt = 0;                                                                                         \
    strcpy(deq_obj->type_name, "");                                                                                 \
}                                                                                                                   \
                                                                                                                    \
void fn_dtor(Deque_##x *deq_obj) {                                                                                  \
    delete[](deq_obj->id);                                                                                          \
    deq_obj->id = NULL;                                                                                             \
}                                                                                                                   \
                                                                                                                    \
void fn_sort(Deque_##x *, Deque_##x##_Iterator, Deque_##x##_Iterator);                                              \
                                                                                                                    \
x &fn_at(Deque_##x *deque_itr, size_t num) {                                                                        \
    int deque_index = deque_itr->front_ind - num;                                                                   \
    if (deque_index < 0) {                                                                                          \
        deque_index = deque_itr->deque_size + (deque_itr->front_ind - num);                                         \
    }                                                                                                               \
    return deque_itr->id[deque_index];                                                                              \
}                                                                                                                   \
                                                                                                                    \
void Deque_##x##_ctor(Deque_##x *deq_obj, bool (*pf)(const x &, const x &)) {                                       \
    deq_obj->front_ind = 0;                                                                                         \
    deq_obj->back_ind = 0;                                                                                          \
    deq_obj->deque_size = 10;                                                                                       \
    deq_obj->deque_cnt = 0;                                                                                         \
    deq_obj->id = new x[deq_obj->deque_size];                                                                       \
    strcpy(deq_obj->type_name, "Deque_" #x);                                                                        \
    deq_obj->size = fn_size;                                                                                        \
    deq_obj->empty = fn_empty;                                                                                      \
    deq_obj->push_back = fn_push_back;                                                                              \
    deq_obj->push_front = fn_push_front;                                                                            \
    deq_obj->pop_back = fn_pop_back;                                                                                \
    deq_obj->pop_front = fn_pop_front;                                                                              \
    deq_obj->front = fn_front;                                                                                      \
    deq_obj->back = fn_back;                                                                                        \
    deq_obj->begin = fn_begin;                                                                                      \
    deq_obj->end = fn_end;                                                                                          \
    deq_obj->clear = fn_clear;                                                                                      \
    deq_obj->dtor = fn_dtor;                                                                                        \
    deq_obj->sort = fn_sort;                                                                                        \
    deq_obj->at = fn_at;                                                                                            \
    deq_obj->pf = pf;                                                                                               \
}                                                                                                                   \
                                                                                                                    \
bool Deque_##x##_equal(Deque_##x deq1, Deque_##x deq2) {                                                            \
    if (deq1.deque_cnt != deq2.deque_cnt) {                                                                         \
        return false;                                                                                               \
    }                                                                                                               \
    size_t counter = 0;                                                                                             \
    while (counter < deq1.deque_cnt) {                                                                              \
        x deq1_item = deq1.at(&deq1, counter);                                                                      \
        x deq2_item = deq2.at(&deq2, counter);                                                                      \
        if (deq1.pf(deq1_item, deq2_item) || deq2.pf(deq2_item, deq1_item)) {                                       \
            return false;                                                                                           \
        }                                                                                                           \
        counter++;                                                                                                  \
    }                                                                                                               \
                                                                                                                    \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
bool Deque_##x##_Iterator_equal(Deque_##x##_Iterator deque_itr1, Deque_##x##_Iterator deque_itr2) {                 \
    /*considering the case that back index is end which is one greater than back index*/                            \
    if (deque_itr1.current_ind == deque_itr2.current_ind) {                                                         \
        return true;                                                                                                \
    }                                                                                                               \
    return false;                                                                                                   \
}                                                                                                                   \
                                                                                                                    \
void fn_sort(Deque_##x *deq_obj, Deque_##x##_Iterator deq_begin, Deque_##x##_Iterator deq_end) {                    \
                                                                                                                    \
    int local_array_cnt = 0, begin = deq_begin.current_ind, end = deq_end.current_ind;                              \
                                                                                                                    \
    while (begin != end) {                                                                                          \
        local_array_cnt++;                                                                                          \
        begin--;                                                                                                    \
        if (begin < 0) {                                                                                            \
            begin = deq_begin.deque_size + begin;                                                                   \
        }                                                                                                           \
    }                                                                                                               \
                                                                                                                    \
    x *local_array = new x[local_array_cnt];                                                                        \
    int counter = 0;                                                                                                \
    Deque_##x##_Iterator it = deq_begin;                                                                            \
                                                                                                                    \
    for (; !Deque_##x##_Iterator_equal(it, deq_end); it.inc(&it)) {                                                 \
        local_array[counter] = it.deref(&it);                                                                       \
        counter++;                                                                                                  \
    }                                                                                                               \
                                                                                                                    \
    std::sort(local_array, local_array + local_array_cnt, deq_obj->pf);                                             \
                                                                                                                    \
    int deq_indx = deq_begin.current_ind;                                                                           \
                                                                                                                    \
    for (int i = 0; i < local_array_cnt; i++) {                                                                     \
        if (deq_indx < 0) {                                                                                         \
            deq_indx = deq_begin.deque_size + deq_indx;                                                             \
        }                                                                                                           \
        deq_obj->id[deq_indx] = local_array[i];                                                                     \
        deq_indx--;                                                                                                 \
    }                                                                                                               \
                                                                                                                    \
    delete [] local_array;                                                                                          \
}

#endif