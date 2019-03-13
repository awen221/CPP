using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;



namespace DllCall
{
    using CppMathFunc;
    class Program
    {

        #region Call_Dll_dllexport
        const string DllName = "Dll_dllexport.dll";
        //傳入和傳出的型態格式必須同ForExternCall.cpp內的設置！！

        //設置進入點
        [DllImport(DllName, EntryPoint = "Add", CallingConvention = CallingConvention.Cdecl)]
        private static extern int add(int a, int b);

        //也可以不設置進入點，但函數名稱必須相同
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Sub(int a, int b);

        [DllImport(DllName, EntryPoint = "Multi", CallingConvention = CallingConvention.Cdecl)]
        private static extern int mul(int a, int b);

        [DllImport(DllName, EntryPoint = "Div", CallingConvention = CallingConvention.Cdecl)]
        private static extern float div(int a, int b);
        static void Call_Dll_dllexport()
        {
            Console.WriteLine(add(10, 20));
            Console.WriteLine(Sub(10, 20));
            Console.WriteLine(mul(10, 20));
            Console.WriteLine(div(10, 20));

            Console.ReadKey();
            //如果出現這種錯誤訊息：System.BadImageFormatException: 試圖載入格式錯誤的程式。 (發生例外狀況於 HRESULT: 0x8007000B)
            //原因就是Visual Studio編譯環境的問題，將Any CPU或x64改成x86即可解決。
        }
        #endregion

        #region Call_Dll_namespace_ref_class

        class aaa : Arithmetics
        {

        }
        
        static void Call_Dll_namespace_ref_class()
        {
            aaa a = new aaa();

            
            TEST t = new TEST();
            t.T++;

            Arithmetics ar = new Arithmetics();
            ar.i++;
            Console.WriteLine(ar.Add(10, 20));
            Console.WriteLine(ar.Subtract(10, 20));
            Console.WriteLine(ar.Multiply(10, 20));
            Console.WriteLine(ar.Divide(10, 20));

            Console.ReadKey();
        }
        #endregion

        static void Main(string[] args)
        {
            //Call_Dll_dllexport();

            Call_Dll_namespace_ref_class();
        }

    }

}
