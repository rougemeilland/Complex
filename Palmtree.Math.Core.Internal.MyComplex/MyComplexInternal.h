/*
 * The MIT License
 *
 * Copyright 2019 Palmtree Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#pragma once
#ifndef __INCLUDE_PALMTREE_MATH_CORE_INTERNAL_MYCOMPLEX
#define __INCLUDE_PALMTREE_MATH_CORE_INTERNAL_MYCOMPLEX

#include <windows.h>

typedef struct __tag_MINICOMPLEX
{
    double ___r; // Internal 以外から直接参照するのはダメ
    double ___i; // Internal 以外から直接参照するのはダメ
} MINICOMPLEX;

typedef struct __tag_MYCOMPLEX_ENTRY_POINT
{
    MINICOMPLEX* (*From)(double r, double i);
    void (*Dispose)(MINICOMPLEX* p);
    MINICOMPLEX* (*Add)(const MINICOMPLEX* u, const MINICOMPLEX* v);
    MINICOMPLEX* (*Subtruct)(const MINICOMPLEX* u, const MINICOMPLEX* v);
    MINICOMPLEX* (*Multiply)(const MINICOMPLEX* u, const MINICOMPLEX* v);
    MINICOMPLEX* (*Divide)(const MINICOMPLEX* u, const MINICOMPLEX* v);
    void(*ToString)(const MINICOMPLEX* u, wchar_t* buffer, size_t buffer_size);
    double(*GetR)(const MINICOMPLEX* u);
    double(*GetI)(const MINICOMPLEX* u);

} MYCOMPLEX_ENTRY_POINT;

typedef struct __tag_MYCOMPLEX_EXCEPTION
{
    int code;
} MYCOMPLEX_EXCEPTION;



MYCOMPLEX_ENTRY_POINT* WINAPI GetEntryPoint();


#endif // __INCLUDE_PALMTREE_MATH_CORE_INTERNAL_MYCOMPLEX


/*
 * END OF FILE
 */