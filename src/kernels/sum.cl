__kernel void sum(__global ulong *a, __global ulong *b, __global ulong *res){

    int gid = get_global_id(0);
    // printf("%d", a[gid]);

    for(int i=0;i<50;i++){
        res[gid] = a[gid] + b[gid];
    }
}