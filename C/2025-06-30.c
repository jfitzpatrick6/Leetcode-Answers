typedef struct {
    int key;
    int count;
    UT_hash_handle hh;
} Entry;

Entry* freq = NULL;

void add(int key) {
    Entry* e;
    HASH_FIND_INT(freq, &key, e);
    if (e) {
        e->count++;
    } else {
        e = malloc(sizeof(Entry));
        e->key = key;
        e->count = 1;
        HASH_ADD_INT(freq, key, e);
    }
}

Entry* find(int key) {
    Entry* e;
    HASH_FIND_INT(freq, &key, e);
    return e;
}

int findLHS(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        add(nums[i]);
    }
    int best = 0; Entry *e;
    for (e = freq; e != NULL; e = e->hh.next) {
        printf("%d\n", e->key);
        Entry* neighbor = find(e->key + 1);
        if (neighbor) {
            int sum = e->count + neighbor->count;
            if (sum > best) best = sum;
        }
    }
    Entry *tmp;
    HASH_ITER(hh, freq, e, tmp) {
        HASH_DEL(freq, e);
        free(e);
    }

    return best;
}
