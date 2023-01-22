// Copyright (c) Killian Griffin. All Rights Reserved.

namespace HW2
{
    /// <summary>
    /// Represents the output window, with a method that invokes
    /// the <see cref="DistinctIntegersCalculator.HashSet(List{int})"/>,
    /// <see cref="DistinctIntegersCalculator.InPlace(List{int})"/>, and <see cref="DistinctIntegersCalculator.Sort(List{int})"/>
    /// methods and displays their outputs.
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Form1"/> class and
        /// runs the <see cref="RunDistinctIntegers()"/> method.
        /// </summary>
        public Form1()
        {
            this.InitializeComponent();
            this.RunDistinctIntegers();
        }

        /// <summary>
        /// Runs the <see cref="DistinctIntegersCalculator.HashSet(List{int})"/>,
        /// <see cref="DistinctIntegersCalculator.InPlace(List{int})"/>, and <see cref="DistinctIntegersCalculator.Sort(List{int})"/>
        /// methods using randomly generated integer lists (<see cref="Random.Next(long, long)"/>)
        /// as inputs. Prints the outputs of these functions to <see cref="Form1.textBox1"/>.
        /// </summary>
        private void RunDistinctIntegers()
        {
            int hashOutput, inPlaceOutput, sortOutput;
            List<int> randomIntegers = new List<int>();
            Random random = new Random();
            for (int i = 0; i < 10000; i++)
            {
                randomIntegers.Add(random.Next(0, 20000));
            }

            hashOutput = DistinctIntegersCalculator.HashSet(randomIntegers);
            inPlaceOutput = DistinctIntegersCalculator.InPlace(randomIntegers);
            sortOutput = DistinctIntegersCalculator.Sort(randomIntegers);

            this.TextBox1.Text = "1. HashSet method: " + hashOutput + " unique numbers\r\n" +
            "Time complexity: O(n). Requires one full iteration through the input list, or a comparison per each element.\r\n" +
            "2. O(1) storage method: " + inPlaceOutput + " unique numbers\r\n" +
            "3. Sorted method: " + sortOutput + " unique numbers\r\n";
        }
    }
}
