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

#include "MyComplexInternal.h"

using namespace System;

namespace Palmtree::Math::Core
{
	public ref class MyComplexEngine
        : IMyComplexEngine
	{
    private :
        MYCOMPLEX_ENTRY_POINT* _ep;

    public:
        MyComplexEngine();

        const MYCOMPLEX_ENTRY_POINT* GetEP();

        // IMyComplexEngine を介して継承されました
        virtual Palmtree::Math::Core::IMyComplexHandle ^ CreateInstance(double r, double i);
        virtual void Dispose(Palmtree::Math::Core::IMyComplexHandle ^u);
        virtual Palmtree::Math::Core::IMyComplexHandle ^ Add(Palmtree::Math::Core::IMyComplexHandle ^u, Palmtree::Math::Core::IMyComplexHandle ^v);
        virtual Palmtree::Math::Core::IMyComplexHandle ^ Subtruct(Palmtree::Math::Core::IMyComplexHandle ^u, Palmtree::Math::Core::IMyComplexHandle ^v);
        virtual Palmtree::Math::Core::IMyComplexHandle ^ Multiply(Palmtree::Math::Core::IMyComplexHandle ^u, Palmtree::Math::Core::IMyComplexHandle ^v);
        virtual Palmtree::Math::Core::IMyComplexHandle ^ Divide(Palmtree::Math::Core::IMyComplexHandle ^u, Palmtree::Math::Core::IMyComplexHandle ^v);
        virtual System::String ^ ToString(Palmtree::Math::Core::IMyComplexHandle ^u);
    };
}
