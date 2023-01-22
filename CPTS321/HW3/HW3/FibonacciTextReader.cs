// <copyright file="FibonacciTextReader.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>

namespace HW3
{
    using System.Numerics;
    using System.Text;

    /// <summary>
    /// A class deriving from <see cref="System.IO.TextReader"/> that
    /// contains methods <see cref="FibonacciTextReader.ReadLine()"/> and
    /// <see cref="FibonacciTextReader.ReadLine()"/>.
    /// </summary>
    public class FibonacciTextReader : System.IO.TextReader
    {
        private uint maxSequence;
        private uint currentSequence;
        private BigInteger previous1;
        private BigInteger previous2;

        /// <summary>
        /// Initializes a new instance of the <see cref="FibonacciTextReader"/> class.
        /// </summary>
        /// <param name="maxSequence">
        /// Determines maximum length of Fibonacci sequence.
        /// </param>
        public FibonacciTextReader(uint maxSequence)
        {
            this.maxSequence = maxSequence;
            this.currentSequence = 0;
            this.previous1 = 0;
            this.previous2 = 0;
        }

        /// <summary>
        /// Calculates the next number in the Fibonacci sequence based
        /// on the previous two results of the method call.
        /// </summary>
        /// <returns>
        /// String representation of the next Fibonacci number.
        /// </returns>
        public override string ReadLine()
        {
            BigInteger nextFibonacci = 0;
            if (this.currentSequence >= this.maxSequence)
            {
                return string.Empty;
            }

            if (this.previous1 == 0 && this.previous2 == 0)
            {
                nextFibonacci = 1;
            }
            else
            {
                nextFibonacci = this.previous1 + this.previous2;
            }

            this.previous2 = this.previous1;
            this.previous1 = nextFibonacci;
            ++this.currentSequence;

            return nextFibonacci.ToString();
        }

        /// <summary>
        /// Runs the <see cref="FibonacciTextReader.ReadLine()"/> method
        /// a number of times equal to the <see cref="maxSequence"/> to
        /// build a string containing the full Fibonacci sequence up to
        /// that number of iterations.
        /// </summary>
        /// <returns>
        /// Formatted string of the Fibonacci sequnece to <see cref="maxSequence"/>
        /// iterations.
        /// </returns>
        public override string ReadToEnd()
        {
            string sequence = string.Empty;
            for (int i = 1; i <= this.maxSequence; ++i)
            {
                sequence += i.ToString() + ". " + this.ReadLine() + "\r\n";
            }

            return sequence;
        }
    }
}
