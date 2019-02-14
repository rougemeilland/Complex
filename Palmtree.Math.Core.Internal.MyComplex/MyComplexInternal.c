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

#include <windows.h>
#include <wchar.h>
#include "MyComplexInternal.h"

static MINICOMPLEX* From(double r, double i)
{
    MINICOMPLEX* p = malloc(sizeof(MINICOMPLEX));
    p->___r = r;
    p->___i = i;
    return (p);
}

static void Dispose(MINICOMPLEX* p)
{
    free(p);
}

static MINICOMPLEX* Add(const MINICOMPLEX* u, const MINICOMPLEX* v)
{
    MINICOMPLEX* w = malloc(sizeof(MINICOMPLEX));
    w->___r = u->___r + v->___r;
    w->___i = u->___i + v->___i;
    return (w);
}

static MINICOMPLEX* Subtruct(const MINICOMPLEX* u, const MINICOMPLEX* v)
{
    MINICOMPLEX* w = malloc(sizeof(MINICOMPLEX));
    w->___r = u->___r - v->___r;
    w->___i = u->___i - v->___i;
    return (w);
}

static MINICOMPLEX* Multiply(const MINICOMPLEX* u, const MINICOMPLEX* v)
{
    MINICOMPLEX* w = malloc(sizeof(MINICOMPLEX));
    w->___r = u->___r * v->___r - u->___i * v->___i;
    w->___i = u->___r * v->___i + u->___i * v->___r;
    return (w);
}

static MINICOMPLEX* Divide(const MINICOMPLEX* u, const MINICOMPLEX* v)
{
    MINICOMPLEX* w = malloc(sizeof(MINICOMPLEX));
    double d = v->___r * v->___r + v->___i * v->___i;
    w->___r = (u->___r * v->___r + u->___i * v->___i) / d;
    w->___i = (u->___r * v->___i - u->___i * v->___r) / d;
    return (w);
}

static void ToString(const MINICOMPLEX* u, wchar_t* buffer, size_t buffer_size)
{
    if (u->___i >= 0)
        swprintf(buffer, buffer_size, L"(%g+%gi)", u->___r, u->___i);
    else
        swprintf(buffer, buffer_size, L"(%g-%gi)", u->___r, -u->___i);
}

static double GetR(const MINICOMPLEX* u)
{
    return (u->___r);
}

static double GetI(const MINICOMPLEX* u)
{
    return (u->___i);
}

MYCOMPLEX_ENTRY_POINT* WINAPI GetEntryPoint()
{
    static int initialized = 0;
    static MYCOMPLEX_ENTRY_POINT entry_point;
    if (!initialized)
    {
        entry_point.From = From;
        entry_point.Dispose = Dispose;
        entry_point.Add = Add;
        entry_point.Subtruct = Subtruct;
        entry_point.Multiply = Multiply;
        entry_point.Divide = Divide;
        entry_point.ToString = ToString;
        entry_point.GetR = GetR;
        entry_point.GetI = GetI;
    }
    return (&entry_point);
}


/*
 * END OF FILE
 */