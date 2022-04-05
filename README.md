# Pools
Для реализации соединения бассейнов каналами был применен алгоритм системы непересекающихся множеств с эвристикой по размеру поддерева и эвристикой сжатия пути.
Сперва реализация эвристики сжатия пути была рекурсивной:
```c++
size_t DisjointSetUnion::FindDelegateRecImpl(const size_t elem_tag) {
  if (parents_[elem_tag] = elem_tag) {
    return elem_tag;
  }
  parents_[elem_tag] = FindDelegateRecImpl(parents_[elem_tag]);
  return parents_[elem_tag];
}
```
 что легко приводило к переполнению стека. После размотки рекурсии:
 ```c++
 size_t DisjointSetUnion::FindDelegate(size_t elem_tag) {
  if (!IsTagValid(elem_tag)) {
    return INVALID_ELEM_TAG;
  }

  size_t res_tag = elem_tag;
  while (parents_[res_tag] != res_tag) {
    res_tag = parents_[res_tag];
  }

  size_t old_parent = parents_[elem_tag];
  while (old_parent != elem_tag) {
    old_parent = parents_[elem_tag];
    parents_[elem_tag] = res_tag;
    elem_tag = old_parent;
  }

  return res_tag;
}
 ```
 проблема исчезла.

Применение этих двух эвристик даёт время работы `O(f(n))` на запрос, где `f` - обратная функция Аккермана (`f(n) <= 4` при разумных `n`, так что можно считать `O(1)`).
