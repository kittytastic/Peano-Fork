from typing import Callable, List, Optional
from compute_graph.DAG import *

def rusanov(
    unknowns:int,
    auxiliarys:int,
    dims: int,
    max_eigen_builder: Callable[[], Graph],
    flux_builder: Optional[Callable[[], Graph]],
    ncp_builder: Optional[Callable[[], Graph]],
    friendly_name:str="rusanov")->Graph:
    
    total_var = unknowns+auxiliarys
    use_flux = flux_builder is not None
    use_ncp = ncp_builder is not None
    assert(use_flux or use_ncp)

    # Q left (unknowns)
    # Q right (unknowns)
    # patch center (2)
    # patch dx     (1)
    # t            (1)
    # dt           (1)
    g = Graph(total_var*2 + dims+1+1+1, unknowns*2, friendly_name)
    flux_r:Optional[Graph] = flux_builder() if flux_builder is not None else None
    flux_l:Optional[Graph] = flux_builder() if flux_builder is not None else None

    ncp:Optional[Graph] = ncp_builder() if ncp_builder is not None else None
    
    eigen_l = max_eigen_builder()
    eigen_r = max_eigen_builder()

    if ncp:
        for v in range(total_var): 
            add1 = Add(2)
            h = Constant(0.5)
            Q = Multiply(2)
            deltaQ = Subtract()
            g.fill_node_inputs([g.get_internal_input(v), g.get_internal_input(total_var+v)], add1)
            g.fill_node_inputs([h, add1], Q)
            g.fill_node_inputs([g.get_internal_input(total_var+v), g.get_internal_input(v)], deltaQ)
            g.add_edge((Q,0), ncp.get_external_input(v))
            g.add_edge((deltaQ,0), ncp.get_external_input(total_var+v))
        
        for e in range(dims+1+1+1): 
            g.add_edge(g.get_internal_input(2*total_var+e), ncp.get_external_input(2*total_var+e))

    
    # Flux
    if flux_l is not None and flux_r is not None:
        for v in range(total_var):
            g.add_edge(g.get_internal_input(v), flux_l.get_external_input(v))
            g.add_edge(g.get_internal_input(total_var + v), flux_r.get_external_input(v))

        for e in range(2+1+1+1):
            g.add_edge(g.get_internal_input(total_var*2+e), flux_l.get_external_input(total_var+e))
            g.add_edge(g.get_internal_input(total_var*2+e), flux_r.get_external_input(total_var+e))
    

    # Eigen Value
    for v in range(total_var):
        g.add_edge(g.get_internal_input(v), eigen_l.get_external_input(v))
        g.add_edge(g.get_internal_input(total_var + v), eigen_r.get_external_input(v))

    for e in range(dims+1+1+1):
        g.add_edge(g.get_internal_input(total_var*2+e), eigen_l.get_external_input(total_var+e))
        g.add_edge(g.get_internal_input(total_var*2+e), eigen_r.get_external_input(total_var+e))

    l_max = Max(2)
    g.fill_node_inputs([eigen_l, eigen_r], l_max)

    for i in range(unknowns):
        h = Constant(0.5)
        zero = Constant(0)
        eigen_contrib = Subtract()
        flux_contrib = Add(2)
        ncp_contrib = Multiply(2)


        if True:
            sub1 = Subtract()
            mul1 = Multiply(3)
            # 0.5 * lmax * (QR - QL)
            g.fill_node_inputs([g.get_internal_input(i+total_var), g.get_internal_input(i)], sub1)
            g.fill_node_inputs([h, l_max, sub1], mul1)
            g.fill_node_inputs([zero, mul1], eigen_contrib)

        next_node_l = eigen_contrib
        next_node_r = eigen_contrib

        if flux_l is not None and flux_r is not None:
            # 0.5 * FL + 0.5 * FR
            mul1 = Multiply(2)
            mul2 = Multiply(2)
            add1 = Add(2)
            g.fill_node_inputs([h, (flux_l, i)], mul1)
            g.fill_node_inputs([h, (flux_r, i)], mul2)
            g.fill_node_inputs([mul1, mul2], flux_contrib)
            g.fill_node_inputs([next_node_l, flux_contrib], add1)
            next_node_l = add1
            next_node_r = add1

        if ncp is not None:
            add1 = Add(2)
            sub1 = Subtract()
            g.fill_node_inputs([h, (ncp, i)], ncp_contrib)
            g.fill_node_inputs([next_node_l, ncp_contrib], add1)
            g.fill_node_inputs([next_node_r, ncp_contrib], sub1)
            next_node_l = add1
            next_node_r = sub1



        g.add_edge((next_node_l, 0), g.get_internal_output(i))
        g.add_edge((next_node_r, 0), g.get_internal_output(i+unknowns))
    
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


def patchUpdate_2D(cells_per_axis: int, unknowns: int, auxiliary:int, rusanov_x:Callable[[str], Graph], rusanov_y:Callable[[str], Graph], source_term:Callable[[], Graph])->Graph:
    total_var = unknowns+auxiliary
    dim = 2
    Qins:int = (cells_per_axis+2)**dim * total_var
    Qout:int = (cells_per_axis)**dim * total_var


    Q_in_loc = 0
    t_loc = Q_in_loc + Qins
    dt_loc = t_loc+1
    patch_center_loc = dt_loc + 1
    patch_size_loc = patch_center_loc + dim
    total_inputs = patch_size_loc+dim

    g=Graph(total_inputs, Qout, "PatchUpdate")

    Q_out_pos_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]
    Q_out_neg_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]
    Q_source_terms: List[Optional[OutPort]]= [None] * Qout


    symNumPatches = Constant(cells_per_axis) 
    vol_h = Divide()
    g.fill_node_inputs([g.get_internal_input(patch_size_loc), symNumPatches], vol_h)

    dt_div_size = Divide()
    g.fill_node_inputs([g.get_internal_input(dt_loc), vol_h], dt_div_size)
    
    # Source Terms
    for x in range(cells_per_axis):
        for y in range(cells_per_axis):
            voxelInPreImage = voxelInPreimage_2D(x-1, y, cells_per_axis)
            voxelInImage = voxelInImage_2D(x-1, y, cells_per_axis)

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

            st = source_term()
            for v in range(total_var): g.add_edge(g.get_internal_input(Q_in_loc + voxelInPreImage*total_var + v), (st, v))
            g.add_edge((volX,0), (st, total_var))
            g.add_edge((volX,1), (st, total_var+1))
            g.add_edge((vol_h, 0), (st, total_var+2))
            g.add_edge(g.get_internal_input(t_loc), (st, total_var+3))
            g.add_edge(g.get_internal_input(dt_loc), (st, total_var+4))

            for u in range(unknowns):
                mul_dt = Multiply(2)
                g.fill_node_inputs([(st, u), g.get_internal_input(dt_loc)], mul_dt)
                Q_source_terms[voxelInImage*total_var +u] = OutPort((mul_dt, 0))





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
            for v in range(total_var):
                g.add_edge(g.get_internal_input(Q_in_loc + leftVoxelInPreImage*total_var + v), (rus, v))
                g.add_edge(g.get_internal_input(Q_in_loc + rightVoxelInPreImage*total_var + v), (rus, v+total_var))
            g.add_edge((volX,0), (rus, 2*total_var))
            g.add_edge((volX,1), (rus, 2*total_var+1))
            g.add_edge((vol_h, 0), (rus, 2*total_var+2))
            g.add_edge(g.get_internal_input(t_loc), (rus, 2*total_var+3))
            g.add_edge(g.get_internal_input(dt_loc), (rus, 2*total_var+4))

            # Update out
            for u in range(unknowns):
                if x>0:
                    Q_out_neg_contrib[leftVoxelInImage*total_var+u].append(OutPort((rus, u)))

                if x<cells_per_axis:
                    Q_out_pos_contrib[rightVoxelInImage*total_var+u].append(OutPort((rus,u+unknowns)))


    
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
            for v in range(total_var):
                g.add_edge(g.get_internal_input(Q_in_loc + leftVoxelInPreImage*total_var + v), (rus, v))
                g.add_edge(g.get_internal_input(Q_in_loc + rightVoxelInPreImage*total_var + v), (rus, v+total_var))
            g.add_edge((volX,0), (rus, 2*total_var))
            g.add_edge((volX,1), (rus, 2*total_var+1))
            g.add_edge((vol_h, 0), (rus, 2*total_var+2))
            g.add_edge(g.get_internal_input(t_loc), (rus, 2*total_var+3))
            g.add_edge(g.get_internal_input(dt_loc), (rus, 2*total_var+4))

            # Update out
            for u in range(unknowns):
                if y>0:
                    Q_out_neg_contrib[leftVoxelInImage*total_var+u].append(OutPort((rus, u)))

                if y<cells_per_axis:
                    Q_out_pos_contrib[rightVoxelInImage*total_var+u].append(OutPort((rus, u+unknowns)))

    # Sum all contributions
    for x in range(cells_per_axis):
        for y in range(cells_per_axis):

            image_voxel = voxelInImage_2D(x, y, cells_per_axis)
            pre_image_voxel = voxelInPreimage_2D(x, y, cells_per_axis)
            for u in range(unknowns):
                add_pos = Add(len(Q_out_pos_contrib[image_voxel*total_var+u]))
                add_neg = Add(len(Q_out_neg_contrib[image_voxel*total_var+u]))
                diff = Subtract()
                scale = Multiply(2)
                add_input1 = Add(2) 
                add_input2 = Add(2) 

                g.fill_node_inputs(Q_out_pos_contrib[image_voxel*total_var+u], add_pos) # type:ignore
                g.fill_node_inputs(Q_out_neg_contrib[image_voxel*total_var+u], add_neg) # type:ignore
                g.fill_node_inputs([add_pos, add_neg], diff)
                g.fill_node_inputs([diff, dt_div_size], scale)
                st = Q_source_terms[image_voxel*total_var+u]
                assert(st is not None)
                g.fill_node_inputs([scale, st], add_input1)
                g.fill_node_inputs([add_input1, g.get_internal_input(Q_in_loc+ pre_image_voxel*total_var+u)], add_input2)
                g.add_edge((add_input2, 0), g.get_internal_output(image_voxel*total_var+u))
            
            for a in range(auxiliary):
                g.add_edge(g.get_internal_input(Q_in_loc + pre_image_voxel*total_var+unknowns+a), g.get_internal_output(Q_in_loc+image_voxel*total_var+unknowns+a))
    
    return g

def voxelInPreimage_2D(x: int, y:int, patch_len: int): return x+1 + (y+1) * (2+patch_len)
def voxelInImage_2D(x: int, y:int, patch_len: int): return x + y * patch_len


def source_term_zeros(unknowns: int, auxiliary: int, dims: int)->Graph:
    total_var = unknowns+auxiliary
    g = Graph(total_var+dims+1+1+1, total_var, "source term zeros")
    c1 = Constant(0)
    for u in range(total_var):
        g.add_edge((c1,0), g.get_internal_output(u))

    return g



def volumeX_3D(axis:str)->Graph:
    assert(axis=="x" or axis == "y" or axis=="z" or axis=="no_face")
    # 0,1,2 patchCenter
    # 3,4,5 patchSize
    # 6   volH
    # 7   x
    # 8   y
    # 8   z
    volH = 6
    
    g = Graph(10, 3, f"volumeX - {axis}")
    half = Constant(0.5)
    mul1 = Multiply(2)
    mul2 = Multiply(2)
    mul3 = Multiply(2)
    sub1, sub2, sub3 = Subtract(), Subtract(), Subtract()

    g.fill_node_inputs([half, g.get_internal_input(3)], mul1)
    g.fill_node_inputs([half, g.get_internal_input(4)], mul2)
    g.fill_node_inputs([half, g.get_internal_input(5)], mul3)
    g.fill_node_inputs([g.get_internal_input(0), mul1], sub1)
    g.fill_node_inputs([g.get_internal_input(1), mul2], sub2)
    g.fill_node_inputs([g.get_internal_input(2), mul2], sub3)

    x_defalt = g.get_internal_input(7)
    y_defalt = g.get_internal_input(8)
    z_defalt = g.get_internal_input(9)

    if axis!="x":
        tmp_add = Add(2)
        g.fill_node_inputs([x_defalt, half], tmp_add)
        x_defalt = tmp_add

    if axis!="y":
        tmp_add = Add(2)
        g.fill_node_inputs([y_defalt, half], tmp_add)
        y_defalt = tmp_add

    if axis!="z":
        tmp_add = Add(2)
        g.fill_node_inputs([z_defalt, half], tmp_add)
        z_defalt = tmp_add

    mul4, mul5, mul6 = Multiply(2), Multiply(2), Multiply(3)
    g.fill_node_inputs([x_defalt, g.get_internal_input(volH)], mul4)
    g.fill_node_inputs([y_defalt, g.get_internal_input(volH)], mul5)
    g.fill_node_inputs([z_defalt, g.get_internal_input(volH)], mul6)


    add1, add2, add3 = Add(2), Add(2), Add(3)
    g.fill_node_inputs([mul4, sub1], add1)
    g.fill_node_inputs([mul5, sub2], add2)
    g.fill_node_inputs([mul6, sub3], add3)
    g.add_edge((add1, 0), g.get_internal_output(0))
    g.add_edge((add2, 0), g.get_internal_output(1))
    g.add_edge((add3, 0), g.get_internal_output(2))

    return g