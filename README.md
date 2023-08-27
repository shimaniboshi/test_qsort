# C言語の学習

- 構造体をソートするにあたって、構造体のデータそのものをソートするのではなく、構造体へのポインタをソート
    - 構造体のサイズよりポインタのサイズの方が小さいので、交換時のコストが小さい
- <stdlib.h>のqsort()関数を使用してソート
    - ```void qsort(void base[.size * .nmemb], size_t nmemb, size_t size, int (*compar)(const void [.size], const void [.size]));```
    - qsort()関数の第4引数の型は、「void * と void * を引数にとりint型を返す関数へのポインタ」となっている.
    - qsort()の第4引数の型（関数へのポインタ）の配列は、int (* array[])(const void *, const void *)
    - 第4引数の型を返す関数で引数をとらないもの、すなわち、「void * とvoid * を引数にとりint型を返す関数へのポインタを返す引数無しの関数」は、int (* func(void))(const void *, const void *)
    - これらは```typedef int (*Comparator)(cost void *, const void *)```というように型のエイリアスをつけることでシンプルに表記できるようになる
        - int (* array[])(const void *, const void *)  =>  Comparator array[]
        - int (* func(void))(const void *, const void *) => Comparator func(void)
- マクロ関数の変数は()でくくること
- 列挙型は整数に名前をつけているような感じ
