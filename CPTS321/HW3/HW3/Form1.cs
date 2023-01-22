namespace HW3
{
    /// <summary>
    /// A form class that contains menu items for loading files into the
    /// main text box, saving text from the main text box into a file, and
    /// loading the Fibonacci sequence to 50 and 100 numbers.
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Form1"/> class.
        /// </summary>
        public Form1()
        {
            this.InitializeComponent();
        }

        private void OpenFileDialog1_FileOk(object sender, EventArgs e)
        {

        }

        private void LoadText(TextReader sr)
        {
            this.mainTextBox.Text = sr.ReadToEnd();
        }

        private void LoadMenuItem_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.ShowDialog();
            FileStream input = (FileStream)this.openFileDialog1.OpenFile();
            StreamReader sr = new StreamReader(input);

            this.LoadText(sr);

            sr.Close();
            input.Close();
        }

        private void SaveText(object sender, EventArgs e)
        {
            this.saveFileDialog1.ShowDialog();
            FileStream output = (FileStream)this.saveFileDialog1.OpenFile();
            StreamWriter sw = new StreamWriter(output);
            sw.WriteLine(this.mainTextBox.Text);

            sw.Close();
            output.Close();
        }

        private void Fibonacci50MenuItem_Click(object sender, EventArgs e)
        {
            FibonacciTextReader fibonacciSequence = new FibonacciTextReader(50);
            this.mainTextBox.Text = fibonacciSequence.ReadToEnd();
        }

        private void Fibonacci100MenuItem_Click(object sender, EventArgs e)
        {
            FibonacciTextReader fibonacciSequence = new FibonacciTextReader(100);
            this.mainTextBox.Text = fibonacciSequence.ReadToEnd();
        }
    }
}