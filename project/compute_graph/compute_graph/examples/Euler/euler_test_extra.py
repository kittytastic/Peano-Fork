from typing import Callable, List
from math import nan

patch_update_in_1 = [4.67263473170548023e-310, 6.93814240153539777e-310, 0.00000000000000000e+00, 6.93814240153539777e-310, 1.01000000000000006e-01, 3.53352604387589158e-03, 0.00000000000000000e+00, 7.60655156520209045e-03, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, -nan, 2.22329540628560945e-322, -nan, 6.95252218511725810e-310, 1.01000000000000006e-01, 3.67864739561240967e-02, 0.00000000000000000e+00, 2.17046295797094585e-01, 1.01000000000000006e-01, 3.53352604387589158e-03, 0.00000000000000000e+00, 7.60655156520209045e-03, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.01000000000000006e-01, 3.67864739561240967e-02, 0.00000000000000000e+00, 2.17046295797094585e-01, 1.01000000000000006e-01, 3.53352604387589158e-03, 0.00000000000000000e+00, 7.60655156520209045e-03, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.01000000000000006e-01, 3.67864739561240967e-02, 0.00000000000000000e+00, 2.17046295797094585e-01, 1.01000000000000006e-01, 3.53352604387589158e-03, 0.00000000000000000e+00, 7.60655156520209045e-03, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 4.67244976444855371e-310, 4.67244894550678161e-310, 6.95252218513069668e-310, 6.95252218513148719e-310, 1.01000000000000006e-01, 3.53352604387589158e-03, 0.00000000000000000e+00, 7.60655156520209045e-03, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 6.36598737289581695e-314, 4.24399158291867592e-314, 9.88131291682493088e-324, 4.67244894487833011e-310]

patch_update_out_1 = [1.02827347963613425e-01, 1.07692148847298441e-02, 0.00000000000000000e+00, 2.81236792133374575e-02, 1.00188652036386591e-01, 1.99392473752075985e-04, 0.00000000000000000e+00, 1.09679070897408364e-04, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.02827347963613425e-01, 1.07692148847298441e-02, 0.00000000000000000e+00, 2.81236792133374575e-02, 1.00188652036386591e-01, 1.99392473752075985e-04, 0.00000000000000000e+00, 1.09679070897408364e-04, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00, 1.02827347963613425e-01, 1.07692148847298441e-02, 0.00000000000000000e+00, 2.81236792133374575e-02, 1.00188652036386591e-01, 1.99392473752075985e-04, 0.00000000000000000e+00, 1.09679070897408364e-04, 1.00000000000000006e-01, 0.00000000000000000e+00, 0.00000000000000000e+00, 0.00000000000000000e+00]

patch_update_extra_1 = {
    "pos0": 5.12345679012345734e-01,
    "pos1": 2.53086419753086433e-01,
    "size0": 1.23456790123456783e-02,
    "size1": 1.23456790123456783e-02,
    "t": 8.23045267489711809e-04,
    "dt": 4.11522633744855904e-04,
}

def voxelInPreimage(x: int, y:int, patch_len: int): return x+1 + (y+1) * (2+patch_len)
def voxelInImage(x: int, y:int, patch_len: int): return x + y * patch_len

def analytical_patch_update(Qin:List[float], patch_len: int, dim: int, unknowns: int, rusanov_x:Callable[[List[float]], List[float]], rusanov_y:Callable[[List[float]], List[float]])->List[float]:
    num_in_states:int = (patch_len+2)**dim * unknowns
    num_out_states:int = (patch_len)**dim * unknowns

    t = Qin[num_in_states] # type: ignore
    dt = Qin[num_in_states + 1]
    pos0 = Qin[num_in_states + 2] #type: ignore
    pos1 = Qin[num_in_states + 3] #type: ignore
    size0 = Qin[num_in_states + 4]
    size1 = Qin[num_in_states + 5] # type: ignore

    
    Q_out_pos_contrib:List[List[float]] = [[] for _ in range(num_out_states)]
    Q_out_neg_contrib:List[List[float]] = [[] for _ in range(num_out_states)]
    Qout:List[float] = [0]*num_out_states


    
    vol_h = size0/patch_len
    dt_div_size = dt/vol_h
    
    # Flux x
    for x in range(patch_len+1):
        for y in range(patch_len):
            leftVoxelInPreImage = voxelInPreimage(x-1, y, patch_len)
            rightVoxelInPreImage = voxelInPreimage(x, y, patch_len)

            leftVoxelInImage = voxelInImage(x-1, y, patch_len)
            rightVoxelInImage = voxelInImage(x, y, patch_len)


            # Rusanov
            rusanov_input = Qin[leftVoxelInPreImage*unknowns:(leftVoxelInPreImage+1)*unknowns]+Qin[rightVoxelInPreImage*unknowns:(rightVoxelInPreImage+1)*unknowns]
            rus = rusanov_x(rusanov_input)
            

            # Update out
            for u in range(unknowns):
                if x>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(rus[u])

                if x<patch_len:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(rus[u])


    
    # Flux y
    for x in range(patch_len):
        for y in range(patch_len+1):
            leftVoxelInPreImage = voxelInPreimage(x, y-1, patch_len)
            rightVoxelInPreImage = voxelInPreimage(x, y, patch_len)

            leftVoxelInImage = voxelInImage(x, y-1, patch_len)
            rightVoxelInImage = voxelInImage(x, y, patch_len)


            # Rusanov
            rusanov_input = Qin[leftVoxelInPreImage*unknowns:(leftVoxelInPreImage+1)*unknowns]+Qin[rightVoxelInPreImage*unknowns:(rightVoxelInPreImage+1)*unknowns]
            rus = rusanov_y(rusanov_input)
            

            # Update out
            for u in range(unknowns):
                if y>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(rus[u])

                if y<patch_len:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(rus[u])

    for x in range(patch_len):
        for y in range(patch_len):

            image_voxel = voxelInImage(x, y, patch_len)
            pre_image_voxel = voxelInPreimage(x, y, patch_len)
            for u in range(unknowns):
                Qout[image_voxel*unknowns+u] = Qin[pre_image_voxel*unknowns+u] + dt_div_size * sum(Q_out_pos_contrib[image_voxel*unknowns+u]) - dt_div_size * sum( Q_out_neg_contrib[image_voxel*unknowns+u])
    
    return Qout