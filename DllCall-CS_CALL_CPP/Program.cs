using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace DllCall
{
    class Program
    {
        //傳入和傳出的型態格式必須同ForExternCall.cpp內的設置！！

        //我將dll檔放到D:，然後設置進入點
        [DllImport("Dll.dll", EntryPoint = "Add", CallingConvention = CallingConvention.Cdecl)]
        private static extern int add(int a, int b);

        //也可以不設置進入點，但函數名稱必須相同
        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Sub(int a, int b);

        [DllImport("Dll.dll", EntryPoint = "Multi", CallingConvention = CallingConvention.Cdecl)]
        private static extern int mul(int a, int b);

        [DllImport("Dll.dll", EntryPoint = "Div", CallingConvention = CallingConvention.Cdecl)]
        private static extern float div(int a, int b);

        static void Main(string[] args)
        {
            Console.WriteLine(add(10, 20));
            Console.WriteLine(Sub(10, 20));
            Console.WriteLine(mul(10, 20));
            Console.WriteLine(div(10, 20));

            Console.ReadKey();

        }
        //如果出現這種錯誤訊息：System.BadImageFormatException: 試圖載入格式錯誤的程式。 (發生例外狀況於 HRESULT: 0x8007000B)
        //原因就是Visual Studio編譯環境的問題，將Any CPU或x64改成x86即可解決。
    }

}
