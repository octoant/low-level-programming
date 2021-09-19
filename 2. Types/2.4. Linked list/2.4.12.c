struct maybe_int64 maybe_read_int64() {
    int64_t tmp;
    if (scanf("%" SCNd64, &tmp) == 1) {
        return some_int64(tmp);
    }
    else return none_int64;
}