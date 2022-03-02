from typing import List, Union, Tuple, Any, Optional, cast, Type, Set, TypeVar
from enum import Enum
from abc import ABC
import inspect

_T = TypeVar("_T")


class IR_DataTypes(Enum):
    VOID = 0
    FP64 = 1

class IR_Symbol(ABC):
    def __init__(self) -> None:
        super().__init__()
        self._cached_attributes:Optional[Tuple[Set[str], Set[str], Set[str]]]=None


    def _get_all_attributes(self)->List[Tuple[str, Any]]:
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return attributes

    def _enforce_property_creation(self):
        if not hasattr(self, "_cached_attributes"):
            self._cached_attributes = None         

    def _get_sub_symbol_keys(self)->Tuple[Set[str], Set[str]]:
        self._enforce_property_creation()
        
        if self._cached_attributes is None:
            attribute_keys = [a for a, _ in self._get_all_attributes()]
            single_keys = [k for k in attribute_keys if isinstance(getattr(self, k), IR_Symbol)]
            multi_keys = [k for k in attribute_keys if self._is_list_of_symbol(getattr(self, k))]
            unknown_keys = [k for k in attribute_keys if isinstance(getattr(self, k), list) and len(getattr(self, k))==0]

            self._cached_attributes = (set(single_keys), set(multi_keys), set(unknown_keys))
        
        '''
        rs:Set[str] = set()
        for uk in self._cached_attributes[2]:
            uk_v = getattr(self, uk)
            assert(isinstance(uk_v, list))
            uk_v = cast(List[Any], uk_v)

            if len(uk_v)>0:
                rs.add(uk)
                
                if self._is_list_of_symbol(uk_v):
                    self._cached_attributes[1].add(uk)
        
        for r in rs:
            self._cached_attributes[2].remove(r)
        '''
                
        return (self._cached_attributes[0], self._cached_attributes[1])

    def _is_list_of_symbol(self, in_list:Any)->bool:
        if not isinstance(in_list, list):
            return False
        
        '''
        in_list = cast(List[Any], in_list)
        if len(in_list)==0:
            return False
        
        #for i in in_list:
        #    if not isinstance(i, IR_Symbol):
        #        return None
        
        if not isinstance(in_list[0], IR_Symbol):
            return False
            '''
        
        return True
    

    def __contains__(self, key:Union['IR_Symbol', type]):
        if inspect.isclass(key):
            if isinstance(self, key):
                return True
        else:
            if key is self:
                return True
        
        sing_attr, list_attr = self._get_sub_symbol_keys() 
        for k in sing_attr:
            if key in getattr(self, k):
                return True
            
        for k in list_attr:
            lst = getattr(self, k)
            for l in lst:
                if key in l:
                    return True
        #child_ins:List[bool] = [key in getattr(self, k) for k in sing_attr]
        #child_lists:List[List['IR_Symbol']] = [getattr(self, k) for k in list_attr]
        #child_list_ins: List[bool] = [key in i for l in child_lists for i in l]

        #        return any(child_ins) or any(child_list_ins)
        return False

    def replace(self, find:'IR_Symbol', replace: 'IR_Symbol')->int:
        if find is self:
            raise Exception("Cannot replace. The symbol you called replace on needs to be replaced")

        sing_attr, list_attr = self._get_sub_symbol_keys() 

        replacement_count = 0
        for k in sing_attr:
            s = getattr(self, k)
            if s is find:
                setattr(self, k, replace)
                replacement_count +=1
            else:
                replacement_count += s.replace(find, replace)

        for k in list_attr:
            l_ref = getattr(self, k)
            for idx, v in enumerate(l_ref):
                if v is find:
                    l_ref[idx] = replace
                    replacement_count +=1
                else:
                    replacement_count += v.replace(find, replace)


        return replacement_count
    
    def get_instances(self, symbol_type: Type[_T])->Set[_T]:
        if isinstance(self, symbol_type):
            return set([self])
        
        sing_attr, list_attr = self._get_sub_symbol_keys() 
        child_symbols:List[ IR_Symbol] = [getattr(self, k) for k in sing_attr]
        child_lists:List[List['IR_Symbol']] = [getattr(self, k) for k in list_attr]

        instances_from_syms = [s.get_instances(symbol_type) for s in child_symbols]
        instances_from_list = [s.get_instances(symbol_type) for l in child_lists for s in l]

        base_set: Set[_T] =  set()
        base_set = base_set.union(*instances_from_syms)
        base_set = base_set.union(*instances_from_list)
        return base_set