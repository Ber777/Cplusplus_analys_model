using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Dopka_ASOIU
{
    public partial class Form2 : Form
    {
        public static MaskedTextBox[] mytxt1;
        List<TextBox> txt_list;

        public Form2()
        {
            InitializeComponent();
            txt_list = new List<TextBox>(Form1.m*5);
            String precision = Form1.precision;
            textBox2.Text = Form1.Tc.ToString(precision);
            textBox1.Text = Form1.lyamda.ToString(precision);
            textBox3.Text = Form1.sum_P.ToString(precision);
            textBox4.Text = Form1.sum_L.ToString(precision);
            textBox7.Text = Form1.sum_Q.ToString(precision);
            textBox5.Text = Form1.sum_T.ToString(precision);
            textBox6.Text = Form1.sum_W.ToString(precision);

            for (int i = 0; i < Form1.m; i++)
            {
                Label[] mylb1 = new Label[Form1.m];
                TextBox[] mytxt1 = new TextBox[Form1.m];
                mylb1[i] = new Label();
                mylb1[i].Location = new Point(0, 25 * (i + 1 + i));
                mylb1[i].Width = 225;
                mylb1[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                mylb1[i].Text = "P" + Convert.ToString(i + 1) + " - коэффициент загрузки " + Convert.ToString(i + 1) + " СМО";
                panel1.Controls.Add(mylb1[i]);

                mytxt1[i] = new TextBox();
                mytxt1[i].Location = new Point(3, 25 * (i + 2 + i));
                panel1.Controls.Add(mytxt1[i]);
                mytxt1[i].Text = Form1.vec_P[i].ToString(precision);
                txt_list.Add(mytxt1[i]);
            }

            for (int i = 0; i < Form1.m; i++)
            {
                Label[] mylb2 = new Label[Form1.m];
                TextBox[] mytxt2 = new TextBox[Form1.m];
                mylb2[i] = new Label();
                mylb2[i].Location = new Point(0, 25 * (i + 1 + i));
                mylb2[i].Width = 205;
                mylb2[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                mylb2[i].Text = "L" + Convert.ToString(i + 1) + "- кол-во заявок в " + Convert.ToString(i + 1) + " СМО";
                panel2.Controls.Add(mylb2[i]);

                mytxt2[i] = new TextBox();
                mytxt2[i].Location = new Point(3, 25 * (i + 2 + i));
                panel2.Controls.Add(mytxt2[i]);
                mytxt2[i].Text = Form1.vec_L[i].ToString(precision);
                txt_list.Add(mytxt2[i]);
            }

            for (int i = 0; i < Form1.m; i++)
            {
                Label[] mylb1 = new Label[Form1.m];
                TextBox[] mytxt1 = new TextBox[Form1.m];
                mylb1[i] = new Label();
                mylb1[i].Location = new Point(0, 25 * (i + 1 + i));
                mylb1[i].Width = 260;
                mylb1[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                mylb1[i].Text = "Q" + Convert.ToString(i + 1) + " - кол-во заявок в очереди " + Convert.ToString(i + 1) + " СМО";
                panel3.Controls.Add(mylb1[i]);

                mytxt1[i] = new TextBox();
                mytxt1[i].Location = new Point(3, 25 * (i + 2 + i));
                panel3.Controls.Add(mytxt1[i]);
                mytxt1[i].Text = Form1.vec_Q[i].ToString(precision);
                txt_list.Add(mytxt1[i]);
            }

            for (int i = 0; i < Form1.m; i++)
            {
                Label[] mylb1 = new Label[Form1.m];
                TextBox[] mytxt1 = new TextBox[Form1.m];
                mylb1[i] = new Label();
                mylb1[i].Location = new Point(0, 25 * (i + 1 + i));
                mylb1[i].Width = 320;
                mylb1[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                mylb1[i].Text = "T" + Convert.ToString(i + 1) + " [c] - ср. время пребывания заявок в " + Convert.ToString(i + 1) + " СМО";
                panel4.Controls.Add(mylb1[i]);

                mytxt1[i] = new TextBox();
                mytxt1[i].Location = new Point(3, 25 * (i + 2 + i));
                panel4.Controls.Add(mytxt1[i]);
                mytxt1[i].Text = Form1.vec_T[i].ToString(precision);
                txt_list.Add(mytxt1[i]);
            }

            for (int i = 0; i < Form1.m; i++)
            {
                Label[] mylb1 = new Label[Form1.m];
                TextBox[] mytxt1 = new TextBox[Form1.m];
                mylb1[i] = new Label();
                mylb1[i].Location = new Point(0, 25 * (i + 1 + i));
                mylb1[i].Width = 300;
                mylb1[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                mylb1[i].Text = "W" + Convert.ToString(i + 1) + " [c] - ср. время ожидания в очереди в " + Convert.ToString(i + 1) + " СМО";
                panel5.Controls.Add(mylb1[i]);

                mytxt1[i] = new TextBox();
                mytxt1[i].Location = new Point(3, 25 * (i + 2 + i));
                panel5.Controls.Add(mytxt1[i]);
                mytxt1[i].Text = Form1.vec_W[i].ToString(precision);
                txt_list.Add(mytxt1[i]);
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void panel3_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel5_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel4_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
            textBox5.Text = "";
            textBox6.Text = "";
            textBox7.Text = "";

            for (int i = 0; i < Form1.m*5; i++)
            {
                txt_list[i].Text = "";
            }

        }
    }
}
