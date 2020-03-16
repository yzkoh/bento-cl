__kernel void sum(__global ulong *a, __global ulong *b, __global ulong *res, int iterations){

    int gid = get_global_id(0);

    for(int i=0;i<iterations;i++){
        res[gid] = a[gid] + b[gid];
    }
}