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
    public partial class Form1 : Form
    {
        public static int N;
        public static int m;
        public static int Quantity;

        public static int X1 = 1;
        double P1;
        public static double Tc, lyamda, t1;
        public static int check, r;
        public static String precision;

        public static List<TextBox> list_of_t;
        public static List<MaskedTextBox> list_of_mt;

        List<int> vec_t;
	    List<double> vec_X;
	    public static List<double> vec_P;
        public static List<double> vec_L;
        public static List<double> vec_Q;
        public static List<double> vec_T;
        public static List<double> vec_W;
        public static Label[] mylb1;
        public static MaskedTextBox[] mytxt1;

        public static double sum_P = 0;
        public static double sum_L = 0;
        public static double sum_Q = 0;
        public static double sum_T = 0;
        public static double sum_W = 0;

        private bool button1WasClicked = false;

        public Form1()
        {
            InitializeComponent();
            list_of_t = new List<TextBox>(m);
            list_of_mt = new List<MaskedTextBox>(m);
            vec_t = new List<int>(m);
	        vec_X = new List<double>(m);
	        vec_P = new List<double>(m);
	        vec_L = new List<double>(m);
            vec_Q = new List<double>(m);
	        vec_T = new List<double>(m);
            vec_W = new List<double>(m);
            mylb1 = new Label[m];
            mytxt1 = new MaskedTextBox[m];
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public void analyze()
        {
            int N;
            if (!Int32.TryParse(maskedTextBox2.Text, out N))
                return;
            int m;
            if (!Int32.TryParse(maskedTextBox1.Text, out m))
                return;
            int Quantity;
            if (!int.TryParse(maskedTextBox3.Text, out Quantity))
                return;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            analyze();
            if (!Int32.TryParse(maskedTextBox2.Text, out N))
                return;
            if (!Int32.TryParse(maskedTextBox1.Text, out m))
                return;
            if (!int.TryParse(maskedTextBox3.Text, out Quantity))
                return;
            if ((!Int32.TryParse(maskedTextBox1.Text, out m)) || (!Int32.TryParse(maskedTextBox2.Text, out N)) || (!Int32.TryParse(maskedTextBox3.Text, out Quantity)) || (m == 0) || (N == 0) || (Quantity == 0))
            {
                button1WasClicked = false;
                return;
            }
            else
            {
                button1WasClicked = true;
                m = Convert.ToInt32(maskedTextBox1.Text);
                mylb1 = new Label[m];
                mytxt1 = new MaskedTextBox[m];

                for (int i = 0; i < m; i++)
                {
                    /*myBtn[i] = new Button();
                    myBtn[i].Location = new Point(0, 25 * (i + 1));
                    myBtn[i].Text = "button " + Convert.ToString(i);
                    myBtn[i].Click += new EventHandler(Form1_Load);
                    panel1.Controls.Add(myBtn[i]);*/

                    mylb1[i] = new Label();
                    mylb1[i].Location = new Point(0, 25 * (i + 1));
                    mylb1[i].Width = 310;
                    mylb1[i].Font = new Font("TimesNewRoman", 9, FontStyle.Regular);
                    mylb1[i].Text = "t" + Convert.ToString(i + 1) + " [c] - среднее время обработки заявки в " + Convert.ToString(i + 1) + " СМО";
                    panel1.Controls.Add(mylb1[i]);

                    mytxt1[i] = new MaskedTextBox();
                    mytxt1[i].Location = new Point(320, 25 * (i + 1));
                    mytxt1[i].Text = "1";
                    panel1.Controls.Add(mytxt1[i]);
                    list_of_mt.Add(mytxt1[i]);
                }
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
           
        }

        private void maskedTextBox1_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {

        }

        private void maskedTextBox2_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            analyze();
            if (!button1WasClicked)
            {
                return;
            }

            if (!Int32.TryParse(maskedTextBox1.Text, out m))
                return;
            if (!Int32.TryParse(maskedTextBox2.Text, out N))
                return;
            if (!int.TryParse(maskedTextBox3.Text, out Quantity))
                return;
            precision = "F" + Quantity.ToString();
            for (int i = 0; i < m; i++)
            {
                if (!Int32.TryParse(list_of_mt[i].Text, out check))
                    return;
                check = Convert.ToInt32(list_of_mt[i].Text);
            }

            for (int i = 0; i < m; i++)
            {  
                vec_t.Add(Convert.ToInt32(list_of_mt[i].Text));
            }
	
	        for(int j = 0; j < m; j++)
	        {
                vec_X.Add(vec_t[j] / vec_t[0]);
	        }

            double[,] arr_X = new double[N+1, m];
	        for(int i=0; i < N+1; i++)
	        {
		        for(int j=0; j < m; j++)
		        {
			        if(i == 0 || j == 0)
			        {
				        arr_X[i,j] = 1;
				        continue;
			        }
			        arr_X[i,j] = arr_X[i,j-1] + vec_X[j]*arr_X[i-1,j];
			        P1 = arr_X[i-1,j] / arr_X[i,j];
		        }
	        }

	        for(int j=0; j < m; j++)
	        {
                vec_P.Add(vec_X[j] * P1);
                sum_P += vec_P[j];
	        }

	        double sum = 0;
	        int count1 = 0;

	        for(int k = 0; k < m; k++)
	        {
	            for(int i=0; i < N+1; i++)
	            {
		            for(int j=0; j < m; j++)
		            {
				        if(count1 == N)
			            {
					    count1 = 0;
                        vec_L.Add(sum/arr_X[N,m-1]);
                        sum_L += vec_L[k];
				        sum = 0;
			            }

			            if(i < N && j == m-1)
			            {
				            sum += Math.Pow(vec_X[k],i+1)*arr_X[N-i-1,m-1];
				            count1++;
			            }
		            }
	            }
	        }

	        for(int j=0; j < m; j++)
	        {
                vec_Q.Add(vec_L[j] - vec_P[j]);
                sum_Q += vec_Q[j];
	        }

	        Tc = N * vec_t[0] / vec_P[0];

	        lyamda = N/Tc;

	        for(int i=0; i < m; i++)
	        {
                vec_T.Add(Tc * vec_L[i] / N);
                sum_T += vec_T[i];
	        }

    	    for(int i=0; i < m; i++)
	        {
                vec_W.Add(vec_T[i] - vec_t[i]);
                sum_W += vec_W[i];
	        }

            Form2 f = new Form2();
            f.Owner = this;
            f.Show();
        }

        private void maskedTextBox3_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form3 f = new Form3();
            f.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
            this.Close(); 
        }

        private void button5_Click(object sender, EventArgs e)
        {
            maskedTextBox1.Text = "5";
            maskedTextBox2.Text = "10"; 
            maskedTextBox3.Text = "3";

            int count2 = 0;
            while (count2 != m)
            {
                list_of_mt.RemoveAt(0);
                count2++;
            }

            for (int i = 0; i < m; i++)
            {
                panel1.Controls.Remove(mylb1[i]);
                panel1.Controls.Remove(mytxt1[i]);
                vec_t.Clear();
                vec_X.Clear();
                vec_P.Clear();
                vec_L.Clear();
                vec_Q.Clear();
                vec_T.Clear();
                vec_W.Clear();
                sum_P = 0;
                sum_L = 0;
                sum_Q = 0;
                sum_T = 0;
                sum_W = 0;
            }
        }
    }
}
