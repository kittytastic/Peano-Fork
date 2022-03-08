from typing import Callable, List

from compute_graph.DAG import *

def rusanov(
    unknowns:int,
    max_eigen_builder: Callable[[], Graph],
    flux_builder: Callable[[], Graph],
    friendly_name:str="rusanov")->Graph:

    # Q left (unknowns)
    # Q right (unknowns)
    # patch center (2)
    # patch dx     (1)
    # t            (1)
    # dt           (1)
    g = Graph(unknowns*2 + 2+1+1+1, unknowns*2, friendly_name)
    flux_l = flux_builder()
    flux_r = flux_builder()

    eigen_l = max_eigen_builder()
    eigen_r = max_eigen_builder()

    # Flux and Eigen
    for u in range(unknowns):
        g.add_edge(g.get_internal_input(u), flux_l.get_external_input(u))
        g.add_edge(g.get_internal_input(unknowns + u), flux_r.get_external_input(u))
        g.add_edge(g.get_internal_input(u), eigen_l.get_external_input(u))
        g.add_edge(g.get_internal_input(unknowns + u), eigen_r.get_external_input(u))

    for e in range(2+1+1+1):
        g.add_edge(g.get_internal_input(unknowns+e), flux_l.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), eigen_l.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), flux_r.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), eigen_r.get_external_input(unknowns+e))

    l_max = Max(2)
    g.fill_node_inputs([eigen_l, eigen_r], l_max)

    for i in range(unknowns):
        h = Constant(0.5)
        mul1 = Multiply(2)
        mul2 = Multiply(2)
        mul3 = Multiply(3)
        sub1 = Subtract()
        sub2 = Subtract()
        add1 = Add(2)

        # QR - QL
        g.fill_node_inputs([g.get_internal_input(i+unknowns), g.get_internal_input(i)], sub1)
        # 0.5 * lmax * (...)
        g.fill_node_inputs([h, l_max, sub1], mul3)

        # 0.5 * FL + 0.5 * FR
        g.fill_node_inputs([h, (flux_l, i)], mul1)
        g.fill_node_inputs([h, (flux_r, i)], mul2)
        g.fill_node_inputs([mul1, mul2], add1)

        g.fill_node_inputs([add1, mul3], sub2)

        g.add_edge((sub2, 0), g.get_internal_output(i))
        g.add_edge((sub2, 0), g.get_internal_output(i+unknowns))
    
    return g

def volumeX_2D(axis:str)->Graph:
    assert(axis=="x" or axis == "y")
    # 0,1 patchCenter
    # 2,3 patchSize
    # 4   volH
    # 5   x
    # 6   y
    
    g = Graph(7, 2, f"volumeX - {axis}")
    half = Constant(0.5)
    mul1 = Multiply(2)
    mul2 = Multiply(2)
    sub1 = Subtract()
    sub2 = Subtract()

    g.fill_node_inputs([half, g.get_internal_input(2)], mul1)
    g.fill_node_inputs([half, g.get_internal_input(3)], mul2)
    g.fill_node_inputs([g.get_internal_input(0), mul1], sub1)
    g.fill_node_inputs([g.get_internal_input(1), mul2], sub2)

    mul3 = Multiply(2)
    mul4 = Multiply(2)
    add1 = Add(2)
    add2 = Add(2)
    add3 = Add(2)

    if axis=="x":
        g.fill_node_inputs([g.get_internal_input(5), g.get_internal_input(4)], mul3)
        g.fill_node_inputs([half, g.get_internal_input(6)], add3)
        g.fill_node_inputs([add3, g.get_internal_input(4)], mul4)
    else:
        g.fill_node_inputs([half, g.get_internal_input(5)], add3)
        g.fill_node_inputs([add3, g.get_internal_input(4)], mul3)
        g.fill_node_inputs([g.get_internal_input(6), g.get_internal_input(4)], mul4)

    g.fill_node_inputs([mul3, sub1], add1)
    g.fill_node_inputs([mul4, sub2], add2)
    g.add_edge((add1, 0), g.get_internal_output(0))
    g.add_edge((add2, 0), g.get_internal_output(1))

    return g


def patchUpdate_2D(cells_per_axis: int, unknowns: int, rusanov_x:Callable[[str], Graph], rusanov_y:Callable[[str], Graph])->Graph:
    dim = 2
    Qins:int = (cells_per_axis+2)**dim * unknowns
    Qout:int = (cells_per_axis)**dim * unknowns


    Q_in_loc = 0
    t_loc = Q_in_loc + Qins
    dt_loc = t_loc+1
    patch_center_loc = dt_loc + 1
    patch_size_loc = patch_center_loc + dim
    total_inputs = patch_size_loc+dim

    g=Graph(total_inputs, Qout, "PatchUpdate")

    Q_out_pos_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]
    Q_out_neg_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]


    symNumPatches = Constant(cells_per_axis) 
    vol_h = Divide()
    g.fill_node_inputs([g.get_internal_input(patch_size_loc), symNumPatches], vol_h)

    dt_div_size = Divide()
    g.fill_node_inputs([g.get_internal_input(dt_loc), vol_h], dt_div_size)

    # Flux x
    for x in range(cells_per_axis+1):
        for y in range(cells_per_axis):
            leftVoxelInPreImage = voxelInPreimage_2D(x-1, y, cells_per_axis)
            rightVoxelInPreImage = voxelInPreimage_2D(x, y, cells_per_axis)

            leftVoxelInImage = voxelInImage_2D(x-1, y, cells_per_axis)
            rightVoxelInImage = voxelInImage_2D(x, y, cells_per_axis)

            c_x = Constant(x)    
            c_y = Constant(y)    
            volX = volumeX_2D("x")
            g.fill_node_inputs([
                g.get_internal_input(patch_center_loc),
                g.get_internal_input(patch_center_loc+1),
                g.get_internal_input(patch_size_loc),
                g.get_internal_input(patch_size_loc+1),
                vol_h,
                c_x,
                c_y
                ], volX)

            # Rusanov
            rus = rusanov_x(f"rusanov-x ({x}, {y})")
            for u in range(unknowns):
                g.add_edge(g.get_internal_input(Q_in_loc + leftVoxelInPreImage*unknowns + u), (rus, u))
                g.add_edge(g.get_internal_input(Q_in_loc + rightVoxelInPreImage*unknowns + u), (rus, u+unknowns))
            g.add_edge((volX,0), (rus, 2*unknowns))
            g.add_edge((volX,1), (rus, 2*unknowns+1))
            g.add_edge((vol_h, 0), (rus, 2*unknowns+2))
            g.add_edge(g.get_internal_input(t_loc), (rus, 2*unknowns+3))
            g.add_edge(g.get_internal_input(dt_loc), (rus, 2*unknowns+4))

            # Update out
            for u in range(unknowns):
                if x>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(OutPort((rus, u)))

                if x<cells_per_axis:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(OutPort((rus,u)))


    
    # Flux y
    for x in range(cells_per_axis):
        for y in range(cells_per_axis+1):
            leftVoxelInPreImage = voxelInPreimage_2D(x, y-1, cells_per_axis)
            rightVoxelInPreImage = voxelInPreimage_2D(x, y, cells_per_axis)

            leftVoxelInImage = voxelInImage_2D(x, y-1, cells_per_axis)
            rightVoxelInImage = voxelInImage_2D(x, y, cells_per_axis)

            c_x = Constant(x)    
            c_y = Constant(y)    
            volX = volumeX_2D("y")
            g.fill_node_inputs([
                g.get_internal_input(patch_center_loc),
                g.get_internal_input(patch_center_loc+1),
                g.get_internal_input(patch_size_loc),
                g.get_internal_input(patch_size_loc+1),
                vol_h,
                c_x,
                c_y
                ], volX)

            # Rusanov
            rus = rusanov_y(f"rusanov-y ({x}, {y})")
            for u in range(unknowns):
                g.add_edge(g.get_internal_input(Q_in_loc + leftVoxelInPreImage*unknowns + u), (rus, u))
                g.add_edge(g.get_internal_input(Q_in_loc + rightVoxelInPreImage*unknowns + u), (rus, u+unknowns))
            g.add_edge((volX,0), (rus, 2*unknowns))
            g.add_edge((volX,1), (rus, 2*unknowns+1))
            g.add_edge((vol_h, 0), (rus, 2*unknowns+2))
            g.add_edge(g.get_internal_input(t_loc), (rus, 2*unknowns+3))
            g.add_edge(g.get_internal_input(dt_loc), (rus, 2*unknowns+4))

            # Update out
            for u in range(unknowns):
                if y>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(OutPort((rus, u)))

                if y<cells_per_axis:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(OutPort((rus, u)))

    # Sum all contributions
    for x in range(cells_per_axis):
        for y in range(cells_per_axis):

            image_voxel = voxelInImage_2D(x, y, cells_per_axis)
            pre_image_voxel = voxelInPreimage_2D(x, y, cells_per_axis)
            for u in range(unknowns):
                add_pos = Add(len(Q_out_pos_contrib[image_voxel*unknowns+u]))
                add_neg = Add(len(Q_out_neg_contrib[image_voxel*unknowns+u]))
                diff = Subtract()
                scale = Multiply(2)
                add_input = Add(2) 

                g.fill_node_inputs(Q_out_pos_contrib[image_voxel*unknowns+u], add_pos) # type:ignore
                g.fill_node_inputs(Q_out_neg_contrib[image_voxel*unknowns+u], add_neg) # type:ignore
                g.fill_node_inputs([add_pos, add_neg], diff)
                g.fill_node_inputs([diff, dt_div_size], scale)
                g.fill_node_inputs([scale, g.get_internal_input(Q_in_loc+ pre_image_voxel*unknowns+u)], add_input)
                g.add_edge((add_input, 0), g.get_internal_output(image_voxel*unknowns+u))
    
    return g

def voxelInPreimage_2D(x: int, y:int, patch_len: int): return x+1 + (y+1) * (2+patch_len)
def voxelInImage_2D(x: int, y:int, patch_len: int): return x + y * patch_len