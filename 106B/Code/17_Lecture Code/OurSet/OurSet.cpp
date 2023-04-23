#include "OurSet.h"
using namespace std;

const int kInitialBucketCount = 6; // Or really anything, really.

/********************************************
 * private:
 *    Vector<Vector<string>> buckets;
 *    HashFunction<string> hashFn;
 *    int numElems;
 */

OurSet::OurSet() {
    /* Create buckets */
    for (int i = 0; i < kInitialBucketCount; i++) {
        buckets.add({ });
    }

    /* Pick a hash function */
    hashFn = forSize(kInitialBucketCount);

    /* Other shenanigans */
    numElems = 0;
}

void OurSet::add(const string& value) {
    /* If already present, do nothing. */
    if (contains(value)) return;

    /* Otherwise, find its bucket and put it there. */
    int bucket = hashFn(value);
    buckets[bucket] += value;
    numElems++;
}

bool OurSet::contains(const string& value) const {
    /* If it's here, it's in the bucket associated with its hash code.
     * So look there and see if we can find it.
     */
    int bucket = hashFn(value);

    for (string elem: buckets[bucket]) {
        if (elem == value) return true;
    }

    return false;
}

/* Size is tracked separately from the number of buckets. */
int OurSet::size() const {
    return numElems;
}

/* We're empty if we have size zero. */
bool OurSet::isEmpty() const {
    return size() == 0;
}
