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
 
 namespace Palmtree.Math.Core
{
    /// <summary>
    /// ネイティブ言語(C++/CLI)で記述されたエンジンが実装していなければならないインターフェース
    /// </summary>
    public interface IMyComplexEngine
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="r">虚数の実部</param>
        /// <param name="i">虚数の虚部</param>
        /// <returns>複素数のインスタンス</returns>
        IMyComplexHandle CreateInstance(double r, double i);

        // マネージリソースの解放はガベージコレクタ任せなので実装しない
        //void Dispose(IMyComplexHandle u);

        /// <summary>
        /// u + v を計算する
        /// </summary>
        /// <param name="u"></param>
        /// <param name="v"></param>
        /// <returns>計算結果</returns>
        IMyComplexHandle Add(IMyComplexHandle u, IMyComplexHandle v);

        /// <summary>
        /// u - v を計算する
        /// </summary>
        /// <param name="u"></param>
        /// <param name="v"></param>
        /// <returns>計算結果</returns>
        IMyComplexHandle Subtruct(IMyComplexHandle u, IMyComplexHandle v);

        /// <summary>
        /// u * v を計算する
        /// </summary>
        /// <param name="u"></param>
        /// <param name="v"></param>
        /// <returns>計算結果</returns>
        IMyComplexHandle Multiply(IMyComplexHandle u, IMyComplexHandle v);

        /// <summary>
        /// u / v を計算する
        /// </summary>
        /// <param name="u"></param>
        /// <param name="v"></param>
        /// <returns>計算結果</returns>
        IMyComplexHandle Divide(IMyComplexHandle u, IMyComplexHandle v);

        /// <summary>
        /// u を文字列化する
        /// </summary>
        /// <param name="u"></param>
        /// <returns></returns>
        string ToString(IMyComplexHandle u);
    }
}
