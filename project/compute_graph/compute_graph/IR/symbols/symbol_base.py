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
        self._attributes: Tuple[Set[str], Set[str]] = self._get_sub_symbol_keys()
        self._single_attr = self._attributes[0]
        self._list_attr = self._attributes[1]

    def _get_all_attributes(self)->List[Tuple[str, Any]]:
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        #attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return attributes


    def _get_sub_symbol_keys(self)->Tuple[Set[str], Set[str]]:
        attribute_keys = [a for a, _ in self._get_all_attributes()]
        single_keys = [k for k in attribute_keys if isinstance(getattr(self, k), IR_Symbol)]
        multi_keys = [k for k in attribute_keys if isinstance(getattr(self, k), list)]
        return (set(single_keys), set(multi_keys))
    

    def __contains__(self, key:Union['IR_Symbol', type]):
        if inspect.isclass(key):
            if isinstance(self, key):
                return True
        else:
            if key is self:
                return True
        
        sing_attr, list_attr = self._attributes 
        for k in sing_attr:
            if key in getattr(self, k):
                return True
            
        for k in list_attr:
            lst = getattr(self, k)
            for l in lst:
                if key in l:
                    return True
       
        return False

    def replace_and_count(self, find:'IR_Symbol', replace: 'IR_Symbol')->int:
        if find is self:
            raise Exception("Cannot replace. The symbol you called replace on needs to be replaced")

        replacement_count = 0
        for k in self._single_attr:
            s = getattr(self, k)
            if s is find:
                setattr(self, k, replace)
                replacement_count +=1
            else:
                replacement_count += s.replace_and_count(find, replace)

        for k in self._list_attr:
            l_ref = getattr(self, k)
            for idx, v in enumerate(l_ref):
                if v is find:
                    l_ref[idx] = replace
                    replacement_count +=1
                else:
                    replacement_count += v.replace_and_count(find, replace)


        return replacement_count
    
    def replace(self, find:'IR_Symbol', replace: 'IR_Symbol')->None:
        if find is self:
            raise Exception("Cannot replace. The symbol you called replace on needs to be replaced")

        for k in self._single_attr:
            s = getattr(self, k)
            if s is find:
                setattr(self, k, replace)
            else:
                s.replace(find, replace)

        for k in self._list_attr:
            l_ref = getattr(self, k)
            for idx, v in enumerate(l_ref):
                if v is find:
                    l_ref[idx] = replace
                else:
                    v.replace(find, replace)


    def get_instances(self, symbol_type: Type[_T])->Set[_T]:
        if isinstance(self, symbol_type):
            return set([self])
        
        sing_attr, list_attr = self._attributes
        child_symbols:List[ IR_Symbol] = [getattr(self, k) for k in sing_attr]
        child_lists:List[List['IR_Symbol']] = [getattr(self, k) for k in list_attr]

        instances_from_syms = [s.get_instances(symbol_type) for s in child_symbols]
        instances_from_list = [s.get_instances(symbol_type) for l in child_lists for s in l]

        base_set: Set[_T] =  set()
        base_set = base_set.union(*instances_from_syms)
        base_set = base_set.union(*instances_from_list)
        return base_set