from typing import List, Union, Tuple, Any, Optional, cast, Type, Set, TypeVar
from enum import Enum
from abc import ABC
import inspect

_T = TypeVar("_T")


class IR_DataTypes(Enum):
    VOID = 0
    FP64 = 1

class IR_Symbol(ABC):
    def _get_all_attributes(self)->List[Tuple[str, Any]]:
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return attributes

    def _is_list_of_symbol(self, in_list:Any)->Optional[List['IR_Symbol']]:
        if not isinstance(in_list, list):
            return None
        
        in_list = cast(List[Any], in_list)
        for i in in_list:
            if not isinstance(i, IR_Symbol):
                return None
        
        return in_list
    

    def __contains__(self, key:Union['IR_Symbol', type]):
        if inspect.isclass(key):
            if isinstance(self, key):
                return True
        else:
            if key == self:
                return True
        
        attributes = self._get_all_attributes()
        child_ins:List[bool] = [key in val for _, val in attributes if isinstance(val, IR_Symbol)]
        
        child_sym_lists:List[List['IR_Symbol']] = [l for _,l in attributes if self._is_list_of_symbol(l)]
        child_list_ins: List[bool] = [key in i for l in child_sym_lists for i in l]

        return any(child_ins) or any(child_list_ins)
    
    def replace(self, find:'IR_Symbol', replace: 'IR_Symbol')->int:
        if find == self:
            raise Exception("Cannot replace. The symbol you called replace on needs to be replaced")

        attributes = self._get_all_attributes() 
        child_symbols = [(k,v) for k, v in attributes if isinstance(v, IR_Symbol)]
        child_lists:List[Tuple[str,List['IR_Symbol']]] = [(k,l) for k,l in attributes if self._is_list_of_symbol(l)]

        replacement_count = 0
        for k, s in child_symbols:
            if s == find:
                setattr(self, k, replace)
                replacement_count +=1
            else:
                replacement_count += s.replace(find, replace)

        for k, l in child_lists:
            l_ref = getattr(self, k)
            for idx, v in enumerate(l):
                if v==find:
                    l_ref[idx] = replace
                    replacement_count +=1
                else:
                    replacement_count += v.replace(find, replace)


        return replacement_count
    
    def get_instances(self, symbol_type: Type[_T])->Set[_T]:
        if isinstance(self, symbol_type):
            return set([self])
        
        attributes = self._get_all_attributes() 
        child_symbols = [s for _, s in attributes if isinstance(s, IR_Symbol)]
        child_lists:List[List['IR_Symbol']] = [l for _,l in attributes if self._is_list_of_symbol(l)]

        instances_from_syms = [s.get_instances(symbol_type) for s in child_symbols]
        instances_from_list = [s.get_instances(symbol_type) for l in child_lists for s in l]

        base_set: Set[_T] =  set()
        base_set = base_set.union(*instances_from_syms)
        base_set = base_set.union(*instances_from_list)
        return base_set