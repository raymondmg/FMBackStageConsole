using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    class test1
    {

        [DllImport("DllTest.dll", EntryPoint = "Add", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Winapi)]
        public static extern IntPtr Add();


        [DllImport("DllTest.dll", EntryPoint = "Get_Msg_Test", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Get_Msg_Test(IntPtr hwnd);
    }
}
