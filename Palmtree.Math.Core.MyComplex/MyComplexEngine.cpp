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
#include <msclr/marshal.h>
#include "MyComplexEngine.h"
#include "MyComplexHandle.h"
#include "MyComplexInternal.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace msclr::interop;

namespace Palmtree::Math::Core
{
    MyComplexEngine::MyComplexEngine()
    {
        marshal_context ctx;
        String^ _dll_path = Path::Combine(Path::GetDirectoryName(Assembly::GetAssembly(MyComplexEngine::typeid)->Location), "Palmtree.Math.Core.Internal.MyComplex.dll");
        const char* dll_path = ctx.marshal_as<const char*>(_dll_path);
        HMODULE hLib = LoadLibraryA(dll_path);
        if (hLib == NULL)
            throw gcnew System::ApplicationException("DLL のロードに失敗しました。");
        MYCOMPLEX_ENTRY_POINT* (WINAPI * fp_GetEntryPoint)() = (MYCOMPLEX_ENTRY_POINT* (WINAPI * )())GetProcAddress(hLib, "GetEntryPoint");
        if (fp_GetEntryPoint == NULL)
            throw gcnew System::ApplicationException("Palmtree.Math.Core.Internal.MyComplex.dll にてシンボル GetEntryPoint の解決に失敗しました。");
        _ep = (*fp_GetEntryPoint)();
    }

    IMyComplexHandle ^ MyComplexEngine::CreateInstance(double r, double i)
    {
        return (gcnew MyComplexHandle(this,  _ep->From(r, i)));
    }


    const MYCOMPLEX_ENTRY_POINT* MyComplexEngine::GetEP()
    {
        return (_ep);
    }

    void MyComplexEngine::Dispose(IMyComplexHandle ^u)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        _ep->Dispose(_u->Handle);
    }

    IMyComplexHandle ^ MyComplexEngine::Add(IMyComplexHandle ^u, IMyComplexHandle ^v)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        MyComplexHandle^ _v = safe_cast<MyComplexHandle^>(v);
        MyComplexHandle^ _w = gcnew MyComplexHandle(this, _ep->Add(_u->Handle, _v->Handle));
        return (_w);
    }

    IMyComplexHandle ^ MyComplexEngine::Subtruct(IMyComplexHandle ^u, IMyComplexHandle ^v)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        MyComplexHandle^ _v = safe_cast<MyComplexHandle^>(v);
        MyComplexHandle^ _w = gcnew MyComplexHandle(this, _ep->Subtruct(_u->Handle, _v->Handle));
        return (_w);
    }

    IMyComplexHandle ^ MyComplexEngine::Multiply(IMyComplexHandle ^u, IMyComplexHandle ^v)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        MyComplexHandle^ _v = safe_cast<MyComplexHandle^>(v);
        MyComplexHandle^ _w = gcnew MyComplexHandle(this, _ep->Multiply(_u->Handle, _v->Handle));
        return (_w);
    }

    IMyComplexHandle ^ MyComplexEngine::Divide(IMyComplexHandle ^u, IMyComplexHandle ^v)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        MyComplexHandle^ _v = safe_cast<MyComplexHandle^>(v);
        MyComplexHandle^ _w = gcnew MyComplexHandle(this, _ep->Divide(_u->Handle, _v->Handle));
        return (_w);
    }

    System::String ^ MyComplexEngine::ToString(IMyComplexHandle ^u)
    {
        MyComplexHandle^ _u = safe_cast<MyComplexHandle^>(u);
        wchar_t temp[256];
        _ep->ToString(_u->Handle, temp, 256);
        return (marshal_as<System::String^>(temp));
    }
}