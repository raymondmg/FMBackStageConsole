using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class WindowName : Form
    {
        public WindowName()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                test1.Get_Msg_Test(this.Handle);
            }
            catch (System.Exception ex)
            {
                //程序收到C++发过来的消息后，此处有异常
            }   
        }


        //用户自定义消息
        public const int WM_USER = 0x0400;
        public const int WM_TEST = WM_USER + 1;

        /// <summary>
        /// Message 接收GetLParam方法返回值
        /// LParamData返回内容与LParamData结构体相同
        /// </summary>
        public struct LParamDataSruct
        {
            public String lParamData;
        }

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                //旺旺最后一条聊天记录消息
                case WM_TEST:
                    LParamDataSruct lparam = (LParamDataSruct)m.GetLParam(typeof(LParamDataSruct));
                    String msg = lparam.lParamData;//此处能得到C++ DLL发送的消息内容
                    MessageBox.Show(msg);
                    break;
                default:
                    break;
            }
            base.WndProc(ref m);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //调用VCDLL的代码...

            IntPtr intPtr = test1.Add();

            string str = Marshal.PtrToStringAnsi(intPtr);
            MessageBox.Show(str);
        }
    }
}
