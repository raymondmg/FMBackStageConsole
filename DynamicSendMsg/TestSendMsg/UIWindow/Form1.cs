using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UIWindow
{
    public partial class WindowName : Form
    {
        public WindowName()
        {
            InitializeComponent();
        }

        private void WindowName_Load(object sender, EventArgs e)
        {
            testConnect.Add();
            MessageBox.Show("发送请求");
        }

        
        //消息处理函数
        protected override void WndProc(ref Message m)
        {
            const int WM_SYSCOMMAND = 0x0112;
            if (m.Msg == WM_SYSCOMMAND)
            {
                MessageBox.Show("111");
            }

       

            base.WndProc(ref m);
        }
    }
}
