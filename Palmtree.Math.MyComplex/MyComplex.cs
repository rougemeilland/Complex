using System;
using System.IO;
using System.Linq;
using System.Reflection;

namespace Palmtree.Math
{
    public class MyComplex
        : IDisposable
    {
        private static Core.IMyComplexEngine _engine;
        private bool _is_disposed;
        private Core.IMyComplexHandle _handle;

        static MyComplex()
        {
            try
            {
                var current_assembly = Assembly.GetAssembly(typeof(MyComplex));
                var base_directory = Path.GetDirectoryName(current_assembly.Location);
                string engine_path = GetEnginePath(base_directory);
                var engine_assemply = Assembly.LoadFrom(engine_path);
                var interface_name = typeof(Core.IMyComplexEngine).FullName;

                _engine = engine_assemply.GetTypes()
                          .Where(t => t.IsClass && t.IsPublic && !t.IsAbstract && t.GetInterface(interface_name) != null)
                          .Select(t => (Core.IMyComplexEngine)engine_assemply.CreateInstance(t.FullName))
                          .FirstOrDefault();
                if (_engine == null)
                    throw new ApplicationException("ロードしたアセンブリの中に IMyComplexEngine を実装するクラスが見つかりませんでした。");
            }
            catch (ApplicationException)
            {

                throw;
            }
        }

        public MyComplex()
            : this(_engine.CreateInstance(0, 0))
        {
        }

        public MyComplex(double r, double i)
            :this(_engine.CreateInstance(r, i))
        {
        }

        private MyComplex(Core.IMyComplexHandle handle)
        {
            _is_disposed = false;
            _handle = handle;
        }

        public MyComplex Add(MyComplex v)
        {
            return (new MyComplex(_engine.Add(_handle, v._handle)));
        }

        public MyComplex Subtruct(MyComplex v)
        {
            return (new MyComplex(_engine.Subtruct(_handle, v._handle)));
        }

        public MyComplex Multiply(MyComplex v)
        {
            return (new MyComplex(_engine.Multiply(_handle, v._handle)));
        }

        public MyComplex Divide(MyComplex v)
        {
            return (new MyComplex(_engine.Divide(_handle, v._handle)));
        }

        public double R
        {
            get
            {
                return (_handle.R);
            }
        }

        public double I
        {
            get
            {
                return (_handle.I);
            }
        }

        public override string ToString()
        {
            return (_engine.ToString(_handle));
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_is_disposed)
                return;

            if (disposing)
            {
                // マネージリソースの解放
                if (_handle != null)
                    _handle = null;
            }

            // アンマネージリソースの解放

            _is_disposed = true;
        }

        private static string GetEnginePath(string base_directory)
        {
            string sub_dir;
            switch (IntPtr.Size)
            {
                case 4:
                    sub_dir = "x86";
                    break;
                case 8:
                    sub_dir = "x64";
                    break;
                default:
                    throw new ApplicationException(string.Format("IntPtr.Size が未知の値({0})です。", IntPtr.Size));
            }
            return (Path.Combine(base_directory, sub_dir, "Palmtree.Math.Core.MyComplex.dll"));
        }
    }
}
